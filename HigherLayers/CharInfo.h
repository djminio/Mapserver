// CharInfo.h: interface for the CCharInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARINFO_H__1A212137_3131_4DD3_8343_EE42343C165E__INCLUDED_)
#define AFX_CHARINFO_H__1A212137_3131_4DD3_8343_EE42343C165E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExchangeMgr.h"
#include "ItemMgr.h"

extern int MAX_EXP_LEVEL;  // CSD-040204
extern int MAX_TAC_LEVEL;  // CSD-040204

///////////////////////////////////////////////////////////////////////////////
// ĳ���Ϳ� ���� ����Ÿ
struct CHAR_DATA
{	
	BYTE			bAlive;					// ĳ������ ���翩��(	REMOVE_:0 / ALIVE_:1 / DEAD_:2 / BUFE_:3)	// Check_
	int				deadcount;					// ĳ���Ͱ� ������ ���� ������������� count
	BYTE			installType;
	DWORD			total_id;
	short			eventno;
	short			generationpos;		// NPC�ϰ�� �߻� ��ġ Table�� Index���� ����ϰ� �ִ´�.
	short			generationtype;		// NPC�ϰϿ� �߻����( GT_SKB_FILE, GT_SCRIPT );
	char			Name[20];
	int				namenumber;			// NPC_Name_Ref[ namenumber].Female�� �ǹ��Ѵ�. 
	DWORD			Exp;
	short int		Gender;						// 0:���� 1 : ����
	short int		Face;						
	short int		Class;						// 0:���� 1:�ü� 2:���� 3:������ 4:������
	short int		Spell;					// ������:0 / ������:1
	short int		fame;
	short int		timeshot; // add by rogerio
	short int       fame_pk;			// 010915 LTS //Fame_PK -> NWCharacter�� ��ü DB���� ������ NWCharacter�� ���� ���ϴ�.	// LTS AI2	//����� ���� ��ȣ���	
	NW_Character	NWCharacter;		// 010915 LTS

	short int       social_status;
	unsigned char	Tactics ;						// ������ ������� (�����ֱ� ����)
	unsigned char	Tactics_para;					// ���� skill�� ������ �Ķ���Ͱ��� ������ ����...
	short int		Race;						// ����
	short int		Str  ;				//  ��
	short int		Con  ;				//  �ǰ�
	short int		Dex  ;				//	��ø��
	short int		Wis  ;				//	����
	short int		Int  ;				//	����
	short int		MoveP;				//	�̵���
	short int		Char ;				//	�ŷ�
	short int		Endu ;				//  �����
	short int		Moral;				//	���
	short int		Luck ;				//	���
	short int		wsps ;				//  ������->���� �޸������
	//����, Armor, �Ǽ��縮 ,ETC �� ���� 	
	short int		Strw;				//  ��
	short int		Conw;				//  �ǰ�
	short int		Dexw;				//	��ø��
	short int		Wisw;				//	����
	short int		Intw;				//	����
	short int		MovePw;				//	�̵���
	short int		Charw;				//	�ŷ�
	short int		Enduw;				//  �����
	short int		Moralw;				//	���
	short int		Luckw;				//	���
	short int		wspsw;

	BYTE			item_Hit_Rate;
	BYTE			item_Deffence_Rate;

	CCharRank		name_status;		// 0927 YGI
	DWORD			scan_time;			// LTS AI2 NPC SUMMON DELAY TIME
	short int		Ac;//AC( ���� )
	short int		Job;
	
	DWORD			Money;

	//Hp Mp ����� ��
	int		Hp;
	int		HpMax;
	int		Mana;
	int		ManaMax;
	int		Hungry;	
	int		HungryMax;
	int		Cp;
	int		CpMax;

	float	fChangeHungry;//����� ��ġ ��ȭ��//020214 lsw
	
	char			MapName[20];
	unsigned char	Peacests;
	int				Sight; //020425 YGI
	short int		BodyR, BodyG, BodyB;		// �� ���� R.G.B
	short int		ClothR, ClothG, ClothB;		// �� ���� R.G.B
	short int		Age;
	short int		nk[MAX_NATION];							// ���簡1
	
	DWORD			killmon;					// 1�迭���� ų����
	DWORD			killanimal;					// ���� ų����
	DWORD			killpc;						// ���,NPC ų����
	char			KillerName[40];
	
	BYTE Ws[200];			//	����
	BYTE Ps[200];			//	�Ź�
	BYTE Skill[MAX_SKILL_NO];

	t_skillexp		skillexp[MAX_SKILL_EXP];		// 011012 lsw //��ų����ġ ����

	// ���� ������ �ִ� ������..
	ItemAttr	inv[3][3][8] ;// �κ��丮
	ItemAttr	equip[8] ;// ����
	ItemAttr	quick[7] ;// �� 
	ItemAttr	handheld ;// �տ� ��� �ִ�
	ItemAttr	bank[5][3][6];// ���࿡ ����ǰ

