/**
 * @file	TeamInfo.cpp.
 *			implementation of the CTeamInfo class.
 */
//#include "..\stdafx.h"
#include "StdAfx.h"	// ������ �ð��� 20���� �ɷ���, ����ȭ �۾�

#include "TeamInfo.h"
#include "WarfieldInfo.h"
#include "LogManager.h"

CSquad::CSquad()
: m_nSquadLeader(-1)
, m_nSquadNo(-1)
{
	m_ltSquad.clear();
	m_xyLoadingPoint.x = 0;
	m_xyLoadingPoint.y = 0;
	INT nI;
	for (nI = 0; nI < 3; ++nI)
	{
		m_naNumOfJoinNation[nI] = 0;
		m_naNumOfDeathNation[nI] = 0;
	}
}

/**
 * @fn		CSquad::GetNationMemberCount().
 * @brief	�� ������ �ο� ���� ��ȯ �Ѵ�.
 * @param	INT nNationNo. Ư�� ����.
 * @return	INT. Ư�� ������ �ο� ��.
 */
INT CSquad::GetNationMemberCount(INT nNationNo)
{
	switch(nNationNo)
	{
	case NW_BY:
		return m_naNumOfJoinNation[0];

	case NW_ZY:
		return m_naNumOfJoinNation[1];

	case NW_YL:
		return m_naNumOfJoinNation[2];
	}
	
	return 0;
}	

/**
 * @fn		CSquad::GetMemberCount().
 * @brief	�� �δ��� �� �ο� �� ��ȯ.
 * @return	INT. �� �δ��� �� �ο� ��.
 */
INT CSquad::GetMemberCount()
{
	INT nMemberCount = m_ltSquad.size();
	return nMemberCount;
}	

/**
 * @fn		CSquad::InsertMember().
 * @brief	�δ�� �߰��ϴ� �Լ�.
 * @param	INT nCn. ���� �ν� ��ȣ.
 * @return	VOID.
 */
VOID CSquad::InsertMember(INT nCn)
{
	SquadMember* lpSquadMember = new SquadMember;
	lpSquadMember->SetData(nCn);
	m_ltSquad.push_back(lpSquadMember);

	switch (connections[nCn].chrlst.name_status.nation)
	{
	case NW_BY:
		++m_naNumOfJoinNation[0];
		break;

	case NW_ZY:
		++m_naNumOfJoinNation[1]; 
		break;

	case NW_YL:
		++m_naNumOfJoinNation[2];
		break;
	}
	connections[nCn].chrlst.NWCharacter.SquadNo = (DWORD)m_nSquadNo;
	//< �α� ��ȭ.
	g_pLogManager->SaveLogNeoNationWar(NNT_CHARACTER_INFO, "%s Join in Squad %d, Nation %d", connections[nCn].name, \
		m_nSquadNo, connections[nCn].chrlst.name_status.nation);
	g_pLogManager->SaveLogNeoNationWar(NNT_CHARACTER_INFO, "Number Of %d Squad Member : %d", m_nSquadNo, \
		m_ltSquad.size());
	//> 
}	

/**
 * @fn		CSquad::DeleteMember().
 * @brief	�δ�� ����.
 * @param	INT nCn. ���� �ν� ��ȣ.
 * @return	VOID.
 */
VOID CSquad::DeleteMember(INT nCn)
{
	INT nCheckID;
	SquadMember* lpSquadMember;
	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();
	while (ltSquadIt != ltSquadItEnd)
	{ 
		nCheckID = (*ltSquadIt)->GetData();
		if (nCheckID == nCn)
		{
			switch (connections[nCn].chrlst.name_status.nation)
			{
			case NW_BY:
				--m_naNumOfJoinNation[0];
				break;

			case NW_ZY:
				--m_naNumOfJoinNation[1];
				break;

			case NW_YL:
				--m_naNumOfJoinNation[2];
				break;
			}
			//< �α� �߰�!!
			connections[nCn].chrlst.NWCharacter.SquadNo = 0;
			g_pLogManager->SaveLogNeoNationWar(NNT_CHARACTER_INFO, "%s Withdrew from Squad %d, Nation %d", connections[nCn].name, \
				m_nSquadNo, connections[nCn].chrlst.name_status.nation);
			g_pLogManager->SaveLogNeoNationWar(NNT_CHARACTER_INFO, "Number Of %d Squad Member : %d", m_nSquadNo, m_ltSquad.size() - 1);
			//> 

			lpSquadMember = (*ltSquadIt);
			m_ltSquad.remove(lpSquadMember);
			SAFE_DELETE(lpSquadMember);
			connections[nCn].chrlst.NWCharacter.SquadNo = 0;
			break;
		}
		else
			ltSquadIt++; 
	}
}	

