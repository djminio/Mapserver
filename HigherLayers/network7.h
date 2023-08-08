


#ifndef _NETWORK7_H_
#define _NETWORK7_H_

enum	KYO_CODE
{
	SPELL_MAP_MOVE_TYPE			=	10,		//alive_zone�� alive_word_type��

	CMD_RM_NOW_REPAIR			=	14000,
	CMD_WHAT_QUEST_IN_MAP		=	14001,

	CMD_SCRIPT_SHOW_COLOR_MSG	=	14002,
	
	//Ÿ�̸ӿ�
	CMD_SCRIPT_TIMER_START		=	14110,
	CMD_SCRIPT_TIMER_SYNC		=	14111,
	CMD_SCRIPT_TIMER_END_SUC	=	14112,
	CMD_SCRIPT_TIMER_END_FAL	=	14113,
	//ī���Ϳ�
	CMD_SCRIPT_COUNTER_START	=	14120,
	CMD_SCRIPT_COUNTER_SYNC		=	14121,
	CMD_SCRIPT_COUNTER_END		=	14122,

	CMD_SCRIPT_SPELL_MAPMOVE	=	14200,	// 021128 kyo
	CMD_SCRIPT_SPELL_MAPMOVE_SUC=	14201,	// 021128 kyo
	CMD_SCRIPT_SPELL_MAPMOVE_FAIL=	14202,	// 021128 kyo

	DEFAULT_TIMER_SYNC_TIME		=	5000,	//5��
	MAX_TIMER_TIME				= 5 * 3600 * 1000,		//5�ð��� �����̴�.
	MIN_SYNCH_TIME				= 2 * 1000,				//2�����ϴ�.
       
};
//#include "Dr_Network.h"

//packet type
typedef struct DATA_INTEGER
{
	int	iData;
}t_int;

typedef struct DATA_CHAR
{
	char cData;
}t_char;

typedef struct DATA_DATA
{
	char szData[30];
}t_data;

typedef struct QUEST_IN_MAP
{
	char	name[21];
	int		iMapnumber;
	int		iQuestInfo;

}t_quest_in_map;

typedef struct SHOW_COLOR_MSG
{
	int		R;
	int		G;
	int		B;
	char	szMsg[0xff];
	int		iMsgNum;	//���߿� ���ڿ� ��� ��ȣ�� �������� ������.
}t_show_msg;

typedef struct SCRIPT_TIMER
{
	DWORD	dwTime;
}t_script_timer;

typedef struct SCRIPT_COUNTER	//�������� ���̾������ؼ�
{
	int iNum;
	int	iType;
	int iMuch;
	int iCounter;
}t_script_counter;

typedef struct DB_FIELD_TYPE
{
	int iType;
	int iData;
	char szData[48];
	int iBufferSize;
}t_field_type;

/*
typedef struct SCRIPT_DATA
{
	t_script_counter 
};
*/

//table type
typedef struct QUEST_IN_MAP_TABLE
{
	int		quest_num;
	int		map_num;

}table_quest_in_map;

typedef struct QUEST_INFO_BYMAP_TABLE
{
	int		quest_num;
	int		begin_step;
	int		end_step;
	int		quest_info;

}table_quest_info_bystep;

typedef struct REUITAL_LIST_TABLE
{
	int		Map_num;
	int		Npc_index;
	int		Quest_no;
	int		Quest_step;
	int		Item_no;
	int		Item_rare_type; //0,1,2
	int		Item_rare_count;
	int		Item_Min;
	int		Item_Max;
	int		Real_Fame;
	int		Dual_Fame;
	int		Tile_area;
	int		WarStatus;	// BBD 040318
	int		Sardonyx;		// BBD 040329
	int		LeafOfBlessed;	// BBD 040329
	int		ref_index;		// BBD 040329

}table_requital_list;

//<! BBD 040329
typedef struct REUITAL_ITEM_TABLE
{
	int index;
	int count;
	int rate;
	int item_no[5];
	int grade;
	int kind1;
	int kind2;
	int kind3;
	int IsDynamic;
	int HighRare;
}table_requital_Item;
//> BBD 040329

//<! BBD 040329		�߿� �������� ID�� ������ �ص���
#define SARD_ID								1046
#define LEAFBLESS_ID						1047
//> BBD 040329

typedef struct SCRIPT_SPELLMAPMOVE // 021128 kyo
{
	int cn;
	int	iX;
	int iY;
	char szMap[20];
	char szSpell[128];
	int isSuc;
}t_script_spellmapmove;
//extern void SendWhatQuestInMap( int iMapNum, int cn);

extern void CheckSpellMapMoveArea( char *szMsg, int cn);

#endif //_NETWORK7_H_