	short int	Item[MAX_LEARN_ITEM];		// ����� �ִ� ������		1220
	short int	ItemMax;					// ���� ����� �ִ� ������ �ִ�ġ 1220
	int			itemweight;					// ��ȯ�� ������ ID			// LTS AI2

	//  Client�� ���� Data
	short int		SprNo;
	short int		mutant;  // 0810 KHS
	short int		npc_index; // NPC index concerned by Parameter 'index'
	short int		SprType;	
	short int		ElementType; // ��õ���� �Ӽ��� �ǹ��Ѵ�. (��) �̳�: ��(fire)		
	BYTE			accessory[4];
	
	short int		mantle;		// 011018 KHS ����
	short int		jjing;      // 011030 KHS JJING

	DIRECTION		Direction;
	DWORD			IDWhoImAttacked;	// ���� ģ���� ������..
	short int		nCurrentAction;						
	short int       ox, oy;		// �ڽ��� �¾���..
	short int		X, Y;		// ���� ��ǥ( Dot ���� )
	short int		MovePathCount;
	short int		MoveLength;
	unsigned char	MoveType;
	short int		OldMoveSx,MoveSx;	// ������ǥ(Ÿ�ϴܵ� )
	short int		OldMoveSy,MoveSy;
	unsigned char   MoveDirTbl[MAX_DIR_TABLE];
	short int		MoveGox;			// �������� ��ǥ( Dot ���� )
	short int		MoveGoy;
	short int		Tox, Toy;			// Ÿ���� ������ �и���.( Dot���� )
	short int		detect_x, detect_y;
	int				path[ MAX_SHORTPATH][2];		// PathBuild()�� ���� ����..
	int				pathcount;
	// --------------  NPC Pattern---------- NPC������ ����..-
	short 			patterntype;
	short 			oldpatterntype;
	int				targetid;
	int				bossid;
	short			attackcount;		// NPC�� ����Ѵ�. ������������� �ʴ´�. 
	DWORD 			aitimedelay;
	DWORD			aidelayhowmuch;
	int				tx, ty, how;// �̵��� ���õȻ���.
	int				attacked;
	bool			notcomeinside; // ���ȿ� ���� ����. 
	//  ------------------------------------- NPC�� ������ ������ �ִ� �͵�...
	short int		Get_meat;
	char			Meat_amount;
	short int		Get_skin;
	char			Skin_amount;
	short int		Get_Wool;
	char			Wool_amount;
	short int		Get_beewax;
	char			BeeWax_amount;
	char			viewtype;
	short int		openhouse;
	short int		tame;				// tame��ġ... 
	short int		tamingable;
	short int		tamingcountdown;
	BYTE			tame_cmd;
	char			HostName[ 20]; // ������ �̸�...
	short int		HostId;
	char			TargetName[ 31]; // ������ ���� �������� �̸�.
	short			pkid;		//
	short			pkcount;	// �� ��ġ�� 3�̻��̸� PK�� �Ѱ��̴� ! 
	DWORD			cast_pk;	// BroadCast�� �ð�.
	//------------------------   ���������� ����ϴ� para...
	DWORD			WalkTime;
	DWORD			desttime;
	short int		cur_skillno; // ���� ����Ǳ� ���� �������� Skill...
	short int		cur_skillx;
	short int		cur_skilly;
	short int		cur_skilltargettype;
	short int		cur_skilltarget_id;
	short int		cur_skillKey;//030102 lsw Skill Key
	POS				cur_skillPOS;
	char			cur_skillTargetName[31];//020531 lsw
	DWORD			exetime_skill; // ����� Skill�� �ð�.

	short int		MaxWizardSpell ;
	short int		MaxPriestSpell ;

	short int		Weight, MaxWeight ;

	DWORD			tac_skillEXP[13] ;
	char			cur_tac_skill;	// ���� ������� �̷��������� Setting�Ǹ� ������� Index�� ����. ( TACTICS_Crapple....�� ���� )

	DWORD			LastTotal;
	DWORD			LastLoan;
	DWORD			LastLoan_time;
//	DWORD			box_id;							// ���� ���� �ִ� �ڽ��� ���� ID
	int				Defence;						// ����
	
	// Chatting���� ���� ----------------
	char			chatname[ 31];
	char			chattype;
	short int		whisperid;
	
	// Party / Relation / Employment.
	CharacterParty party[MAX_PARTY_MEMBER];			
	CharacterParty relation[3];				
	CharacterParty employment[6];				
	
