#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sqlext.h>
#include <winerror.h>
#include <crtdbg.h>

#define _NATION_APPLY_

#define ATTACKPOWER_PRO_	140
#define GET_EXP_PC_AND_PC_	30// PC������ ����ġ�� NPC�� ���� ��� ��ġ�� �Ʒ���ġ�� ������ �ش�. ( �ǰ� �ɱ��ش�. )
#define ULTRA_PK_NUM_		100// �ؾ�PK�ΰ�� �Ʒ� ��ġ�� �ѰԵǸ� name_status.ultra_pk == 1�̵ǰ� ������ ���ϰ� �ȴ�. 

///////////////////////////////////////////////////////////////////////////////
//< CSD-030517
const int Num_Of_Effect = 700;
const int Num_Of_Magic = 251;
const int Num_Of_NPC_Type = 100;
const int Num_Of_NPC_Lev = 256;
const int Num_Of_NPC_Name = 7932;
const int Num_Of_NPC_Generation	= 398;

const int MAX_LOG_TYPE = 4;     // CSD-TW-030622
const int MAX_COMBAT_LEVEL = 3; // CSD-TW-030622
const int MAX_NATION = 7;
const int MAX_AREA_BUFFER =	1000;
const int MAX_MAUL = 10;
const int MAX_MAP_IN_MAUL = 20;
const int MAX_GAMBLE_ITEM_KIND = 8;
const int MAX_GAMBLE_ITEM_TYPE  = 7;
const int MAX_GUARDIAN_GUILD = 3;
const int MAX_MAXIMUM_NUMBER = 24; // CSD-TW-030704
const int MAX_CDUNGEONBASIC_INT = 6; // CSD-030723
const int MAX_PARTY_MEMBER = 6; // CSD-030723
const int MAX_SKILL_NO	= 200; // CSD-030723
const int MAX_DIR_TABLE = 256; // CSD-030723
const int MAX_SHORTPATH = 100; // CSD-030723 // LTS AI
const int MAX_LEARN_ITEM = 1000; // CSD-030723
const int MAX_PC_CONTROL_NPC = 32; // CSD-030723
const int MAX_CLASS = 5; // CSD-030723
const int MAX_RESIST_TYPE = 6; // CSD-030723
const int MAX_GENERATE_POSITION_ = 100; // CSD-031106
const DWORD MAX_BANK_MONEY = 4000000000; // CSD-030723
//< CSD-030723
const double HT_NORMAL_CHANGE_VALUE = 0.003;	//������ ������ ���� ��
const double HT_WALK_CHANGE_VALUE = 0.013;	//�ǽ���� ������
const double HT_RUN_CHANGE_VALUE = 0.030;	//�ǽ���� �۶�
const double HT_BATTLE_WALK_CHANGE_VALUE = 0.020;	//��Ʋ��� ������
const double HT_BATTLE_RUN_CHANGE_VALUE = 0.040;	//��Ʋ��� �۶�
const double HT_ATTACK_CHANGE_VALUE = 0.030;	//�������ݽ�
const double HT_MAGIC_CHANGE_VALUE = 0.030;	//��������
const double HT_SKILL_CHANGE_VALUE = 0.050;	//������
// �׾����� �� 5�ʸ��� Check�Ѵ�. 
const int DEAD_CHARACTER_CHECK_TIME = 5;
// �������� ���ðų�, Ghost�� �ٲ�� �ð��� ���Ѵ�. 
// ������ DEAD_CHARACTER_CHECK_TIME(��)�̴�. 
const int DEAD_PC_COUNT_ = 65;
const int DEAD_NPC_COUNT_BOTTOM_ = 5; // NPC : ((DEAD_PC_COUNT_ - DEAD_NPC_COUNT_BOTTOM_ ) * DEAD_CHARACTER_CHECK_TIME )�ʰ� ��ü�λ��°� ���ӵȴ�. 
const int DEAD_PC_COUNT_BOTTOM_ = DEAD_PC_COUNT_ - 5;	// PC�� ��ü�λ��¸� (5 * DEAD_CHARACTER_CHECK_TIME)�ʰ��� ���ӵȴ�. 
const int DEAD_NPC_ANIMAL_COUNT_ = 25;
const int DEAD_NPC_HUNT_MONSTER_COUNT_ = 6; // CSD-040407
const int DEAD_NPC_MONSTER_COUNT_ = 15;
const int DEAD_SEALSTONE_COUNT_ = (2*60*60)/5;		// LTS NEW LOCALWAR
//> CSD-030723
const int CIB_POTION_BOX = 70; // CSD-030723
const int LOTTO_PAY = 20000; // CSD-TW-030704 : �ζ� ���� ���
const int GUILD_WEAR01	   = 102; // ��Ű�� ��庹

const int PS_EXP		= 10;  // �׳� ����ġ
const int PS_TACTIC	= 20;  // ��ƽ ����ġ
const int PS_MAGIC_TAC	= 30;  // ���� ��ƽ ����ġ
const int NO_TAC		= 13;  // ������ ���Ǵ� ��ƽ��
const int ULTRA_NK     = 100; // Ultra NK ��ġ
const int ENABLE_DUMMY_LEVEL = 10; // CSD-030806
const int ENABLE_DUEL_LEVEL = 10; // CSD-030806
const int ENABLE_GM_LEVEL = 20; // CSD-030806
const int ENABLE_NATIONWAR_LEVEL = 10; // CSD-030806
const int ENABLE_PARTY_LEVEL = 35; // CSD-030806
const int ENABLE_FREE_LEVEL = 50; // CSD-030806
const int ENABLE_HOMETOWN_LEVEL = 20; // CSD-030806
const int BUILD_GUILD_LEVEL = 40; // CSD-030806
const int CROSSING_CLASS_LEVEL = 101; // CSD-030806

enum LOG_TYPE 
{
	LT_ACCELATER = 0,
	LT_BATTLE = 1,
	LT_CHANGE = 2,
	LT_CHECK = 3,
	LT_LEVEL_UP = 4,
	LT_NORMALCHAT = 5,
	LT_SCRIPT	= 6,	// 030826 kyo
	LT_AUCTION	= 7,	// BBD 040226
	LT_EVENTITEM = 8,	// BBD 040308
	LT_LOCAL_WAR = 9,   // CSD-040407
	LT_DUPE = 10,		// Thralas
	LT_TELEPORT = 11,	// Finito
	LT_ETC = 12,
	LT_EARCHAT = 13,	// Finito
	LT_ATTACKRANGE = 14, // Finito 25/08/07
	LT_TIMECHECKS = 15, // Finito 25/08/07
	LT_TILECHECKS = 16, // Finito 26/08/07
	LT_GUILDCHAT = 17, // Finito 18/09/07
	LT_PARTYCHAT = 18, // Finito 18/09/07 
	LT_COLOSSUSCHAT = 19, // Finito 18/09/07 
	LT_VENDOR = 20, // Rogerio
	LT_HACK = 21, // Rogerio 
	LT_MANTLEDYE = 22, // Finito
	LT_NATIONTRANSFER = 23, // Finito 12/06/09
	LT_SEXCHANGE = 24, // Finito 12/06/09
	LT_TACTICUP = 25, //Eleval 15/08/09 - Log when Tactic Level Up >= 100
	LT_NEONATIONWAR = 26,					// 1.04 �ű� �������� ���� �α�
	LT_MOVETOWARFIELD = 27,					// 1.04+ ��ȭ �Ⱓ ������ �̵� ���� �α�
};
enum NEO_NATIONWAR_TYPE
{ // 1.04 �ű� �������� ���� �α� ����
	NNT_TIME_INFO = 0,			// �ð� ���� ����
	NNT_STATE_INFO = 1,			// ���� ���� ����
	NNT_FAME_INFO = 2,			// Fame ���� ����
	NNT_CHARACTER_INFO = 3,		// Character ���� ����
	NNT_WAR_INFO = 4,			// ���� ���� ����
};

enum MOVE_TO_WARFIELD_TYPE
{ //1.04p ��ȭ�Ⱓ ������ �̵� ���� �α� ����
	MTWT_GUARD_INFO = 0,		// ���� ���� ����
	MTWT_STATE_INFO = 1,		// ���� ���� ����
	MTWT_MONSTER_INFO = 2,		// ������ ���� ���� ����
	MTWT_CHARACTER_INFO = 3,	// Character ���� ����
};

//<! BBD 040308 �̺�Ʈ ������ �α� Ÿ��
enum EVENTITEM_LOG_TYPE
{
	// EILT = Event Item Log Type
	EILT_INVALID_CONNECTION = 0,		// �ܳؼ��� ��������
	EILT_INVALID_NAME = 1,				// �̸��� �ٸ���
	EILT_NOTENOUGH_INVENTORY = 2,		// ��û�� ���� �κ��� ä����.
};
//> BBD 040308 �̺�Ʈ ������ �α� Ÿ��

//<! BBD 040226 ���Ƿα� Ÿ��
enum AUCTION_LOG_TYPE
{
	// �ŷ��� ������ ����ɶ��� �αװ� ���ܾ� ��
	ACLT_SELLER_REGIST = 0,			// �Ĵ� ���� ����Ҷ� ����� �α�
	ACLT_SELLER_CANCLE = 1,			// �Ĵ� ���� ����Ҷ� ����� �α�
	ACLT_BUYER_TAKE = 2,			// ��� ���� ������ ���������� �ŷ��� ����ɶ� ����� �α�
	ACLT_SELLER_TAKE = 3,			// �Ĵ� ���� ����� ȸ�������� �ŷ��� ����ɶ� ����� �α� 
};
//> BBD 040226 ���Ƿα� Ÿ��

enum DAY_TYPE
{	//< CSD-030804
	SUNDAY = 0,
	MONDAY = 1,
	TUESDAY = 2,
	WEDNESDAY = 3,
	THURSDAY = 4,
	FRIDAY = 5,
	SATURDAY = 6
};	//> CSD-030804

enum NATION_TYPE
{	
	N_NEUTRAL = 0,
	N_NONSTER = 2,
	N_VYSEUS = 3,
	N_ZYPERN = 4,
	N_HEGEMONIA = 5,
	N_YLLSE = 6,
	N_NATION_ALL = 7
};

