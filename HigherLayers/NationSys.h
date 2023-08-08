#ifndef _NATION_SYS_H_
#define _NATION_SYS_H_

#include "NationSys_Define.h"
#include "LTSSupport.h"
#include "WarStartInfo.h"

#define MAX_WARTIME_COUNT			30
#define	GIVE_FAME_RANGE				15

typedef struct MonPoint
{
	int		MonsterIndex;
	int		Size;
	POINTS* Points;
}	t_MonPoint;


// Structure Squad Infomation
typedef struct SquadInformation_P
{
	char	SquadNo;
	int		CO_ID;
	char	CO_Name[NW_NAME_MAX];
	int		SoliderCount;
	char	Sok[NW_SQUAD_RARE_MAX];
	char	LoadingPoint;
} t_SquadInformation;


// Structure Commander or Commander Candidate
typedef struct CommanderInformation_P
{
	char		VoteNo;
	int			CO_ID;
	char		CO_Name[NW_NAME_MAX];
	BYTE		btLevel; // CSD-030806
	short		Fame;
	short int	Face;
	short int	Gender;
	short int	Class;
	__int8		nDual;					// 011020 LTS
	__int8		nStep;					// 011020 LTS
	DWORD		LadderScore;
	WORD		VoteCount;
} t_CommanderInformation;

typedef struct WeaponStruct_P
{
	int		NPC_ID;
	int		MonPointIndex;
	int		NPC_Index;
	int		Phase;			// 011022 LTS
	int		Locationx;
	int		Locationy;
	int		EventNo;
	int		GenerationPos;
	int		GenerationType;
	int		Status;
}	t_WeaponStruct;

typedef	struct MWarfield
{
	char	Status;
	int		Possession;
}	t_Warfield;

typedef struct DeadWeapon_P
{
	char	NPCCount;
	int*	NPC_ID;
} t_DeadWeapon;



class SquadMember
{
	int		m_iData;
	char	m_cStatus;

public :
	SquadMember(){}
	SquadMember(int i) { m_iData=i;}
	SquadMember(int i,int Status) {m_iData=i; m_cStatus=Status; }
	~SquadMember() {}
	void SetData(int i)	{ m_iData=i;}
	int  GetData()	{ return m_iData; }
	void SetStatus(int i)	{ m_cStatus=i; }
	int	GetStatus()	{ return m_cStatus; }
};

class cKiller
{
	char	m_sUserName[20];
	WORD	m_wKillSprNo;
public :
	cKiller(){}
	cKiller(char* Name,int SprNo) { strcpy_s(m_sUserName, sizeof(m_sUserName),Name); m_wKillSprNo=SprNo; }
	~cKiller() {}
	void SetUserName(char* Name) { strcpy_s(m_sUserName, sizeof(m_sUserName),Name); }
	void SetKillSprNo(int SprNo) { m_wKillSprNo=SprNo; }
	const char* GetUserName() { return m_sUserName; }
	int GetKillSprNo() { return m_wKillSprNo; }
};

class cMonster			
{
	t_WeaponStruct	Data;

public :
	cMonster(){}
	cMonster(t_WeaponStruct Monster) 
	{
		Data.NPC_ID=Monster.NPC_ID;
		Data.MonPointIndex=Monster.MonPointIndex;
		Data.NPC_Index=Monster.NPC_Index;
		Data.Locationx=Monster.Locationx;
		Data.Locationy=Monster.Locationy;
		Data.EventNo=Monster.EventNo;
		Data.GenerationPos=Monster.GenerationPos;
		Data.GenerationType=Monster.GenerationType;
		Data.Status=Monster.Status;
	}
	~cMonster(){}
	int GetMonsterID() { return Data.NPC_ID; }
	void SetMonsterID(int ID) { Data.NPC_ID=ID; } 
	t_WeaponStruct GetMonsterData() { return Data; } 
};



// Class cWarfield 

typedef struct Squad_P
{
	t_CommanderInformation			Commander;							// Commander
	t_CommanderInformation			Candidater[NW_CANDIDATE_MAX];		// Candidater
	t_SquadInformation				SquadInfo[NW_SQUAD_MAX];			// Squad Information
	SquadMember*					SquadDataLink[NW_SQUAD_MAX];		// Squad Hash
} t_Squad;


struct MonPoint2
{
	int Size;
	POINTS* MPoint; 
};

struct MonsterPoints2
{
	int CastleGateWayNo;
	int MonsterIndex;
	int locationX;
	int LocationY;
	MonPoint2* MonsterPoint;
	MonPoint2* EMonsterPoint;
};

using namespace std;


typedef list<SquadMember*> SquadList;
typedef list<cKiller*> KillerList;
typedef list<cMonster*> MonsterList;

typedef SquadList::iterator SquadListItor; // STL List
typedef KillerList::iterator KillerListItor;
typedef MonsterList::iterator MonsterListItor;

struct LoopTimeDefine						// 011101 LTS
{
	DWORD	NWPeaceTime1;		// �������� ��ȭ�ð� 
	DWORD	NWPeaceTime2;		// ������������ ���� ������� ���۽ð� 
	DWORD	NWPeaceTime3;		// ����������� ���� ������� ���۽ð� 
	DWORD	NWPeaceTime4;		// ��  �������� ���� ������� ���۽ð� 
	DWORD	NWVoteTime;			// ���� ��ǥ �ð�
	DWORD	NWPrepareTime;		// ���� �غ� �ð� 
	DWORD	NWWarTime;			// ���� �ð� 
	DWORD	NWBonusTime;		// ������� ���½ð�
	DWORD	NWVoteMin;			// ��ǥ �ּ��ο�			// LTS LOCALWAR
	WORD	NWBYJoinMAX;		// ������ �����ο� ���� �ƽ�
	WORD	NWZYJoinMAX;		// ������ �����ο� ���� �ƽ�
	WORD	NWYLJoinMAX;		// ������ �����ο� �Ͻ� �ƽ�
};