	/// up_date��
	char		party_str[6][31];
	char		relation_str[3][31];
	char		employment_str[6][31];
	int			partyrequestflag;
	BYTE		Status;				// ĳ������ �޽� ���� 0�� nomal		//0108
	DWORD		timetoupdate;
	char		updatable; // CSD-TW-030620
	int			balancingtest;
	DWORD		attackedblock;  // �ʿ� ������  0810 KHS							
	AREA		area_tbl[MAX_AREA_BUFFER];							
	int			ctrlpc;			// NPC�ϰ�� ���� �����ϴ� NPC�� ID, ���� ��� -1�� ������ �ִ�.
	int			ctrlnpc[MAX_PC_CONTROL_NPC];		
	DWORD		SpeedUp;			//  ���� �ӵ��� 1/2��ŭ �� ������
	char		believe_god;		// ���� �ϴ� ��
	short int	faith;				// �žӽ�
	char		preach_name[20];	// ������ ����� �̸�
	short int	god_cast_level;		// ���� �ֹ� �н� �ܰ�	// 0410	YGI	// sql ���� �ʿ�
	bool		in_temple;			// �����ȿ� �ִ�		// 0410	YGI	// sql ���� �ʿ� ����
	int			is_god_meeting;		// ���� �������̴�		// 0410	YGI	// sql ���� �ʿ� ����
	DWORD		god_meeting_start_time;	// ���� ������ �ð�	// 0410	YGI	// sql ���� �ʿ� ����
	bool		i_go_year_meeting;		// ���� ���迡 ����.// 0410	YGI	// sql ���� �ʿ� ����
	bool		i_go_month_meeting;		// ���� ���迡 ����.// 0410	YGI	// sql ���� �ʿ� ����
	bool		i_go_day_meeting;		// ���� ���迡 ����.// 0410	YGI	// sql ���� �ʿ� ����
	bool		use_supper;				// ���� ������ �޴� ���̤�.		// 0601
	int			much_supper;			// ���� �޴� ������ ��			// 0601
	DWORD		can_memorize_time;		// ������ �ð�	// ������ �ʿ� ����  0414 YGI
	short int	startposition;
	short int	startmap;
	//////////////////////////////////  ���� �ý���...
	char        dualname[20];
	char        dualstatus;	// 0: No Dual    1: ��û�ѻ���..   2: ������.
	DWORD		dualvictory;	
	DWORD		dualfail;	
	DWORD		dualdraw;	
	/////////////////// DB Update���� Packet���� Ÿ ���Ӽ����� ����.
	char		change_map_confirm[9];						// YGI 0521
	int			now_changing_map;	// ���� �� ��ȯ ���̴�	// YGI 0521
	POINT		memory_Position;			//Ÿ����Ż������ �̵��� �� ��ǥ(Ÿ�� ��ǥ)
	int			homemap;
	int         homex, homey;
	BOOL		fight_flag;	//1:1 ��� ����üũ.
	int			fight_id;	//������ ��..
	DWORD		first_ResultMagicTime;		//�Ϲ� ��󸶹��� ��� 1�ʿ� 1�� �̳��� �����ϱ� ���� �ð����
	DWORD		magic_delay;
	int			curr_fight_map;		// 0907 YGI
	int			dec_duration;		// ����� Duration�� ��������� Check�Ѵ�. 
	short int	vote_num;			// ������ ���� ������ ��¥
	int         sealstone;	// ��輮�� ������ �̼�ġ�� �ö󰡸�. ������ �ö󰥶�����. Ŭ���̾�Ʈ�� �����ش�. 
	int			view_job;		// �����ֱ� ����		//001028 YGI
  
	// Added by chan78 at 2000/11/27
	short int		MapChange_MoveGox;
	short int		MapChange_MoveGoy;
	short int		MapChange_X;
	short int		MapChange_Y;
	short int		MapChange_MovePathCount;
	short int		MapChange_MoveLength;
	short int		MapChange_MoveSx;
	short int		MapChange_MoveSy;

	DWORD			Last_MapChangeTime;
	
	// 010406 YGI
	DWORD			LadderScore;		// �ݷμ��� ���� ����
	WINLOSEPOINT	WinLoseScore;		// �ݷμ��� ����
	bool			refresh_ladder;		// ���� ��ŷ ��� ������ �ʿ䰡 �ִ°�? // 010511 YGI

	DWORD	dwSkillTime;//010703 lsw
	DWORD	dwSkillMakeitemTime;//010703 lsw
 
	int iPhysicalTotalDamage;
	int iPhysicalRandomDamage;
	
	//�����̳� Ʈ���� ���� �ð�
	bool	bCanViewGhost;
	DWORD	dwCanViewGhostTime;
	
	bool	bCanViewTrap;
	DWORD	dwCanViewTrapTime;
	
	bool	bCanViewBomb;
	DWORD	dwCanViewBombTime;

	short	nSkillSadCount;
	short	nSkillBlessLeaf;
	
	//ȸ�� �ð�
	DWORD	dwHungryRecoverTime;
	DWORD	dwHpRecoverTime;
	DWORD	dwManaRecoverTime;
	DWORD	dwDivineRecoverTime;
	DWORD	dwCpRecoverTime;
	
