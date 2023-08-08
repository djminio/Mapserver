/*
// 021008 �߰��ϴ� �Լ���
//extern �� ��� network7.h�� ����ִ�. 
*/

#include "..\stdafx.h"
//#include "MAIN.H"
//#include "servertable.h"
#include "QuestFunction.h"
#include "Dr_network.h"

extern CAliveMapZoneAll g_AliveMap;		//m_Map���̺��� ����ϱ� ����

void RecvWhatQuestInMap( t_packet *p, int cn);			//�ʹ�ȣ�� ���� ���� ����Ʈ�� ���� ���ܰ��� �����Ͽ� ������ȣ�� ������.
void CheckSpellMapMoveArea( char *szMsg, int cn);		//�� ������ �ֹ����� ���̵� �ϴ� �����̸� ���ڿ��� g_QuestInMap.m_szClientSpell�� �ִ´�.


void RecvWhatQuestInMap( t_packet *p, int cn)
{

	t_quest_in_map *tp = &(p->u.quest_in_map);

	CHARLIST *ch = CheckServerId( cn );
	if( !ch) return;

	//�̸�Ȯ��
	if( 0 != strcmp( ch->Name, p->u.quest_in_map.name ) ) return;

	g_QuestInMap.SendQuestInfo( tp, cn );

}

void CheckSpellMapMoveArea( char *szMsg, int cn)
{//���� 1, ���� 0
	CHARLIST *ch = CheckServerId( cn );
	if( !ch ) return;

	if( !szMsg ) return;

	if( ch->viewtype == VIEWTYPE_GHOST_ ) return; //����Ÿ���̸� �ȵȴ�. 

	for( int i =0;i < g_AliveMap.m_Max; i++)
	{
		if( g_AliveMap.m_Map[i].map_number != MapNumber ) continue;
		//if( ! TileMap[ch->MoveSx][ch->MoveSy].attr_inside ) // ���� �Ӽ��� �ִ� ���� �ƴ϶��
		//	continue;

		if( BoxAndDotCrash( g_AliveMap.m_Map[i].x,g_AliveMap.m_Map[i].y, g_AliveMap.m_Map[i].xl, g_AliveMap.m_Map[i].yl, ch->MoveSx, ch->MoveSy	) )
		{	//�� ���ھȿ� ������
			if( g_AliveMap.m_Map[i].alive_word_type == SPELL_MAP_MOVE_TYPE ) //10�� �Ӽ��϶�..
			{
				//���� cn���� �̾��� ����� ���� ����. 
				g_QuestInMap.DeleteSpellUser( cn );	

				CSpellMove cSpell(cn, szMsg);				
				g_QuestInMap.m_szClientSpell.push_back( cSpell );
				break;
			}
		}
	}
	return;
}

int HandleCommand3( t_packet *packet, t_connection c[], const int cn )
{
	switch( packet->h.header.type)
	{
	case CMD_WHAT_QUEST_IN_MAP:		// 021008 kyo ����Ʈ ������ ������
		{
			RecvWhatQuestInMap( packet, cn);			
		}break;
	case CMD_SCRIPT_TIMER_START:	// 021022 kyo ��ũ��Ʈ Ÿ�̸ӿ� ���õȰ�
	case CMD_SCRIPT_TIMER_SYNC:
	case CMD_SCRIPT_TIMER_END_SUC:
	case CMD_SCRIPT_TIMER_END_FAL:
		{
			g_QuestInMap.RevcScriptTimerPacket( (&packet->u.script_timer), packet->h.header.type, cn);
		}break;
	case CMD_SCRIPT_COUNTER_SYNC:	// 030108
		{
			g_QuestInMap.RevcScriptCounterSync( (&packet->u.script_counter),  cn);
		}break;

	case CMD_SCRIPT_SPELL_MAPMOVE:
		{
			g_QuestInMap.RecvSpellMapMove( &packet->u.spell_mapmove, cn );
		}break;
	default:	
		{
			return 0;
		}break;
	}
	return 1;
}