/**
 * @fn		CSquad::SendMessageAllMember().
 * @brief	�� �δ������ ä�� �޽��� ������.
 * @param	t_packet * p. ��Ŷ ����.
 * @return	VOID.
 */
VOID CSquad::SendMessageAllMember(t_packet *p)
{
	INT nCn = -1;
	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();
	for (; ltSquadIt != ltSquadItEnd; ltSquadIt++)
	{
		nCn = (*ltSquadIt)->GetData();
		QueuePacket(connections, nCn, p, 1);
	}
}

/**
 * @fn		CSquad::FindMember().
 * @brief	�δ�� ã��.
 * @param	INT nCn. ���� �ν� ��ȣ.
 * @return	BOOL. ã������ TRUE.
 */
BOOL CSquad::FindMember(INT nCn)
{
	INT nID = -1;
	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();
	BOOL bFind = FALSE;
	for (; ltSquadIt != ltSquadItEnd; ltSquadIt++)
	{
		nID = (*ltSquadIt)->GetData();
		if (nID == nCn)
		{
			bFind = TRUE;
			break;
		}
	}

	return bFind;
}	

/**
 * @fn		CSquad::GetNationDeathCount().
 * @brief	Ư�� ������ ���� ��� �� ��ȯ.
 * @param	INT nNationNo. Ư�� ���� ��ȣ.
 * @return	INT. ���� ��� ��.
 */
INT CSquad::GetNationDeathCount(INT nNationNo)
{
	switch(nNationNo)
	{
	case NW_BY:
		return m_naNumOfDeathNation[0];

	case NW_ZY:
		return m_naNumOfDeathNation[1];

	case NW_YL:
		return m_naNumOfDeathNation[2];
	}
	
	return 0;
}

extern void SendFameChange(LPCHARLIST lpChar,int AddFame);

/**
 * @fn		CSquad::GiveFame().
 * @brief	Ÿ�� �������κ��� ���� �Ÿ��� �ִ� ������� �ش� ��ġ�� �ش�.
 * @param	LPCHARLIST lpCaster. ��ġ�� �޴µ� ���� �� ���,
 * @param	LPCHARLIST lpTarget. Ÿ��.
 * @param	INT nRange. ���� �Ÿ�
 * @param	INT nAddFame. ���� ��ġ.
 * @return	VOID.
 */
VOID CSquad::GiveFame(LPCHARLIST lpCaster, LPCHARLIST lpTarget, INT nRange, INT nAddFame)
{
	INT nCn;
	DWORD dwTileRange = (nRange * TILE_SIZE) * (nRange * TILE_SIZE);
	DWORD dwTargetRange = 0;
	INT nSx = lpTarget->X;
	INT nSy = lpTarget->Y;
	INT nDx, nDy;
	LPCHARLIST	lpChar;
	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();
	for (; ltSquadIt != ltSquadItEnd; ltSquadIt++)
	{
		nCn = (*ltSquadIt)->GetData();
		if (lpCaster->GetServerID() != nCn)
		{
			lpChar = &connections[nCn].chrlst;
			nDx = lpChar->X;
			nDy = lpChar->Y;
			dwTargetRange = (nSx - nDx) * (nSx - nDx) + (nSy - nDy) * (nSy - nDy);
			if (dwTileRange > dwTargetRange)
			{
				g_pLogManager->SaveLogChange_Fame(lpChar, lpChar->fame, lpChar->fame + nAddFame, LF_NATIONWAR);
				g_pLogManager->SaveLogNeoNationWar(NNT_FAME_INFO, "Fame Change, Name : %s, OldFame : %d, NewFame : %d, Gap : %d", \
					lpChar->Name, lpChar->fame, lpChar->fame + nAddFame, nAddFame);
				lpChar->fame += nAddFame;
				::SendFameChange(lpChar, nAddFame);
			}
		}
	}
}