typedef struct StartWarTime
{
	int DayofWeek;
	int DHour;
}* LP_START_WAR_TIME;

class cWarfield
{
	// Lopp Concern
	char			m_cLoopActive;										//������ ������ ��Ʈ�� �Ѵ�.
	__int64			m_LoopTime;										// ������ �ַ��� Ÿ��
	char			m_Status;										// �������� ����
	bool			m_bRequestCommanderVotingResult;				// ��ɰ� ��ǥ ����� ��û�߳�?

	bool			m_bBonusActive;									// ���ʽ����� ��Ʈ�� ���� 
	__int64			m_dBonusLoopTime;								// ���ʽ� ���� ����Ÿ�� 
	DWORD			m_dRemainTime;

	LoopTimeDefine	m_LoopTimeDefine;							// ��������� ���� MapServer.ini�� ���� // 011101 LTS

	// Data Concern //�ε��� DB���� �о���� �κ��̴�. 

	int				m_WarfieldCode;									// ������ ��ȣ
	int				m_MapPortNum;									// ��Ʈ��ȣ
	char			m_pWarfieldName[NW_NAME_MAX];					// ������ �̸�
	int				m_NationCode;									// ���� ����
	DWORD			m_dwStartDateTime;								// ������۽ð�
	DWORD			m_dwEndDateTime;								// ��������ð�
	DWORD			m_dwNextDateTime;								// ���� ������۽ð�

	char			m_cNpcCount;									// ����, ��ȣ���� ī��Ʈ

	char			m_cGuardStoneCount;								// ��ȣ�� ī��Ʈ
	char			m_cCastleDoorCount;								// ����ī��Ʈ

	char			m_cGuardStoneBossCount;							// �ռ�ȣ�� ī��Ʈ

	char			m_cGuardStoneBrokenCount;						// �μ��� ��ȣ�� ī��Ʈ
	char			m_cCastleDoorBrokenCount;						// �μ��� ���� ī��Ʈ

	bool			m_bAttackerWin;									// �����ڰ� �̰�°�?
	bool			m_bFirstMakeMonster;							// ���Ͱ� ���� ����� ���°�?

	POINTS			m_LivePoints[NW_SQUAD_KIND];					// ������ ������� ���� ��Ƴ��� ����Ʈ		// 011015 LTS


	// Squad Concern

	t_Squad			m_tSquad[NW_SQUAD_KIND];						// NW_ATTACKER, NW_DEFENCER, NW_REINFORCE		// �δ����
	t_WeaponStruct	m_tWeaponData[NW_MAX_NPC];						// ����,��ȣ�� ����
	t_MonPoint		m_tMonsterPoint[MAX_MONSTER_POINT];				// ������ ��ġ �� ��Ʈ�� ��ġ 	

	SquadList		g_AttackSquadList[NW_SQUAD_MAX];				// ���� �ʿ� �ִ� ������ ����Ʈ
	SquadList		g_DefenceSquadList[NW_SQUAD_MAX];				// ����� ����Ʈ
	SquadList		g_ReinforceSquadList[NW_SQUAD_MAX];				// ������ ����Ʈ
	SquadList		g_CommanderList[NW_SQUAD_KIND];					// �δ��� , ��ɰ� ����Ʈ

	KillerList		g_KillerList;									// ����, ��ȣ���� �μ� ��� ����Ʈ	
	MonsterList		m_MonsterList;									// �Ͻ������� �����Ǵ� ��Ʈ�� ����Ʈ ���ʽ� Ÿ�ӿ�..

	int				g_SquadCount[NW_SQUAD_KIND][NW_SQUAD_MAX];		// �δ뺰 �� �ο� ī��Ʈ 
	int				m_JoinSquadCount[NW_SQUAD_KIND];				// �Ͻ��� �δ� ī��Ʈ		// 011016 LTS


	MonsterPoints2	m_MonsterPoint2;								//���� ����Ʈ Ȯ���

	bool			m_bCommanderExist[NW_SQUAD_KIND];					// �����Ϳ� �δ����� ����
	bool			m_bSquadLeaderExist[NW_SQUAD_KIND][NW_SQUAD_MAX];	// �����Ϳ� ��ɰ��� ���� ���Ʒ� �ٲ�
	DWORD			m_KilledCount[NW_SQUAD_KIND];

	WORD			m_NationMemberCount[3];							// ���� ���� �Ͻ��� ���ī��Ʈ	// 011218 LTS


public :

	cWarfield();
	~cWarfield();

	bool			InitWarfield();
	bool			LoadWarfieldData(WORD PortNum);
	bool			LoadWarfieldWeaponData(WORD PortNum);
	bool			LoadWarfieldMonsterData(WORD PortNum);
	bool			LoadMonsterPoint();								//���϶Ǵ� ������ ���̽�..
//	bool			LoadNationWar_Exp();							// LTS NEW LOCALWAR
	void			InitWarLoop();
	void			Destroy();
	void			UpdateWarfieldStatus();							// OLD		LoopTime
	void			WarUpdate();
	void			ClearCommander();
	void			ClearCommander(int Kind);
	void			ClearSquadCount();

	inline int		GetLoopActive()				{ return m_cLoopActive; }
	inline void		SetLoopActive(bool Active)	{ m_cLoopActive=Active; }
	inline DWORD	GetLoopTime()				{ return m_LoopTime; }

	inline int		GetNationCode()				{ return m_NationCode; }
	inline void		SetNationCode(int Code)		{ m_NationCode=Code; }
	inline int		GetWarfieldCode()			{ return m_WarfieldCode; }