enum HOUSE_TYPE
{	//< CSD-030723
	BLACKSMITH = 0,	 // ���尣
	FARM = 1,		 // ����
	RESTAURANT = 2,	 // ������
	HERBSHOP = 3,	 // ������
	SHAMBLES = 4,	 // Ǫ�ְ�
	CANDLE = 5,		 // ������
	SLOPSHOP = 6,	 // �ʰ��� 
	ALCHEMY = 7,	 // Ȱ ȭ��
	WOODWORKING = 8, // �����
	BOWCRAFT = 9,	 // Ȱ ȭ��
	SHIPYARD = 10,	 // ������
	PUB = 11,	     // ����
	HOSPITAL = 12,	 // ����
	STORE = 13,		 // ��ȭ��
	INN = 14,		 // ����
	MAGIC_GUILD = 15,
	STORE_TOTAL = 17
};	//> CSD-030723

enum LIFE_TYPE
{	//< CSD-030723
	REMOVE_ = 0,
	ALIVE_ = 1,	
	DEAD_ = 2,
	BUFE_ = 3
};	//> CSD-030723

enum NK_TYPE
{	
	NK_TYPE_STEAL_ = 0,
	NK_TYPE_KILL_ = 1,
	NK_TYPE_NO_KILL_ = 2
};

enum CLASS_TYPE
{	//< CSD-030723
	WARRIOR	= 0,
	THIEF = 1,
	ARCHER = 2,
	WIZARD = 3,
	PRIEST = 4,
	CREATURE = 5
};	//> CSD-030723

enum CHAR_STATUS_TYPE
{	//< CSD-030723
	CS_NOMAL = 0,	// ���� ����
	CS_REST = 1,	// �޽� ����
	CS_SLEEP = 2	// ���� �ڱ� ����
};	//> CSD-030723

enum VIEW_TYPE
{	
	VIEWTYPE_NORMAL_ = 0,
	VIEWTYPE_CAMELEON_ = 1,
	VIEWTYPE_GHOST_	= 2,
	VIEWTYPE_TREE_	= 3,
	VIEWTYPE_OBSERVE_ = 4,
	VIEWTYPE_CONFUSION_	= 5,
	VIEWTYPE_POISON_ = 6,
	VIEWTYPE_STONE_	= 7,
	VIEWTYPE_SLOW_ = 8,
	VIEWTYPE_FROZEN_ = 9,
	VIEWTYPE_CURSE_	= 10,
	VIEWTYPE_TRANSPARENCY_ = 11,
	VIEWTYPE_SELECT_ = 12,
	VIEWTYPE_STAND_UP_ = 13
};

enum CONDITION_TYPE
{	//< CSD-030723
	CON_NORMAL = 0x00,	// ������ ����	 00000000
	CON_CURSE = 0x01,	// ������ ����	 00000001
	CON_FROZEN = 0x02,	// �õ��� ����   00000010
	CON_SLOW = 0x04,	// ������ ����   00000100
	CON_DAZE = 0x08,	// ȥ���� ����	 00001000
	CON_POISON = 0x10,	// �ߵ��� ����	 00010000
	CON_STONE = 0x20,	// ��ȭ�� ����	 00100000
	CON_DEATH = 0x40,	// ������ ����	 01000000
	CON_DARKNESS = 0x80 // ����� ����   10000000
};	//> CSD-030723

enum HUNGRY_TYPE
{	//< CSD-030723
	HT_NORMAL = 0, // (-(HT_WALK * 40.))
	HT_WALK = 1,
	HT_RUN = 2,
	HT_BATTLE_WALK = 3,
	HT_BATTLE_RUN = 4,
	HT_ATTACK = 5,
	HT_MAGIC = 6,
	HT_SKILL = 7,
	HT_COMBAT = 8
};	//> CSD-030723

enum DIRECTION
{	//< CSD-030723
	DIRECTION_SAME = 0,
	DIRECTION_UP = 4,
	DIRECTION_RIGHTUP = 5,
	DIRECTION_RIGHT	= 6,
	DIRECTION_RIGHTDOWN	= 7,
	DIRECTION_DOWN = 0,
	DIRECTION_LEFTDOWN = 1,
	DIRECTION_LEFT = 2,
	DIRECTION_LEFTUP = 3	
};	//> CSD-030723

enum HIT_TYPE
{ 
	HIT_FAILED = 0,
	HIT_AND_DEAD = 1,
	HIT_AND_NOTDEAD = 2,
	HIT_AND_ALIVE = 3,
	HIT_GHOSTRESURRECTION = 4,
	HIT_SUMMONING = 5
};

enum RESIST_TYPE
{	//< CSD-030723
	RESIST_UNKNOWN = 0,
	RESIST_FIRE = 1,
	RESIST_ICE = 2,
	RESIST_ELECT = 3,
	RESIST_POISON = 4,
	RESIST_CURSE = 5,
	RESIST_HOLY = 6,
	RESIST_IGNORE = 7
};	//> CSD-030723

enum eRESIST_TYPE
{
	RT_POISON	=0,
	RT_CURSE	=1,
	RT_HOLY 	=2,
	RT_FIRE		=3,
	RT_ICE		=4,
	RT_ELECT	=5
};

enum TACTIC_TYPE
{ 
	CRAPPLE_ = 0,
	SWORD_ = 1,
	ARCHERY_ = 2,
	FENCING_ = 3,
	MACE_ = 4,
	PIERCE_ = 5,
	WHIRL_ = 6,		
	HURL_ = 7,
	PARRYING_ = 8,
	D_SWORD_ = 9,
	D_MACE_ = 10,
	MAGERY_ = 11,
	ORISON_ = 12
};

enum JOB_TYPE
{	//< CSD-030723
	J_FAMER = 20,
	J_MINNER = 21,
	J_FISHER = 22,
	J_LUMBERJACK = 23,
	J_BUTCHER = 24,
	J_HERB_DIGGER = 25,
	J_HERDSMAN = 26,
	J_CARPENTER = 27,
	J_BLACKSMITH = 28,
	J_COOKER = 29,
	J_TAILOR = 30,
	J_BOWCRAFT = 31,
	J_ALCHEMIST = 32,
	J_CANDLEMAKER = 33,
	J_MERCHANT = 34
};	//> CSD-030723

enum MAGIC_TYPE
{ 
	MT_PROTECTION = 2,
	MT_ASSISTANCE = 3,
	MT_CURSE = 4
};

enum CHAR_STEP_TYPE
{	//< CSD-TW-030620
	CLS_STEP = 0,  // ��� Ŭ���� �ܰ�
	DUAL_CLS = 1,  // ��� Ŭ���� ����
	EXP_STEP = 2,  // ����ġ �ܰ�
	T01_STEP = 3,  // ��ƽ ����ġ �ܰ�
	T02_STEP = 4,
	T03_STEP = 5,
	T04_STEP = 6,
	T05_STEP = 7,
	T06_STEP = 8,
	T07_STEP = 9,
	T08_STEP = 10,
	T09_STEP = 11,
	T10_STEP = 12,
	T11_STEP = 13,
	T12_STEP = 14,
	T13_STEP = 15,
	CSP_STEP = 16, // ������ų ������
	MAX_STEP = 17  // �ִ� ����Ÿ��
};	//> CSD-TW-030620

enum WEAPON_RANGE_TYPE
{	//< CSD-031007
	WR_SHORT = 0,
	WR_MIDDLE = 1,
	WR_LONG1 = 2,
	WR_LONG2 = 3,
	WR_LONG3 = 4,
	WR_EFFECT = 5
};	//> CSD-031007

