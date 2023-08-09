#ifndef NW_PACKET_DEFINE_
#define NW_PACKET_DEFINE_

// Packet Define _________________________________________

#define		CMD_REQUEST_CHECK_VOTE					26001
#define		CMD_ANSWER_CHECK_VOTE					26002
#define		CMD_WARFIELD_STATUS						26003
#define		CMD_WAR_BBS								26004
#define		CMD_REQUEST_WARFIELD_STATUS				26005
#define		CMD_ANSWER_WARFIELD_STATUS				26006
#define		CMD_REQUEST_VOTE_DATA					26007
#define		CMD_ANSWER_VOTE_DATA					26008
#define		CMD_VOTING_DATA							26009 
#define		CMD_REQUEST_VOTE_RESULT					26010
#define		CMD_ANSWER_VOTE_RESULT					26011
#define		CMD_REQUEST_SQUAD_INFO					26012
#define		CMD_ANSWER_SQUAD_INFO					26013
#define		CMD_REQUEST_COMMANDER_VOTE_DATA			26014
#define		CMD_ANSWER_COMMANDER_VOTE_DATA			26015
#define		CMD_REQUEST_COMMANDER_VOTING_RESULT		26016
#define		CMD_ANSWER_COMMANDER_VOTING_RESULT		26017
#define		CMD_COMMANDER_VOTING_DATA				26018
#define		CMD_COMMANDER_DATA						26019
#define		CMD_CHANGE_SQUAD						26020
#define		CMD_FAME_DATA							26021
//#define		CMD_WARFIELD_STATUS_CHANGE_RESULT		26022
#define     CMD_CHECK_WARFIELD_STATUS				26023
#define		CMD_CHECK_WARFIELD_STATUS_RESULT		26024
#define		CMD_REQUEST_DELIVERY					26029
#define		CMD_ANSWER_DELIVERY						26030
#define		CMD_REQUEST_COMMANDER_REG_DATA			26031
#define		CMD_JOIN_SQUAD							26032
#define		CMD_SET_SQUAD_LOADING_POINT				26033
#define		CMD_ANSWER_COMMANDER_REG_DATA			26034
#define		CMD_YOU_ARE_SQUAD_COMMANDER				26035
#define		CMD_YOU_ARE_SQUAD_LEADER				26036
#define		CMD_CHANGE_LOADING_POINT				26037
#define     CMD_REQUEST_NATION_WAR_COUNT			26038			// Compare Nation War Count For Dirty Player
#define     CMD_ANSWER_NATION_WAR_COUNT				26039
#define		CMD_NW_MAP_MOVE							26040
#define		CMD_CHANGED_WARFIELD_STATUS				26041			// ManageServer to Other MapServer 
#define		CMD_NW_MAP_MOVE_FAIL					26042
#define		CMD_MAP_NATION_CODE_CHANGED				26043
#define		CMD_REQUEST_TILE_DONT					26044
#define		CMD_ANSWER_TILE_DONT					26045
#define		CMD_TILE_DONT_CHANGED					26046
#define		CMD_SQUAD_CHAT							26047
#define		CMD_CLEAR_SQUAD_DATA					26048			// �δ�Ӽ� Ŭ���� 
#define		CMD_REQUEST_WARFIELD_INFO				26049			// �����ڿ� ������� Ȯ�� 
#define		CMD_ANSWER_WARFIELD_INFO				26050
#define		CMD_WAR_BEGIN							26051			// ����ʿ� �ִ� ����� ������� �޼���..
#define		CMD_WAR_END								26052			// ��۵� ������.. �ȵȴ�.
#define		CMD_REG_SQUAD_LEADER					26053			// ������ 
#define		CMD_REQUEST_CHECK_WARFIELD_POSSESSION	26054
#define		CMD_ANSWER_CHECK_WARFIELD_POSSESSION	26055
#define		CMD_FREELANCER_SQUAD_JOIN				26056
#define		CMD_REQUEST_WARFIELD_POSSESSION			26057
#define		CMD_ANSWER_WARFIELD_POSSESSION			26058
#define		CMD_REQUEST_WARFIELD_WAR_DATA			26059
#define		CMD_WARFIELD_WAR_DATA1					26060			// ���� ��ȣ�� ����Ÿ
#define		CMD_WARFIELD_WAR_DATA2					26061			// �����ð�, ���ī��Ʈ 
#define		CMD_WARFIELD_WAR_DATA3					26062			// ���δ� ����
#define		CMD_WARFIELD_WAR_DATA4					26063			// ���ݺδ� ����
#define		CMD_WARFIELD_WAR_DATA5					26064			// ������ �δ� ����
#define		CMD_REQUEST_CHECK_WARNO					26065			// �����ȣ�� �Ǵ��Ѵ�.
#define		CMD_ANSWER_CHECK_WARNO					26066
#define		CMD_CLEAR_WAR_CHARACTER_DATA			26067			// Ŭ���̾�Ʈ
#define		CMD_SET_COMMANDER						26068			// DB���� 
#define		CMD_STARTUP_NATION_CODE_CHANGE			26069			// ���Ｍ��->��������->�ʼ���
#define		CMD_ANSWER_SQUAD_INFO2					26070			// �δ����� ��Ʈ2
#define		CMD_ANSWER_COMMANDER_VOTE_DATA2			26071
#define		CMD_SET_WARFIELD_POSSESSION				26072			// 020115 LTS
#define		CMD_REQUEST_SUBSTRACT_MONEY				26073			// ���� �����.. �� ����.
#define		CMD_ANSWER_SUBSTRACT_MONEY				26074			// ���� ����� ������ ��Ŷ
#define		CMD_SQUAD_JOIN_RESULT					26075			// �δ� �շ����� 

#define		CMD_REQUEST_WAR_GIVE_LIFE				26076			// ���� �츮�� ��û	// 011015 LTS
#define		CMD_ANSWER_WAR_GIVE_LIFE				26077			// ���� �츮�� ���� 
#define		CMD_CHECK_AM_I_DEFEAT					26078			// ������ ���� ������ ƨ���	
#define		CMD_SQUAD_LOADING_POINT					26079			// �������� -> ���Ｍ�� �ε�����Ʈ ���� 
#define		CMD_SQUAD_RARE							26080
#define		CMD_REQUEST_NOTICE						26081
#define		CMD_ANSWER_NOTICE						26082
#define		CMD_REQUEST_DELIVERY_NOTICE				26083
#define		CMD_SET_REMAIN_TIME						26084
#define		CMD_WAR_CONTROL							26085			
#define		CMD_WAR_LOOP_TIME						26086			// 011025 LTS
#define		CMD_SECRET_OPEN							26087			// 011025 LTS

#define		CMD_CHECK_ABILITY_CHANGE_MONEY			26200			// LTSSupport.cpp