	inline void		SetTileDont(int MonNo,int type);
	void			CheckCastleGateWay();
	void			CheckGroup(SquadList* g_SquadList);
	void			CheckCommanderGroup();
	void			SendTileDont(t_packet *p, t_connection c[], int cn );
	void			SendAllTileDont(int type);
	void			SendTileDontChange(int MonNo,int type);

	void			KickDefeatUser2Home();


	void			SetStatus(char Status);
	char			GetStatus() { return m_Status; }

	inline int		GetGuardStoneCount()		{ return m_cGuardStoneCount; }
	inline int		GetCastleDoorCount()		{ return m_cCastleDoorCount; }

	inline int		GetNpcCount()				{ return m_cNpcCount; }
	inline int		GetWeaponIndex(int No)		{ return m_tWeaponData[No].NPC_Index; }
	inline int		GetWeaponStatus(int No)		{ return m_tWeaponData[No].Status; }

	inline int		GetAllSquadCurrentMemberCount(int Kind) 
												{
													int temp=0;
													temp+=g_SquadCount[Kind][0];	// LOOP UNROLL
													temp+=g_SquadCount[Kind][1];	// NW_SQUAD
													temp+=g_SquadCount[Kind][2];
													temp+=g_SquadCount[Kind][3];
													temp+=g_SquadCount[Kind][4];
													temp+=m_JoinSquadCount[Kind];
													return temp;
												}
	inline int		GetSquadCurrentMemberCount(int Kind,int SquadNo)
												{return g_SquadCount[Kind][SquadNo];}

	
	t_SquadInformation*			GetSquadInfo(int Kind,int SquadNo);	// Kind : 0 : Attack, 1: Defence, 2:Reinforce

	void			InitSquad();

    inline void		IncSquadMemberCount(int Kind, int SquadNo)			// �δ����� (�����Ȳ�� �ƴҶ�..) ���ο� ����
												{m_tSquad[Kind].SquadInfo[SquadNo].SoliderCount++;}
	inline void		DecSquadMemberCount(int Kind, int SquadNo)			// �δ����� (�����Ȳ�� �ƴҶ�..) ���ο� ����
												{m_tSquad[Kind].SquadInfo[SquadNo].SoliderCount--;}
	inline int		GetSquadMemberCount(int Kind,int SquadNo) 
												{ return m_tSquad[Kind].SquadInfo[SquadNo].SoliderCount; }
	inline void		SetSquadLoadingPoint(int Kind,int SquadNo,int LoadingPoint) 
												{m_tSquad[Kind].SquadInfo[SquadNo].LoadingPoint=LoadingPoint;}
	void			SetSquadLeader(int Kind,int SqaudNo,t_CommanderInformation* SquadLeaderInfo);

	void			SetCommander(int Kind,int CandidaterNo);
	void			SetCommander(int Kind,t_CommanderInformation* Commander);

	void			InitCommanderCandidater();

	inline t_CommanderInformation*		GetCommanderInfo(int Kind) 
												{ return &m_tSquad[Kind].Commander; }
	inline t_CommanderInformation*		GetCandidaterInfo(int Kind,int CandidaterNo) 
												{ return &m_tSquad[Kind].Candidater[CandidaterNo];}
	inline void		IncCommanderVoteData(int Kind,int CandidaterNo) 
												{ m_tSquad[Kind].Candidater[CandidaterNo].VoteCount++; }
	inline int		GetCommanderVoteData(int Kind,int CandidaterNo) 
												{ return m_tSquad[Kind].Candidater[CandidaterNo].VoteCount; }
	bool			CanRegCommanderCandidater(int Kind,int CandidaterNo);
	void			SetCandidaterInfo(int Kind,int CandidaterNo,t_CommanderInformation* CandidaterInfo);

	void			AllGuardStoneWasBroked(); // ��������� ����..
	void			ProcessNationWarEnd(bool AttackerWin);    //������ ó�� //���� ��Ÿ��.. �ð�, ��ȣ��..

	void			FirstMakeWeaponData();
	void			MakeWeaponData();   //NPC����
  void      WeaponDataList();   // ����׿�

	void			GiveSquadPoint2Other(int cn,int Point);
	void			GiveGuildPoint2Other(int cn,int Point);
	void			ReturnFame();		// Ŀ�ؼ��� �� �μ̴ٸ� ���� �����Ѵ�.
	void			CalcFame(bool AttackerWin);		// FAME��� 

	void			SendCheckWarfieldStatus();
	void			SendWarfieldStatus();
	void			ChangeWarfieldStatus(int Result);
	void			SendCMD_REQUEST_VOTE_RESULT();
	void			RecvCMD_ANSWER_VOTE_RESULT(t_packet *p, t_connection c[], int cn );
	void			SendStartUpMapPossession();
	void			SendMapPossessChanged();

	void			ClearAllSquad(int Nation);
	void			MoneySpread(double TotalMoney);

	void			DisplaySquadMember(int Type,int SquadNo); 
	void			DisplayMember(SquadList* g_SquadList);
	void			DeleteSquadMember(const int cn); //020903 lsw
	void			DeleteSquadMember(const int Type,const int SquadNo,const int ID);
	void			DeleteMember(SquadList* g_SquadList,int ID); // Type : Attacker, Defender
	void			SendSquadMessage(int Type,int SquadNo,t_packet* p);
	void			SendMessage(SquadList* g_SquadList,t_packet* p);
	void			DeleteSquadHash(SquadList* g_SquadList);
	void			DeleteAllSquadMember();
	void			InsertSquadMember(int cn,int Status=1);
	void			InsertSquadMember(int Type,int SquadNo,int ID,int Status=1); // Type : Attacker, Defender, Reinforce, Commander
	void			InsertMember(SquadList* g_SquadList,int ID,int Status=1); 