	DWORD	dwCheckAccelTime;
	DWORD	dwSendedAccelTime;

	//��� ����
	short int nDayLightControl;

	DWORD		dwDayLightControlCustomTime;
	short int	nDayLightControlCustom;//020610 lsw
		
	RareMain					SquadRare;
	DYNAMICRAREEFFECT			DynamicRare;
	STATICRAREEFFECT			StaticRare;		//���� ������
  
	// 011108 YGI
	BYTE	select_rune;			// �׺�� ���õ� �� ��ȣ
 	int 	JoinLocalWar;			// �������� ���� ���� ���� �ʾ���	// LTS LOCALWAR		// LTS AI2 MONSTER �׷��ȣ // CSD-030528
	char	GainedFame;				// ���������� ���� ��			// LTS LOCALWAR			// LTS AI2 ���� ������ȣ
	char	CurrentPhase;			// ���������� �������� �ʿ��� �Ѵܰ辿 ����
	char	ChairNum;				// ���ڹ�ȣ						// LTS SITDOWN BUG

	char	reporter_mode;
	char	party_select;	// ��Ƽ�� �ö󰡴� ����ġ ����
	char	ox_select;		// ox event ���� ������ ��

	char			EventLocalWarJoin;			// 020115 LTS			// �����̺�Ʈ�� �������� 
	Event_Join		EventJoin;					// 020115 LTS
	int				EventPoint;					// 020115 LTS

	char			HorseNo;					// LTS HORSERIDER		// LTS NEW AI		// ��Ŀ���� ī��Ʈ 
	char			RiderNo;					// LTS HORSERIDER
	char			HorseGrade;					// LTS HORSERIDER
	char			RiderGrade;					// LTS HORSERIDER

	char			pk_on_off;		// YGI 020418
	char			QuestMode;					// LTS DRAGON MODIFY
	char			DragonLordWarTeam;			// LTS DRAGONLORD		// 0 : ���� 1: BLUE 2: RED

	//021030 lsw ��ȯ ����
	K_ITEM			give[MAX_EXCHANGE_ITEM];		// ���� ��� �ϴ� ������
	K_ITEM			recv[MAX_EXCHANGE_ITEM];		// ���� �޾ƾ� �ϴ� ������
	short int		m_iExchangeTargetId;		// �ŷ� ���
	char			m_szExchangeTargetName[21];		// �ŷ� ��� �̸�
	int				m_iExchangeType;		// �ŷ��ϰ� �ִ��� ������...
	int				m_iExchangeState;		// �ŷ��ϰ� �ִ��� ������...
	bool			m_bExchangeMode;		// �ŷ��ϰ� �ִ��� ������...
	int				m_nUserAge;				// 030929 kyo // �±������� ����ϴ� ���� ����
	DWORD			m_dwLastMoveTime;	// finito 21/08/07 last time that a CMD_MOVE packet sent (should be 300ms or more)
	bool			m_bIsDuelAllow;		// finito 25/08/07 are duel requests allowed
	int				hack_timestart; // Add by rogerio
	int				hack_timeend; // Add by rogerio
	int				hack_counthits; // Add by rogerio
	std::vector<int>	TamedMonster; //Eleval 21/06/09 - To keep a track of the monsters the player tamed
	int				s_quest_floor;	//Eleval 10/08/09 - To keep a track of the floor the player was in when he DCed

	//Char's option by Eleval
	bool hat_is_hidden;
	//End of it
};

///////////////////////////////////////////////////////////////////////////////
// ȹ�� �����Ϳ� ���� Ŭ����
class CGainPoint
{
public:
	CGainPoint() : m_nPoint(0)
	{
	}
	
public:
	void Clear() { m_nPoint = 0; }
	
	int GetPoint() const { return m_nPoint; }
	void SetPoint(int nPoint) { m_nPoint = nPoint; }
	void Increase(int nPoint = 1) { m_nPoint += nPoint; }
	void Decrease(int nPoint = 1) { m_nPoint -= nPoint; }
	
	bool IsEnough(int nPoint) const
	{ 
		return (m_nPoint >= nPoint) ? true:false;
	}
	
public:
	int m_nPoint;
};
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ���� �����Ϳ� ���õ� Ŭ����
class CStatePoint
{
public:
	CStatePoint() :	m_nMaxPoint(0), m_nCurPoint(0)
	{
	
	}

public:
	int Increase(int nPoint, int nPercent);
	int Decrease(int nPoint, int nPercent);

public:
	void SetMaximumPoint(int nPoint)
	{
		m_nMaxPoint = nPoint;
	}

	int GetMaximumPoint() const
	{
		return m_nMaxPoint;
	}

	void SetCurrentPoint(int nPoint)
	{
		m_nCurPoint = nPoint;
	}