#define		CMD_LOCALWAR_STATUS						26300			// LTS LOCALWAR
#define		CMD_REQUEST_LOCALWAR_INFO				26301
#define		CMD_ANSWER_LOCALWAR_INFO				26302
#define		CMD_REQUEST_LOCAL_DELIVERY				26303
#define		CMD_ANSWER_LOCAL_DELIVERY				26304
#define		CMD_LOCALWAR_JOIN						26305
#define		CMD_LOCALWAR_JOIN_RESULT				26306
#define		CMD_REQUEST_COMPARE_PHASE				26307
#define		CMD_INC_USER_LOCALWARFIELD				26308
#define		CMD_DEC_USER_LOCALWARFIELD				26309
#define		CMD_USER_JOIN_LOCALWAR					26310
#define		CMD_LOCALWAR_BEGIN						26311
#define		CMD_LOCALWAR_END						26312
#define		CMD_SEALSTONE_BROKED					26313
#define		CMD_SEALSTONE_ATTACKED					26314
#define		CMD_LOCALWAR_POINT_CHANGED				26315
//#define		CMD_LOCALWAR_RESULT						26316
#define		CMD_LOCALWAR_NATION_POINT_CHANGED		26317
#define		CMD_LOCALWAR_POINT_BBS					26318

#define		CMD_ACTION_STATUS						26319
#define		CMD_SITDOWN_DIRECTION_CHANGED			26320
#define		CMD_LOCALWAR_STARTUP_STATUS				26321
#define		CMD_WAR_GIVE_LIFE2						26322
#define		CMD_HERO_ACTION_CHANGED					26323
#define		CMD_CHECK_WARFIELD_NATION_MEMBERCOUNT	26324
#define		CMD_EVENT_LOCALWAR_CONTROL				26325
#define		CMD_EVENT_LOCALWAR_CONTROL_D			26326
#define		CMD_EVENT_LOCALWAR_STATUS_CHANGE		26327
#define		CMD_EVENT_LOCALWAR_JOIN					26328
//#define		CMD_EVENT_LOCALWAR_REMAIN_TIME			26329
#define		CMD_FAME_EXP_CHANGE						26330
#define		CMD_EVENT_LOCALWAR_MESSAGE				26331
#define		CMD_EVENT_LOCALWAR_MOVE					26332
#define		CMD_EVENT_LOCALWAR_JOIN_RESULT			26333
#define		CMD_EVENT_LOCALWAR_MOVE_RESULT			26334
#define		CMD_DELETE_EVENT_JOIN					26335
#define		CMD_EVENT_POINT_CHANGE					26336
#define		CMD_EVENT_REMAIN_TIME					26337		// LTS BUG
#define		CMD_AI_STATUS							26338		// LTS AI2
#define		CMD_AI_DATA_RELOAD						26339		// LTS AI2 TEMP
#define		CMD_EVENT_MONSTER						26340		// LTS AI2 TEMP
#define		CMD_EVENT_MONSTER_CREATED				26341		// LTS AI2
#define		CMD_COMMUNITY_ACTION					26342		// LTS ACTION
#define		CMD_LOCALWAR_NATION_RESULT				26343		// LTS NEW LOCALWAR
#define		CMD_LOCALWAR_MAPMOVE					26344		// LTS NEW LOCALWAR
#define		CMD_LOCALWAR_MAPMOVE_RESULT				26345		// LTS NEW LOCALWAR
#define		CMD_LOCALWAR_CHAT						26346		// LTS NEW LOCALWAR
#define		CMD_LOCALWAR_CHAT_B						26347		// LTS NEW LOCALWAR
#define		CMD_LOCALWAR_FAME_EXP					26348		// LTS NEW LOCALWAR
#define		CMD_LOCALWAR_DEFENCE_POINT				26349		// LTS NEW LOCALWAR

#define		CMD_GOTO_GUILD_HOUSE_RESULT				26350			// �迵��
#define		CMD_CHECK_GUILD_HOUSE_RESULT			26351			// �迵��

#define		CMD_AI_FOG								26352		// LTS NEW AI
#define		CMD_AI_SOUND							26353		// LTS NEW AI
#define		CMD_AI_ACTION_TEST						26354		// LTS NEW AI TEST
#define		CMD_AI_MOVE								26355		// LTS NEW AI
#define		CMD_AI_NPC_ACTION						26356		// LTS DRAGON MODIFY
#define		CMD_AI_EARTHQUAKE						26357		// LTS DRAGON MODIFY

#define		CMD_SET_QUESTMODE						26358		// LTS DRAGON MODIFY
#define		CMD_ACTIVE_DRAGONLORD_WAR				26359		// LTS DRAGONLORD	
#define		CMD_DRAGONLORDWAR_TEAM_CHANGE			26360		// LTS DRAGONLORD	


#define		CMD_REQUEST_CHECK_DUAL_FAME				26361   // LTS DUAL FAME
#define		CMD_ANSWER_CHECK_DUAL_FAME				26362

#define		CMD_START_WAR_LOOP						26363	// LTS NEW_NATION_WAR
#define		CMD_SAVE_WARNO							26364	// LTS NEW_NATION_WAR	// DBDEMON
#define		CMD_NWARFIELD_START_WAR					26365
#define		CMD_REQUEST_NEW_WARFIELD_TILE_DONT		26366
#define		CMD_NWARFIELD_END_WAR					26367
#define		CMD_FAME_CHANGE							26368
#define		CMD_WAR_RESULT							26369
#define		CMD_CHECK_DEFEAT						26370
#define		CMD_ANSWER_NEW_WARFIELD_TILE_DONT		26371
#define		CMD_DONT_CHANGE							26372
#define		CMD_GUARD_KILLER						26373
#define		CMD_LOOPTIME_CHANGE						26374	
#define		CMD_NWARFIELD_STATUS_CHANGE				26375		
#define		CMD_REQUEST_NEW_WARFIELD_STATUS			26376
#define		CMD_ANSWER_NEW_WARFIELD_STATUS			26377
#define		CMD_REQUEST_NEW_WARFIELD_DATA			26378
#define		CMD_ANSWER_NEW_WARFIELD_DATA			26379
#define		CMD_WAR_YL_JOIN							26380
#define		CMD_GUARD_BROKE							26381
#define		CMD_LOCALWAR_BEGIN_TIME					26382 // finito 050707 the remaining time until local war starts
#define		CMD_SERVER_TIME							26383 // finito 060707
#define     CMD_GUARD_CAN_NOT_BROKE					26501
//<soto-030417
#define		CMD_SYMBOL_MAKE							26400
#define		CMD_SYMBOL_UPGRADE						26401
//>soto-030417

#define		CMD_OPEN_LUCKY_MENU						26402 //soto-030429
#define		CMD_OPEN_WINNER_MENU					26403 //soto-030502