	void			DeleteAllKiller();
	void			DeleteKiller(char* Name);
	void			InsertKiller(char* Name,int KillSprNo);
	void			DeleteAllMonsterData();
	void			InsertMonsterData(t_WeaponStruct Monster);

	void			CommanderEnter(int Type);
	void			CommanderLeave(int Type);
	void			SquadLeaderEnter(int Type,int SquadNo);
	void			SquadLeaderLeave(int Type,int SquadNo);

	inline bool		CommanderExist(int Type)				{ return m_bCommanderExist[Type]; }
	inline bool		SquadLeaderExist(int Type,int SquadNo)	{ return m_bSquadLeaderExist[Type][SquadNo]; }

	inline const char*	GetCommanderName(int Kind)			{ return m_tSquad[Kind].Commander.CO_Name; }
	inline const char*	GetCandidaterName(int Kind,int CandidaterNo) 
															{ return m_tSquad[Kind].Candidater[CandidaterNo].CO_Name; }
	inline const int	GetCandidaterVoteCount(int Kind,int CandidaterNo) 
															{ return m_tSquad[Kind].Candidater[CandidaterNo].VoteCount; }

	void			ActiveBonusTime();
	void			FirstMakeMonster();
	void			MakeMonster();
	void			PrepareSquadForWar();
	inline bool		isBonusTime()							{ return m_bBonusActive; }

	SquadList*		GetSquadListPointer(int iBattleType, int iSqaudNo) 
															{
																switch(iBattleType)
																{
																case NW_ATTACKER:
																	return &g_AttackSquadList[iSqaudNo];
																case NW_DEFENCER:
																	return &g_DefenceSquadList[iSqaudNo];
																case NW_REINFORCE:
																	return &g_ReinforceSquadList[iSqaudNo];
																}
																return NULL;
															}

	inline void		IncKilledCount(int Kind)				{ m_KilledCount[Kind]++; }
	inline int		GetKilledCount(int Kind)				{ return m_KilledCount[Kind]; }

	inline POINTS	GetLivePoints(int Kind)					{ return m_LivePoints[Kind]; }		// 011015 LTS
	inline char		GetSquadLoadingPoint(int Kind,int SquadNo) 
															{ return m_tSquad[Kind].SquadInfo[SquadNo].LoadingPoint; }
	inline char		GetSquadRareSok(int Kind,int SquadNo,int SokNo) 
															{ return m_tSquad[Kind].SquadInfo[SquadNo].Sok[SokNo]; } //�������� 
	inline char*	GetSquadRareSok2(int Kind,int SquadNo)	{ return m_tSquad[Kind].SquadInfo[SquadNo].Sok; } //�������� 
	inline void		SetSquadRareSok(int Kind,int SquadNo,int SokNo,int Sok) 
															{ m_tSquad[Kind].SquadInfo[SquadNo].Sok[SokNo]=Sok; }
	char*			GetLeadCandidaterName(int Kind);
	inline bool		ElectCommander()						{ return m_bRequestCommanderVotingResult; }
	inline bool		CheckSecretPlaceOpen()					{ return m_bBonusActive; }
	inline void		SetRemainTime(DWORD RemainTime)			{ m_dRemainTime=RemainTime;}
	inline DWORD	GetRemainTime()							{ return m_dRemainTime; }
	DWORD			GetWarLoopTime();						// 011025 LTS
	void			SetWarLoopTime(DWORD LoopTime);		// 011025 LTS
	inline void		SetSecretOpen(bool isActive)			{ m_bBonusActive=isActive; }	// 011025 LTS

	void			SendSecretActiveMessage2Manager();
	void			InitWarLoopDefine();									// 011101 LTS
	void			IncNationMemberCount(int Nation);
	void			DecNationMemberCount(int Nation);
	int				GetNationMemberCount(int Nation);
	int				GetNationMemberMax(int Nation);
	void			ClearGainedFame();
	void			CalcNationWar_Exp();

	void			UpdateProgressofWar();										// LTS NEW_NATION_WAR
	void			UpdateStatusofWar();										// LTS NEW_NATION_WAR
	void			SetStatusVote();													// LTS NEW_NATION_WAR
	void			LoopTimeChange(t_packet* p);

	void			RemoveWonHonor(int cn); //Eleval 07/09/09 - To remove the Honor if a player dc or another reason



public:
  cWarfield& operator[](int nIndex);
};

struct tSealStoneIndex															// LTS NEW LOCALWAR
{
	int SealStoneNo;
	int Status;
	int Hp; // 030516 kyo
};


class cNation
{
	cWarfield*					Warfield;
	cLocalWarfield*				LocalWarfield;					// LTS LOCALWAR

	int							m_VoteData[NW_WARFIELD_COUNT];
	DWORD						m_WarNo;

	int							m_LocalWarfieldSize;				

	int							m_LocalWarStart;					//�������� ���۵Ǿ���.
	int							m_WarStart;
	unsigned short				m_LocalWarPoint[NW_NATION_COUNT];	// BY,ZY,YL LocalWar Point	// 020130 LTS
	__int64						g_LocalWarRemainTime;				// 020115 LTS

	tSealStoneIndex				LocalWarSealStoneStatus[3][9];					// LTS NEW LOCALWAR
	unsigned short				m_LocalWarDefencePoint[3];							// LTS NEW LOCALWAR
	int							m_LocalWarResult[3];								// LTS NEW LOCALWAR
	unsigned short				m_nAllLocalWarSealStoneHP[3];		// ������ ��� ��輮HP��

	LP_START_WAR_TIME			m_pStartWarTime;									// LTS NEW_NATION_WAR
	int							m_iStartWarTimeCount;								// LTS NEW_NATION_WAR
	TimeData					m_tTimeData;										// LTS NEW_NATION_WAR

