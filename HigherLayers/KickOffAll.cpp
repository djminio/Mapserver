// KickOffAll.cpp: implementation of the CKickOffAll class.
//
//////////////////////////////////////////////////////////////////////

#include "../stdafx.h"
#include "KickOffAll.h"
#include "UserManager.h"		// BBD 040110

typedef map<string, WORD>     HASH_USER;	// BBD 040110
#define DEFAULT_KICKAMOUNT1TIMES	10	// BBD 040110

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKickOffAll::CKickOffAll()
{
	m_bIsKicking = false;
	//<! BBD 040401
	m_nKickAmount1Time = 0;
	m_bIsAllKick = false;
	//> BBD 040401
}

CKickOffAll::~CKickOffAll()
{
	//<! BBD 040401
	 m_nKickAmount1Time = 0;
	//> BBD 040401
}


/////////////////////////////////////////////////////
//BBD 040110 
// �Լ��� : InitKickoffUserAll
// ��� : ������ �������� ���� �ʱ�ȭ�� ����
/////////////////////////////////////////////////////
bool CKickOffAll::InitKickOffUserAll()
{
//<! BBD 040401
/*
	if(!g_pUserManager)		// ��ȿ���� �˻�
	{
		return false;
	}
	HASH_USER users = g_pUserManager->GetUserSet();
	m_nConnectAmount = users.size();
*/
//>! BBD 040401

	m_nKickAmount1Time =GetPrivateProfileInt("KICKOFF_INFO", "KickAmount1Times" , 0, MapServerConfigFileName);
	
	if(!m_nKickAmount1Time) // �ѹ��� �ϵ� ���߸��� �Ұ� ����
	{
		return false;
	}

	m_bIsKicking = true;
	m_bIsAllKick = false;	// BBD 040401
	return true;
}

//////////////////////////////////////////////////////
// BBD 040110
// �Լ��� : KickOffSeverlUser
// ��� : ������ �ִ� ����� ������ �����ϰ� ��������
//////////////////////////////////////////////////////
void CKickOffAll::KickOffSeverlUser()
{	//<! BBD 040401
	if(m_bIsAllKick || !m_bIsKicking)	// Kick���� �ƴϰų� ��� ű�������� �� ����
	{
		return;
	}


/*	if(!m_nConnectAmount)	// ��� �� �߷�������
	{
		return;
	}

	// ��������F �����ϰ� �߶�����
	static int s_KickCurrent = DRAGON_CONNECTIONS_START;					// ���� �ڸ� �ܳؼ��� �ε���
	static int s_KickEnd = DRAGON_CONNECTIONS_START + m_nKickAmount1Time;	// �̹��� �߶��� �ܳؼ��� Maximum
*/
	// ������ ���� �̹��� �߶��� ����� �ڸ���
	int count = 0;
	for(int cn = DRAGON_CONNECTIONS_START; cn < DRAGON_MAX_CONNECTIONS; ++cn)
	{
		if( connections[cn].dwAgentConnectionIndex && connections[cn].state >= CONNECT_JOIN )
		{
			CHARLIST *ch = &connections[cn].chrlst;			
			::closeconnection( connections, cn, -33 , false);		// BBD 040401
			count++;
			if(count >= m_nKickAmount1Time)
			{
				return;
			}
		}
	}
	// ������� Ż���Ѱ��� ��ü�� ���� �ܳؼ��� �� ����ٴ� ��
	m_bIsAllKick = true;
	//> BBD 040401
}

bool CKickOffAll::StopKicking()
{
	m_bIsKicking = false;
	return true;
}
