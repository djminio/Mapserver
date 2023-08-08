// SkillMgr.h: interface for the CSkillMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKILLMGR_H__6108FBB6_55CB_4499_832C_6B1598CC6824__INCLUDED_)
#define AFX_SKILLMGR_H__6108FBB6_55CB_4499_832C_6B1598CC6824__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define		SKILL_EXP_FIX_					10000
#define		SKILL_ABILITY_FIX_				10000
#define		NPC_ITEM_TABLE_X				61
#define		NPC_ITEM_TABLE_Y				64
#define		NPC_ITEM_TABLE_TOTAL_ITEM		60							//���� �ȿ� �ִ� �������� ��// 
#define		NPC_ITEM_TABLE_START_ITEM_POS	2							//�迭���� ��ġ
#define		NPC_ITEM_TABLE_PROBABILITY_POS	62							//�迭���� ��ġ.�����δ� 50��° ��ġ.
#define		NPC_ITEM_TABLE_BETWEEN_POS		63							//�迭���� ��ġ.
#define		NPC_ITEM_TABLE_LEVEL_POS		1							//�迭���� ��ġ.

const int	MAX_ITEM_SKILL_COUNT	=	10000;//020527 lsw
const int	SADONIX_NO				=	1046;
const int	BLESSLEAF_NO			=	1047;

const int	STATIC_RARE_VIEW_FORCE_TIME = 60;

#define		SKILLFAIL_NO_TOOL			1	// �ʿ� ������ ����.
#define		SKILLFAIL_NO_MATTER			2	// �ʿ� ��ᰡ ����.

#define		SKILL_LEVEL_EXP_TABLE_MAX_	100
#define		SKILL_EXP_TABLE_MAX_		100

const int	HP_RECOVER_RATE						=	5		;//1ȸ �ڵ� ȸ�� �ۼ�������
const int	DEFAULT_RECOVER_HP_MAX_PERCENT		=	50		;//�ִ� �ڵ� ȸ�� �ۼ�������
const int	DEFAULT_RECOVER_HP_TIME				=	25000	;//�и�������

const int	MANA_RECOVER_RATE					=	5		;//1ȸ �ڵ� ȸ�� �ۼ�������
const int	DEFAULT_RECOVER_MANA_MAX_PERCENT	=	50		;//�ִ� �ڵ� ȸ�� �ۼ�������
const int	DEFAULT_RECOVER_MANA_TIME			=	30000	;//�и�������

const int	DIVINE_RECOVER_RATE					=	5		;//1ȸ �ڵ� ȸ�� �ۼ�������
const int	DEFAULT_RECOVER_DIVINE_MAX_PERCENT	=	100		;//�ִ� �ڵ� ȸ�� �ۼ�������
const int	DEFAULT_RECOVER_DIVINE_TIME			=	20000	;//�и������� �����ڰ� �ణ�� ������

const int	HUNGRY_CHANGE_RATE					=	5		;//1ȸ �ڵ� ȸ�� �ۼ�������
const int	DEFAULT_CHANGE_HUNGRY_MAX_PERCENT	=	100		;//�ִ� �ڵ� ȸ�� �ۼ�������
const int	DEFAULT_CHANGE_HUNGRY_TIME			=	10000	;//�и�������

const int	CP_CHANGE_RATE				    	=	2		;//1ȸ �ڵ� ȸ�� �ۼ�������
const int	DEFAULT_CHANGE_CP_MAX_PERCENT		=	100		;//�ִ� �ڵ� ȸ�� �ۼ�������
const int	DEFAULT_RECOVER_CP_TIME				=	10000	;//�и�������

const int	COMBAT_RECOVERY_TIME				=	5000	;//5�� ���� cp �ø� // 030415 kyo 