#include "Scrp_exe.h"
/* g_pLogManager�� �̵�(��������)
extern void SaveLogChange_DualFame( CHARLIST *ch, const int nOldDualFame, const int nNewDualFame, eLDF_TYPE type);
*/

/**
 * @fn		CSquad::GiveFame2Dual().
 * @brief	��� ��ġ�� �ش�.
 * @param	INT nAddFame. ���� ��ġ.
 * @return	VOID.
 */
VOID CSquad::GiveFame2Dual(INT nAddFame)
{
	INT nCn = 0;
	LPCHARLIST lpChar = NULL;

	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();
	for (; ltSquadIt != ltSquadItEnd; ltSquadIt++)
	{
		nCn = (*ltSquadIt)->GetData();
		lpChar = &connections[nCn].chrlst;
		if (NULL == lpChar)
			continue;
		if (lpChar->IsDual())
		{
			g_pLogManager->SaveLogChange_DualFame(lpChar, lpChar->fame, lpChar->fame + nAddFame, LDF_NEOWAR);
			g_pLogManager->SaveLogNeoNationWar(NNT_FAME_INFO, "Fame Change, Name : %s, OldFame : %d, NewFame : %d, Gap : %d", \
				lpChar->Name, lpChar->fame, lpChar->fame + nAddFame, nAddFame);
			lpChar->fame += nAddFame;
			::SendFameChange(lpChar, nAddFame);
		}
	}
}	

/**
 * @fn		CSquad::AddDeathCount().
 * @brief	Ư�� ������ ���� ����� �߰�.
 * @param	INT nNationNo. Ư�� ���� ��ȣ.
 * @return	VOID.
 */
VOID CSquad::AddDeathCount(INT nNationNo)
{
	switch(nNationNo)
	{
	case NW_BY:
		++m_naNumOfDeathNation[0];
		break;

	case NW_ZY:
		++m_naNumOfDeathNation[1];
		break;

	case NW_YL:
		++m_naNumOfDeathNation[2];
		break;
	}
}	

/**
 * @fn		CSquad::DeleteAllMember().
 * @brief	��� �δ�� ����.
 * @return	VOID.
 */
VOID CSquad::DeleteAllMember()
{
	SquadMember* lpSquadMember;
	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();
	while (ltSquadIt != ltSquadItEnd)
	{
		lpSquadMember = (*ltSquadIt);
		m_ltSquad.remove(lpSquadMember);
		SAFE_DELETE(lpSquadMember);

		ltSquadIt++;
	}

	m_nSquadLeader = -1;
	m_ltSquad.clear();
	INT nI;
	for (nI = 0; nI < 3; ++nI)
	{
		m_naNumOfJoinNation[nI] = 0;
		m_naNumOfDeathNation[nI] = 0;
	}
}	

/**
 * @fn		CSquad::RemoveArmor().
 * @brief	������ �����.
 * @return	VOID.
 */
VOID CSquad::RemoveArmor()
{
	INT nID;
	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();

	while (ltSquadIt != ltSquadItEnd)
	{
		nID = (*ltSquadIt)->GetData();
		::CheckAndSendChangeEquip(&connections[nID].chrlst, 1);
		ltSquadIt++;
	}
}

//----------------------------------------------------------------------------------

/**
 * @fn		CTeamInfo::GetNationMemberCount().
 * @brief	Ư�� ������ ������� ��ȯ.
 * @param	INT nNationNo. Ư�� ���� ��ȣ.
 * @return	INT. Ư�� ������ ��� ��.
 */
INT CTeamInfo::GetNationMemberCount(INT nNationNo)
{
	INT nNationMember = 0;
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
	{
		nNationMember += m_lpSquad[nI].GetNationMemberCount(nNationNo);
	}

	return nNationMember;
}	