#define		CMD_INSERT_LOTTO_INFO					26404 //soto-030503 //DB����
#define		CMD_DELETE_LOTTO_ALL_USER				26405 //soto-030503 //DB����
#define		CMD_CUR_LOTTO_INFO						26406 //soto-030503 //DB����
#define		CMD_LOTTERY_INFO						26407 //soto-030503 //DB����
#define		CMD_NEW_EVENT							20408 //soto-030504 //DB����
#define		CMD_LOTTO_BUY							20409 //soto-030504
#define		CMD_CAN_BUY								20410 //soto-030504
#define		CMD_WINNER_CHECK						20411 //soto-030505
#define		CMD_CHECK_OK							20412 //soto-030505
#define		CMD_DEL_LOTTO_USER						20413 //soto-030505

#define		CMD_CHECK_WINNER_MENU					20414 //soto-030505

#define		CMD_OPEN_LOTTOMENU						20415 //soto-030520
#define		CMD_LOTTERY_BROADCAST					20416 //soto-HK030924
#define		CMD_LOTTO_SEEK							20417 //soto-Lotto�߰�

#define		CMD_DEL_LOTTO_USER_OK					20418	// BBD 040127	�ζ����μ��� ����

//<soto-HK030924
typedef struct	tag_LOTTERY_INFO
{
	int	nLottoID;
	int nWinNumCount;
	int	anWinNumbers[10]; // ��÷ ��ȣ.
}t_LOTTERY_INFO;
//>soto-HK030924


typedef	struct tag_OPEN_LOTTO_MENU
{
	int	nMaxNumberCount; //���ڸ��� ���� �ζǸ�  �������.
}t_OPEN_LOTTO_MENU;

typedef struct tag_CHECK_WINNER
{
	int		nLottoID;//soto-LottoADD
	char	strCharName[21];
	int		nWinItemCount;// 0�̸� ��÷ ���� �ʾҽ�. -1�̸� ����� ���ġ ����.
	int		anWinNumbers[10];
	int		anWinItemsCount[5];//���⿡ ����� ���� �Ǵ� ������ ������ ����.//soto-Lotto�߰�.
}t_CHECK_WINNER;
//<! BBD 040127	�ζ� ���μ��� ����
typedef struct tag_DEL_LOTTO_USER_OK
{
	bool	bIsDelOK;

}t_DEL_LOTTO_USER_OK;
//> BBD 040127	�ζ� ���μ��� ����

//<! BBD 040308		�̺�Ʈ ���� ������ ���޿� ����ü
typedef struct tag_EVENT_RARE_ITEM_LIST
{
	int			nCn;
	char		szChrName[21];
	char		szLoginID[21];
	int			nIndex[10];
	ITEMATTR	item[10];

}t_EVENT_RARE_ITEM_LIST;
//> BBD 040308		�̺�Ʈ ���� ������ ���޿� ����ü

typedef	struct tag_BUY_LOTTO
{
	int	nLottoID;//soto-LottoADD
	char strCharName[21];
	int	anLottoNumber[10];
	int	m_nLottoPay;//�ζǿ� ���ҵǴ� ��.
}t_BUY_LOTTO;


//<soto-Lotto�߰�.
typedef struct tag_WINNER_MENU
{
	int	nLottoID;//soto-LottoADD
	int	 nMaxLottoCount;//���ڸ� ���� �ζ� ��ȣ�� �����̳�?	
	char strCharName[21];
	int	anWinNumbers[10];
	int	nViewCount;//���� ȭ�鿡 ������ �ζ��� ī��Ʈ. 0�ʰ�.
	int	anLottoNumber[5][10];
	int	nTotalLottoCount;
}t_WINNER_MENU;
//>soto-Lotto�߰�.

//< soto-030418 // �ɺ� �����۰��� ��Ŷ. ������ ���׷��̵忡 ���δ�.
typedef struct tag_SYMBOL_ITEM_MSG
{
	int m_nItemNumber;
	int	m_nGrade; // 1�� ����.
} t_SYMBOL_ITEM_MSG;
//> soto-030418

//<soto-Lotto�߰�.
typedef struct tag_LOTTOPAPER_SEEK
{
	char	strChrName[20];
	int		nPage;//���ϴ� �������� ����.
	int		nViewCount;//���� ��µǴ� ������ ����.
	int		anLottoNumber[5][10];//����Ʈ�� �ִ� �ζ� ��ȣ���� ����.
	int		nLottoID;//�ζ��� ȸ���� ����.
}t_LOTTOPAPER_SEEK;
//>soto-Lotto�߰�.



// Packet Define End ____________________________________
 
const int 	NW_NATION_COUNT					=3;
const int 	NW_WARFIELD_COUNT				=3;
const int 	MAX_NEW_WARFIELD				=1;

const int 	NW_NAME_MAX						=64; //Eleval 21/08/09 - Put 64 to prevent any problem with a buffer too small
const int 	NW_SQUAD_MAX					=5;		// 0�δ� : �δ� ���� ���� ���� �ο��� ����.
const int 	NW_CANDIDATE_MAX				=6;
const int 	NW_SQUAD_KIND					=3;
const int 	MAX_STRING_PK					=600;
const int 	NW_SQUAD_RARE_MAX				=3;
const int 	FOG_MAX							=30;	// LTS DRAGON MODIFY
const int 	MAX_DONT_DATA					=10;

//<------------------------------- 1.04 addition ------------------------------------------
#define CMD_CHECK_WARFIELD_SQUAD_MEMBERCOUNT  26501	// �δ� �ο� ���� ��ũ�Ѵ�. ��Ŷ
#define  CMD_MONSTER_RAID_START  26502	// ���� ���� ������ �����Ѵ� �ű������͸ʼ���->�ش� �ʼ���
#define  CMD_MONSTER_RAID_END  26503	// ���� ���� ������ ������. �ű������� �ʼ���-> �ش� �ʼ���.
#define  CMD_GUARD_CAN_NOT_BROKE  26504	// �����̳� ��ȣ���� �μ� �� ����
#define CMD_CHECK_REMAIN_GUARD  26505	// ���� �����̳� ��ȣ���� ��ȯ�Ѵ�.
// LTH-040207-KO ���� ������3�� + ����������1�� + ���������� 1�� �� 5���� ������
INT const MAX_WARFIELD = NW_WARFIELD_COUNT + MAX_NEW_WARFIELD + 1;



/**
 * @struct	CheckSquadMemberCount_.
 * @brief	�δ� �ο� ī��Ʈ.
 */
typedef struct CheckSquadMemberCount_
{
	char cWarfieldNo;
	char cSquad;
}	t_CheckSquadMemberCount;

/**
 * @struct	CheckSquadMemberCountR_.
 * @brief	�δ� �ο� üũ ���.
 */
typedef struct CheckSquadMemberCountR_
{
	char cWarfieldNo;
	char cResult;
}	t_CheckSquadMemberCountR;

int const NEO_NUMOFGUARD = 17;

/**
 * @struct	NEO_WARFIELD_DATA.
 * @brief	�ű� ������ ���� ���ۿ�.
 */