	int GetCurrentPoint() const
	{
		return m_nCurPoint;
	}

private:
	int	m_nMaxPoint;
	int	m_nCurPoint;
};
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ĳ���� ������ ���� Ŭ����
class CBaseArena;
class CArenaTeam;
class CCharInfo : public CHAR_DATA
{
public:
	CCharInfo();
	
public:
	void InitCombat();
	void IncAbility(BYTE nType);
	void DecAbility(BYTE nType);
	
	void ResetAbility(BYTE nCombat);
	void DivideAbility(BYTE nNext);
	void ConvertTacticsLevel(BYTE nKind);
	void Message(BYTE nType, BYTE nKind, WORD nNumber);
	
	bool IncExperience(int nExp); // CSD-030930
	bool DecExperience(bool bNK); // CSD-030930

	bool IncTacticExp(BYTE nKind, int Exp); // CSD-030930
	bool DecTacticExp(BYTE nKind, bool bNK); // CSD-030930

	int GetWeaponSkill();
	int GetAbility(BYTE nType) const;
	int GetNpcAttack() const;
	int GetNpcDefence() const;
	int GetNpcMagic() const;
	int GetNpcDefence(BYTE nType) const;
	int GetNpcStrikePiercing() const; // CSD-021024
	int GetNpcMagicPiercing() const;  // CSD-021024
	int GetNpcStunAvoid() const;      // CSD-021024
	int GetNpcSlowAvoid() const;      // CSD-021024
	int GetNpcPoisonAvoid() const;    // CSD-021024
	int GetNpcBlindAvoid() const;     // CSD-021024
	int GetNpcDrainAvoid() const;     // CSD-021024
	int GetNpcFreezeAvoid() const;    // CSD-021024
	int GetMovePower(BYTE nType) const;
	int GetDistance(int nX, int nY) const;
	int GetRiseFall(int nX, int nY) const;	
	int GetWeaponKind() const;
	int GetTacticsKind() const;
	int GetCombatValue(int nIndex) const;
	int GetPureLife() const;
	int GetExtendAc() const;
	int GetItemEffectNumber() const; // CSD-031007
	
	void GetStepInfo(char* pData, int nSize);
	void SetStepInfo(char* pData, int nCount);
	
	int CorrectCombatAttack(int nCombat, int nResult) const;
	int CorrectCombatDefense(int nCombat, int nResult) const;
	int CorrectItemEffect() const; // CSD-031007
	
	bool LevelUpAbility();
	bool LevelUpTactics(int nKind);
	bool LevelUpCombat(int nKind, int nPoint);

	bool ChangeUpAddExp(int nExp); // CSD-TW-030624
	bool ChangeUpAddExpBonus(int nExp); // CSD-TW-030624 
	bool ChangeUpTacExp(int nType, int nExp); // CSD-TW-030624

	void GenerateNpcName();
	void AutoAttribute();
	void SetAttribute(int nRace);
	
	bool IsShield() const;
	bool IsArrow() const;
	bool IsLimit(int nPoint = 0) const;
	bool IsEnableCombat(BYTE nCombat) const;
	
	void Rare_Squad();
	void Rare_Eat();
	void Rare_Inv();
	void Rare_Quick();
	void Rare_Equip();
	void CalcRareEffect(int iFlag);
	bool IsLimitedAge( const int nLimitedAge){ return ( m_nUserAge > nLimitedAge ? false:true); }; // 030929 kyo //�±����� ����ϴ� �������� ����
	
public:
	inline int IncLife(int nVolume, int nMax);
	inline int DecLife(int nVolume, int nMin);
	inline int IncMana(int nVolume, int nMax);
	inline int DecMana(int nVolume, int nMin);
	inline int IncHungry(int nVolume, int nMax);
	inline int DecHungry(int nVolume, int nMin);
	inline int IncCombat(int nVolume, int nMax);
	inline int DecCombat(int nVolume, int nMin);
	
	short GetServerID() const { return m_idServer; } // CSD-HK-030830
	int GetLevel() const { return m_nLevel; } // CSD-030806
	int GetGuildCode() const { return m_nGuildCode; } // CSD-030806
	int GetReservedPoint() const { return m_gnAbility.GetPoint(); }
	int GetCombatPoint() const { return m_gnCombat.GetPoint(); }
	int GetDualClass() const { return m_nDualCls; }
	int GetClassStep() const { return m_nClsStep; }
	int GetExperienceStep() const { return m_nExpStep; }
	int GetTacticsStep(int nIndex) const { return m_aTacStep[nIndex]; }
	int GetNK(int nNation) const { return nk[nNation]; }
	int GetCombatLevel(int nIndex) const { return Skill[nIndex - 100]; }
	int GetWanted() const { return m_bWanted; }
	CBaseArena* GetJoinArenaGame() const { return m_pArenaGame; }  // CSD-030509
	CArenaTeam* GetJoinArenaTeam() const { return m_pArenaTeam; }  // CSD-030509
	