/**
 * @fn		CTeamInfo::GetSquadMemberCount().
 * @brief	Ư�� �δ��� �δ�� ��.
 * @param	INT nSquadNo. Ư�� �δ� ��ȣ.
 * @return	INT. Ư�� �δ��� �δ�� ��.
 */
INT CTeamInfo::GetSquadMemberCount(INT nSquadNo)
{
	// �δ밡 ���� ���� ���� �Ͱ� �������� �̹Ƿ�...
	if (m_nNumOfSquad == 0)
		return 0;

	INT nSquadMember = m_lpSquad[nSquadNo].GetMemberCount();
	return nSquadMember;
}	

extern LPWARFIELDINFO g_pcWarfieldInfo;

/**
 * @fn		CTeamInfo::CheckSquadOfCharacter().
 * @brief	Ư�� ������ ������ �ش� ���￡���� ��� �δ��ΰ� ��ȯ.
 * @param	INT nWarfieldNo. ���� ������ ��ȣ.
 * @param	INT nCharLv. Ư�� ������ ����.
 * @return	INT. ��� �δ�.
 */
INT CTeamInfo::CheckSquadOfCharacter(INT nWarfieldNo, INT nCharLv)
{
	CSoldierSet cSoldier = g_pcWarfieldInfo->GetSoldierSet(nWarfieldNo);
	INT nSquadNo = -1;
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
	{
		if ((nCharLv >= cSoldier.m_tagaSquad[nI].nLevelMin) && (nCharLv <= cSoldier.m_tagaSquad[nI].nLevelMax))
			break;
	}
	nSquadNo = nI;

	return nSquadNo;
}	

/**
 * @fn		CTeamInfo::Init().
 * @brief	CTeamInfo class �ʱ�ȭ.
 * @param	INT nNumOfSquad. �� �δ� ��.
 * @return	HRESULT.
 */
HRESULT CTeamInfo::Init(INT nNumOfSquad)
{
	m_nNumOfSquad = nNumOfSquad;
	//< ��� �� �δ�� �־���Ѵ�
	if (m_nNumOfSquad == 0)
		return E_FAIL;
	//> 
	m_lpSquad = new CSquad[m_nNumOfSquad];
	_ASSERT(NULL != m_lpSquad);

	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
		m_lpSquad[nI].SetSquadNo(nI);
	return S_OK;
}	

/**
 * @fn		CTeamInfo::InsertSquadMember().
 * @brief	�δ�� �߰�.
 * @param	INT nWarfieldNo. ������ ��ȣ.
 * @param	INT nCn. ���� �ν� ��ȣ.
 * @return	VOID.
 */
VOID CTeamInfo::InsertSquadMember(INT nWarfieldNo, INT nCn)
{
	//< ��� ĳ���� �δ뿡 ���� ��Ű�� �������� �߰�
	LPCHARLIST lpChar = ::CheckServerId(nCn);
	if (lpChar == NULL)
		return;
	if (lpChar->IsCounselor()) 
		return;
	//>

	INT nCharLv = connections[nCn].chrlst.GetLevel();
	INT nSquadNo = CheckSquadOfCharacter(nWarfieldNo, nCharLv);
	m_lpSquad[nSquadNo].InsertMember(nCn);
}	

/**
 * @fn		CTeamInfo::DeleteSquadMember().
 * @brief	�δ�� ����.
 * @param	INT nWarfieldNo. �����͹�ȣ.
 * @param	INT nCn. ���� �ν� ��ȣ.
 * @return	VOID.
 */
VOID CTeamInfo::DeleteSquadMember(INT nWarfieldNo, INT nCn)
{
	//< ��� ĳ���� �δ뿡 ���� ��Ű�� �������� �߰�
	LPCHARLIST lpChar = ::CheckServerId(nCn);
	if (lpChar == NULL)
		return;
	if (lpChar->IsCounselor()) 
		return;
	//> 
	
	INT nCharLv = connections[nCn].chrlst.GetLevel();
	INT nSquadNo = CheckSquadOfCharacter(nWarfieldNo, nCharLv);
	m_lpSquad[nSquadNo].DeleteMember(nCn);
}	