	LP_START_WAR_TIME			m_pNewStartWarTime;									// LTS NEW_NATION_WAR
	int							m_iNewStartWarTimeCount;

	int							m_NewWarfieldStatus[MAX_NEW_WARFIELD];				// LTS NEW_NATION_WAR
	DWORD						m_NewWarfieldRemainTime[MAX_NEW_WARFIELD];

	inline int		GetPointMAXIndex(unsigned short Point[3]);										// LTS NEW LOCALWAR	
	inline int		GetPointMAXIndex();										//030505 kyo �ѹ����� �������¸������� �����Ѵ�.
	inline int		GetPointEqual(int Index,unsigned short Point[3]);								// LTS NEW LOCALWAR	
	inline int		GetLPointEqual(int Index,unsigned short Point[3],unsigned short DPoint[3]);				// LTS NEW LOCALWAR	

public :

	cNation();
	~cNation();

	bool InitNation();
	bool LoadWarfieldData();
	bool InitLocalWarfield();

	void SetWarFieldStatus(int WarfieldNo,int Status);
	void CheckWarFieldStatus(int WarfieldNo,int Status);
	int  GetWarfieldStatus(int WarfieldNo);

	void			CheckStartWarfieldWar();						// New		Day of Week
	void			CheckAndActive(int Index);
	void			NewCheckAndActive(int Index);
	void			GetDayofWeek();

	int  GetVoteData(int WarfieldNo) { return m_VoteData[WarfieldNo]; }
	void IncVoteData(int WarfieldNo) { m_VoteData[WarfieldNo]++; }
	void InitVoteData(int WarfieldNo) { m_VoteData[WarfieldNo]=0; }

	void ClearWarfieldData(int Warfieldno);

	DWORD GetWarCount() { return (DWORD)m_WarNo%128; }
	int   GetWarNo()  { return m_WarNo; }

	int GetSquadKind(int Nation,int WarfieldNo)
	{
		int tempNation=Warfield[WarfieldNo].GetNationCode();
		if (Nation==NW_YL) return NW_REINFORCE;
		if (Nation==tempNation) return NW_DEFENCER;
		else return NW_ATTACKER;
	}

	int GetAttacker(int WarfieldNo)
	{
		if (Warfield[WarfieldNo].GetNationCode()==NW_BY) return NW_ZY;
		else return NW_BY;
	}

	int GetDefender(int WarfieldNo)
	{
		if (Warfield[WarfieldNo].GetNationCode()==NW_BY) return NW_BY;
		else return NW_ZY;
	}

	int GetReinforce(int WarfieldNo)
	{
		return NW_YL;
	}

	int GetNation(int WarfieldNo,int Kind)
	{
		int tempNation=Warfield[WarfieldNo].GetNationCode();
		switch(Kind)
		{
		case NW_ATTACKER :
			if (tempNation==NW_BY) return NW_ZY;
			else return NW_BY;
			break;
		case NW_DEFENCER :
			return tempNation;
			break;
		case NW_REINFORCE :
			return NW_YL;
			break;
		}
	}

	t_SquadInformation*	GetSquadInfo(int Nation,int WarfieldNo,int SquadNo) 
	{ 
		return Warfield[WarfieldNo].GetSquadInfo(GetSquadKind(Nation,WarfieldNo),SquadNo); 
	}

    void IncSquadMemberCount(int Nation,int WarfieldNo,int SquadNo) 
	{ 
		Warfield[WarfieldNo].IncSquadMemberCount(GetSquadKind(Nation,WarfieldNo),SquadNo); 

	}
	void DecSquadMemberCount(int Nation,int WarfieldNo,int SquadNo) 
	{ 
		Warfield[WarfieldNo].DecSquadMemberCount(GetSquadKind(Nation,WarfieldNo),SquadNo); 
	}
	int GetSquadMemberCount(int Nation,int WarfieldNo,int SquadNo) 
	{ 
		return Warfield[WarfieldNo].GetSquadMemberCount(GetSquadKind(Nation,WarfieldNo),SquadNo); 
	}
	void SetSquadLoadingPoint(int Nation,int WarfieldNo,int SquadNo,int LoadingPoint) 
	{ 
		Warfield[WarfieldNo].SetSquadLoadingPoint(GetSquadKind(Nation,WarfieldNo),SquadNo,LoadingPoint); 
	}
	void SetSquadLeader(int Nation,int WarfieldNo,int SquadNo,t_CommanderInformation* SquadLeaderInfo) 
	{ 
		Warfield[WarfieldNo].SetSquadLeader(GetSquadKind(Nation,WarfieldNo),SquadNo,SquadLeaderInfo); 
	}

	t_CommanderInformation* GetCommanderInfo(int Nation,int WarfieldNo) 
	{ 
		return Warfield[WarfieldNo].GetCommanderInfo(GetSquadKind(Nation,WarfieldNo)); 
	}

	t_CommanderInformation* GetCommanderInfoByKind(int Kind,int WarfieldNo) 
	{ 
		return Warfield[WarfieldNo].GetCommanderInfo(Kind); 
	}