	void SetServerID(short idServer) { m_idServer = idServer; } // CSD-HK-030829
	void SetLevel(int nLevel) { m_nLevel = nLevel; } // CSD-030806
	void SetGuildCode(int nGuildCode) { m_nGuildCode = nGuildCode; } // CSD-030806
	void SetReservedPoint(int nPoint) { m_gnAbility.SetPoint(nPoint); }
	void SetCombatPoint(int nPoint) { m_gnCombat.SetPoint(nPoint); }
	void SetDualClass(int nDual) { m_nDualCls = __int8(nDual); }
	void SetClassStep(int nStep) { m_nClsStep = __int8(nStep); }
	void SetExperienceStep(int nStep) { m_nExpStep = __int8(nStep); }
	void SetTacticsStep(int nIndex, int nStep) { m_aTacStep[nIndex] = __int8(nStep); }
	void SetCombatLevel(int nIndex, int nLevel) { Skill[nIndex - 100] = nLevel; }
	void SetWanted(bool bWanted) { if (IsPlayer())  m_bWanted = bWanted; }
	void SetJoinArenaGame(CBaseArena* pGame) { m_pArenaGame = pGame; }  // CSD-030509
	void SetJoinArenaTeam(CArenaTeam* pTeam) { m_pArenaTeam = pTeam; }  // CSD-030509
	
	void IncReservedPoint(int nPoint = 1) { m_gnAbility.Increase(nPoint); }
	void DecReservedPoint(int nPoint = 1) { m_gnAbility.Decrease(nPoint); }
	void IncCombatPoint(int nPoint = 1) { m_gnCombat.Increase(nPoint); }
	void DecCombatPoint(int nPoint = 1) { m_gnCombat.Decrease(nPoint); }
	
	bool IsDead() const { return (Hp <= 0) ? true:false; }
	bool IsHungry() const { return (Hungry <= 0) ? true:false; }
	bool IsFullLife() const {return (Hp >= HpMax) ? true:false; }
	bool IsFullMana() const {return (Mana >= ManaMax) ? true:false; }
	bool IsFullHungry() const {return (Hungry >= HungryMax) ? true:false; }
	bool IsFullCombat() const {return (Cp >= CpMax) ? true:false; } // CSD-030506
	bool IsPlayer() const { return (SprType < SPRITETYPE_NPC) ? true:false; }
	bool IsNpc() const { return (SprType > SPRITETYPE_CHARACTER) ? true:false; }
	bool IsDual() const { return m_nClsStep > 0; }
	bool IsUltraNK(int nNation) const { return (nk[nNation] >= ULTRA_NK) ? true:false; }
	bool IsJoinArenaGame() const { return (m_pArenaGame == NULL) ? false:true; } // CSD-030509
	bool IsJoinArenaTeam() const { return (m_pArenaTeam == NULL) ? false:true; } // CSD-030509
	bool IsLevelUp()            const { return (GetLevel() < MAX_EXP_LEVEL) ? true:false; }
	bool IsLevelUp(int nLevel)  const { return (nLevel < MAX_TAC_LEVEL) ? true:false; }
	
	bool IsIgnoreNormalLevel()     const { return m_bsAttr[IGNORE_NORMAL_LEVEL]; }
	bool IsIgnorePhysicalAttack()  const { return m_bsAttr[IGNORE_STRIKE_ATTACK]; }
	bool IsIgnorePhysicalDefence() const { return m_bsAttr[IGNORE_STRIKE_DEFENSE]; }
	bool IsIgnoreMagicAmplify()    const { return m_bsAttr[IGNORE_MAGIC_AMPLIFY]; }
	bool IsIgnoreMagicResist()     const { return m_bsAttr[IGNORE_MAGIC_RESIST]; }
    
	void SendCharInfoBasic(BYTE nKind, DWORD dwData) const; // CSD-TW-030620
	void SendCharInfoTactic(BYTE nKind) const; // CSD-TW-030620
	//021030 lsw ��ȯ ����
	int  GetExchangeTargetId()const{return m_iExchangeTargetId;}//�ŷ� ����� �޴´�
	const char*  GetExchangeTargetName()const{return &m_szExchangeTargetName[0];}//�ŷ� ����� �޴´�
	void SetExchangeTarget(const int iTradeTarget,const char* szTargetName)
	{
		m_iExchangeTargetId = iTradeTarget;
		strcpy_s(m_szExchangeTargetName, sizeof(m_szExchangeTargetName),szTargetName);
	}//�ŷ� ����� ���� �Ѵ�
	
	int  GetExchangeType()const{return m_iExchangeType;}//�ŷ� Ÿ���� �޴´�
	void SetExchangeType(const int iTradeType){m_iExchangeType = iTradeType;}//�ŷ� Ÿ���� �����Ѵ�
	
