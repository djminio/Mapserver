#include "..\stdafx.h"
#include "DefaultHeader.h"
#include "SealStone.h"
#include "UserManager.h"

#include "..\LowerLayers\define.h"
#include "..\LowerLayers\servertable.h"
					
int KingCommandBlock;
int SealStoneBreakable;


static char packet_msg[ MM_MAX_PACKET_SIZE ];

int ReturnSealStoneBreakable( void )
{
	switch( SealStoneBreakable )
	{
		case CMD_STEALSTONE_BREAKABLE	 :	
		case CMD_STEALSTONE_NON_BREAKABLE_PEACE	:	
		case CMD_STEALSTONE_NON_BREAKABLE:			return SealStoneBreakable;
	}

	return CMD_STEALSTONE_NON_BREAKABLE;
	
}

void Recv_CMD_SEALSTONE_STATUS( t_sealstone_status *tp )
{	//< CSD-CN-031213
	DWORD nation = N_NEUTRAL;

	switch (tp->sealstonesprno)
	{			
	case 91: nation = N_YLLSE;  break;
	case 98: nation = N_VYSEUS; break;	
	case 99: nation = N_ZYPERN; break;	
	}			

	t_packet p;
	p.h.header.type = CMD_SEALSTONE_STATUS;
	p.h.header.size = sizeof(t_sealstone_client_status);
	p.u.sealstone_client_status.mapnumber = tp->mapnumber;
	p.u.sealstone_client_status.status = tp->status;
	p.u.sealstone_client_status.x = tp->x;
	p.u.sealstone_client_status.y = tp->y;

	CUserManager::HASH_USER mpUser = g_pUserManager->GetUserSet();

	for (CUserManager::ITOR_USER i = mpUser.begin(); i != mpUser.end(); ++i)
	{
		const int idUser = i->second;
		CHARLIST* pUser = CheckServerId(idUser);
		
		if (pUser != NULL)
		{
			if (pUser->name_status.nation == nation && pUser->GetLevel() >= ENABLE_FREE_LEVEL)
			{
				QueuePacket(connections, idUser, &p, 1);
			}
		}
	}
}	//> CSD-CN-031213
	
//	LoginServer���� ������ ���۵ȴٴ� ��⸦ �����. 
//	���� ���� �ֵ����� �ѷ��ش�. 
extern void	SendPacket2NationClients(const int Nation,t_packet* p);	// CSD-030415

void Recv_CMD_SEALSTONE_WAR_START( int nation )
{	//< CSD-030415			
	t_packet p;				
	p.h.header.type = CMD_SEALSTONE_WAR_START;
	p.h.header.size = 0;
	SendPacket2NationClients(nation, &p);
}	//> CSD-030415	
					
//	�α伷���� ������ ����� �����־���. 
//	����� ĳ���Ϳ��� �ѷ��ش�. 
void Recv_CMD_SEALSTONE_RESULT( t_sealstone_result *tp )
{	//< CSD-CN-031213
	t_packet ap;
	ap.h.header.size = 0;

	switch (tp->aresult)
	{
	case SSR_FAIL:
		{
			ap.h.header.type = CMD_SEALSTONE_RESULT_DEFEAT;
			break;
		}
	case SSR_VICTORY:
		{
			ap.h.header.type = CMD_SEALSTONE_RESULT_VICTORY;
			break;
		}
	case SSR_DRAW:
		{
			ap.h.header.type = CMD_SEALSTONE_RESULT_DRWAW;
			break;
		}
	}
	
	t_packet bp;
	bp.h.header.size = 0;

	switch (tp->bresult)
	{
	case SSR_FAIL:
		{
			bp.h.header.type = CMD_SEALSTONE_RESULT_DEFEAT;		
			break;
		}
	case SSR_VICTORY:
		{
			bp.h.header.type = CMD_SEALSTONE_RESULT_VICTORY;
			break;
		}
	case SSR_DRAW:
		{
			bp.h.header.type = CMD_SEALSTONE_RESULT_DRWAW;
			break;
		}
	}

	CUserManager::HASH_USER mpUser = g_pUserManager->GetUserSet();

	for (CUserManager::ITOR_USER i = mpUser.begin(); i != mpUser.end(); ++i)
	{
		const int idUser = i->second;
		CHARLIST* pUser = CheckServerId(idUser);
		
		if (pUser != NULL)
		{
			if (pUser->name_status.nation == (DWORD)tp->anation)
			{
				QueuePacket(connections, idUser, &ap, 1);
			}
			
			if (pUser->name_status.nation == (DWORD)tp->bnation)
			{
				QueuePacket(connections, idUser, &bp, 1);
			}
		}
	}
}	//> CSD-CN-031213