////////////////////////////////////////////////////////////////
// ��ų ���� �� �ϴ°� ���õȰ�
#define ITEMMAKE_YOUCAN					10000
#define ITEMMAKE_UNKNOWN				-1
#define ITEMMAKE_NOT_RESOURCE			-2	
#define ITEMMAKE_NOT_TOOL				-3
#define ITEMMAKE_NOT_FLATFORM			-4
#define ITEMMAKE_TIRED					-5
#define ITEM_MAKE_NO_JOIN				-6
#define ITEMMAKE_GOGOGO					-7		// ����Ȯ�� 100%  �۾��� ���� ��� ������ Definition...
#define ITEMMAKE_NO						-8
#define SKILLFAIL_NOT_PROPER_PLACE		-9  // ����� ���� ������ ��Ұ� �ƴմϴ�. 
#define SKILLFAIL_UNKNOWN_ITEM			-10
#define SKILLFAIL_NOT_RESOURCE			-20	
#define SKILLFAIL_NOT_FLATFORM			-40
#define SKILLFAIL_TIRED					-41
#define SKILLFAIL_NOT_TOOL48			-48
#define SKILLFAIL_NOT_TOOL49			-49
#define SKILLFAIL_NOT_TOOL50			-50
#define SKILLFAIL_NOT_TOOL51			-51
#define SKILLFAIL_NOT_TOOL52			-52
#define SKILLFAIL_NOT_TOOL53			-53
#define SKILLFAIL_NOT_TOOL54			-54
#define SKILLFAIL_NOT_TOOL55			-55
#define SKILLFAIL_NOT_TOOL56			-56
#define SKILLFAIL_NOT_TOOL57			-57
#define SKILLFAIL_NOT_TOOL58			-58
#define SKILLFAIL_NOT_TOOL59			-59
#define SKILLFAIL_NOT_TOOL60			-60
#define SKILLFAIL_NOT_TOOL61			-61
#define SKILLFAIL_NOT_TOOL62			-62
#define SKILLFAIL_NOT_TOOL63			-63
#define SKILLFAIL_NOT_TOOL64			-64
#define SKILLFAIL_NOT_TOOL65			-65
#define SKILLFAIL_NOT_TOOL66			-66
#define SKILLFAIL_NOT_TOOL67			-67
#define SKILLFAIL_NOT_TOOL68			-68
#define SKILLFAIL_NOT_TOOL69			-69
#define SKILLFAIL_NOT_TOOL70			-70
#define SKILLFAIL_NOT_TOOL71			-71
#define SKILLFAIL_NOT_TOOL72			-72
#define SKILLFAIL_NOT_TOOL73			-73
#define SKILLFAIL_NOT_TOOL74			-74
#define SKILLFAIL_NOT_TOOL75			-75
#define SKILLFAIL_NOT_TOOL76			-76
#define SKILLFAIL_NOT_TOOL77			-77
#define SKILLFAIL_NOT_TOOL78			-78
#define SKILLFAIL_NOT_TOOL79			-79
#define SKILLFAIL_NOT_TOOL80			-80
#define SKILLFAIL_NOT_TOOL81			-81
#define SKILLFAIL_NOT_TOOL82			-82
#define SKILLFAIL_NOT_TOOL83			-83
#define SKILLFAIL_NOT_TOOL84			-84
#define SKILLFAIL_NOT_TOOL85			-85
#define SKILLFAIL_NOT_TOOL86			-86
#define SKILLFAIL_NOT_TOOL87			-87
#define SKILLFAIL_NO_SHEAR				-100
#define SKILLFAIL_NO_MEET				-101
#define SKILLFAIL_NO_MINING				-102	// ���̻� �ĳ����� ���..
#define SKILLFAIL_NO_DIGGING			-103	// ���̻� ĳ�� ���ʰ� ���.
#define SKILLFAIL_NO_CUTTING			-104	// ���̻� �߶� ������ ���. 
#define SKILLFAIL_NO_SEED				-105	// �۹��� �ƴ϶� ��Ȯ�Ҽ� �����ϴ�. 
#define SKILLFAIL_NOT_YET_HARVEST		-106	// ���� ��Ȯ�Ҷ��� ���� �ʾҽ��ϴ�. 
#define SKILLFAIL_NOT_YET_SOW			-107	// ���� ô���ϰų� �ѱ��뿡 �ʹ� ���� �ɾ����ϴ�. 
#define SKILLFAIL_NO_MORE_RACLAIM		-108	// �׸� �����ص� �˴ϴ�. 
#define SKILLFAIL_NO_FISHING			-109	// ���̻� ����Ⱑ �����ϴ�
#define SKILLFAIL_LOW_LEVEL_TO_TAMING	-110	//taming�� �� ���� �ɷ�ġ�� ������ ������ �ִ�
#define SKILLFAIL_NO_TAMING_ALLOWED		-111	//taming�� �� ���� ���
#define SKILLFAIL_TARGET_IS_NOT_NPC		-112	//taming�� �� �ִ� NPC�� �ƴϴ�

#define MAX_EARTHSKILL				5000

////////////////////////////////////////////////////////////////////////
// ��ų �� ����
#define	TOOL_FARMING				1
#define	TOOL_MINING					2
#define	TOOL_FISHING				3
#define	TOOL_CHOPPING				4
#define	TOOL_HUB					5	
#define	TOOL_NPC_GENER				6
#define	TOOL_DONTSKILL				7