	t_CommanderInformation* GetCandidaterInfo(int Nation,int WarfieldNo,int CandidaterNo) 
	{ 
		return Warfield[WarfieldNo].GetCandidaterInfo(GetSquadKind(Nation,WarfieldNo),CandidaterNo); 
	}
	void IncCommanderVoteData(int Nation,int WarfieldNo,int CandidaterNo) 
	{ 
		Warfield[WarfieldNo].IncCommanderVoteData(GetSquadKind(Nation,WarfieldNo),CandidaterNo); 
	}
	int GetCommanderVoteData(int Nation,int WarfieldNo,int CandidaterNo) 
	{ 
		return Warfield[WarfieldNo].GetCommanderVoteData(GetSquadKind(Nation,WarfieldNo),CandidaterNo); 
	}
	int GetCommanderVoteDataByKind(int WarfieldNo,int Kind,int CandidaterNo)
	{
		return Warfield[WarfieldNo].GetCommanderVoteData(Kind,CandidaterNo);
	}
	bool CanRegCommanderCandidater(int Nation,int WarfieldNo,int CandidaterNo) 
	{ 
		return Warfield[WarfieldNo].CanRegCommanderCandidater(GetSquadKind(Nation,WarfieldNo),CandidaterNo); 
	} 
	void SetCandidaterInfo(int Nation,int WarfieldNo,int CandidaterNo,t_CommanderInformation* CandidaterInfo) 
	{ 
		Warfield[WarfieldNo].SetCandidaterInfo(GetSquadKind(Nation,WarfieldNo),CandidaterNo,CandidaterInfo); 
	}
	void SetCommander(int WarfieldNo,int Kind,int CandidaterNo)
	{
		Warfield[WarfieldNo].SetCommander(Kind,CandidaterNo);
	}

	int  GetWarfieldNationCode(int WarfieldNo) { return Warfield[WarfieldNo].GetNationCode(); }
	int  GetWarfieldNationCode() 
	{
		if (Warfield[0].GetStatus()>=2) return Warfield[0].GetNationCode();
		if (Warfield[1].GetStatus()>=2) return Warfield[1].GetNationCode();
		if (Warfield[2].GetStatus()>=2) return Warfield[2].GetNationCode();
	}
	void SetWarfieldNationCode(int WarfieldNo,int Code) {Warfield[WarfieldNo].SetNationCode(Code); }

	const char* GetCommanderName(int WarfieldNo,int Nation) { return Warfield[WarfieldNo].GetCommanderName(GetSquadKind(Nation,WarfieldNo)); }
	const char* GetCandidaterName(int WarfieldNo,int Nation,int CandidaterNo) { return Warfield[WarfieldNo].GetCandidaterName(GetSquadKind(Nation,WarfieldNo),CandidaterNo); }
	const int GetCandidaterVoteCount(int WarfieldNo,int Nation,int CandidaterNo) { return Warfield[WarfieldNo].GetCandidaterVoteCount(GetSquadKind(Nation,WarfieldNo),CandidaterNo); }
	char GetSquadLoadingPoint(int WarfieldNo,int Kind,int SquadNo) { return Warfield[WarfieldNo].GetSquadLoadingPoint(Kind,SquadNo); }
	char GetSquadRareSok(int WarfieldNo,int Kind,int SquadNo,int SokNo) { return Warfield[WarfieldNo].GetSquadRareSok(Kind,SquadNo,SokNo); }
	char* GetSquadRareSok2(int WarfieldNo,int Kind,int SquadNo) { return Warfield[WarfieldNo].GetSquadRareSok2(Kind,SquadNo); }

	char* GetLeadCandidaterName(int WarfieldNo,int Kind)
	{
		return Warfield[WarfieldNo].GetLeadCandidaterName(Kind);
	}

	bool ElectCommander(int WarfieldNo) { return Warfield[WarfieldNo].ElectCommander(); }
	bool CheckSecretPlaceOpen(int WarfieldNo) { return Warfield[WarfieldNo].CheckSecretPlaceOpen(); }
	bool CheckSecretPlaceOpen()
	{
		if (Warfield[0].CheckSecretPlaceOpen()) return true;
		if (Warfield[1].CheckSecretPlaceOpen()) return true;
		if (Warfield[2].CheckSecretPlaceOpen()) return true;
		if (m_NewWarfieldStatus[0]==NW_SOPEN) return true;
		return false;
	}

	int GetSecretOpenedWarfieldNo()
	{
		if (Warfield[0].CheckSecretPlaceOpen()) return 0;
		if (Warfield[1].CheckSecretPlaceOpen()) return 1;
		if (Warfield[2].CheckSecretPlaceOpen()) return 2;
		if (m_NewWarfieldStatus[0]==NW_SOPEN) return 3;
		return -1;
	}
	void SetRemainTime(int WarfieldNo,DWORD RemainTime) 
	{
		if (WarfieldNo>=0&&WarfieldNo<=2)
			Warfield[WarfieldNo].SetRemainTime(RemainTime); 
		else
		if (WarfieldNo>=3)
			m_NewWarfieldRemainTime[WarfieldNo-3]=RemainTime;
	}
	DWORD GetRemainTime(int WarfieldNo) 
	{ 
		switch(WarfieldNo)//030116 lsw ���� ����
		{
		case 0:
		case 1:
		case 2:
			{
				return Warfield[WarfieldNo].GetRemainTime(); 
			}break;
		case 3:
		default:
			{
				return m_NewWarfieldRemainTime[WarfieldNo-3];
			}break;
		}
		return 0;
	}

	void GetWarRemainTime(char* ReturnStr);
	void GetNewWarRemainTime(char* ReturnStr);

	void SetSecretOpen(int WarfieldNo,bool isActive) { Warfield[WarfieldNo].SetSecretOpen(isActive); }	// 011025 LTS

	void SetLocalWarStatus(int isStart);
	void SetLocalWarStatus2(int isStart);				// LTS NEW LOCALWAR
	int	 GetLocalWarStatus()			{ return m_LocalWarStart; }

	//LocalWarfield_Info	GetLocalWarfieldInfo(int Index) { return LocalWarfield[Index].GetLocalWarfieldInfo(); }
	//void				SetLocalWarfieldInfo(int Index, LocalWarfield_Info LF) { LocalWarfield[Index].SetLocalWarfieldInfo(LocalWarfield_Info LF); }