struct NEO_WARFIELD_DATA
{
	DWORD dwRemainTime;
	INT nWarfieldNo;				// �����ȣ�� �Ǿ����.
	INT nTeamCount[2];
	INT nRemainGuardCount[2][4];		// ������ ���� Guard �� 0 : ������ȣ��, 1 : ������ȣ��, 2 : ���� 3 : �ܼ���ȣ��
	CHAR cGuardStatus[2][NEO_NUMOFGUARD];	// Hades War�� �������ִ�. �ܼ� : 4, ����(��) : 4, ����(��) : 4, ���� : 4, ���� : 1
};

/**
 * @struct	NEO_WAR_RESULT.
 * @brief	���� ��� ���ۿ�.
 */
struct NEO_WAR_RESULT
{
	INT nBYMemberCount;
	INT nZYMemberCount;
	INT nYLMemberCount;
	INT nBYDeathCount;
	INT nZYDeathCount;
	INT nYLDeathCount;
	bool bAllNationJoin;	// ��� ���� ������ ������ ���� ��� â�� ����� �ʱ� ����
	WORD wWarfieldPort;
	CHAR cVictoryTeam;
};

/**
 * @struct	GUARD_CAN_NOT_BROKE.
 * @brief	���带 �μ��� ���� ��������.
 */
struct GUARD_CAN_NOT_BROKE
{
	int nWarfieldNo;
	int nType;
};

/**
 * @struct	REMAIN_GUARD.
 * @brief	���� ����(����, ��ȣ��)�� ���� ��ȯ�Ѵ�.
 */
struct REMAIN_GUARD
{
	DWORD dwRemainTime;				// �� ���� ���� �ð����� �����ڱ�
	int nWarfieldNo;				// ������ ��ȣ�� �����ڱ�!!
	int aRemainGuardCount[2][4];	// �絹 ���� ���� ���� ��������~!
};
//>------------------------------- 1.04 addition ------------------------------------------

//<------------------------------- 1.04+ addition ------------------------------------------
#define CMD_NW_MAP_PEACE_MOVE  26506;	// ��ȭ �Ⱓ�� ������ �̵� ��û C -> M
#define CMD_NW_MAP_PEACE_MOVE_RESULT  26507;	// ��ȭ �Ⱓ�� ��û�� ������ �̵� ��� M -> C
#define CMD_WARFIELD_INFO = 26508;	// ������ �����ڿ� ������ ���� ��û M -> WM
#define CMD_WARFIELD_INFO_RESULT  26509;	// ������ �����ڿ� ������ ���� ��û WM -> M

/**
 * @struct	tagWarfieldPeaceMove.
 * @brief	��ȭ �Ⱓ�� �����Ϳ� �̵� ��û �Ҷ��� �ʿ�.
 */
typedef struct tagWARFIELD_PEACE_MOVE
{
	int nWarfieldNo;		// �̵��� ������ ��ȣ.
	int nUserID;			// �̵��� ������ ID.
} tagWarfieldPeaceMove;

/**
 * @struct	tagWarfieldPeaceMoveResult.
 * @brief	��ȭ �Ⱓ�� �����Ϳ� �̵� ��û�� ���� ���.
 */
typedef struct tagWARFIELD_PEACE_MOVE_RESULT
{
	DWORD dwYlMoveMoney;		// �Ͻ��� �̵� ���
	int nResult;				// ������ �̵� ��û ���. ������ ��� �ڵ� �����̴�.
	int nWarfieldNo;			// ������ ��ȣ
	int nPossessionNation;		// �������� ��ȣ
} tagWarfieldPeaceMoveResult;

/**
 * @struct	tagWarfieldInfo.
 * @brief	������ �����ڿ� ������ ���� ��û.
 */
typedef struct tagWARFIELD_INFO
{
	int nWarfieldNo;			// ��û�� ������
	int nUserID;				// �̵��� ������ ID.
	WORD wPort;					// ��û�� �ʼ��� ��Ʈ
} tagWarfieldInfo;

/**
 * @struct	tagWarfieldInfoResult.
 * @brief	������ �����ڿ� ������ ���� ��û ���.
 */
typedef struct tagWARFIELD_INFO_RESULT
{
	int nWarfieldNo;			// �̵��� ������ ��ȣ.
	int nUserID;				// �̵��� ������ ID.
	int nWarfieldPossession;	// ������ ������
	int nWarfieldStatus;		// ������ ����
} tagWarfieldInfoResult;
//>------------------------------- 1.04+ addition ------------------------------------------


typedef struct CommonDataC_P
{
	BYTE	Data;
}	t_CommonDataC;

typedef struct CommonDataDw_P
{
	DWORD	Data;
}	t_CommonDataDw;


typedef struct CheckVote_P
{
	char	WarfieldNo;
	char	Status;
}	t_CheckVote;

typedef struct WarfieldStatusChange_P
{
	WORD	WarfieldNo;
	char	Status;
}	t_WarfieldStatusChange;

typedef struct WarBBS_P
{
	char	WarfieldNo;
	char	BBSType;
	char	LanNo;				//�������� ��ȣ
	char	ArgType;			// 0 :���ڿ� 1: ���� 
	char	Size;				// ArgType�� ���ڿ��̸� ���ڿ��� ũ�� 1:�����̸� ������ ���� 
	char	Arg[MAX_STRING_PK];
}	t_WarBBS;

typedef struct WarfieldStatus_P
{
	BYTE	PacketStatus;
	char	Status[NW_WARFIELD_COUNT];
}	t_WarfieldStatus;

typedef struct WarfieldStatusM_P
{
	char	WarNo;
	char	Status[NW_WARFIELD_COUNT];
	char	Possession[NW_WARFIELD_COUNT];
}	t_WarfieldStatusM;

typedef struct VoteData_P
{
	char	WarfieldNo;
	short	VoteCount;				//���峪 ���������� ��ȯ �ʿ� // 011028 LTS
}	t_VoteData;

typedef struct RequestSquadInfo_P
{
	char	Nation;
	char	WarfieldNo;
	char	SquadNo;
}	t_RequestSquadInfo;

typedef struct SquadInfo_P
{
	char	SquadNo;
	int		ChipID;
	char	ChipName[NW_NAME_MAX];
	int		SoldierCount;
	char	Sok[NW_SQUAD_RARE_MAX];					//����Ӽ� //��Ʈ����	
	char	LoadingPoint;
}	t_SquadInfo;

typedef struct SquadInfo2_P
{
	char	CommanderName[NW_NAME_MAX];
	short	SquadCount[NW_SQUAD_MAX];				// 011028 LTS
}	t_SquadInfo2;