	int  GetExchangeState()const{return m_iExchangeState;}//�ŷ� ���¸� �޴´�
	void SetExchangeState(const int iStateType){m_iExchangeState = iStateType;}//�ŷ� ���¸� �����Ѵ�
	
	void SetTradeMode(const bool bIsTradeOn){m_bExchangeMode = bIsTradeOn;}//�ŷ� ���¸� �����Ѵ�
	bool IsTradeOn()const{return !m_bExchangeMode;}//Trade On Off ���� �����Ѵ�. m_bExchangeMode --> false �ϰ�� Trade On �̴�
	
	void ClearExchangeInfo()//�ŷ� ������ Ŭ���� ��Ŵ
	{
		::memset( give, 0, sizeof( K_ITEM ) * MAX_EXCHANGE_ITEM );
		::memset( recv, 0, sizeof( K_ITEM ) * MAX_EXCHANGE_ITEM );
		m_iExchangeTargetId =0; 
		m_iExchangeType = EXCHANGE_TYPE_NO; 
		m_iExchangeState = EXCHANGE_STATE_READY;
		::strcpy_s(m_szExchangeTargetName, sizeof(m_szExchangeTargetName),"");
	}

	bool IsCounselor() const { return (name_status.counselor) ? true:false; }
	bool IsReporter() const { return (name_status.reporter) ? true:false; }
	bool IsPayedUser() const { return (BT_FREE != GetBillingType()) ? true:false; } //�� ������ ���� �� �����ΰ�?

	short GetBillingType()const{return m_nBillingType;}
	void SetBillingType(const short wValue){m_nBillingType = wValue;}

	DWORD GetBankMoney() const 
	{	//< CSD-030723
		return m_dwBankMoney;
	}	//> CSD-030723
	
	void SetBankMoney(const DWORD dwMoney, const eBankMoneyChangeType BMCT)
	{	//< CSD-030723
		::SaveChangeBankMoney(GetServerID(), GetBankMoney(), dwMoney, BMCT);
		
		m_dwBankMoney = dwMoney;
	}	//> CSD-030723
			
	bool IncBankMoney(const DWORD dwMoney, const eBankMoneyChangeType BMCT, const bool bSend = true)
	{	//< CSD-030723
		if (DWORD(MAX_BANK_MONEY - m_dwBankMoney) >= dwMoney) //ULONG_MAX
		{
			SetBankMoney(m_dwBankMoney + dwMoney, BMCT);
			
			if (bSend)
			{	//���൷ ����
				SendCharInfoBasic(BANKMONEY, GetBankMoney());
			}

			return true;
		}

		return false;
	}	//> CSD-030723

	bool DecBankMoney(const DWORD dwMoney, const eBankMoneyChangeType BMCT, const bool bSend = true)
	{	//< CSD-030723
		if (m_dwBankMoney >= dwMoney) //���� ������ �ִ� ���� ������
		{	//���൷ ����
			SetBankMoney(m_dwBankMoney - dwMoney, BMCT);
			
			if(bSend)
			{
				SendCharInfoBasic(BANKMONEY, GetBankMoney());
			}
			
			return true;
		}

		return false;
	}	//> CSD-030723

	bool IsEventRecv() { return m_bEventRecv; } ;			// BBD 040308
	void SetEventRecv(bool val) { m_bEventRecv = val; } ;	// BBD 040308
	
protected:
	int GetExtStr() const;
	int GetExtCon() const;
	int GetExtDex() const;
	int GetExtWis() const;
	int GetExtInt() const;
	int GetExtMove() const;
	int GetExtChar() const;
	int GetExtEndu() const;
	int GetExtMor() const;
	int GetExtLuck() const;
	int GetExtWs() const;
	int GetExtPs() const;
	
	int GetRemainStr() const;
	int GetRemainCon() const;
	int GetRemainDex() const;
	int GetRemainWis() const;
	int GetRemainInt() const;
	int GetRemainMove() const;
	int GetRemainChar() const;
	int GetRemainEndu() const;
	int GetRemainMor() const;
	int GetRemainLuck() const;
	int GetRemainWs() const;
	int GetRemainPs() const;
	
	int CalcNewLife(BYTE nCombat) const;
	int CalcNewMana(BYTE nCombat) const;
	int CalcNewHungry(BYTE nCombat) const;
	int CalcNewCombat() const;
	int CalcNewAc() const;
	
	int CalcWeaponHit() const;
	int CalcCriticalHit(BYTE nActive, BYTE nPassive) const;
	int CalcTacticExp(BYTE nKind, DWORD dwExp) const;
	