	int				ConvertNation2Index(int Nation) { return LocalWarfield[0].ConvertNation2Index(Nation); }
	short			GetLocalWarfieldManCount(int NationIndex);
	short			GetLocalWarfieldManCount(int Index,int NationIndex) {return LocalWarfield[Index].GetManCount(NationIndex); }
	void			IncLocalWarfieldManCount(int Index,int NationIndex);
	void			DecLocalWarfieldManCount(int Index,int NationIndex);
	void			ClearLocalWarfieldManCount();

	/*short 			GetLocalWarfieldPoint(int NationIndex);
	short			GetLocalWarfieldPoint(int Index,int NationIndex) { return LocalWarfield[Index].GetPoint(NationIndex); }
	void			IncLocalWarfieldPoint(int Index,int NationIndex,int Value) { LocalWarfield[Index].IncPoint(NationIndex,Value); }
	void			ClearLocalWarfieldPoint();*/

	short 			GetLocalWarPoint(int NationIndex) { return m_LocalWarPoint[NationIndex]; }
	void			IncLocalWarPoint(int NationIndex,int Value) { m_LocalWarPoint[NationIndex]+=Value; }
	void			ClearLocalWarPoint() { m_LocalWarPoint[0]=0;m_LocalWarPoint[1]=0;m_LocalWarPoint[2]=0; }
	void			ClearLocalWarDefencePoint() {m_LocalWarDefencePoint[0]=100;m_LocalWarDefencePoint[1]=100;m_LocalWarDefencePoint[2]=100;}
	void			ClearLocalWarRemainTime() { g_LocalWarRemainTime=0; }
	__int64			GetLocalWarRemainTime()	{ return g_LocalWarRemainTime; }	// 020115 LTS

	void			SetSealStoneStatus(int NationIndex,int SealNo,int Status, int nHP);// 030516 kyo // LTS NEW LOCALWAR	
	void			CheckSealStoneStatus();												// LTS NEW LOCALWAR	
	inline int		CheckAllSealStoneBroked(int NationIndex);							// LTS NEW LOCALWAR	
	void			ClearLocalWarResult();												// LTS NEW LOCALWAR	
	inline void		SetLocalWarResult(int NationIndex,int Result);						// LTS NEW LOCALWAR	
	void			CalcDefencePoint(int NationIndex);									// LTS NEW LOCALWAR	
	int				CheckWinNation();													// LTS NEW LOCALWAR	
	int				CheckLocalWarResult();												// LTS NEW LOCALWAR	
	void			ClearSealStoneStatus();												// LTS NEW LOCALWAR
	int				GetLocalWarDefencePoint(int NationIndex);							// LTS NEW LOCALWAR		

	cWarfield*		GetWarfield(int WarfieldNo);										// LTS NEW_NATION_WAR
	void			UpdateStatus();														// LTS NEW_NATION_WAR
	bool			LoadWarStartupData();												// LTS NEW_NATION_WAR
	bool			LoadNewWarStartupData();
	void			LoadWarNo();														// LTS NEW_NATION_WAR	
	void			SaveWarNo();														// LTS NEW_NATION_WAR
	bool			CheckWarStart();													// LTS NEW_NATION_WAR
	int				GetNewWarfieldStatus(int Index);												// LTS NEW_NATION_WAR
	void			SetNewWarfieldStatus(int Index,int Status);												// LTS NEW_NATION_WAR	
	bool			InitNewWarfield();

	void			CheckAndSendWarStart(t_packet* p);

	void			ClearAllLocalSealStoneHP();			//030506 kyo // m_nAllLocalWarSealStoneHP�ʱ�ȭ
	void			GetAllLocalSealStoneHP();			//030506 kyo // ���������� ��� ��輮�� HP��

	unsigned long	GetLocalWarAllSealStoneHP(const int nNationIndex) const { return m_nAllLocalWarSealStoneHP[nNationIndex]; };
	
public:
	void SetWarStartInfo(CWarStartInfo* pWarStartInfo)
	{	//< CSD-030723
		Dbg_Assert(pWarStartInfo != NULL);
		m_pWarStartInfo = pWarStartInfo;
	}	//> CSD-030723

	CWarStartInfo* GetWarStartInfo()
	{	//< CSD-030723
		return m_pWarStartInfo;
	}	//> CSD-030723

private:
	CWarStartInfo* m_pWarStartInfo; // CSD-030723
};	


typedef void	*LPVOID,**LP2VOID;
typedef class CTeam															// Team Class �� �и�...
{
	typedef list<SquadMember*>		TeamList;				
	typedef TeamList::iterator		TeamItor;

	TeamList						m_TeamList;

	int								m_iTeamNo;							// A or B Team
	int								m_iTeamMemberCount;	// 030509 kyo 	// m_TeamList.Size();
	int								m_iDeathCount;

	POINT							m_LivePoint;

	int								m_NationMember[3];


public :

	CTeam();
	~CTeam();

	void	Clear();
	void	InsertTeamMember(int cn);
	void	DeleteMember(int cn);
	void	SendMessage(t_packet* p);
	int		GetTeamCount();
	int		GetTeamNo();
	void	SetTeamNo(int TeamNo);
	bool	CheckTeam(int cn);
	void	KickTeamAll();
	void	KickUser(int ID);
	void	GiveFame(LPCHARLIST pCaster,LPCHARLIST pTarget,int Range,int AddFame);
	void	GiveFame2All(int AddFame);
	int		GetNationCount(int Nation);
	void	AddDesthCount();
	int		GetDeathCount();

	void	RemoveArmor();

	void	SetLivePoint(POINT lPoint);
	POINT	GetLivePoint();
	int		GetNationMemberCount(int Nation);

} *LPTEAM;