typedef struct RegSquadLeader_P			// ������ ��Ŷ 
{
	char		Nation;
	char		WarfieldNo;
	char		SquadNo;
	int			ChipID;
	char		ChipName[NW_NAME_MAX];
	short		Level;					// 011028 LTS
	short		Fame;
	short int	Face;
	short int	Gender;
	short int	Class;					// 011016 LTS
	__int8		nDual;					// 011020 LTS
	__int8		nStep;					// 011020 LTS
	DWORD		LadderScore;
	
}	t_RegSquadLeader;

typedef struct RequestCommanderVoteData_P
{
	char	Nation;
	char	WarfieldNo;
	char	CandidaterNo;
}	t_RequestCommanderVoteData;

typedef struct CommanderVoteData_P
{
	char		VoteNo;
	int			CandidaterID;
	char		Name[NW_NAME_MAX];
	short		Level;					// 011028 LTS
	short		Fame;
	short int	Face;
	short int	Gender;
	short int	Class;					// 011016 LTS
	__int8		nDual;					// 011020 LTS
	__int8		nStep;					// 011020 LTS
	DWORD		LadderScore;
	short		VoteCount;				//���峪 ���������� ��ȯ �ʿ�		// 011028 LTS
}	t_CommanderVoteData;

typedef struct CommanderVoteData2_P
{
	char	CandidaterName[NW_CANDIDATE_MAX][NW_NAME_MAX];
	short	VoteCount[NW_CANDIDATE_MAX];									// 011028 LTS
}	t_CommanderVoteData2;

typedef struct RequestCommanderRegData_p
{
	char		Nation;
	char		WarfieldNo;
	char		CandidaterNo;
	int			CandidaterID;
	char		Name[NW_NAME_MAX];
	short		Level;					// 011028 LTS	
	short		Fame;
	short int	Face;
	short int	Gender;
	short int	Class;					// 011016 LTS
	__int8		nDual;					// 011020 LTS
	__int8		nStep;					// 011020 LTS
	DWORD		LadderScore;
}	t_RequestCommanderRegData;

typedef struct CommanderVotingResult_P
{
	char		Type;	// Attacker, Defender, Reinforce
	int			ID;
	char		Name[NW_NAME_MAX];
	short		Level;					// 011028 LTS
	char		Fame;
	short int	Face;
	short int	Gender;		
	short int	Class;					// 011016 LTS
	__int8		nDual;					// 011020 LTS
	__int8		nStep;					// 011020 LTS
	DWORD		LadderScore;
}	t_CommanderVotingResult;

typedef	struct ChangeSquad_P
{
	char	Nation;
	char	WarfieldNo;
	char	OldSquadNo;
	char	NewSquadNo;
}	t_ChangeSquad;

typedef	struct JoinSquad_P
{
	char	Nation;
	char	WarfieldNo;
	char	SquadNo;
}	t_JoinSquad;

typedef struct SetLoadingPoint_P
{
	char	Nation;
	char	WarfieldNo;
	char	SquadNo;
	char	LoadingPoint;
}	t_SetLoadingPoint;

typedef struct FameData_P
{
	signed char	Fame;
}	t_FameData;

typedef struct Delivery_P
{
	WORD	Port;
	DWORD	UserID;
	WORD	Size;
	char	Data[MAX_STRING_PK];
}	t_Delivery_R;

typedef struct Delivery_K
{
	DWORD	UserID;
	WORD	Size;
	int		nType; // 030518 kyo
	BYTE	Data[MAX_STRING_PK]; // 030518 kyo
	//char	Data[MAX_STRING_PK];
}	t_Delivery_A;

typedef struct NWMapMove_P
{
	char	WarfieldNo;
	char	SquadNo;
}	t_NWMapMove;

typedef struct TileDont_P
{
	char	WarfieldNo;
	char	TypeNumber;
	char	Value;
}	t_TileDont;

typedef struct SquadChat_P
{
	char	Type;
	char	Size;
	char	Message[MAX_STRING_PK];
}	t_SquadChat;

typedef struct WarfieldInfo_P
{
	char	AttackWarfieldNo;
	char	DefenceWarfieldNo;
}	t_WarfieldInfo;

typedef struct WarfieldPossession_P
{
	char	RequestType;
	char	Possession[NW_WARFIELD_COUNT];
}	t_WarfieldPossession;

typedef struct WarfieldData1_P			//����, ��ȣ�� 
{
	char	GuardStoneCount;
	char*   GuardStoneStatus;
	char	CastleGateWayCount;
	char*	CastleGateWayStatus;
}	t_WarfieldData1;

typedef struct WarfieldData2_P			// ���� ���� �ð�, ���,����,������ ��
{
	DWORD	RemainTime;
	int		DefencerCount;				// 010927 LTS
	int		AttackerCount;
	int		ReinforceCount;
}	t_WarfieldData2;

typedef struct WarfieldData3_P			//�δ����� 
{
	char	Type;						// Attacker, Defencer, Reinforce
	WORD	MemberCount[NW_SQUAD_MAX];
}	t_WarfieldData3;

typedef	struct RequestCheckWarNo_P
{
	//char	Size;
	WORD	Port;
	int		ServerID;
}	t_RequestCheckWarNo;

typedef struct AnswerCheckWarNo_P
{
	BYTE	WarNo;
	int		ServerID;
}	t_AnswerCheckWarNo;

typedef struct SetCommander_P
{
	char	CommanderName[NW_NAME_MAX];
}	t_SetCommander;

typedef struct RequestWarfieldWarData_P
{
	char	WarfieldNo;
	char	Nation;
}	t_RequestWarfieldWarData;

typedef struct SWarfieldPossession_P
{
	char	WarfieldNo;
	char	Possession;
}	t_SWarfieldPossession;

typedef struct RequestSubstractMoney_P
{
	int		Nation;
	char	Type;
	WORD	MapServerPort;
	double	Money;
}	t_RequestSubstractMoney;

typedef struct AnswerSubstractMoney_P
{
	char	Type;
	char	Result;
}	t_AnswerSubstractMoney;

typedef struct SquadLoadingPoint_P
{
	char	SquadLoadingPoint[NW_SQUAD_KIND][NW_SQUAD_MAX];
}	t_SquadLoadingPoint;

typedef struct NWSquadRare_P
{
	char	SquadRare[NW_SQUAD_KIND][NW_SQUAD_MAX][NW_SQUAD_RARE_MAX];
}	t_NWSquadRare;


// Notice Packet _________________
typedef struct NoticeJoinVoteA_
{
	char	Type;
	char	WarfieldNo;
	short	VoteCount;							// 011028 LTS
	DWORD	RemainTime;
}	t_NoticeJoinVoteA;

typedef struct NoticeJoinVoteD_
{
	char	Type;
	char	Nation;
}	t_NoticeJoinVoteD;

typedef struct NoticePrepare1_				// In Case, Not Unified Warfield
{
	char	Type;
	char	LeadCandidaterName[NW_NAME_MAX];
	char	WarfieldNo;
	DWORD	RemainTime;
}	t_NoticePrepare1;