enum BATTLE_TYPE
{	//< CSD-031007
	// ������ ���� 
	PHYSICAL = 0,                  
	// ����
	LIFE_UP = 1,                   // ü��ȸ�� 
	PROTECTION = 2,                // ��ȣ
	SHIELD = 3,                    // ��ȣ��
	DECIPHER = 4,                  // �ص� ����
	HEAL_DISEASE = 5,              // ����ġ��
	GREAT_HEAL = 6,                // ��ü��ȸ��
	SLOW = 10,                     // �ӵ�����
	CONFUSION = 11,                // ȥ��
	INTOXICATION = 12,             // �ߵ�
	STONELY =	13,                // ��ȭ
	ABSOLUTE_PARALYSIS = 14,       // ���븶��
	TOXIC_CLOUD = 15,              // ������  
	DISEASE_INDUCE = 16,           // �������� 
	VAMPIRE_TOUCH = 17,            // �����̾��� �ձ�
	SPIDER_WEB = 19,               // �Ź���  
	MAGICAL_TRAP = 20,             // ����Ʈ��
	ENCHANT_WEAPON = 21,           // ��þƮ����
	TRANSPARENCY = 22,             // �����ֹ�
	NULLITY_MAGIC = 24,            // ������ȿȭ  
	MINOR_AMPLIFY = 25,            // ������
	MAGIC_AMPLIFY = 26,            // ��������
	FIRE_RESIST = 28,              // �ҿ� ���� ����  
	FIRE_ARROW = 29,               // ȭ��ȭ�� 
	FIRE_BALL= 30,                 // ȭ����
	SCORCHER = 31,                 // ȭ����(ȭ�����)
	CIRCLE_FLAME= 33,              // ���ȭ��
	FIRE_WALL = 34,                // ȭ����
	FLAME_WAVE = 35,               // �����̴� ȭ����
	APOCALYPSE = 36,               // ������ ��
	ICE_RESIST = 37,               // ���� ����
	ICE_ARROW = 38,                // ����ȭ��
	ICE_BALL = 39,                 // ������ 
	FREEZE_5TILE_RADIUS = 41,      // �ݰ� 5Ÿ�� ��	
	ICE_WALL = 42,                 // ������  	
	CIRCLE_ICE = 43,               // �������� ����
	ICE_STORM = 44,                // ������ǳ
	FREEZE_9TILE_RADIUS = 45,      // �ݰ� 9Ÿ�� �󸮱�	
	LIGHT = 46,                    // ��
	ELECT_RESIST = 47,             // ���ݿ� ���� ����
	LIGHTNING_BOLT = 48,           // ����
	CHAIN_LIGHTNING = 50,          // ���� ����
	CIRCLE_LIGHTNING = 51,         // ���� ���� 
	LIGHTNING = 52,                // ���� ����
	TWINKLE_STAR = 53,             // ��ȣ��
	LIGHTNING_5TILE_RADIUS = 54,   // �ݰ� 5Ÿ�� ����
	LOW_MONSTER_RECALL = 55,       // ���� ���� ��ȯ
	MIDDLE_MONSTER_RECALL = 58,    // �߱� ���� ��ȯ
	SNOWSTORM	= 59,			   // �������� ��ǳ
	ICE_BREATH2	= 60,			   // ���̽� �극��2
	BLOOD_LIGHTNING = 61,		   // ���� ����Ʈ��
	PHASING = 64,                  // ����̵�
	MEMORIZING_LOCATION = 65,      // �̵���ұ��
	TELEPORT = 66,                 // �����̵�
	MULTI_PORT = 67,               // ���������̵�
	TOWN_PORTAL = 68,              // �����̵�
	MAGIC_DETECT = 75,             // ����Ž��
	REMOVE_CURSE = 78,             // ��������
	PROTECT_RANGE_WEAPON = 79,     // ��Ÿ� ����κ��� ��ȣ
	PHEONIX = 80,				   // �һ�
	METEOR_STRIKE = 81,			   // � // 030509 kyo //030506���� 110
	LOST_SIGHT = 82,               // �÷»��   
	SPEED_UP = 83,                 // �ӵ�����
	GREAT_THUNDER_BOLT = 84,       // ������
	GREAT_METEOR = 85,             // �� 
	DRAGON_SCALE = 86,             // �巡���� ���
	DEATH_FIRE = 87,               // �������̾�
	SUMMONING_SKELETON = 88,       // ��������Ʈ ��ȯ
	FLYING_SPARK = 89,             // �ö��� ����ũ
	VAMPIRE_POISON = 90,           // �����̾��� ��
	VAMPIRE_DODGE = 91,            // �����̾� ȸ��
	SUMMONING_UNDEAD = 92,         // �𵥵� ��ȯ
	FEATHER_OF_CURSE = 93,         // ������ ����
	CURSE_OF_HELL = 94,            // ���� ����
	RECALL_FOLLOW = 95,            // ���� ��ȯ
	FIRE_EXPLOSION = 96,           // ȭ������
	FIRE_STORM = 97,               // ���̾��
	SHADOW_OF_EVIL = 98,           // ���� �׸���
	FREEZING = 99,                 // ���� ��
	BLITZ_SPEAR = 100,             // ����â
	LIGHTNING_CLOUD = 101,         // ���� ����
	FIRE_BREATH = 102,             // ȭ�� �극��
	ICE_BREATH = 103,              // ���� �극��
	LIGHTNING_BREATH = 104,        // ���� �극��
	FLAME_PILLAR = 105,            // ȭ�� ���
	FLAME_POUR = 106,              // ȭ�� ��ǳ 
	OCTA_LIGHTNING = 107,          // ��� ����
	BLOOD_SPRINKLE = 108,          // �ǻѸ���
	GAZER	= 109,				   // ������
	FLAME_ARROW = 110,             // ȭ��ȭ�� 

	AREA_BAT_ATTACK = 111,         // ���� �������
	AREA_PARALYSIS = 112,          // ���� ����
	AREA_POISON = 113,             // ���� �ߵ�
	AREA_CONFUSION = 114,          // ���� ȥ��
	AREA_SLOW = 115,               // ���� �ӵ�����

	RESTORE_AUTHORITY = 151,       // ȸ���ǱǴ�  
	PROTECT_DANGER = 152,          // �������κ��� ��ȣ
	BLESS = 153,                   // ���� �ູ
	RECOVER_POISON = 154,          // �ص��� �Ǵ�
	CURE_DISEASE = 155,            // ����ġ���� �Ǵ�
	MIRACLE_RECOVER = 156,     	   // ��ġ�� ����
	PERFECT_PROTECT = 157,         // ������ ���  
	GREAT_SHIELD = 158,            // ��ȣ�� ����
	CANCEL_DIVINE = 159,           // �ݽŷ� ��ȿȭ
	RECURRENCE_DIVINE = 160,       // ȸ���� �Ǵ�
	PRAY_POWER = 161,              // �⵵�� ����
	HOLY_LIGHT = 162,              // �������� ��  
	ANTHEM = 163,                  // ����
	RELIEF_AUTHORITY = 164,        // ������ �� 
	HOLY_FIRE = 165,               // �������� ��
	GREAT_PRAY = 166,              // ������ �⵵  
	APPRECIATE = 167,              // �ٸ� ������
	INFLUENCE_DIVINE = 168,        // �ſ��� ��ȭ
	VOICE_SOUL = 169,              // ��ȥ�� �Ҹ�
	HOLY_RAGE = 170,               // ������ �г�
	TURN_UNDEAD = 171,             // �� �𵥵�
	CURSE = 172,                   // ���� ���� 
	AUTHORITY_RECOVER_SIGHT = 173, // �÷�ȸ���� �Ǵ�	
	DIVINE_POWER = 174,            // ����� �Ŀ�
	AUTHORITY_LUCK = 175,          // ���� ����� �Ǵ�	
	AUTHORITY_LOST_SIGHT = 177,    // �÷»���� �Ǵ�
	PRAY = 178,	                   // �⵵
	HOLY_CURE = 179,               // �ż��� ġ��
	AUTHORITY_SIMUNIAN = 181,      // �ù��Ͼ��� �Ǵ�
	AUTHORITY_CHARISNUMEN = 182,   // ī���� ������ �Ǵ�
	AUTHORITY_LETHY = 183,         // ��Ƽ�� �Ǵ�
	AUTHORITY_OF_ATHYAS	= 185,     // �ƻ����� �Ǵ�
	AUTHORITY_OF_WHOARENCHA	= 187, // ȭ������ �Ǵ�
	RAGE_STONE = 189,              // ������ �г�
	LIFE_DRAIN = 190,              // ����� Ż��  
	RAGE_BLAST = 191,              // ȭ���� �г�
	RAGE_LIGHT_BALL = 192,         // ������ �г�
	THROW_ARROW = 194,             // ȭ��
	THROW_KNIFE = 195,             // ��
	// ���� �Ӽ� ������ų
	LIGHTNING_BOOM = 215,          
	THUNDER_BLOW = 216,
	LIGHTNING_SHOCK = 217,
	THUNDER_STRIKE = 218,
	LIGHTNING_SHIELD = 219,
	LIGHTNING_EXTREME = 220,
	// ���� �Ӽ� ������ų
	BLOOD_EARTH = 221,             
	GROUND_ATTACK = 222, 
	BLOOD_WILL = 223,
	STONE_ARMOR = 224,
	SIMUNIAN_BOSOM = 225,
	EARTH_EXTREME = 226,
	// ȭ�� �Ӽ� ������ų 
	SWORD_N_ROSES = 227,
	MULTIPLE_FIRE = 228, 
	FLEET_MISSILE = 229,
	CONVERTING_ARMOR = 230, 
	BURNING_BLOODY= 231,
	FIRE_EXTREME = 232,
	// ��� �Ӽ� ������ų
	POISONING_NOVA = 233,
	CHERROY_SHADE = 234, 
	DARK_BLADE = 235, 
	TYBERN_GIFT = 236,
	ACUQUIRE_DARK = 237,
	DARK_EXTREME = 238,
	// ���� �Ӽ� ������ų
	ICING_BLAST = 239,
	CRITICAL_HIDING = 240, 
	SHARK_MISSILE = 241, 
	HORN_OF_ICEBERG = 242, 
	ICE_SHIELD = 243,
	ICE_EXTREME = 244,
	// �ٶ� �Ӽ� ������ų
	CHARGING = 245,
	DOUBLE_ATTACK = 246, 
	WHILWIND = 247,
	TWISTER = 248, 
	GUST = 249, 
	WIND_EXTREME = 250,
	// ����Ʈ ������
	ITEM_FIRE_EFFECT = 610, // CSD-030916
	ITEM_ICE_EFFECT = 611, // CSD-030916
	ITEM_LIGHTNING_EFFECT = 612, // CSD-030916	
	// �̺�Ʈ
	THROW_SNOW = 193,
	THROW_WATER_BALL = 661,
	THROW_BIG_GULP = 663,
	// ������ ȿ��
	ITEM_EFFECT_FIRE = 605,
	ITEM_EFFECT_ICE = 606,
	ITEM_EFFECT_LIGHTNING = 607
};	//> CSD-031007

enum COMBAT_RESULT
{
	CSR_NORMAL,    // �������� ����
	CSR_PRIOR,     // ���а��迡�� ��
	CSR_POSTERIOR, // ���а��迡�� ��
	CSR_CONFLICT,  // �븳���� ����
	CSR_EQUAL      // ������ ����
};

enum VEHICLE_KIND
{
	HORSE = 1,  // ��
	BULL = 2,   // Ȳ��
	PHANTOM = 3 // ����
};

enum NPC_KIND
{	//< CSD-TW-030606
	DUMMY = 0,
	HUMAN = 1,
	GUARD = 2,
	ORC_DUMMY = 3,
	LIFELESS = 4,
	HOBBIT = 5,
	DWARF = 6,
	DRAGON = 7,
	ANIMAL = 8,
	NORM_MON = 9,
	SEALSTONE = 11,
	GUARDSTONE = 12,
	//CASTLEGATEWAY = 12
	//WARARMS = 12
};	//> CSD-TW-030606

enum ATTR_TYPE
{	//< CSD-031027
	AT_NORMAL = 0,
	AT_FIRE = 1,
	AT_ICE = 2,
	AT_LIGHTING = 3,
	AT_UNDEAD = 4,
	AT_PIERCING = 5,
	AT_ANTIMAGIC = 6,
	AT_BOSS = 7,
	AT_SUMMON = 8,
	AT_TAMING = 9,
	AT_SEMIBOSS = 10
};	//> CSD-031027