/**
 * @fn		CTeamInfo::SendMessageAllMember().
 * @brief	�δ�� ä�� ������ ����.
 * @param	t_packet * p. ��Ŷ ����.
 * @return	VOID.
 */
VOID CTeamInfo::SendMessageAllMember(t_packet *p)
{
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
		m_lpSquad[nI].SendMessageAllMember(p);
}	

/**
 * @fn		CTeamInfo::GetLivePoint().
 * @brief	Ư�� ������ ���� �δ��� �ε� ����Ʈ ������.
 * @param	LPCHARLIST lpChar. Ư�� ����.
 * @return	POINT. �ε� ����Ʈ.
 */
POINT CTeamInfo::GetLivePoint(LPCHARLIST lpChar)
{
	INT nI;
	POINT xyTemp = {0, 0};
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
	{
		if (m_lpSquad[nI].FindMember(lpChar->GetServerID()))
		{
			xyTemp = m_lpSquad[nI].GetLivePoint();
			break;
		}
	}

	return xyTemp;
}	

/**
 * @fn		CTeamInfo::KickUser().
 * @brief	Ư�� �δ�� ����.
 * @param	INT nCn. ����
 * @return	BOOL. ������ ������ FALSE.
 */
BOOL CTeamInfo::KickUser(INT nCn)
{
	LPCHARLIST lpChar = ::CheckServerId((WORD)nCn);
	if (NULL == lpChar)
		return FALSE;

	BOOL bIsUser = FALSE;
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
	{
		//< ���ڷ� ���� ���� ���̵� ���ڳ� �����!! �Լ��� �Ǿ��� -_-;
		if (m_lpSquad[nI].FindMember(nCn))
		{
			m_lpSquad[nI].DeleteMember(nCn);
			bIsUser = TRUE;
			break;
		}
		//> 
	}

	return bIsUser;
}	

/**
 * @fn		CTeamInfo::GetNationDeathCount().
 * @brief	Ư�� ������ ���� ��� ���� ��ȯ.
 * @param	INT nNation. Ư�� ���� ��ȣ.
 * @return	INT. ���� ��� ��.
 */
INT CTeamInfo::GetNationDeathCount(INT nNation)
{
	INT nNationDeathMember = 0;
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
	{
		nNationDeathMember += m_lpSquad[nI].GetNationDeathCount(nNation);
	}

	return nNationDeathMember;
}	

/**
 * @fn		CTeamInfo::GiveFame2Dual().
 * @brief	��� ���� �ش�.
 * @param	INT nAddFame. ���� ��ġ.
 * @return	VOID.
 */
VOID CTeamInfo::GiveFame2Dual(INT nAddFame)
{
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
		m_lpSquad[nI].GiveFame2Dual(nAddFame);
}	

/**
 * @fn		CTeamInfo::GiveFame().
 * @brief	Ư�� ĳ���� �����ϰ� ���� �Ÿ��� ĳ������ ��ġ�� �ش�.
 * @param	LPCHARLIST lpCaster. ��ġ�� ���� ���� ĳ��.
 * @param	LPCHARLIST lpTarget. Ÿ��.
 * @param	INT nRange. ���� �Ÿ�.
 * @param	INT nAddFame. ���� ��ġ.
 * @return	VOID.
 */
VOID CTeamInfo::GiveFame(LPCHARLIST lpCaster, LPCHARLIST lpTarget, INT nRange, INT nAddFame)
{
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
	{
		m_lpSquad[nI].GiveFame(lpCaster, lpTarget, nRange, nAddFame);
	}
}	

/**
 * @fn		CTeamInfo::Clear().
 * @brief	��� �δ�� ����.
 * @return	VOID.
 */
VOID CTeamInfo::Clear()
{
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
		m_lpSquad[nI].DeleteAllMember();
}	

/**
 * @fn		CTeamInfo::RemoveArmor().
 * @brief	���� �����.
 * @return	VOID.
 */
VOID CTeamInfo::RemoveArmor()
{
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
		m_lpSquad[nI].RemoveArmor();
}	