typedef struct NoticePrepare1Reinforce_
{
	char	Type;
	char	AttackNation;
	char	DefenceNation;
	char	WarfieldNo;
	DWORD	RemainTime;
}	t_NoticePrepare1Reinforce;

typedef struct NoticePrepare2_
{
	char	Type;
	char	WarfieldNo;
	char	CommanderName[NW_NAME_MAX];
	DWORD	RemainTime;
}	t_NoticePrepare2;

typedef struct NoticePrepare2Reinforce_
{
	char	Type;
	char	AttackNation;
	char	DefenceNation;
	char	WarfieldNo;
	DWORD	RemainTime;
}	t_NoticePrepare2Reinforce;

typedef struct NoticePrepare3_				// In Case, Unified Warfield
{
	char	Type;
	char	LeadCandidaterName[NW_NAME_MAX];
	char	WarfieldNo;
	DWORD	RemainTime;
}	t_NoticePrepare3;

typedef struct NoticePrepare3Reinforce_
{
	char	Type;
	char	DefenceNation;
	DWORD	RemainTime;
}	t_NoticePrepare3Reinforce;

typedef struct NoticePrepare4_
{
	char	Type;
	char	WarfieldNo;
	char	CommanderName[NW_NAME_MAX];
	DWORD	RemainTime;
}	t_NoticePrepare4;

typedef struct NoticePrepare4Reinforce_
{
	char	Type;
	char	DefenceNation;
	DWORD	RemainTime;
}	t_NoticePrepare4Reinforce;

typedef struct NoticeWar1A_
{
	char	Type;
	char	DefenceNation;
	char	WarfieldNo;
	DWORD	RemainTime;
}	t_NoticeWar1A;

typedef struct NoticeWar1D_
{
	char	Type;
	char	AttackNation;
	char	WarfieldNo;
	char	tmp;// 030520 kyo
	DWORD	RemainTime;
}	t_NoticeWar1D;

typedef struct NoticeWar1Reinforce_
{
	char	Type;
	char	AttackNation;
	char	DefenceNation;
	char	WarfieldNo;
	DWORD	RemainTime;
}	t_NoticeWar1Reinforce;

typedef struct NoticeWar2A_
{
	char	Type;
	char	DefenceNation;
	char	WarfieldNo;
	DWORD	RemainTime;
}	t_NoticeWar2A;

typedef struct NoticeWar2D_
{
	char	Type;
	char	DefenceNation;
	char	AttackNation;
	char	WarfieldNo;
	DWORD	RemainTime;
}	t_NoticeWar2D;

typedef struct NoticeWar2Reinforce_
{
	char	Type;
	char	DefenceNation;
	char	WarfieldNo;
	DWORD	RemainTime;
}	t_NoticeWar2Reinforce;

typedef	struct NoticeWarPeace1V_				// War Result	// 011025 LTS
{
	char	Type;
	char	SecretWarfieldNo;	
	char	WarfieldNo;
	DWORD	Money;
	DWORD	Warfield1RemainTime;
	DWORD	Warfield2RemainTime;
	DWORD	Warfield3RemainTime;
}	t_NoticeWarPeace1V;

typedef	struct NoticeWarPeace1D_				// War Result	// 011025 LTS
{
	char	Type;
	char	WarfieldNo;
	DWORD	Money;
	DWORD	Warfield1RemainTime;
	DWORD	Warfield2RemainTime;
	DWORD	Warfield3RemainTime;
}	t_NoticeWarPeace1D;

typedef struct NoticeWarPeace1Reinforce_						// 011025 LTS
{
	char	Type;
	char	SecretWarfieldNo;
	char	WarfieldNo;
	char	VictoryNation;
	char	DefeatNation;
	DWORD	Warfield1RemainTime;								
	DWORD	Warfield2RemainTime;
	DWORD	Warfield3RemainTime;
}	t_NoticeWarPeace1Reinforce;

typedef struct NoticeWarPeace2_									// 011025 LTS
{
	char	Type;
	DWORD	Warfield1RemainTime;								
	DWORD	Warfield2RemainTime;
	DWORD	Warfield3RemainTime;
}	t_NoticeWarPeace2;

struct NOTICE_SOPEN
{
	char	Type;
	char	WarfieldNo;
};

typedef struct Delivery_Notice_
{
	WORD	Port;
	DWORD	UserID;
	char	Nation;
	WORD	Size;
	char	Data[MAX_STRING_PK];
}	t_Delivery_Notice;

typedef struct RemainTime_
{
	char	WarfieldNo;
	char	Status;
	DWORD	RemainTime;
}	t_RemainTime;

typedef struct WarControl_				// 011025 LTS			// ���Ｍ�������� ����ǰ� �Ѵ�.	
{
	char	Type;			// 0 : Set	 1 : View
	char	WarfieldNo;		// 0 : 5991, 1 : 5992, 2 : 5993
	char	Status;			// 1 : ��ȭ, 2 : ��ǥ, 3 : �����غ�, 4 : ���� 
	char	Active;			// 0 : ����, 1 : ����, 2 : Ŭ���� 
}	t_WarControl;

typedef struct WarLoopTime_				// 011025 LTS
{
	char	Type;			// 0 : Set,  1 : View	
	char	WarfieldNo;		// 0 : 5991, 1 : 5992, 2 : 5993
	char	Status;			// 1 : ��ȭ, 2 : ��ǥ, 3 : �����غ�, 4 : ���� 
	DWORD	LoopTime;		// SetLoopTime, CurrentLoopTime			//�ð�����
}	t_WarLoopTime;

typedef struct SecretOpen_				// 011025 LTS
{
	char	WarfieldNo;
	char	isOpen;
}	t_SecretOpen;

typedef	struct	CheckNationMemberCount_
{
	char	WarfieldNo;
	char	Nation;
}	t_CheckNationMemberCount;
typedef	struct	CheckNationMemberCountR_
{
	char	WarfieldNo;
	char	Result;
}	t_CheckNationMemberCountR;

typedef struct	FameExpChange_			// 020115 LTS
{
	short int	GainedFame;
	DWORD		GainedExp;
}	t_FameExpChange;

struct WAR_RESULT
{
	int			BYCount;
	int			ZYCount;
	int			YLBYCount;
	int			YLZYCount;
	int			BYDeathCount;
	int			ZYDeathCount;
	WORD		WarfieldPort;   // 030509 kyo char�� �� ������.
	char		VictoryTeam;	// 030509 kyo char�� �� ������.
};

struct DONT_DATA
{
	int			Size;
	int			DontNo[MAX_DONT_DATA];
	int			Status[MAX_DONT_DATA];
};

struct DONT_CHANGE
{
	int DontNo;
	int Status;
};

struct GUARD_KILLER
{
	int KillerID;
	int GuardID;
};

struct NEW_WARFIELD_STATUS
{
	char	Status[MAX_NEW_WARFIELD];
};