enum NPC_PARAMETER_TYPE
{	//< CSD-031106 : Client���� ��ȭ�� NPC �Ķ���͸� Server�� �����ش�. 
	NPC_PARAMETER_TARGETID = 0,
	NPC_PARAMETER_TARGETNAME = 1,
	NPC_PARAMETER_BOSSID = 2,
	NPC_PARAMETER_HOSTID = 3,
	NPC_PARAMETER_TAME_CMD = 4,
	NPC_PARAMETER_PATTERNTYPE = 5,
	NPC_PARAMETER_OLDPATTERNTYPE = 6,
	NPC_PARAMETER_ATTRIBUTE = 7
};	//> CSD-031106

enum ARENA_TYPE
{
	AT_UNKNOWN = 0,
	AT_CORE = 1,
	AT_STONE = 2,
	AT_MONSTER = 3,
	AT_LMS = 4
};

enum ARENA_STATE
{
	CS_NOW_PEACE	= 0, // ��ȭ�ο� ����(����ʰ� �ٸ��� ���� ����
	CS_NOW_REGISTER	= 1, // ���� ���� ����ϴ� ����. 
	CS_NOW_FIGHT	= 2  // ���� ���� ����
};

enum ARENA_RESULT
{
	FST_WIN = 0,
	FST_DEFEAT = 1,
	FST_DISCONNECT = 2
};

enum ARENA_ITEM
{
	GT_RESOURCE = 5,
	GT_ARENA_LOW = 6,
	GT_ARENA_HIGH = 7
};
//> CSD-030517
///////////////////////////////////////////////////////////////////////////////

struct AREA
{	
	BOOL	  bAlive;
	short int Type;
	short int ID;
};

///////////////////////////////////////////////////////////////////////////////
//< CSD-030723
enum eBillingType
{	//-������ ���� �ؾ� �մϴ�. CheckPW_TotalDB_SQL�� ���� ��¥(���)�� �����ϱ� �����Դϴ�.
	BT_WRONG_ID					= -1,//ID Ʋ��
	BT_WRONG_PW					= -2,//PW Ʋ��

	BT_NEED_PAY					= -3,//�� ����

	BT_COMMERCIAL_TIME_REMAIN	= -4,//���� �ð� �ִ³�
	BT_COMMERCIAL_IP			= -20,//IP ������
	BT_FREE						= -100,//��¥
	BT_WAIT_BILLING_MSG			= -200,//�븸 ���� ���� ó�� ��� ������ ��ٸ����� ó��
};	//DBDemon�� �׻� ����ȭ ��Ű�ʽÿ�

enum eBankMoneyChangeType
{
	BMCT_ARENA_GAMBLE_DIVIDEND	=	1,
	BMCT_ARENA_GAMBLE_BETTING	=	2,
	BMCT_BANK_DEPOSIT			=	3,
	BMCT_BANK_DEFRAYAL			=	4,
	BMCT_AUCTION_ITEM_BUY		=	5,
	BMCT_AUCTION_ITEM_REGISTER	=	6,
	BMCT_BUY_LOTTO				=	7,
	BMCT_RESET_ABILITY			=	8,
	BMCT_CHAR_LOGIN				=	9,
	BMCT_RECV_MAP_CHANGE		=	10,
	BMCT_RECV_CHAR_INFO_BASIC	=	11,
	BMCT_SKILL_RESET			=	12,
};

enum eSendCharInfoType//021030 lsw 
{
	STR			=0,
	DEX			=1,
	CON			=2,
	WIS			=3,
	INT_		=4,
	CHA			=5,
	MOVP		=6,
	ENDU		=7,
	MOR			=8,
	WSPS		=9,
	LUCK		=10,
	HEALTH		=11,
	MOV			=12,
	AC			=13,
	FAME		=14,
	DAMAGE		=15,
	HIT			=16,
	TACTICS		=17,
	MONEY		=18,
	LVPOINT		=19,
	LEV			=20,
	EXP			=21,
	HP	  		=22,
	MAX_HP		=23,
	MP			=24,
	MAX_MP		=25,
	SP			=26,
	MAX_SP		=27,
	CP      	=28,
	MAX_CP  	=29,
	BP	    	=30,
	MAX_BP  	=31,
	R_FIR		=32,
	R_ICE		=33,
	R_ELE		=34,
	DAM_MIN		=35,
	DAM_MAX		=36,
	HIT_RAT		=37,
	DEF_RAT		=38,
	TAC_L1		=39,
	TAC_L2		=40,
	TAC_L3		=41,
	TAC_L4		=42,
	TAC_L5		=43,
	TAC_L6		=44,
	TAC_L7		=45,
	TAC_L8		=46,
	TAC_L9		=47,
	TAC_L10		=48,
	TAC_L11		=49,
	TAC_L12		=50,
	TAC_L13		=51,
	TAC_E1		=52,
	TAC_E2		=53,
	TAC_E3		=54,
	TAC_E4		=55,
	TAC_E5		=56,
	TAC_E6		=57,
	TAC_E7		=58,
	TAC_E8		=59,
	TAC_E9		=60,
	TAC_E10		=61,
	TAC_E11		=62,
	TAC_E12		=63,
	TAC_E13 	=64,
	BANKMONEY	=65,
	FAITH		=66,
	VIEWGHOST	=67,
	VIEWBOMB	=68,
	VIEWTRAP	=69,
};

enum eMkType//021030 lsw 
{
	MK_NORMAL      =0,	// �Ϲ����� ���
	MK_WARNING     =1,	// ����, ���
	MK_SHORTAGE    =2,	// ����
	MK_INFORMATION =3,	// ����
};