#define SKILLTARGETTYPE_ITEM_		10
#define SKILLTARGETTYPE_CHAR_		20
#define SKILLTARGETTYPE_MAP_		30
#define SKILLTARGETTYPE_HERO_		40
#define SKILLTARGETTYPE_TABLE_      50
#define SKILLTARGETTYPE_2NDGM_      50
////////////////////////////////////////////////////////////////////////

class CItem_Join
{
public :
	int no;
	int item_id;
	char item_name[31];
	int item_amount;
	char han_name[31];	
	int need_know;	
	int teach_place;	
	int need_skill1;	
	int skill1_minimum;	
	int skill1_maximum;	
	int need_skill2;	
	int skill2_minimum;	
	int skill2_maximum;	
	int tech_price;	
	int Tool_kind;	
	int Flatform_kind;	
	int resource1;	
	int resource1_amount;	
	int resource2;	
	int resource2_amount;	
	int resource3;	
	int resource3_amount;	
	int resource4;	
	int resource4_amount;	
	int Result_resource1;	
	int Result_resource1_amount;	
	int Result_resource2;	
	int Result_resource2_amount;	
	int reutilizerble;	
	int k1;	
	int k2;
	char explain[500];		// 0710 YGI
	char txt[220];

public :
	void ReadItemJoin( char *string );

};

#define MAX_LEARN_ITEM_CONVERT 40
typedef struct LEARNITEMCONVERT
{
	int iBeforeItemNo;
	int iAfterItemNo;
}t_LearnItemConvert;
extern LEARNITEMCONVERT LIC[MAX_LEARN_ITEM_CONVERT];

#define RETURN_SMT_ITEMNO 0
#define RETURN_SMT_DEMAND 1

typedef struct  tagMAPSKILLTABLE
{
	int type;							//�Ϲ����� ������� Ÿ���� ���->0 / NPC ���� ��ġ ����->1
	int x, y;							//�ش� ����Ӽ��� ���� Ÿ���� ��ǥ(Ÿ�ϴ���) //��ȹ�䱸->�������̽��� ������� ����
	int skillno;						//����Ӽ� ������ȣ
	int tile_Range;						//�ش�Ÿ�Ϸκ��� ȿ���� ��ȿ�� Ÿ�� �Ÿ�(������)
	int probability;						//�ش����� ������ Ȯ��
	int type_Num;					//NPC ���� Ÿ�� ��ȣ(0~99) // NPC�ϰ�쿡�� ���...
	int subType;						//�ش� ����� ���� ���� �����Ͱ�
	
	struct  tagMAPSKILLTABLE *prev;		//���� ��ų �Ӽ� ���̺� ������	
	struct  tagMAPSKILLTABLE *next;		//���� ��ų �Ӽ� ������
}	MAPSKILLTABLE, *lpMAPSKILLTABLE;

typedef struct
{
	short reclaim_old[ MAX_EARTHSKILL ];
	short reclaim[ MAX_EARTHSKILL ];
	short reclaimcount;
	short mining_old[ MAX_EARTHSKILL ];
	short mining[ MAX_EARTHSKILL ];
	short miningcount;
	short fishing_old[ MAX_EARTHSKILL ];
	short fishing[ MAX_EARTHSKILL ];
	short fishingcount;
	short cutting_old[ MAX_EARTHSKILL ];
	short cutting[ MAX_EARTHSKILL ];
	short cuttingcount;
	short digging_old[ MAX_EARTHSKILL ];
	short digging[ MAX_EARTHSKILL ];
	short diggingcount;
}t_earthpower;

typedef struct RAREITEMBAG
{
	int iNo;
	int iRareItemBagPercentTableNo;
	int iGradeMin;
	int iGradeMax;
	int ItemNo[21];//0 ���� ���� ��
}t_RareItemBag;
const int MAX_RAREITEMBAG = 1000;

typedef struct BASICITEMBAG
{
	int iNo;
	int iBasicItemPercentTableNo;
	int ItemNo[21];//0���� ���°�
}t_BasicItemBag;
const int MAX_BASICITEMBAG = 1000;

typedef struct ItemControlPercent
{
	int iNo	;
	int	per[8];//0���� ��Ż�� 1~5�� ������ �׷� 6~7�� ���� �׷�
}t_ItemControlPercent;
const int MAX_ITEMCONTROLPERCENT = 1000;

typedef struct ITEMFALLPERCENT
{
	int iNo;
	int per[21];//0 ���� ��Ż �� �̴�
}t_ItemFallPercent;
const int MAX_ITEMFALLPERCENT = 1000;

