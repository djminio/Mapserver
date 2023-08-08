/**
 * @file	GuardInfo.cpp
 *			implementation of the CGuardInfo class.
 */
//#include "..\stdafx.h"
#include "StdAfx.h"	//060109_kch ������ �ð��� 20���� �ɷ���, ����ȭ �۾�

#include "GuardInfo.h"

#include "UserManager.h"
#include "LogManager.h"

extern WORD g_wMapServerPort;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGuardInfo::CGuardInfo()
{
	m_pGData = NULL;
	m_iWarfieldNo = -1;
	m_iTeamNo = -1;

	INT nI;
	for (nI = 0; nI < GS_MAX_GUARD_SPECIES; ++nI)
		m_iTypeCount[nI] = 0;
}

CGuardInfo::~CGuardInfo()
{
	Clear();
}

BOOL CGuardInfo::CheckTypeAllBroke(INT nType)
{
	//<060327_kch 5994map Crash (TEAM1 �������϶��� ���彺�� ����, �����ϴµ�, ó��,Debugging����׽�Ʈ������ ��������, �����׽�Ʈ���� crash)
	if (false == IsValidGData())	//���彺�� �����Ͱ� ���ٸ� skip
	{
		return FALSE;
	}
	//060327_kch

	BOOL bAllBroken = TRUE;
	INT nI;
	for (nI = 0; nI < m_iGDataCount; ++nI)
	{
		if (nType == m_pGData[nI].NPCType)
		{
			if (nType == 2)
			{
				if ((m_pGData[nI].DontNo % 2) == 0)
				{
					if (TRUE == ((m_pGData[nI].Status == ALIVE_) && (m_pGData[nI + 1].Status == ALIVE_)))
					{
						bAllBroken = FALSE;
						break;
					}
				}
			}
			else
			{
				if (TRUE == (m_pGData[nI].Status == ALIVE_))
				{
					bAllBroken = FALSE;
					break;
				}
			}
		}
	}
	
	return bAllBroken;
}

BOOL CGuardInfo::IsAllBroken()
{
	BOOL bAllBroken = TRUE;
	INT nI;
	//< LTH-040322-KO �̷�... -_-; ������ �Ǵ��ϸ� �Ǵµ� ���� ����ŭ ���� �־���... ���� ����
	for (nI = 0; nI < GS_MAX_GUARD_SPECIES; ++nI)
	{
		if (FALSE == CheckTypeAllBroke(nI))
		{
			bAllBroken = FALSE;
			break;
		}
	}
	//> LTH-040322-KO

	return bAllBroken;
}

void CGuardInfo::SendCanNotBrokeBBS(int nType)
{
	t_packet packet;

	packet.h.header.type = CMD_GUARD_CAN_NOT_BROKE;
	packet.u.NationWar.GuardCanNotBroke.nWarfieldNo = m_iWarfieldNo;
	packet.u.NationWar.GuardCanNotBroke.nType = nType;

	packet.h.header.size = sizeof(GUARD_CAN_NOT_BROKE);

	g_pUserManager->SendPacket(&packet);
}

void CGuardInfo::SendBrokeBBS(int Team,int Type,int No,LPCHARLIST pTarget)
{
	t_packet packet;

	packet.h.header.type=CMD_GUARD_BROKE;
	packet.u.NationWar.GuardBroke.nWarfieldNo = m_iWarfieldNo;	// LTH-040303-KO 1.4p.
	packet.u.NationWar.GuardBroke.BrokeTeamNo=Team;
	packet.u.NationWar.GuardBroke.Type=Type;
	packet.u.NationWar.GuardBroke.GuardNo=No;
	packet.u.NationWar.GuardBroke.X=pTarget->MoveSx;
	packet.u.NationWar.GuardBroke.Y=pTarget->MoveSy;
	int nI;
	for (nI = 0; nI < GS_MAX_GUARD_SPECIES; ++nI)
		packet.u.NationWar.GuardBroke.aRemainGuard[Team][nI] = GetAliveGuardCount(nI);
	packet.h.header.size=sizeof(GUARD_BROKE);

	::SendPacket2Maps(&packet);
	g_pUserManager->SendPacket(&packet); // CSD-CN-031213
}

extern void SendDontChange(int DontNo,int Status);