enum eSpriteType
{
	SPRITETYPE_NONE			=0,
	SPRITETYPE_CHARACTER	=1,
	SPRITETYPE_NPC			=2,
};
//Skill No
enum eSkillNoIndex
{
	SKILL_UNKNOWN							=0,	// 030117 kyo 
	SKILL_DETECT_GHOST						=1,	
	SKILL_TALK_WITH_GHOST					=2,	
	SKILL_POISONING							=3,	
	SKILL_DETECT_POISON						=4,	
	SKILL_FIND_TRAPS						=5,	
	SKILL_REMOVE_TRAPS						=6,	
	SKILL_ENTRAPMENT						=7,	
	//	SKILL_MAGIC_SCROLLING					=8,	
	//	SKILL_ABILITY_SCROLLING					=9,	
	//	SKILL_EMERGENCY_ALRAM					=10,	
	//	SKILL_FIRST_AID							=11,	
	//	SKILL_FAST_FOOT							=12,	
	//	SKILL_SECRETHEAR						=13,	
	//	SKILL_WALLCLIMBING						=14,	
	//	SKILL_INTUITION							=15,	
	SKILL_DETECT_BOMB						=16,	
	SKILL_BOMB_IN_BOX						=17,	
	SKILL_REMOVE_BOMB						=18,	
	SKILL_STEALING							=19,	
	//	SKILL_LOCKPICKING						=20,	
	SKILL_RECLAIM							=21,	
	SKILL_SOW								=22,	
	//	SKILL_CULTIVATE							=23,	
	SKILL_HAVEST							=24,	
	//	SKILL_DETECT_MINERAL					=25,	
	SKILL_MINING							=26,	
	SKILL_REFINE							=27,	
	SKILL_FISH_HOOKING						=28,	
	//	SKILL_BAITMAKING						=29,	
	SKILL_NETTING							=30,	
	//	SKILL_SAILING							=31,	
	SKILL_CUTTING							=32,	
	SKILL_LUMBERING							=33,	
	SKILL_BUTCHERING						=34,	
	//	SKILL_DETECT_HERB						=35,	
	SKILL_DIGGING							=36,	
	SKILL_MAKEPOWDER						=37,	
	//	SKILL_HERDING							=38,	
	//	SKILL_MILKING							=39,	
	//	SKILL_MIDWIFERY							=40,	
	SKILL_SHEAR								=41,	
	SKILL_CARPENTRY							=42,	
	SKILL_BLACKSMITHY						=43,	
	SKILL_COOKING							=44,	
	SKILL_CLOTHING							=45,	
	//	SKILL_DYEING							=46,	
	SKILL_TAILORING							=47,	
	SKILL_BOWCRAFTING						=48,	
	SKILL_FLETCHING							=49,	
	SKILL_MAKEPOTION						=50,	
	SKILL_MAKEMETAL							=51,	
	SKILL_MAKEBOTTLE						=52,	
	SKILL_CANDLEMAKING						=53,	
	//	SKILL_WAXING							=54,	
	//	SKILL_REPAIRNG							=55,	
	//	SKILL_REUTILIZING						=56,	
	//	SKILL_PLAYING							=57,	
	//	SKILL_PEACEMAKING						=58,	
	//	SKILL_PARALYSIS							=59,	
	//	SKILL_HALLUCINATION						=60,	
	//	SKILL_PROVOCATION						=61,	
	//	SKILL_ENTICEMENT						=62,	
	//	SKILL_NOISE								=63,	
	//	SKILL_TRACKING							=64,	
	SKILL_SNOOPING							=65,	
	//	SKILL_SEARCH							=66,	
	SKILL_MERCHANT							=67,	
	SKILL_BLACKSMITHY_MASTER				=68,	//�������� �⼺	
	SKILL_CARPENTRY_MASTER					=69,	//��� �⼺	
	SKILL_BOWCRAFTING_MASTER				=70,	//Ȱ���ۻ� �⼺	
	SKILL_TAILORING_MASTER					=71,	//��ܻ� �⼺
	//	SKILL_HIDE								=72,	
	//	SKILL_CAMPING							=73,	
	SKILL_MAKEFIRE							=74,	
	SKILL_TAMING							=75,	
	//	SKILL_COMMUNICATE_WITH_ANIMAL			=76,	
	//	SKILL_COMMUNICATE_WITH_OTHER_TRIBE		=77,	
	//	SKILL_ANIMAL_LORE						=78,	
	//	SKILL_ARMS_LORE							=79,	
	SKILL_EVALUATE_INTELIGENCE				=80,	
	SKILL_EVALUATE_WISDOM					=81,	
	SKILL_ANATOMY_JUDGEMENT					=82,	
	SKILL_ITEM_IDENTIFICATION				=83,	
	//	SKILL_TASTE_IDENTIFICATION				=84,	
	//	SKILL_APPRAISAL							=85,	
	//	SKILL_HEALING							=86,	
	SKILL_TACTICS							=87,//021113 lsw
	TACTICS_Crapple							=88,
	TACTICS_swordmanship					=89,
	TACTICS_Archery							=90,
	TACTICS_Fencing							=91,	
	TACTICS_Mace_fighting					=92,
	TACTICS_Pierce							=93,
	TACTICS_Whirl							=94,
	TACTICS_Hurl							=95,
	TACTICS_Parrying						=96,
	TACTICS_Double_Swordmanship				=97,
	TACTICS_Double_MaceFighting				=98,	
	TACTICS_Magery							=99,
	TACTICS_Orison							=100,
	//	SKILL_THREAD							=101,	
	//	SKILL_COLORING							=102,	
	//	SKILL_JUMP								=103,	
	//	SKILL_RIDING							=104,	
	SKILL_GHOST_RESURRECTION				=105,	
	SKILL_GM_CARPENTER						=106,	
	SKILL_GM_BLACKSMITH						=107,	
	SKILL_GM_COOK							=108,	
	SKILL_GM_TAILOR							=109,	
	SKILL_GM_BOWCRAFT						=110,	
	SKILL_GM_ALCHEMIST						=111,	
	SKILL_GM_CANDLEMAKER					=112,	
};
// ������ kind
enum eItemKindType
{
	IK_NONE							=0,	//	non
	IK_GON							=1,	//	��			
	IK_PENCING						=2,	//	��̰�		
	IK_ONE_SWORD					=3,	//	�Ѽհ�
	IK_ONE_AXE						=4,	//	�Ѽյ���
	IK_ONE_MACE						=5,	//	�Ѽ�ö��
	IK_CLUB							=6,	//	������
	IK_WHIRL						=7,	//	��
	IK_STAFE						=8,	//	������
	IK_SPEAR						=9,	//	����â
	IK_FORK							=10,	//	��ũ
	IK_HURL							=11,	//	���,�����¹���
	IK_SHORT_BOW					=12,	//	����Ȱ
	IK_TWO_SWORD					=13,	//	��հ�
	IK_TWO_AXE						=14,	//	��յ���
	IK_TWO_MACE						=15,	//	��� ö��
	IK_TWO_ARROW					=16,	//	ȭ��
	IK_IRON_ARMOR					=17,	//	�谩��
	IK_LEATHER_ARMOR				=18,	//	���װ���
	IK_RING							=19,	//	����
	IK_SHIELD						=20,	//	����
	IK_SHOES						=21,	//	�Ź�
	IK_ROBE							=22,	//	�κ�
	IK_FULL_HELMET					=23,	//	�����
	IK_HALF_HELMET					=24,	//	�������
	IK_NORMAL_CLOTHE				=25,	//	�����
	IK_AMULET						=26,	//	��Ÿ�
	IK_ARMLET						=27,	//	����
	IK_MUSIC						=28,	//	�Ǳ�
	IK_SCROLL						=29,	//	��ũ��
	IK_LONG_BOW						=30,	//	����Ȱ
	IK_BOX							=31,	//	����
	IK_GRAIN						=32,	//	���
	IK_POTION						=33,	//	����
	IK_FOOD_MASS					=34,	//	��� ����
	IK_PLATE_FOOD					=35,	//	��� ����
	IK_DRINK						=36,	//	����
	IK_ARROW_POINT					=37,	//	ȭ�� ��
	IK_FEATHER						=38,	//	����		
	IK_SEED							=39,	//  ����.
	IK_MONEY						=40,	//	��
	IK_MINERAL						=41,	//	����
	IK_MINERAL_LUMP					=42,	//	������ ����( ö��, �ݱ�... )
	IK_HERB							=43,	//	����					// 0626 YGI
	IK_HERB_POWDER					=44,	//	���� ����
	IK_WOOD_BEFOR_USE				=45,		//�������� ����
	IK_WOOD_AFTER_USE				=46,		//�������� ����
	IK_TENT							=47,		//��Ʈ��
	IK_TOOL_RECLAI					=48,		//���� ������
	IK_TOOL_HAVEST					=49,		//���� �߼���
	IK_TOOL_MINING					=50,		//���� ä����
	IK_TOOL_REFINE					=51,		//���� ���ÿ�
	IK_TOOL_FISH_HOOKING			=52,		//���� ���ÿ�
	IK_TOOL_CUTTING					=53,		//���� �����
	IK_TOOL_LUMBERING				=54,		//���� ���簡����
	IK_TOOL_BUTCHERING				=55,		//���� �����
	IK_TOOL_DIGGING					=56,		//���� ����ä����
	IK_TOOL_MAKEPOWDER				=57,		//���� ���縸����
	IK_TOOL_SHEAR					=58,		//���� ������
	IK_TOOL_CARPENTRY				=59,		//���� �����
	IK_TOOL_BLACKSMITHY				=60,		//���� ö����
	IK_TOOL_COOKING_FIRE			=61,		//���� ���¿丮��
	IK_TOOL_COOKING_CUT				=62,		//���� ��¿丮��
	IK_TOOL_PIN						=63,		//���� �ٴ÷�
	IK_TOOL_BOWCRAFTING				=64,		//���� Ȱ���ۿ�
	IK_TOOL_FIRE_BOAD				=65,		//���� �Ҵ�
	IK_TOOL_CANDLEMAKING			=66,		//���� �������ۿ�
	IK_TOOL_OILING					=67,		//���� �г�������
	IK_TOOL_TAMING					=68,		//���� ���ֿ̹�
	IK_TOOL_NETTING					=69,		//���� �׹���
	IK_TOOL_MAKEFIRE				=70,		//���� �ν˵���
	IK_WORK_BOAD_BLAST_FURNACE 		=71,		//�۾��� �뱤��
	IK_WORK_BOAD_BAETLE				=72,		//�۾��� ��Ʋ
	IK_WORK_BOAD_BLOCK				=73,		//�۾��� ����
	IK_WORK_BOAD_ANVIL				=74,		//�۾��� ���
	IK_WORK_BOAD_BRAZIER			=75,		//�۾��� ȭ��
	IK_WORK_BOAD_TEST_TUBE			=76,		//�۾��� �������
	IK_WORK_BOAD_SPINNING_WHEEL		=77,		//�۾��� ����
	IK_WORK_BOAD_FIRE_BOAD			=78,		//�۾��� �Ҵ�
	IK_TOOL_BUCKET					=79,		//���� �絿��
	IK_TOOL_RECYCLE					=80,		//���� ��Ȱ��
	IK_TOOL_REPAIR					=81,		//���� ������
	IK_IRON_SHIELD					=82,		//�����	
	IK_IRON_SHOES					=83,		//�� �Ź�	
	IK_CAP							=84,		//����	
	IK_GOKAL						=85,		//�ΰ�	
	IK_PRIEST_ROBE					=86,		//�����κ�	
	IK_CANDLE						=87,		//����	
	IK_MAN_TO_MAN					=88,		//������	
	IK_CRACKER						=89,		// ����			// 010210 YGI
	IK_RAJA_EMBLEM					=90,		// ���� ����
	IK_POTION_CHANGE_COLOR_CLOTHES	=91,	// �� ������
	IK_POTION_CHANGE_COLOR_HAIR		=92,	// �Ǻ� ������
	IK_NEW_MONEY					=93,	// �űǵ�
	IK_LOCK_STEAL					=94,	// ���Ϲ��� ��
	IK_MAP							=95,	//	����
	IK_GAUNTLET						=96,		//��Ʋ��
	IK_GOOD_FOOD					=97,		//�������
	IK_GOOD_POTION					=98,		//�������
	IK_GOOD_CANDLE					=99,		//��޾���
	IK_UNIQ_RESOURCE				=100,		//����ũ���
	IK_GENERAL_GAMBLE				=101,		//�Ϲݰ׺������
	IK_GRADE_GAMBLE					=102,		//�׷��̵�׺������
	IK_CLOAK						=103,		//����
	IK_CHAIR						=104,		//����			// LTS SITDOWN
	IK_BOMB							=105,		//011212 lsw 
	IK_TRAP							=106,		//011212 lsw 
	IK_THROW_EVENT					=107,		// CSD-030723 : �̺�Ʈ�� ������ ����
	IK_POTION_BOX					=108,		// ���� �ָӴ�		020418 YGI
	IK_FALG							=109,		// ���
	IK_SADDLE						=110,		// ������
	IK_DUAL_GAUNTLET				=111,	
	IK_DUAL_SWORD					=112,	
	IK_DUAL_BOW						=113,	
	IK_DUAL_FENCING					=114,	
	IK_DUAL_AXE						=115,	
	IK_DUAL_SPEAR					=116,	
	IK_DUAL_KNIFE					=117,	
	IK_DUAL_DOUBLE_SWORD			=118,	
	IK_DUAL_DOUBLE_AXE				=119,	
	IK_DUAL_MAGICIAN_STAFF			=120,	
	IK_DUAL_PRIEST_STAFF			=121,	
	IK_DUAL_SHIELD					=122,	
	IK_DUAL_ARMOR					=123,	
	IK_DUAL_ARCHER_LEATHER			=124,	
	IK_DUAL_MAGICIAN_ROBE			=125,	
	IK_DUAL_HELM					=126,	
	IK_DUAL_ARCHER_CAP				=127,	
	IK_DUAL_MAGICIAN_HAT			=128,	
	IK_DUAL_BOOTS					=129,	
	IK_DUAL_ARCHER_SHOES			=130,	
	IK_DUAL_MAGICIAN_SHOES			=131,	
	IK_DUAL_THIEF_SHOES				=132,	
	IK_DUAL_PRIEST_SHOES			=133,	
	IK_DUAL_THIEF_CAP				=134,	
	IK_DUAL_PRIEST_HAT				=135,	
	IK_DUAL_THIEF_LEATHER			=136,	
	IK_DUAL_PRIEST_ROBE				=137,	
	IK_DUAL_THIEF_SHIELD			=138,	
	IK_DUAL_ARROW					=139,	
	IK_ABYSS_MAZE					=140,	//�ƺ� �̱ÿ� ������	
	IK_UNDEAD_DUNGEON				=141,	//�𵥵� ������ ������	
	IK_GREAT_MAZE					=142,	//��̱� �� ������	
	IK_COMBATSKILL_BOOK				=143,
	IK_TREASURE_MAP					=145,	// ��������		// 040105 YGI ����
	IK_POTION_BAG					=147,	// BBD 040213 ������ �ִ� ����
	IK_NOEXCHANGE					=148,   // Fintio 040707 prevent from exchanging item (Auction/Sell/Trade/Drop/Etc)
	IK_SEX_CHANGE					=151, //Eleval 12/06/09 - Sex Change
	IK_NATION_CHANGE				=157, //Eleval 12/06/09 - Application of Exile
	IK_MANTLEDYE					=159,   // Finito 25/06/08 changes colour of a mantle
	IK_SPECIALPOTION				=160,	// Rog�rio 06/05/08 for cp potion and pots whit duration
};