	void AddPhysicalTacExp1(int nKind, int nExp); // CSD-TW-030624
	void AddPhysicalTacExp2(int nKind, int nExp); // CSD-TW-030624
	void AddPhysicalTacExp3(int nKind, int nExp); // CSD-TW-030624
	void AddMagicTacExp1(int nKind, int nExp); // CSD-TW-030624
	void AddMagicTacExp2(int nKind, int nExp); // CSD-TW-030624
	
private:
	bool IsLimitExp(int nLevel);
	bool IsLimitTac(int nKind);
	
protected:
	enum
	{
		IGNORE_NORMAL_LEVEL = 0,
		IGNORE_STRIKE_ATTACK = 1,
		IGNORE_STRIKE_DEFENSE = 2,
		IGNORE_MAGIC_AMPLIFY = 3,
		IGNORE_MAGIC_RESIST = 4,
		IGNORE_MAX = 5
	};
	
	bitset<IGNORE_MAX> m_bsAttr; // �Ӽ���
	
protected:
	mutable __int8 m_nCriticalCount;   // CSD-031007 : ũ��ƼĮ ��Ʈ�� ���� ī��Ʈ
	mutable __int8 m_nItemEffectCount; // CSD-031007 : ������ ȿ���� ���� ī��Ʈ

private:
	short	m_idServer;          // CSD-HK-030829
	int     m_nLevel;			 // CSD-030806
	int		m_nGuildCode;		 // CSD-030806
	__int8  m_nDualCls;          // ��� Ŭ���� ����
	__int8  m_nClsStep;          // Ŭ���� �ܰ�
	__int8  m_nExpStep;          // ����ġ �ܰ�
	__int8  m_aTacStep[NO_TAC];  // ��ƽ ����ġ �ܰ�
	
	bool	m_bEventRecv;		// BBD 040308	�̺�Ʈ ������ �ߺ� ���޿�û�� ���� �÷���
private:
	CGainPoint  m_gnAbility;     // �ø� �� �ִ� �����Ƽ ������
	CGainPoint  m_gnCombat;      // �ø� �� �ִ� ������ų ������
	bool	    m_bWanted;     // ����� ����
	DWORD	    m_dwBankMoney;	//���൷
	short	    m_nBillingType;	//���� Ÿ��
	CBaseArena* m_pArenaGame; // CSD-030509
	CArenaTeam* m_pArenaTeam; // CSD-030509
	vector<int> m_nHunterListIds;
};
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// �ζ��� �Լ�
inline int CCharInfo::IncLife(int nVolume, int nMax = 100) 
{ // Life ����
	const int nOld = Hp;
	const int nLimit = HpMax*nMax/100;
	Hp += nVolume; 
	if (Hp > nLimit)  Hp = nLimit;
	return Hp - nOld;
}

inline int CCharInfo::DecLife(int nVolume, int nMin = 0) 
{ // Life ����
	const int nOld = Hp;
	const int nLimit = HpMax*nMin/100;
	Hp -= nVolume; 
	if (Hp < nLimit)  Hp = nLimit;
	return nOld - Hp;
}
// �����¿� ���õ� Method
inline int CCharInfo::IncMana(int nVolume, int nMax = 100)
{ // Mana ����
	const int nOld = Mana;
	const int nLimit = ManaMax*nMax/100;
	Mana += nVolume; 
	if (Mana > nLimit)  Mana = nLimit;
	return Mana - nOld;
}

inline int CCharInfo::DecMana(int nVolume, int nMin = 0) 
{ // Mana ����
	const int nOld = Mana;
	const int nLimit = ManaMax*nMin/100;
	Mana -= nVolume; 
	if (Mana < nLimit)  Mana = nLimit;
	return nOld - Mana;
}

inline int CCharInfo::IncHungry(int nVolume, int nMax = 100) 
{ // ��������� ����
	const int nOld = Hungry;
	const int nLimit = HungryMax*nMax/100;
	Hungry += nVolume; 
	if (Hungry > nLimit)  Hungry = nLimit;
	return Hungry - nOld;
}

inline int CCharInfo::DecHungry(int nVolume, int nMin = 0)
{ // ��������� ����
	const int nOld = Hungry;
	const int nLimit = HungryMax*nMin/100;
	Hungry -= nVolume; 
	if (Hungry < nLimit)  Hungry = nLimit;
	return nOld - Hungry;
}

inline int CCharInfo::IncCombat(int nVolume, int nMax = 100) 
{ // ������ų ��밡�ɷ� ����
	const int nOld = Cp;
	const int nLimit = CpMax*nMax/100;
	Cp += nVolume; 
	if (Cp > nLimit)  Cp = nLimit;
	return Cp - nOld;
}

inline int CCharInfo::DecCombat(int nVolume, int nMin = 0)
{ // ������ų ��밡�ɷ� ����
	const int nOld = Cp;
	const int nLimit = CpMax*nMin/100;
	Cp -= nVolume; 
	if (Cp < nLimit)  Cp = nLimit;
	return nOld - Cp;
}
//
///////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_CHARINFO_H__1A212137_3131_4DD3_8343_EE42343C165E__INCLUDED_)