typedef struct GDATA
{
	int			NPCType;
	int			NpcIndex;
	int			GenPosX;
	int			GenPosY;
	int			NPC_ID;
	int			Status;
	int			DontNo;
}*LPGDATA;

typedef class CGuardStone
{
	int				m_iWarfieldNo;
	int				m_iTeamNo;

	LPGDATA			m_pGData;
	int				m_iGDataCount;

	int				m_iTypeCount[3];					// 0 : ����, 1 : ����, 2 ����

public :

	CGuardStone();
	~CGuardStone();

	void			Clear();
	void			SetWarfieldNo(int WarfieldNo);
	int				GetWarfieldNo();
	void			SetTeamNo(int TeamNo);
	int				GetTeamNo();

	int				SetGDataSize();								// private,protected  Calc Data Size From DB
	bool			LoadGData();

	bool			LoadData();
	void			FirstMakeNPCPtr();
	void			MakeNPCPtr();
	bool			MakeGuardStone(const int iIndex, const int iCallType);//030102 lsw //FirstMakeNPCPtr() MakeNPCPtr() ������ ȣ�� �մϴ�.

	void			SetDontData();
	// XXX			GetDontData();
	//int			GetDontSize(int No)

	bool			CheckTypeAllBroke(int Type);
	int				GetBrokeStatus();							// 3->1 ���� �Ǵ� ���彺��... ��������..
	bool			CheckNPC(int NpcNo);
	bool			CheckAndUpdateStatus(LPCHARLIST lpChar);

	void			MakeDontTable();
	void			GetTileDont(DONT_DATA* lpDontData);
	void			GetStatus(char* lpStatus);

	void			SendBrokeBBS(int Team,int Type,int No,LPCHARLIST pTarget);

	LPGDATA			GetGData(const int nIndex); // 030506 kyo
	int				GetCount(){return m_iGDataCount;};	// 030506 kyo

}*LPGUARDSTONE;

struct WarTimeData
{
	DWORD			WarTime;
	DWORD			SOpenTime;
};

#define		WARFIELD_PEACE						0
#define		WARFIELD_BATTLE						1
#define		WARFIELD_SOPEN						2


class CNewWarfield
{
	LPTEAM			m_pTeam;
	LPGUARDSTONE	m_pGuard;
	int				m_iTeamCount;
	int				m_iWarfieldNo; 
	
	WarTimeData		m_Time;
	int				m_iStatus;						// 0 : PEACE, 1:WAR, 2 : SOPEN

	__int64			m_64LoopTime;

	int				m_iWinTeam;

	int				MemberMAX[3];

	MonsterList		m_MonsterList;					// �Ͻ������� �����Ǵ� ��Ʈ�� ����Ʈ ���ʽ� Ÿ�ӿ�..

	long			m_nFinalGStoneHP[2];			// 030506 kyo
	long			m_nAllNormalGStoneHP[2];		// 030506 kyo
	long			m_nAllGatelHP[2];				// 030506 kyo

public :

	CNewWarfield();
	~CNewWarfield();

	bool			InitWarfield();
	bool			LoadWarfieldData();
	bool			LoadSMonster(WORD WarfieldNo);
	void			TeamClear();
	void			GuardClear();
	void			SetTeamCount(int Count);

	DWORD			GetRemainTime();

	int				GetWarfieldStatus();

	void			LoadTimeData();
	LPTEAM			GetTeam(int TeamNo);
	LPGUARDSTONE	GetGuard(int TeamNo);

	void			SetWarfieldStatus(int Status);

	void			Update();
	void			UpdatePeace();
	void			UpdateWar();
	void			UpdateSOpen();

	bool			isMyTeam(LPCHARLIST lpChar,int NPCNo);
	int				GetTeamNo(LPCHARLIST lpChar);

	bool			CanAttackGuard(LPCHARLIST pCaster,LPCHARLIST pTarget);

	void			KickAllUser2Home();

	void			SetWinTeam(int TeamNo);
	int				GetWinTeam();

	void			UpdateGuardStatus(LPCHARLIST pCaster,LPCHARLIST pTarget);
	void			GiveFame(int TeamNo,LPCHARLIST pCaster,LPCHARLIST pTarget);
	void			SendWarResult();

	void			CountDeath(LPCHARLIST lpChar);
	void			CheckAndKickUser(int cn);

	void			GetTileDont(DONT_DATA* lpDontData);

	void			DeleteMember(int cn);
	void			LoopTimeChange(t_packet* p);

	void			SendSquadChat(LPCHARLIST lpChar,t_packet* p);
	POINT			GetLivePoint(LPCHARLIST lpChar);

	int				GetNationMemberMax(int Nation);
	int				GetNationMemberCount(int Nation);

	void			InsertMonsterData(t_WeaponStruct Monster);
	void			DeleteAllMonsterData();
	void			MakeMonster();

	//<< 030506 kyo
	long			GetAllGDataTypeHP(const int nTeamNum , const int nType); // 030506 kyo
	void			GetAllGuardsHP(); // 030506 kyo
	void			CheckWinTeam(); //030506 kyo //����ؼ� �̱����� ����� �˾ƺ���.. ����� �����Ѵ�.

	
	long			GetFinalGStoneHP(const int nTeamNum );			
	long			GetAllNormalGStoneHP(const int nTeamNum );		
	long			GetAllGatelHP(const int nTeamNum );		
	void			SetFinalGStoneHP(const int nTeamNum, long lAllHP );
	void			SetAllNormalGStoneHP(const int nTeamNum, long lAllHP );
	void			SetAllGatelHP(const int nTeamNum, long lAllHP );
	void			ClearFinalGStoneHP();
	void			ClearAllNormalGStoneHP();
	void			ClearAllGatelHP();
	//>> 030506 kyo
};


 
 
#endif