enum eFuntionItemIndex
{
	FITEM_MOVABLE			=1,	//����,��ȭ,ȥ�� ����	����迭����	
	FITEM_RECOVERY			=2,	//�ӵ����� ����	�ӵ����� ����	
	FITEM_DETOX				=3,	//�ص��ۿ�	�ص�	
	FITEM_ENLIGHT			=4,	//�÷� ȸ��	�÷»��	
	//FITEM_NULL			=5,	NULL	NULL	
	//FITEM_NULL			=6,	NULL	NULL	
	FITEM_REVIVAL			=7,	//�ڵ� ��Ȱ	�ڵ� ��Ȱ	
	FITEM_COME_BACK			=8,	//�������� ��ȯ	�ڽ��� ���� ������ ������ ���ƿ� 	
	FITEM_RESIST_UP			=9,	//��� �迭 ���׷� ���	��� �迭 ���� ���׷� ���	
	FITEM_STEALTH			=10,	//���� ���� ����	���� �ð� ���� ���� ����	
	FITEM_INVALID_CURSE		=11,	//���� �迭 ���� ��ȿȭ	����� ���� �迭 ���� ��ȿȭ	
	FITEM_INVALID_OFFENCE	=12,	//���� �迭 ���� ��ȿȭ	����� ���� �迭 ���� ��ȿȭ	
	FITEM_POWER_UP			=13,	//������ ���ݷ� ����	������ ���ݷ� ����(%)	
	FITEM_SPEED_UP			=14,	//�̵� �ӵ� ����	�̵� �ӵ� (�̵���) ����	
	FITEM_HEAVY_ARMOR		=15,	//AC ����	AC ��ġ ����	
	FITEM_SPELL_UP			=16,	//���� ������ ����	���� ������ ����(%)	
	FITEM_SPELL_TIME_UP		=17,	//���� ���� �ð� ����	���� ���� �ð� ����(msec)	
	FITEM_CRITICAL			=18,	//CRITICAL DAMAGE 	ũ��Ƽ�� �������� ������ ����	
	FITEM_STROKE			=19,	//������ ���� ������ 100%	������ ���� ������ 100%	
	FITEM_AGILITY			=20,	//������ ���� ȸ���� 70%	������ ���� ȸ���� 70%	
	FITEM_INVALID_PROTECT	=21,	//����� ��ȣ �迭 ���� ����	����� ��ȣ �迭 ������ ������ �����Ͽ� ����(����/���� ���)	
	FITEM_INVALID_RESIST	=22,	//����� ���� ���׷� ����	����� ���� ���׷� ������ ���� (���� ���׷� 0���� ����)	
	FITEM_GHOST				=23,	//������ �� �� ����	������ �� �� ����	
	FITEM_SAMARITAN			=24,	//NK�� ������ ����	NK�� ������/���� ���� ��� ����	
	FITEM_SLIGHT			=25,	//���� ĳ���� �ð� ����	���� ĳ���� �ð� ����(%)	
};
//< CSD-030723
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// ���� ���̺� ����ü
struct MAGICTABLE
{
	int	serial_Num;		    // ������ȣ : ����(1 ~ 200), ������ų(215 ~ 250)
	int	order_Type;		    // �迭 : ������(1 ~ 12), ������(21 ~ 31), ������ų(61 ~ 66)
	char Han_Name[30];
	int	appoint_Type;		  // ��� ������� Ÿ��(0->���ڽ�/1->�������(���ϴ��)/2->�������(�������)/3->��������)
	int	basic_Level;		  // ��� �⺻ ����(1~9)
	int	point_MS;		      // Magic S point 
	int before_Magic;		  // �� �ܰ� ����(���� ������ �� ����)
	int	basic_magery ;		//
	int	cast_Time;		    // ĳ���� �ð�(����ð�)
	int	cast_Continue;	  // ĳ���� ���� �ð�(����ð�)
	int	continue_Time;	  // ���ӽð�(0->������/1~����ð�)
	int	avail_Type;		    // ȿ�� Ÿ��(0->�ڽ�/1->�ڽ� �ƴ� 1��/2~->��ȿ������ �ټ�)
	int	avail_Range;	    // �����Ÿ�(Ÿ�ϴ���/0->�ڽ�/99->����)
	int	exhaust_MP;		    // �Ҹ� MP
	int	exhaust_MS;		    // �Ҹ� MS
	int	require_IT;		    // �䱸 ����
	int	require_WP;		    // �䱸 ����
	int nHDPoint; // CSD-030314 : ���� ������ ���ذ�
	int nHDLimit; // CSD-030314 : ���� ������ ���ذ� ����ġ(���밪)
	int	point_WS;		      // WS ����Ʈ(0->not available/1~)
	int	point_Move;		    // �̵�����Ʈ(0->not available/1~)
	int	invalid_TargetIT;	// ���� ��밡�� ����
	int nClass;           // ������ų ��밡�� Ŭ����  
	int nTactics;         // ������ų ��밡�� ������ƽ
	int nAddition;        // ������ų ���� �Ҹ�Ǵ� �Ҹ�
	int aLevel[4];        // ������ų ����
	int aRandom[4];       // ������ų ���� ����
	int Spell_Type ;		  // 0 Wizard, 1~13 priest(God�� type�� ������ �پ�
	int	Appoint_Type ;
	int	Excute_Type;
	int	magic_Type;
	int	Price;
	int	Exp;
	int	Learnable;
	int	nSummonMax;   // CSD-030314 : ��ȯ������ ��ȯ���� �ִ� ������ ��
	int nCombatCount; // CSD-030314 : ��밡���� ������ų ��
	int nResist;
	int nRiseFall;
	int nDualStep;	// 030415 kyo
};
//
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// 020808 YGI(������ ��ġ�� ������ �ٲ���)
class CEffectTbl
{ 
public:
	CEffectTbl()
	{
		effect_Num = 0;
		pattern_Num = 0;
		sprite_Num = 0;
		static_Effect = false;
		sound_Num = 0;
		sound_Volume = 0;
		sound_loop = 0;
		next_Effect = 0;
		link_Frame = 0;
		trans_Type = 0;
		trans_Level = 0;
		sort_Type = 0;
		spr_Speed = 0;
		spr_Height = 0;
		object_Num = 0;
		fallow = false;
		light = 0;
		end_Time = 0;
		impect_Effect_Num = 0;
		send_result = false;
	}
	
public:
	int Check() const 
	{
		int value;
		char *pValue = (char *)&value;
		pValue[0] = Check1()+Check3();
		pValue[1] = Check2()+Check4();
		pValue[2] = 0;
		pValue[3] = 0;
		return (short int)value;
	}
	
	char Check1() const
	{
		return (char)(effect_Num+end_Time);
	}
	char Check2() const
	{
		return (char)(sort_Type+next_Effect+sort_Type+object_Num);
	}
	char Check3() const
	{
		return (char)(spr_Speed + spr_Height + object_Num);
	}
	char Check4() const
	{
		return (char)(pattern_Num + sprite_Num + link_Frame);
	}
	
public:
	short int	end_Time;			//��������� �� �����Ӽ�
	short int	light;				//����ȿ�� ������?(0->���� ����/100�ڸ���ġ->0�̸� ������ ���/1�̸� ���̰� ���ؼ� ���(1~20 ������ ���� �ܰ�)
	short int	sound_Volume;		//����Ʈ�� ����� ������ ��������	
	char		static_Effect;		//��������Ʈ�� ��Ÿƽ ����
	short int	sprite_Num;			//��������Ʈ�� ���� ��ȣ
	short int	pattern_Num;		//����(�Լ�)�� ��ȣ	
	char		send_result;		//ȿ���� ������ ����� ��û�ϴ��� ����
	short int	spr_Height;			//����Ʈ�� ����
	short int	sound_Num;			//����Ʈ�� ����� ������ ������ȣ
	short int	spr_Speed;			//����Ʈ�� �̵�ġ
	short int	impect_Effect_Num;	//Ÿ�ݽ� ����Ǵ� ����Ʈ�� ��ȣ
	short int	sort_Type;			//ȭ�� sorting ���(9(9+0)->�Ϲ��� ����/10(9+1)->������ �ֻ�/11(9+2)->������ ����/12(9+3)->���ϸ��̼� ȭ�� �����Ͽ� ��������/13(9+4)->������ �յڿ� 2���� ��������Ʈ ����)
	short int	trans_Level;		//Ʈ���� ����
	short int	effect_Num;			//����Ʈ�� ����(�Ϸ�) ��ȣ
	short int	object_Num;			//����Ʈ �ҽ��� ������� ����
	short int	link_Frame;			//���� ����Ʈ�� ���۵� ������
	char		fallow;				//�ι��� ������->1/����->0
	short int	next_Effect;		//���� ����Ʈ ��ȣ
	short int	sound_loop;			//���� ��� Ƚ��
	short int	trans_Type;			//Ʈ���� ���
};