typedef struct ITEMCONTROL
{
	int iNo;
	int ItemControlPercentNo;
	int ItemGroup[8];//0���� ���°� 1~5�� ������ �׷� 6~7�� ���� �׷�
	int	iFallItemCount;//������ ����, ��, �ݺ��� ȣ�� Ƚ��
}t_ItemControl;
const int MAX_ITEMCONTROL = 1000;

class CSkillMgr  
{
public:
	CSkillMgr();
	virtual ~CSkillMgr();
	void	AutoSetCanView(CHARLIST *ch);

	bool	CanViewGhost(CHARLIST *ch)		const	{return ch->bCanViewGhost;}
	bool	CanViewTrap(CHARLIST *ch)		const	{return ch->bCanViewTrap;}
	
	bool	CheckSkillNo( const int iSkillNo )const;
	bool	CheckIsYourSkill( LPCHARLIST ch, const int iSkillNo )const;
	int		CorrectLearnItem(CHARLIST *ch);

	void	CharacterToAlive(CHARLIST *ch, const int iType = 0);
	void	CharacterToGhost(CHARLIST *ch, const int iType = 0);
	
	bool	SetCanViewGhost(CHARLIST *ch, const int iTime);//�ʴ���
	bool	SetCanViewBomb(CHARLIST *ch, const int iTime);//�ʴ���
	bool	SetCanViewTrap(CHARLIST *ch, const int iTime);//�ʴ���

  bool  IncSkillCount(CHARLIST *ch, const int iType, const int iKind, const int iPoint);//�ʴ���
	void	SendSkillExp( const int iType, const t_skillexp exp, const int cn);

	int		FallItemWhenNPCDie(CHARLIST *NPC);
	
	int		GenerateNPCItem2(CHARLIST *NPC, NPC_Generation* g);

	void	RecvCMD_CONFORM_SADONIX(const t_packet &p);
private:
	void	SendCMD_CONFORM_SADONIX(const int cn, const int iItemNo,const int kind,const int x , const int y);//���� private
	bool	IsRecoverAble(const int iNow,const int iMax)const;//���� ���� �ִ뷮�� ���ؼ� �ִ뷮�� ���纸�� ������ �����ϴٸ� �����Ѵ�
	
	int		GetItemFallPercentPos(const int iFallNo);
	int		SetNPCInventory(CHARLIST *NPC, const int iItemControlNo,ItemAttr* pItem, const int iCallType = 0);
	int		SetNPCItem(const int iBagNo, const bool bIsBasic, ItemAttr *pItem,const int iCallType = 0);
	

public:
	void	AutoRecoverHp(CHARLIST *ch);
	void	AutoRecoverMp(CHARLIST *ch);
	void	AutoChangeHungry(CHARLIST *ch );//����� �������� �׳� ���� �ʴ´� Ư���� ��Ȳ������ ����(ex>����)
	void	AutoRecoverCp(CHARLIST *ch);
	void	AutoRefreshRareMakeCount(CHARLIST *ch);
	int		CheckYouCanSkillIt( const int cn, CItem_Join &join, const int skillno, const int x, const int y, const int target_id );
	int 	CheckSkillTool( LPCHARLIST ch, CItem_Join &join, const int iSkillNo, const int target_id );
	int		FindLearnItem( CHARLIST *ch, const int item_no );		// ���� ������ -1�� ����, ������ item_max�� ����
	bool	CanLearnItem( CHARLIST *ch, const int join_num )const;

