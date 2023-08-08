#include "stdafx.h"
#include "LowerLayers\\inetwork.h"
#include "LowerLayers\\ServerTable.h"
#include "RMDefine.h"
#include "HigherLayers\\KickOffAll.h"		// BBD 040110

extern void __stdcall ReLoadGameServerDataByKeyInput(DWORD dwValue); //020511 lsw

CKickOffAll g_KickMgr;		// BBD 040110

void RMProc(DWORD dwConnectionIndex, char* pMsg, DWORD dwLength)
{
	BYTE header;
	memcpy(&header, pMsg + 1, 1);

	switch (header)
	{
	case MSG_SHUT_DOWN:
		{
			g_pServerTable->DestroyServer(FINISH_TYPE_NORMAL);
			break;
		}
	case MSG_RELOAD_GAMESERVER_DATA:
		{
			ReLoadGameServerDataByKeyInput(0);
			break;
		}
	case MSG_CHANGE_WEATHER:	//Ŭ���̾�Ʈ�鿡�� �޼��� �ѷ���~
		{
			PACKET_CHANGE_WEATHER *rcvPacket = (PACKET_CHANGE_WEATHER*)pMsg;

			t_packet packet;
			packet.h.header.type = CMD_RM_CHANGE_WEATHER;
			packet.h.header.size = sizeof(t_rm_change_weather);
			packet.u.RmChangeWeather.bWeather = rcvPacket->bWeather;
			packet.u.RmChangeWeather.dwAmount = rcvPacket->dwAmount;
			packet.u.RmChangeWeather.bStopWeather = rcvPacket->bStopWeather;
			
			for (int cn = DRAGON_CONNECTIONS_START ; cn < DRAGON_MAX_CONNECTIONS ; cn ++)
			{
				if(connections[cn].dwAgentConnectionIndex && connections[cn].state >= CONNECT_JOIN)
				{
					QueuePacket(connections, cn, &packet, 1);
				}
			}

			break;
		}
	case MSG_ECHO:
		{	// Echo
			if (g_pINet)
			{
				g_pINet->SendToServer(dwConnectionIndex, pMsg, dwLength, FLAG_SEND_NOT_ENCRYPTION);
			}
			
			break;
		}
	//<! BBD 040110	RM���� ���������� �������
	case MSG_RM_KICKOFF_USER_ALL:	// ��ü ������ �ʼ����� ���ʴ�� �߶��ش�
		{
			if(!g_KickMgr.IsKicking())				// ������ �ٽ� ������ �����Ѵ�
			{
				//<! BBD 040401
				if(g_KickMgr.InitKickOffUserAll())
				{
					MyLog( LOG_NORMAL, "Start Blocking Agent -> Map Join" );
					MyLog( LOG_NORMAL, "Start Blocking Map -> Map Move" );	// BBD 040329
				}
				//> BBD 040401
			}
			break;
		}
	//> BBD 040110	RM���� ���������� �������

	//<! BBD 040110 RM���� �������� ���������� �ڸ���
	case MSG_RM_KICKOFF_USER_SEVERAL:
		{
			g_KickMgr.KickOffSeverlUser();
			break;
		}
	//> BBD 040110 RM���� �������� ���������� �ڸ���

	//<! BBD 040110 Agent�� �ʼ��� ���� ���
	case MSG_RM_KICKOFF_AGENTCANJOIN:
		{
			//<! BBD 040401
			if(g_KickMgr.IsKicking())	// ű���϶��� ó��
			{
				g_KickMgr.StopKicking();
				MyLog( LOG_NORMAL, "End Blocking Agent -> Map Join" );
				MyLog( LOG_NORMAL, "End Blocking Map -> Map Move" );			// BBD 040329
			}
			//> BBD 040401
			break;
		}
	//> BBD 040110 Agent�� �ʼ��� ���� ���
	}
}