class CEffectTbl2
{ 
public:
	int Check() const 
	{
		int value = 0;
		for( int i=0; i<30; i++ )
			value += sprite_Name[i];
		
		return value;
	}
public:
	char sprite_Name[30];
};
//
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//
class CMagicTbl
{
public:
	CMagicTbl()
	{
		order_Type = 0;
		serial_Num = 0;
		basic_Level = 0;
		WS = 0;
		before_Magic = 0;
		basic_Magery = 0;
		cast_Time = 0;
		cast_Continue = 0;
		continue_Time = 0;
		avail_Type = 0;
		avail_Range = 0;
		exhaust_MP = 0;
		exhaust_WS = 0;
		require_WP = 0;
		require_IT = 0;
		point_WS = 0;
		invalid_TargetIT = 0;
		spell_Type = 0;
		appoint_Type = 0;
		excute_Type = 0;
		magic_Type = 0;
		Price = 0;
		Exp = 0;
		Learnable = 0;
		nSummonMax = 0;
		nCombatCount = 0;
		nResist = 0;
		nRiseFall = 0;
		nDualStep = 0; // 030415 kyo

	}
	
public:
	int Check() const 
	{
		return serial_Num + basic_Level + cast_Time + cast_Continue + 
			continue_Time + avail_Range + excute_Type + appoint_Type +
			avail_Type + spell_Type + magic_Type + nCombatCount;
	}
	
public:
	int	order_Type;			     // �迭(1->��/2->��/3->�Ϲ�/4->ȭ��/5->����/6->����/7->��ȯ/8->�ð�/9->�ż�/10->����/11->����/12->Ư��)
	int	serial_Num;			     // ������ȣ(1~)
	int	basic_Level;		     // ��� �⺻ ����(1~9)
	int	WS;					         // wizwrd spell(or priest spell) point 
	int	before_Magic;		     // �� �ܰ� ����(���� ������ �� ����)
	int	basic_Magery ;		   // �⺻ ������
	int	cast_Time;			     // ĳ���� �ð�(����ð�)
	int	cast_Continue;		   // ĳ���� ���� �ð�(����ð�)
	int	continue_Time;		   // ���ӽð�(0->����,������/1~����ð�)	
	int	avail_Type;			     // ȿ�� Ÿ��(0->�ڽ�/1->�ڽ� �ƴ� 1��/2~->��ȿ������ �ټ�)
	int	avail_Range;		     // �����Ÿ�(Ÿ�ϴ���/0->�ڽ�/99->����)		
	int	exhaust_MP;			     // �Ҹ� MP
	int	exhaust_WS;			     // �Ҹ� WS
	int	require_WP;			     // �䱸 ����					
	int	require_IT;			     // �䱸 ����
	int	point_WS;			       // WS ����Ʈ(0->not available/1~)
	int	invalid_TargetIT;	   // ���� ��밡�� ����
	int	spell_Type ;		     // 0 Wizard, 1~13 priest(God�� type�� ������ �پ�)
	int	appoint_Type;		     // ��� ������� Ÿ��(0->���ڽ�/1->�������(����/�������)/2->Ư������(Ŭ����ġ)/3->��������)
	int	excute_Type;		     // ���� ĳ���� ������ ����ɼ� �ִ� Ƚ��(0->������/1->�ѹ���)
	int	magic_Type;			     // ���� ��з�(0->����ݸ���/1->�����ݸ���/2->�����������ݸ���)
	int	Price;		  // ������ ���µ� �ʿ��� ���
	int	Exp;		  // �Ϲݸ����� ��� ������
	int	Learnable;	  // �� �ź����� Ÿ�Կ� ���� ���� �ִ� ���
	int	nSummonMax;   // CSD-030314 : ��ȯ������ ��ȯ���� �ִ� ������ ��
	int nCombatCount; // CSD-030314 : ��밡���� ������ų ��
	int nResist;      // ���� �� �ִ� ���׷�
	int nRiseFall;    // ������ ���� ����
	int nDualStep;	  //������ ��� �ܰ� // 030415 kyo
};
//
/////////////////////////////////////////////////////////////////////////////////////////

struct NPCName_by_Gender
{
	char Female[17] ;
	char Male[17] ;
	char Last[17] ;
};

struct NPCLev_to_Exp
{	//< CSD-030430
	int nMinExp;         // ���� ������ �ּ� ����ġ
	int nMaxExp;         // ���� ������ �ִ� ����ġ
	int nNeedExp;        // ���� ������ �ö󰡱� ���� ȹ���ؾߵ� ����ġ
	int nTrainingExp;    // ��ƽ �����忡�� ��� ����ġ
	float fExpReduction; // ��ɽ� �׾��� ��� ����ġ �谨��
	float fNKReduction;	 // NK�� �׾��� ��� ����ġ �谨��
	int nTacRate;		 // ��ƽ ����ġ
	int nMaxTactic;	     // ������ ���� ��ƽ �����忡�� �ø� �� �ִ� �ִ� ��ƽ ����
	int	nDyeingPrice;    // ���� ����
	int nLessRate;       // ���� ���� ����ġ  
	int nGreatRate;      // ���� ���� ����ġ  
	int nCspMax;         // �ִ� ������ų ������ ȹ���
	int nBaseCP;         // ������ų �⺻��
	int bank_loan;	     // 010314 YGI
	int nStep;           // ����ġ �ܰ�
	int nWarriorLife;    // ������ �⺻ Life
	int nThiefLife;      // ������ �⺻ Life
	int nArcherLife;     // �ü��� �⺻ Life
	int nWizardLife;     // �������� �⺻ Life
	int nPriestLife;     // �������� �⺻ Life
	int nWarriorExpRate; // ������ ����ġ ������(����%)
	int nThiefExpRate;   // ������ ����ġ ������(����%)
	int nArcherExpRate;  // �ü��� ����ġ ������(����%)
	int nWizardExpRate;  // �������� ����ġ ������(����%)
	int nPriestExpRate;  // �������� ����ġ ������(����%)
};	//> CSD-030430

struct NPC_Generation
{	//< CSD-030806
	int SprNO;
	//char Han_name[31];
	char Name[31];
	//int Selectable;
	int Sel_gender;
	//char Sel_FirstName[31];
	//char Sel_LastName[31] ;
	int nNpcRace;        // NPC ����
	int nNpcNK;          // NPC�� �׾��� �� NKó�� ����
	int nStep;           // Ŭ���� �ܰ�
	int nAttr;           // ���� �Ӽ�
	int nHpMax;          // ���� HP
	int nEpMax;          // ���� EP
	int nStrikeDamage;   // ������ ���� ������
	int nStrikeRandom;   // ������ ���� ������ ��ȭ��
	int nMagicDamage;    // ���� ���� ������
	int nMagicRandom;    // ���� ���� ������ ��ȭ��
	int nCriticalRate;   // ũ��ƼĮ Ȯ��
	int nCriticalDamage; // ũ��ƼĮ ������
	int nPiercingStrike; // �������� �Ǿ�� Ȯ��
	int nPiercingMagic;  // �������� �Ǿ�� Ȯ��
	int Sel_Job_Alchemist;
	int nAIBase;         // �⺻���� Npc AI ���� 
	int nAppearType;     // �������� ������� Ÿ��
	int nAIType;         // Npc AI ���� ��ġ
	int nAINo;           // Npc AI ���� ��ȣ
	int nLvMin;
	int nLvMax;
	int Money_min;						
	int Money_Max;						
	int AttackDelay;	// 0811 NPC KHS	
	int AccessDelay;	// 0811 NPC KHS	
	int BackDelay;		// 0811 NPC KHS	
	int PCfindDelay;	
	int nRvAp;	      // ���ݷ� ����(����%)
	int nRvLife;	    // Life ����(����%)
	int nRvExp;       // ����ġ ����(����%) 
	int nAc;          // �Ϲ� ����(����%)
	int nDpRate;      // ��� ���� ������(����%)
	int nApRate;      // ��� ���ݷ� ������(����%)
	int nPhysical;    // ������ ���ݿ� ���� ����(����%)
	int nFire;	      // �Ұ迭 ���� ������ ���� ���׷�(����%)
	int nIce;		      // �����迭 ���� ������ ���� ���׷�(����%)
	int nElect;	      // ���ݰ迭 ���� ������ ���� �����(����%)
	int nHoly;	      // �ŷ°迭 ���� ������ ���� ���׷�(����%)
	int nStun;        // ����迭 ���� ������ ���� ���׷�(����%)
	int nSlow;        // �ӵ����ϰ迭 ���� ������ ���� ���׷�(����%)
	int nPoison;      // �ߵ��迭 ���� ������ ���� ���׷�(����%)
	int nBlind;       // �÷»�ǰ迭 ���� ������ ���� ���׷�(����%)
	int nDrain;       // ��Ż�迭 ���� ������ ���� ���׷�(����%)
	int nFreeze;      // �õ��迭 ���� ������ ���� ���׷�(����%)
	//int SpiritValue;
	//int SpiritValue_Range;
	//int PS[15];
	//int Sel_Dice;
	//int QuantityperLv;
	//int WS[15] ;
	//int Sel_Dice1;
	//int QuantityperLv1;
	//int Leathal_weapon1;
	//int Leathal_weapon2;
	//int Damage_weapon;
	//int Leathal_attackws[9] ;
	//int Damage_WP;
	//int Leathal_WS;
	//int Success;
	//int Leathal_ps;
	//int DamagePercent_ps;
	int Inventory[15] ;
	//int Amount_Dice;
	//int Righthand;
	//int Lefthand;
	//int Body;
	//int Helmet;
	//int leg;
	//int Leg_Probability;
	//int neck;
	//int neck_Probability	;
	//int unique1;
	//int Unique1_probalbility;
	//int Unique2;
	//int unique2_probability	;
	//int Crapple;
	//int swordmanship;
	//int Archery;
	//int Fencing;
	//int Mace_fighting;
	//int Pierce;
	//int Whirl;
	//int Hurl;
	//int Parrying;
	//int Double_Swordmanship	;
	//int Double_MaceFighting	;
	//int Magery;
	//int Orison;
	//int LV_Str;
	//int Con;
	//int Dex;
	//int Wis;
	//int Int;
	int Movp;
	//int Char;
	//int Endu;
	//int Mor;
	//int Luck;
	//int WS_PS;
	//int Fullpoint;
	//int Suplus_Resist_Death;
	//int Suplus_Resist_Ston;
	//int Suplus_Resist_Magic;
	//int Suplus_Resist_Fire;
	//int Suplus_Resist_Ice;
	//int Suplus_Resist_Light;
	//int DivideLv;
	//int Resist_Range;
	int Tamingable;
	int Taming_min;
	int Taming_max;
	int Talkanimal_min;
	int Talkanimal_max;
	//int Resist;
	//int Resist_range1;
	int ValueHP;
	int ValueSP;
	//int Rely_value;
	//int nor_range;
	//int att_range;
	int offset[20];
	//int neglect_attack;
	//int neglect_avoid;
	//int check_pass;
	//int party;
	//int enemy_no;
	//int levelgap;
	//int apgap;
	//int vpgap;
	//int opendoor;
	//int lockdoor;
	//int closedoor;
	//int breakdoor;
	//int openobj;
	//int lockbj;
	//int closeobj;
	//int breakobj;
	//int act_month;
	//int act_time;
	//int act_bi;
	//int act_chun;
	//int act_nun ;
	int Get_meat;
	int Meat_amount;
	int Get_skin;
	int Skin_amount;
	int Get_Wool;
	int Wool_amount;
	int Get_beewax;
	int BeeWax_amount;
	int mutant;
	