	void	SkillMapper( const int cn, const int iSkillNo, const int x, const int y, const int targettype, const int target_id, const POS s );
	int		MakeItemByItemControl( ItemAttr *pItem, const int iItemControlNo ) { return SetNPCInventory(NULL, iItemControlNo, pItem );}		// 020821 YGI
private:
	int Skill_Detect_ghost					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Talk_with_ghost				(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Poisoning						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Detect_poison					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Find_traps					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Remove_traps					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Entrapment					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Detect_bomb					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Bomb_in_box					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Remove_bomb					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Stealing						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Reclaim						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Sow							(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Havest						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Mining						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Refine						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Fish_hooking					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Netting						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Cutting						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Lumbering						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Butchering					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Digging						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Makepowder					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Shear							(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Carpentry						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Blacksmithy					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Cooking						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Clothing						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Tailoring						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Bowcrafting					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Fletching						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Makepotion					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Makemetal						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Makebottle					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Candlemaking					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Snooping						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Makefire						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Taming						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Evaluate_inteligence			(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Evaluate_wisdom				(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Anatomy_judgement				(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Item_identification			(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_crapple						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_swordmanship				(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_archery						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_fencing						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_mace_fighting				(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_pierce						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_whirl						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_hurl						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_parrying					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_double_swordmanship			(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_double_macefighting			(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_magery						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Tactics_orison						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Ghost_resurrection			(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Gm_carpenter					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Gm_blacksmith					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Gm_cook						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Gm_tailor						(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Gm_bowcraft					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Gm_alchemist					(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
	int Skill_Gm_candlemaker				(const int iCn, const int iSkillNo, const int iX, const int iY, const int targettype, const int iTargetID );
};

extern CSkillMgr  SkillMgr;

extern CItem_Join	item_join[ ITEM_JOIN_MAX];
extern lpMAPSKILLTABLE	Header[8][8];
extern t_earthpower EarthPower;
extern int GiveSpecialItem(int NPCno,int dx,int dy,int MapNo,int How);
extern void SendCharacterCondition( CHARLIST* lpChar, int change_HP );
extern int Npc_Item_Table[NPC_ITEM_TABLE_X][NPC_ITEM_TABLE_Y];	//npc�� ������ ���� �����۵��� ���ִ� ���̺�
extern void RecvSkillInfo( int cn, t_client_skill_info *sp);
extern void RecvSkillCursorView( int cn, t_client_skill_cursor_view  *p);
extern BOOL LoadSkillMapTable(void);
extern bool LoadItemJoinTable( void );
extern void RecvCMD_FOOT_ON_TRAP_0_ITEM( int cn, t_client_foot_on_trap0 *p );
extern void RecvCMD_FOOT_ON_TRAP_1_ITEM( int cn, t_client_foot_on_trap1 *p );
extern void RecvSkillGauge( int cn, t_client_skill_gauge *p );
extern int AddSkillExp( int cn, int skillno, int hitrate );
extern void CheckSkillTimeElapsed( void );
extern DWORD ReturnHowLongTimeGrow( LPITEMLIST i );
extern bool youvegotitInventory( int cn, ItemAttr *item );
extern void RecvDebugChangeSkillExp( t_debug_change_skill_exp *tp );
extern int OutMessage(int cn, DWORD para1, DWORD para2);
extern int OutMessage( LPCHARLIST ch, DWORD para1, DWORD para2);
extern int OutSound(LPCHARLIST ch, const int iFileType, const int iNo);
extern void SendSkillResult( int cn, int skillno, int target_id, int x, int y, int result );
extern int GiveBasicItem(const int cn,const int iSkillTooltype,const int subType);
extern int ReturnDemandFromSkillMapTable( const int iSkillToolType, const int iTableno, const int iHitrate );
extern int ReturnFromSkillMapTable(const int cn, const int iSkillToolType, const int iTableno, const int iHitrate ,int iReturnType);
extern void SkillMapper( const int cn, const int iSkillNo, const int x, const int y, const int targettype, const int target_id, POS s );
extern int TryRareItem(int cn, const int iSkillNo, CItem_Join join, const int iTryRare, const int iRareGruop, const int iMakeCount,const int iSuccess);//020530 lsw
extern void SendViewTypeChange(const int cn, int viewtype );
extern void DecreaseEquipDuration( CHARLIST *ch, const DWORD dwDecValue, const int iItemPos, const int iTargetSprNo, const bool bIsAttacker= true,bool bIsNoCount= false);
extern bool exist(int, int, POS &) ;
extern int exchangePOS_of_Item(const int char_id, t_chr_status_info *cstatus, const POS source, const POS dest);
extern void aliveCharacter(CHARLIST *d);
extern void SendServerEachItem( const POS *pos, const ItemAttr *item, const int cn );			// ���ڸ��� �� �� ���� �����ش�.
extern void SendServerEachItem( const ItemAttr *item, const CHARLIST *ch );	// �����ͷ� ã����
extern bool LoadItemTable( void );
extern bool LoadRareItemBag();
extern bool LoadItemControlPercent();
extern bool LoadItemFallPercent();
extern bool LoadBasicItemBag();
extern bool LoadItemControl();
extern t_RareItemBag RareItemBag[MAX_RAREITEMBAG];
extern t_BasicItemBag BasicItemBag[MAX_BASICITEMBAG];
extern t_ItemControlPercent ItemControlPercent[MAX_ITEMCONTROLPERCENT];
extern t_ItemFallPercent ItemFallPercent[MAX_ITEMFALLPERCENT];
extern t_ItemControl ItemControl[MAX_ITEMCONTROL];
extern bool IsEquipAbleCheckAbleDay(const int start, const int end);
#endif // !defined(AFX_SKILLMGR_H__6108FBB6_55CB_4499_832C_6B1598CC6824__INCLUDED_)