void Recv_CMD_SEALSTONE_WAR_LEFTTIME(int nation, DWORD lefttime)
{	//< CSD-CN-031213
	t_packet p;
	p.h.header.type = CMD_SEALSTONE_WAR_LEFTTIME;
	p.h.header.size = sizeof(t_sealstone_client_warlefttime);
	p.u.sealstone_client_warlefttime.lefttime = lefttime;
	
	CUserManager::HASH_USER mpUser = g_pUserManager->GetUserSet();

	for (CUserManager::ITOR_USER i = mpUser.begin(); i != mpUser.end(); ++i)
	{
		const int idUser = i->second;
		CHARLIST* pUser = CheckServerId(idUser);
		
		if (pUser != NULL && pUser->name_status.nation == (DWORD)nation)
		{
			QueuePacket(connections, idUser, &p, 1);
		}
	}
}	//> CSD-CN-031213
	
void SendSealStoneFromKing( int cn )
{	
	return;
	
	if( connections[cn].chrlst.name_status.king == 0 )
	{	
		// �װ� ���̳�...
		return;
	}

	t_packet p;
		
	if( KingCommandBlock ) // ����� ���ݸ���� ������ ����. 
	{	
		p.h.header.type = CMD_WAR_START_BLOCK;
		p.h.header.size = 0;
		QueuePacket(connections, cn, &p, 1);
	}	
	else
	{
		p.h.header.type = CMD_SEALSTONEFROMKING;
		p.h.header.size = sizeof( t_sealstone_fromking );
		p.u.sealstone_fromking.nation = connections[cn].chrlst.name_status.nation;
		QueuePacket(connections, LOGIN_SERVER_CONNECT, &p, 1);
	}
}
	
void Send_CMD_SEALSTONE_STATUS( LPCHARLIST d, int status )
{	
	t_packet p;
	
	if( d->Race != SEALSTONE  ) return;
	
	p.h.header.type = CMD_SEALSTONE_STATUS;
	p.h.header.size = sizeof( t_sealstone_status );
	p.u.sealstone_status.sealstonesprno = (char )d->SprNo;
	p.u.sealstone_status.id				= d->eventno;
	p.u.sealstone_status.mapnumber		= MapNumber;
	p.u.sealstone_status.x				= d->MoveSx;
	p.u.sealstone_status.y				= d->MoveSy;
	p.u.sealstone_status.status			= status;
	p.u.sealstone_status.Hp				= d->Hp; // 030516 kyo
	
//	QueuePacket( connections, LOGIN_SERVER_CONNECT, &p, 1 );
//	001206 KHS
	
	SERVER_DATA *pData = g_pServerTable->GetOwnServerData();

	if( pData->wPort == NATION_MANAGE_SERVER )
	{
		Recv_CMD_SEALSTONE_STATUS( &p.u.sealstone_status );
	}
	else
	{
		packet_msg[0] = (BYTE)PTCL_MAP_TO_MAP;
		memcpy( packet_msg + 1, (char *)&p, (sizeof( t_header ) + p.h.header.size ) );
		g_pServerTable->Send( (WORD)NATION_MANAGE_SERVER, (char *)&packet_msg, (sizeof( t_header ) + p.h.header.size )+1 ) ;
	}
}	
	
	
	
