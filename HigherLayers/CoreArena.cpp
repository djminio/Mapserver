// CoreArena.cpp: implementation of the CCoreArena class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "CoreArena.h"

///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////////////////////////////////////

CCoreArena::CCoreArena(int nIndex, int nType)
{
	m_nIndex = nIndex;
	m_nArenaType = nType;
	m_bGameOver = false;
#ifdef LMS_MAPSERVER
	m_lvl_min = 1; //Eleval 18/07/09 - LVL Range
	m_lvl_max = 150; //Eleval 18/07/09 - LVL Range
#endif
}

CCoreArena::~CCoreArena()
{

}

///////////////////////////////////////////////////////////////////////////////
// Public Method
///////////////////////////////////////////////////////////////////////////////

void CCoreArena::StartGame(DWORD dwTime)
{
	CBaseArena::StartGame(dwTime);

	for (ITOR_TEAM i = m_ltTeam.begin(); i != m_ltTeam.end(); ++i)
	{
		const int nTeam = (*i)->GetTeamNumber();
		const int nCount = (*i)->GetAliveCount();
		SendRemainCount(nTeam, nCount);
	}

	m_bGameOver = false;
}

void CCoreArena::EndGame(CArenaInfo* pArena)
{
	CBaseArena::EndGame(pArena);
}
	
bool CCoreArena::PlayGame(DWORD dwTime)
{
	DWORD dwRemainTime = m_pState->GetRemainTime(dwTime);

	for (ITOR_TEAM i = m_ltTeam.begin(); i != m_ltTeam.end(); ++i)
	{
		const int nTeam = (*i)->GetTeamNumber();
		const int nCount = (*i)->GetAliveCount();
		SendRemainCount(nTeam, nCount);

		if (nCount <= 0 && !m_bGameOver)
		{
			m_pState->SetContinueTime(dwTime + 5);
			m_bGameOver = true;
			break;
		}
	}
	
	if (dwRemainTime <= 0)
	{
		/////////////////////////////////////////////////////////////////////////////
		//	���� ������ ���� ���� ��� �ִ� ���� ����ϰ� Ȥ�� 
		// ��� �ִ� ���� ���� ��� ���� ���� ���� ���� ����Ѵ�.
		// ���� ���� ��� �ִ� ���� ��� ���� ���� ������ �����صΰ� ���߿� ó���Ѵ�.
		/////////////////////////////////////////////////////////////////////////////
		int top = -1;		// ���� ���� ��� �ִ� ���� �� 
		int bottom_level = 1000000;		// ���� ���� ����
		bool is_over = false;	// ���� ���� ��� �ִ� ���� 2�� �̻��ΰ�?

		for (ITOR_TEAM j = m_ltTeam.begin(); j != m_ltTeam.end(); ++j)
		{
			const int nCount = (*j)->GetAliveCount();
			const int nTotal = (*j)->GetTeamLevel();

			if (top < nCount)
			{
				top = nCount;
				is_over = true;
				bottom_level = nTotal;
			}
			else if (top == nCount)
			{
				if (bottom_level > nTotal) 
				{
					bottom_level = nTotal;
				}
			}			
		}

		if (is_over) // ���� ���� ���� ��� �������� üũ�Ѵ�.
		{
			for (ITOR_TEAM k = m_ltTeam.begin(); k != m_ltTeam.end(); ++k)
			{
				CArenaTeam* pTeam = *k;

				const int nCount = pTeam->GetAliveCount();
				const int nTotal = pTeam->GetTeamLevel();
				
				if (nCount == top && nTotal == bottom_level)
				{
					pTeam->SetGameResult(FST_WIN);
					pTeam->GiveBonus(); // �׺� �������� �ش�.

					const DWORD dwFlowTime = m_pState->GetFlowTime(dwTime);
					
					if (dwFlowTime < 300)		// 5�� �̳����
					{
						MyLog(LOG_NORMAL, "Team Battle End!!! time = %d", dwFlowTime);
					}
				}
				else
				{
					pTeam->SetGameResult(FST_DEFEAT);
				}

				DoResult(pTeam);
			}
		}

		return false;
	}

	return CBaseArena::PlayGame(dwTime);
}

///////////////////////////////////////////////////////////////////////////////
// Protected Method
///////////////////////////////////////////////////////////////////////////////

void CCoreArena::DoResult(CArenaTeam* pTeam)
{
	CBaseArena::DoResult(pTeam);
}

void CCoreArena::DoVictory(CArenaTeam* pTeam)
{
	CBaseArena::DoVictory(pTeam);
}

void CCoreArena::DoDefeat(CArenaTeam* pTeam)
{
	CBaseArena::DoDefeat(pTeam);
}