struct NEW_WARFIELD_DATA1
{
	DWORD	RemainTime;
	int		TeamCount[2]; // 030509 kyo char�� �� ������.
	char	GuardStatus[2][5];
};

struct NOTICE_WAR_PEACE
{
	char	Type;
	int     WarNo;					// ���� �����ȣ
	char    RemainTime[3][2];		// �Ϲ������� 2�� , ���������� 1��
	char	SOpenWarfieldNo;		// ��������� ���� ������
};

struct NEWWAR_START
{
	DWORD			dwTerm;			// ��е��� ��������
	char			WarfieldNo;
	unsigned char	LevelMin;
	unsigned char	LevelMax;
	unsigned char	btNationPoint;	// ������ ���� ����Ʈ
};

struct GUARD_BROKE//reece
{
	int				nWarfieldNo;	// 1.4 Patch.
	int				aRemainGuard[2][4];	// ���� ǥ�ø� ����
	char			BrokeTeamNo;
	char			Type;							// 0 : ���� 1 : ��ȣ��
	char			GuardNo;
	short			X;
	short			Y;
};

typedef union NationWar_P
{
	t_CommonDataC				CommonDataC;
	t_CommonDataDw				CommonDataDw;
	t_CheckVote					CheckVote;
	t_WarfieldStatusChange		WarfieldStatusChange;
	t_WarBBS					WarBBS;
	t_WarfieldStatus			WarfieldStatus;
	t_WarfieldStatusM			WarfieldStatusM;
	t_VoteData					VoteData;
	t_RequestSquadInfo			RequestSquadInfo;
	t_SquadInfo					SquadInfo;
	t_SquadInfo2				SquadInfo2;
	t_RequestCommanderVoteData	RequestCommanderVoteData;
	t_RequestCommanderRegData	RequestCommanderRegData;
	t_CommanderVoteData			CommanderVoteData;
	t_CommanderVoteData2		CommanderVoteData2;
	t_CommanderVotingResult		CommanderVotingResult;
	t_ChangeSquad				ChangeSquad;
	t_JoinSquad					JoinSquad;
	t_SetLoadingPoint			SetLoadingPoint;
	t_FameData					FameData;
	t_Delivery_R				Delivery_R;
	t_Delivery_A				Delivery_A;
	t_NWMapMove					NWMapMove;
	t_TileDont					TileDont;
	t_SquadChat					SquadChat;
	t_WarfieldInfo				WarfieldInfo;
	t_RegSquadLeader			RegSquadLeader;			//������ ��Ŷ 
	t_WarfieldPossession		WarfieldPossession;
	t_WarfieldData1				WarfieldData1;
	t_WarfieldData2				WarfieldData2;
	t_WarfieldData3				WarfieldData3;
	t_RequestCheckWarNo			RequestCheckWarNo;
	t_AnswerCheckWarNo			AnswerCheckWarNo;
	t_SetCommander				SetCommander;
	t_RequestWarfieldWarData	RequestWarfieldWarData;
	t_SWarfieldPossession		SWarfieldPossession;
	t_RequestSubstractMoney		RequestSubstractMoney;
	t_AnswerSubstractMoney		AnswerSubstractMoney;
	t_SquadLoadingPoint			SquadLoadingPoint;
	t_NWSquadRare				NWSquadRare;
	t_NoticeJoinVoteA			NoticeJoinVoteA;
	t_NoticeJoinVoteD			NoticeJoinVoteD;
	t_NoticePrepare1			NoticePrepare1;
	t_NoticePrepare1Reinforce	NoticePrepare1Reinforce;
	t_NoticePrepare2			NoticePrepare2;
	t_NoticePrepare2Reinforce	NoticePrepare2Reinforce;
	t_NoticePrepare3			NoticePrepare3;
	t_NoticePrepare3Reinforce	NoticePrepare3Reinforce;
	t_NoticePrepare4			NoticePrepare4;
	t_NoticePrepare4Reinforce	NoticePrepare4Reinforce;
	t_NoticeWar1A				NoticeWar1A;
	t_NoticeWar1D				NoticeWar1D;
	t_NoticeWar1Reinforce		NoticeWar1Reinforce;
	t_NoticeWar2A				NoticeWar2A;
	t_NoticeWar2D				NoticeWar2D;
	t_NoticeWar2Reinforce		NoticeWar2Reinforce;
	t_NoticeWarPeace1V			NoticeWarPeace1V;
	t_NoticeWarPeace1D			NoticeWarPeace1D;
	t_NoticeWarPeace1Reinforce	NoticeWarPeace1Reinforce;
	t_NoticeWarPeace2			NoticeWarPeace2;
	t_Delivery_Notice			Delivery_Notice;
	t_RemainTime				RemainTime;
	t_WarControl				WarControl;			
	t_WarLoopTime				WarLoopTime;			// 011025 LTS
	t_SecretOpen				SecretOpen;
	t_CheckNationMemberCount	CheckNationMemberCount;
	t_CheckNationMemberCountR	CheckNationMemberCountR;
	t_FameExpChange				FameExpCahnge;			// 020115 LTS
	WAR_RESULT					WarResult;
	DONT_DATA					DontData;
	DONT_CHANGE					DontChange;
	GUARD_KILLER				GuardKiller;
	NEW_WARFIELD_STATUS			NWStatus;
	NEW_WARFIELD_DATA1			NWarfieldData1;
	NOTICE_WAR_PEACE			NoticeWarPeace;
	NEWWAR_START				NewWarStart;
	NOTICE_SOPEN				NoticeSOpen;
	GUARD_BROKE					GuardBroke;
	t_CheckSquadMemberCount		CheckSquadMemberCount;		// Hades War �δ� �ο���
	t_CheckSquadMemberCountR	CheckSquadMemberCountR;		// Hades War �δ� �ο�üũ ���
	NEO_WARFIELD_DATA			NeoWarfieldData;			// ������ ������ ���ۿ�
	NEO_WAR_RESULT				NeoWarResult;				// 1.4 �� ������ ��� ����
	GUARD_CAN_NOT_BROKE			GuardCanNotBroke;			// ���带 �μ� �� ���� ���� ����
	REMAIN_GUARD				RemainGuard;				// ���� ������� ���� ��ȯ
	tagWarfieldPeaceMove		WarfieldPeaceMove;			// 1.4+ ��ȭ�Ⱓ ������ �̵�.
	tagWarfieldPeaceMoveResult	WarfieldPeaceMoveR;			// 1.4+ ��ȭ�Ⱓ ������ �̵� ���.
	tagWarfieldInfo				WarfieldInfoToManager;		// 1.4+ ���� ������������ ������ �����ڿ� ���¸� ��û.
	tagWarfieldInfoResult		WarfieldInfoFromManager;	// 1.4+ ���� ���������� ������ �����ڿ� ���¸� ��ȯ.
} t_NationWar;