/********************************************************************************************�׼�(�ʼ�)���� ����ϴ� �Լ�
��	�� :	�������� ���踦 Loginserver�� ���� ���Ӽ����� ������ ��� ���Ӽ�(�ʼ�)�� �˰� �Ѵ�. 
			
��	�� : int a_nation, b_nation : ���踦 ������ ���� ( �����ڵ�,  3: ���̼���, 4:������ ... )
		int relation           : 0 : ������    1: �������     2: ���°���    3: ��������( a:�� b:��)
		DWORD relationstart		:	���ʵڿ� �����Ұ��ΰ�
		DWORD relationhowlong	:	���ʵ��� �����ɰ��ΰ�? ( 0�̸� ���� )
			
��	�� : LoginServer�� ��������, �ٽ� ���Ӽ�(�ʼ�)���� ��������, �ٽ� Client���� ����� �����ְ� �ȴ�. 
*******************************************************************************************************/
int SendNation2NationRelation( int a_nation, int b_nation, int relation, int year = 0, int yday = 0, int hour = 0, DWORD howlong = 0 )
{			
	t_packet p;
			
	if( relation == NATION_RELATION_FRIEND_ )
	{		
		if( year == 0 ) // �������� 1�ϰ��� ������ �Ѵ�. 
		{	
			year  = g_year;
			yday  = g_yday;
			hour  = g_hour;

			int shour = 24 - g_hour + 2;
			int smin  = 60 - g_min;
			
			howlong = 60*60*shour + smin * 60;
		}
	}	
		
	p.h.header.type = CMD_NATION2NATION_RELATION;
	p.h.header.size = sizeof( t_nation2nation_relation );
		
		p.u.nation2nation_relation.a		= a_nation;
		p.u.nation2nation_relation.b		= b_nation;
		p.u.nation2nation_relation.relation = relation;
		p.u.nation2nation_relation.year		= year;
		p.u.nation2nation_relation.yday		= yday;
		p.u.nation2nation_relation.hour		= hour;
		p.u.nation2nation_relation.howlong	= howlong;
		
	SERVER_DATA *pData= g_pServerTable->GetOwnServerData();
	if( pData->wPort == NATION_MANAGE_SERVER )
	{	
		RecvNation2NationRelation( 0, &(p.u.nation2nation_relation) );
	}	
	else
	{	
		g_pServerTable->BroadCastToEveryServer( (char *)&p, (sizeof( t_header ) + p.h.header.size ),  SERVER_TYPE_MAP );
	}	

	//  QueuePacket( connections, LOGIN_SERVER_CONNECT, &p, 1 );
	return 1;
}		
	
void RecvNation2NationRelationResult(t_packet *p)
{	//< CSD-CN-031213
	switch (p->u.nation2nation_relation_result.why)
	{	
	case NATION_RELATION_SAME_FAIL_: // ���� �̹� �׷��� ������ �Ǿ� �ִ»����Դϴ�. 
	case NATION_RELATION_FAIL_:	     // ������ ��ĵǾ����ϴ�.
		{
			CUserManager::HASH_USER mpUser = g_pUserManager->GetUserSet();

			for (CUserManager::ITOR_USER i = mpUser.begin(); i != mpUser.end(); ++i)
			{
				const int idUser = i->second;
				CHARLIST* pUser = CheckServerId(idUser);
				
				if (pUser != NULL && pUser->name_status.king)
				{
					QueuePacket(connections, idUser, p, 1);
				}
			}
			
			break;
		}
	case NATION_RELATION_SUCCESS_ :	// ������ �����Ǿ����ϴ�. 
		{
			g_pUserManager->SendPacket(p);
			break;
		}
	}
}	//> CSD-CN-031213