	bool CanUse;
};	//> CSD-030806

///////////////////////////////////////////////////////////////////////////////
//
struct TimeData
{
	int Year;
	int Month;
	int Day;
	int DayofWeek;

	TimeData()
	{
		Year=0;
		Month=0;
		Day=0;
		DayofWeek=0;
	}
};
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//< CSD-030408 
struct REGEN_MONSTER_INFO
{
	int nMonsterNo;
	int nMonsterType;
	int nMonsterCount;
};

struct REGEN_PLACE_INFO
{
	int nNumber;
	int nPosX;
	int nPosY;
	int nScope;
};
//> CSD-030408
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//< CSD-030506
struct k_nation_item_data
{
	short int item_no;
	short int fame;
	int	money;
};
//> CSD-030506
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//< CSD-TW-030704
typedef struct tag_LottoUsers
{
	int		nLottoID;
	char	szID[20];
	TIMESTAMP_STRUCT	date;
	int		aNumbers[10];
}LOTTO_USER;

typedef struct tag_LottoEventInfo
{
	int		nLottoID;
	tm		StartDate;
	tm		LotteryDate;
	int		nWinNumCount;
	int		anWinNumbers[10]; // 10�� ���� ����� 4���� ���δ�.
}LOTTO_EVENT_INFO;

typedef	struct	tag_DateCheck
{
	int		nDay;
	int		nHour;
	int		nMin;
}DATECHECK;
//> CSD-TW-030704
///////////////////////////////////////////////////////////////////////////////

struct START_UP_INFO
{	//< CSD-030723
	DWORD idIndex;
	int	  nApplyDay;  
	int   nStartHour;
	int   nStartMinute;
	int   nEndHour;
	int   nEndMinute;
};	//> CSD-030723	

struct CharacterParty
{	//< CSD-030723
	short int	On;
	char		Name[31];
	int			Face;
	int			Level;
	int			Gender;
	int			Str;
	int			Class;
};	//> CSD-030723

struct WINLOSEPOINT
{	//< CSD-030723
	DWORD win:13;
	DWORD defeat:12;
	DWORD disconnect:7;
};	//> CSD-030723

struct Event_Join							// 020115 LTS
{	//< CSD-030723
	unsigned char Event1 : 1;				// �̺�Ʈ 1�� ��������	
	unsigned char Event2 : 1;				// �̺�Ʈ 2�� ��������	
	unsigned char Event3 : 1;				// �̺�Ʈ 3�� ��������	
	unsigned char Event4 : 1;				// �̺�Ʈ 4�� ��������	
	unsigned char Event5 : 1;				// �̺�Ʈ 5�� ��������	
	unsigned char Event6 : 1;				// �̺�Ʈ 6�� ��������	
	unsigned char Event7 : 1;				// �̺�Ʈ 7�� ��������	
	unsigned char Event8 : 1;				// �̺�Ʈ 8�� ��������	
};	//> CSD-030723

struct DiseaseTable
{	//< CSD-030723							
	short int	disease_number;
	char		han_name[31];	
	char		name[31];	
	short int	lv;			
	short int	nut1_1;		
	short int	nut2_1;			
	short int	nut3_1;		
	short int	probability_1;
	short int	andor_1;	
	short int	checktime_1;
	short int	contact_char;
	short int	talk_char;	
	short int	fuck_char;	
	short int	contact_obj;
	short int	eat_obj;	
	short int	nut1_2;		
	short int	nut2_2;	
	short int	nut3_2;
	short int	probability_2;
	short int	checktime_2;
	short int	andor_2;
	short int	dec_str;
	short int	dec_dex;
	short int	dec_con;
	short int	dec_wis;
	short int	dec_int;
	short int	dec_movp;
	short int	dec_char;
	short int	dec_endu;
	short int	dec_mor;
	short int	dec_luck;
	short int	dec_ws;
	short int	dec_ps;
	short int	recoverable;
	short int	life	;
	short int	health	;
	short int	mp	;
	short int	dp	;
	short int	max_	;
	short int	damage	;
	short int	att_rate	;
	short int	depen_rate	;
	short int	ac	;
	short int	mad	;
	short int	poison	;
	short int	stony	;
	short int	sluggish	;
	short int	active	;
	short int	paralysis	;
	short int	active_time	;
	short int	maintain_time	;
	short int	natural_recovery	;
	short int	nut1_3	;
	short int	nut2_3	;
	short int	nut3_3	;
	short int	probability_3	;
	short int	checktime_3	;
	short int	andor_3	;
	short int	price_heal	;
	short int	price_prevent	;	
};	//> CSD-030723

struct GodTable
{	//< CSD-030723
	char meet_year_month;
	char meet_year_day;
	char meet_year_hour;
	char meet_month_day;
	char meet_month_hour;
	char meet_day_hour;
};	//> CSD-030723

struct NW_Character	// 010904 LTS		// LTS CHAR		
{	//< CSD-030723
	DWORD WarNo						:	7;	//	�����ȣ
	DWORD WarfieldNo					:	3;	//	������ ��ȣ
	DWORD SquadNo						:	3;	//	�δ��ȣ
	DWORD isSquadLeader				:	1;	//	�δ����ΰ�?	
	DWORD isCommander					:	1;	//	��ɰ��ΰ�?
	DWORD isCommanderCandidater		:	1;	//  ��ɰ� �ĺ��ΰ�?		// 010915 LTS
	DWORD DoWarJoinVote				:	1;	//	������ ���� ��ǥ�� �߳�?
	DWORD DoCommanderVote				:	1;	//	��ɰ� ��ǥ�� �ߴ�
	DWORD YL_JoinNation				:	4;	//	�Ͻ��ΰ�� �����ݿ��߳�? ���̼����� �߳�?  // ������ȣ
	DWORD Reserved					:	10;	//	����..
};	//> CSD-030723

struct CCharRank
{	//< CSD-030723
	DWORD nation	  :3;  // ���ѳ��� - 0:����, 1, 2, 3:���̼���, 4:������, 5:��Ը�Ͼ�, 6:�Ͻ�
	DWORD guild_master:3;  // ��� ������
	DWORD king		  :1;  // ���� ��
	DWORD dwReserved  :9;  // ������ ����
	DWORD counselor	  :2;  // 0 : ����, 1: ȸ�� ���, 2: ���ӳ� ���
	DWORD ultra_nk3	  :1;  // �ؾ�������	1004 YGI
	DWORD ultra_nk4	  :1;  // �ؾ�������	1004 YGI
	DWORD ultra_nk6	  :1;  // �ؾ�������	1004 YGI
	DWORD reporter	  :1;
	DWORD imsi		  :10; // 1004 YGI
	DWORD santa_power	:2; //Eleval 22/06/09 - Then GMs can Remove Santa Power
};	//> CSD-030723

struct MAP_MOVE_INFO
{	//< CSD-HK-030829
	int idUser;
	int nMapPort;
	int nX;
	int nY;
};	//> CSD-HK-030829

#define LOG_ABNORMAL_PROTOCOL			0
#define LOG_DISCONNECT_LOGIN_SERVER		1
#define LOG_DISCONNECT_DB_DEMON			2
#define LOG_HANDLE_WRITING				3
#define LOG_EXCEPTION_FAIL				4
#define LOG_HANDLE_COMMAND				5
#define LOG_HANDLE_READING				6
#define LOG_INSERT_LOGINTABLE_ERROR		7
#define LOG_SEND_UPDATING_MESSAGE		8
#define LOG_EXCEPTION_ITEM_ABRASION_ERROR    9
#define LOG_HANDLE_WRITING_INSIDE		10

extern DWORD global_time;
extern DWORD g_alive_time;
extern DWORD g_curr_time;
extern DWORD g_curr_time_with_out_year; // 031009 CI YGI


extern int g_year;
extern int g_mon;
extern int g_yday;
extern int g_wday;
extern int g_day;
extern int g_hour;
extern int g_min;
extern int g_sec;

extern int g_count_ok;
extern int g_weatherflag;

extern bool g_block_attack;
extern bool g_block_magic;
extern bool g_block_steal;//030102 lsw
extern bool g_stop_please_give_life;
// ��Ƽ����Ʈ�� ���� Setting.
extern HANDLE g_hSema;

#include "../LowerLayers/MyLog.h"
#include "CharInfo.h" // CSD-030723
#include "MagicState.h" // CSD-030723
#include "ResistState.h" // CSD-030723
#include "CharList.h" // CSD-030723
#include "nation.h"
#include "ItemMgr.h"
#include "dr_network.h"
#include "MYSQL.H"
#include "ITEMLIST.H"
#include "Hong_Sub.h"
#include "OP_Chr_Status.h"
#include "NPCLIST.H"
#include "Object.h"
#include "NPC_Pattern.h"
#include "AREA.H"
#include "SkillMgr.h" //020214 lsw skill.h ����
#include "CrackMgr.h" //020214 lsw skill.h ����
#include "Map.h"
#include "RajaSystem.h"
#include <mmsystem.h> //020214 lsw
#include "RareEffectMgr.h"
#include "menuserver.h"
#include "Nationsys_define.h"
#include "LocalizingMgr.h"
#include "LottoSystem.h" // CSD-TW-030704

extern CRareEffectMgr RareEM;
extern void ResetAbility(CHARLIST *ch);//020303 lsw
extern int MAX_EXP_LEVEL;  // CSD-040204
extern int MAX_TAC_LEVEL;  // CSD-040204