typedef struct LocalWarInfo1_							// LTS LOCALWAR
{
	short	ManCount[NW_NATION_COUNT];
	char	Index;				// MapIndex		
	char	tmp; // 030518 kyo
}	t_LocalWarInfo1;

typedef struct LocalWarInfo2_
{
	char	SealStoneInfo[NW_NATION_COUNT][9];
	char	tmp[5]; // 030518 kyo
}	t_LocalWarInfo2;

typedef struct LocalWarPointChanged_
{
	__int64	RemainTime;		// 020115 LTS
	unsigned short	Point[3];				// 020130 LTS
	char tmp[2];// 030518 kyo
}	t_LocalWarPointChanged;


typedef struct LocalWarInfo_
{
	t_LocalWarInfo1				LocalWarInfo1[7];			// �־��� ���
	t_LocalWarInfo2				LocalWarInfo2;
	t_LocalWarPointChanged		LocalWarPointChanged;	
	char						LocalWarDefencePoint[3];
}	t_LocalWarInfo;


typedef struct LocarWarUserAdd_
{
	char	Index;				// LocalWarfieldServer Index
	char	Nation;
}	t_LocalWarUserAdd;

typedef struct UserJoinLocalWar_ 
{
	unsigned int	ServerID;
}	t_UserJoinLocalWar;

typedef struct SealStoneBroked_
{
	WORD	MapNumber;
	char	Nation;
	WORD	LocateX;
	WORD	LocateY;
}	t_SealStoneBroked;

typedef struct SealStoneAttacked_
{
	WORD	MapNumber;
	char	Nation;
	WORD	LocateX;
	WORD	LocateY;
}	t_SealStoneAttacked;

typedef struct NationPointChaned_
{
	unsigned short	NationPoint[3];		// 020130 LTS
}	t_NationPointChanged;

typedef struct ActionStatus_
{
	int		ServerID;
	char	Direction;
	char	nCurrentAction;
	char	ChairNum;						// LTS SITDOWN BUG
}	t_ActionStatus;

typedef struct SDChanged_
{
	int		ServerID;
	char	Direction;
}	t_SDChanged;

typedef struct EventLocalWarMessage_
{
	char			EventStep;
	char			EventStatus;
	unsigned char	MinLevel;
	unsigned char	MaxLevel;
	POINTS			EventJoinLocation[3];			
}	t_EventLocalWarMessage;

typedef	struct EventJoin_
{
	char			Nation;
	unsigned char	Level;
}	t_EventJoin;

typedef struct DeleteEventJoin_				// DB���󿡴� NationWar�� ���� �Ǿ������� �������.	// 020115 LTS
{
	char	UserName[20];
	char	EventNo;
}	t_DeleteEventJoin;

typedef	struct	EventPoint_
{
	int		Point;
}	t_EventPoint;

typedef struct EventRemainTime_				// LTS BUG
{
	DWORD	RemainTime;
}	t_EventRemainTime;

typedef struct AI_Status_					// LTS AI2 TEMP			// ����׿�
{
	int		ID;
	int		PatternType;
}	t_AI_Status;	

typedef struct EVMonster_					// LTS AI2 TEMP
{
	int		Start;
	int		GroupNo;
}	t_EVMonster;

typedef struct CommunityAction_				// LTS ACTION
{
	int		ID;
	char	Action;
	char	Direction;						
	char	Result;
}	t_CommunityAction;

typedef struct CommunityActionS_			// LTS ACTION
{
	char	Action;
	char	Direction;
}	t_CommunityActionS;

typedef struct LocalWarResult_				// LTS NEW LOCALWAR
{
	char	NationIndex;
	char	Result;
}	t_LocalWarResult;


typedef struct LocalWarChat_				// LTS NEW LOCALWAR	
{
	char	NationIndex;
	char	Message[MAX_PATH];
}	t_LocalWarChat;

typedef struct LocalWarDefencePoint_		// LTS NEW LOCALWAR
{
	int		Point[3];
}	t_LocalWarDefencePoint;

typedef struct AIFog_						// LTS NEW AI
{
	char	Type;
	DWORD	Delay;
	POINTS	Location[FOG_MAX];					
}	t_AIFog;

typedef struct AIActionTest_
{
	char	Action[3];
}	t_ActionTest;

typedef struct AIMove_						// LTS NEW AI
{
	int		ID;
	int		X;
	int		Y;
}	t_AIMove;

typedef struct AINPCAction_					// LTS DRAGON MODIFY
{
	int		ID;
	char	Action;
}	t_AINPCAction;

typedef struct LordWarTeamChange_
{
	int		ID;
	char	TeamNo;
}	t_LordWarTeamChange;

typedef struct LocalWarBeginTime_
{
	int		nHour;
} t_LocalWarBeginTime;


typedef union LocalWar_
{
	t_LocalWarInfo				LocalWarInfo;
	t_Delivery_R				Delivery_R;
	t_Delivery_A				Delivery_A;
	t_CommonDataC				CommonDataC;
	t_CommonDataDw				CommonDataDw;
	t_LocalWarUserAdd			LocalWarUserAdd;
	t_UserJoinLocalWar			UserJoinLocalWar;
	t_SealStoneBroked			SealStoneBroked;
	t_SealStoneAttacked			SealStoneAttacked;
	t_LocalWarPointChanged		LocalWarPointChanged;
	t_NationPointChanged		NationPointChanged;
	t_ActionStatus				ActionStatus;
	t_SDChanged					SDChanged;
	t_EventLocalWarMessage		EventLocalWarMessage;
	t_EventJoin					EventJoin; 
	t_DeleteEventJoin			DeleteEventJoin;		// 020115 LTS
	t_EventPoint				EventPoint;				// 020115 LTS
	t_EventRemainTime			EventRemainTime;		// LTS BUG
	t_AI_Status					AI_Status;				// LTS AI2 TEMP				// ����׿�
	t_EVMonster					EVMonster;				// LTS AI2 TEMP
	t_CommunityAction			CommunityAction;		// LTS ACTION
	t_CommunityActionS			CommunityActionS;		// LTS ACTION
	t_LocalWarResult			LocalWarResult;			// LTS NEW LOCALWAR
	t_LocalWarChat				LocalWarChat;			// LTS NEW LOCALWAR
	t_FameExpChange				FameExpChange;			// LTS NEW LOCALWAR
	t_LocalWarDefencePoint		LocalWarDefencePoint;	// LTS NEW LOCALWAR
	t_AIFog						AIFog;					// LTS NEW AI
	t_AIMove					AIMove;					// LTS NEW AI
	t_ActionTest				ActionTest;				// LTS NEW AI
	t_AINPCAction				AINPCAction;			// LTS DRAGON MODIFY
	t_LordWarTeamChange			LordWarTeamChange;
	t_LocalWarBeginTime			LocalWarBeginTime;		// finito 050707 for announcing time until localwar begins

} t_LocalWar;

#endif