BOOL CGuardInfo::CheckAndUpdateStatus(LPCHARLIST lpChar)
{
	//<060327_kch 5994map Crash (TEAM1 �������϶��� ���彺�� ����, �����ϴµ�, ó��,Debugging����׽�Ʈ������ ��������, �����׽�Ʈ���� crash)
	if (false == IsValidGData())	//���彺�� �����Ͱ� ���ٸ� skip
	{
		return FALSE;
	}
	//060327_kch

	INT nI;
	for (nI = 0; nI < m_iGDataCount; ++nI)
	{
		if (m_pGData[nI].NPC_ID == lpChar->GetServerID())
		{
			m_pGData[nI].Status = 0;
			switch(lpChar->SprNo)
			{
			case 64 :		// ����
				SendBrokeBBS(GetTeamNo(), 0, nI, lpChar);
				break;
			case 63 :		// ���� ��ȣ��
				SendBrokeBBS(GetTeamNo(), 1, nI, lpChar);
				break;
			case 177 :		// ���� 
				SendBrokeBBS(GetTeamNo(), 2, nI, lpChar);
				break;
			case 178 :		// �ܼ� ��ȣ��
				SendBrokeBBS(GetTeamNo(), 3, nI, lpChar);
				break;
			}
			
			//< LTH-040329-KO �α� ��ȭ
			g_pLogManager->SaveLogNeoNationWar(NNT_WAR_INFO, \
					"Update Guard! NPC_ID:%d, NPC_SprNo:%d, NPC_Status:%d, NPC_Type:%d, Position(%d,%d)", \
					m_pGData[nI].NPC_ID, lpChar->SprNo, m_pGData[nI].Status, m_pGData[nI].NPCType, \
					m_pGData[nI].GenPosX, m_pGData[nI].GenPosY);
			//> LTH-040329-KO
			
			if (m_pGData[nI].DontNo>=0)
			{
				::SendDontChange(m_pGData[nI].DontNo, m_pGData[nI].Status);
			}
			return TRUE;
		}
	}
	return FALSE;
}

INT CGuardInfo::GetAliveGuardCount(INT nType)
{
	INT nCount = 0;
	INT nI;

	//<060327_kch 5994map Crash (TEAM1 �������϶��� ���彺�� ����, �����ϴµ�, ó��,Debugging����׽�Ʈ������ ��������, �����׽�Ʈ���� crash)
	if (false == IsValidGData())	//���彺�� �����Ͱ� ���ٸ� skip
	{
		return 0;
	}
	//060327_kch

	for (nI = 0; nI < m_iGDataCount; ++nI)
	{
		if (nType == m_pGData[nI].NPCType)
		{
			if (nType == 2)
			{
				if ((m_pGData[nI].DontNo % 2) == 0)
					if ((m_pGData[nI].Status == ALIVE_) && (m_pGData[nI + 1].Status == ALIVE_))
						++nCount;
			}
			else
			{
				if (m_pGData[nI].Status == ALIVE_)
					++nCount;
			}
		}
	}
	
	return nCount;
}

INT CGuardInfo::GetGuardCount(INT nType)
{
	INT nCount = 0;
	INT nI;

	//<060327_kch 5994map Crash (TEAM1 �������϶��� ���彺�� ����, �����ϴµ�, ó��,Debugging����׽�Ʈ������ ��������, �����׽�Ʈ���� crash)
	if (false == IsValidGData())	//���彺�� �����Ͱ� ���ٸ� skip
	{
		return 0;
	}
	//060327_kch

	for (nI = 0; nI < m_iGDataCount; ++nI)
	{
		if (nType == m_pGData[nI].NPCType)
		{
			if (nType == 2)
				if ((m_pGData[nI].DontNo % 2) == 0)
					++nCount;
			else
				++nCount;
		}
	}

	return nCount;
}

//< LTH-040315-KO ������ ���߿� �ϳ��� ��������... Fame ������ �������
// ���� �ϳ� ���� ���� Fame�� ����Ǵ� ���� ���� ���� ���� ���� �ϳ��� ������ ��������
// ������ Fame�� ���� ���ϵ��� �������
bool CGuardInfo::IsTargetBroken(LPCHARLIST lpTarget, int nType)
{
	bool bIsBroken = FALSE;

	//<060327_kch 5994map Crash (TEAM1 �������϶��� ���彺�� ����, �����ϴµ�, ó��,Debugging����׽�Ʈ������ ��������, �����׽�Ʈ���� crash)
	if (false == IsValidGData())	//���彺�� �����Ͱ� ���ٸ� skip
	{
		return FALSE;
	}
	//060327_kch

	int nI;
	for (nI = 0; nI < m_iGDataCount; ++nI)
	{
		// Ÿ���� �´� ���� �ִ°�
		if (nType == m_pGData[nI].NPCType)
		{
			// �����ΰ�
			if (nType == 2)
			{
				// �ϴ� Ÿ���� ����� ������ ��ġ�ϴ��� �˻��ϰ�
				if (((lpTarget->X / TILE_SIZE) == m_pGData[nI].GenPosX) && \
					((lpTarget->Y / TILE_SIZE) == m_pGData[nI].GenPosY))
				{
					// DontNo�� ¦���̸� ���� �Ͱ� ���ϰ� Ȧ���̸� �տ� �Ͱ� ���Ѵ�
					if ((m_pGData[nI].DontNo % 2) == 0)
					{
						// ���� �̷�� ������ ���� �ȱ����ٸ� Fame�� �޾ƾ��ϹǷ� TRUE!!
						if (TRUE == (m_pGData[nI + 1].Status == ALIVE_))
						{
							bIsBroken = TRUE;
							break;
						}
					}
					else if (((nI - 1) >= 0) && (nType == m_pGData[nI - 1].NPCType))	// �տ� ���� ��ȿ�� ������ Ȯ��
					{
						// ���� �̷�� ������ ���� �ȱ����ٸ� Fame�� �޾ƾ��ϹǷ� ���� TRUE!!!
						if(TRUE == (m_pGData[nI - 1].Status == ALIVE_))
						{
							bIsBroken = TRUE;
							break;
						}
					}
				}
			}
		}
	}

	return bIsBroken;
}
