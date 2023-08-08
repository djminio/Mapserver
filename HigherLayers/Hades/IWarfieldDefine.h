#pragma once

/**
 * @class	CWarTimeInfo.
 * @brief	������ ���� ������ �����ϴ� class.
 */
//< LTH-040419-KO.
class CWarTimeInfo
{
public:
	CWarTimeInfo() 
	: m_btStartDay(0)
	, m_btStartHour(0)
	, m_dwPrepareTime(0)
	, m_dwWarTime(0)
	, m_dwSecretAreaOpenTime(0)
	{}
	~CWarTimeInfo() {}

public:
	DWORD m_dwPrepareTime;			/**< ���� �غ�Ⱓ �ð�. */
	DWORD m_dwWarTime;				/**< ���� �Ⱓ �ð�. */
	DWORD m_dwSecretAreaOpenTime;	/**< ������� ���� �ð�. */
	BYTE m_btStartDay;				/**< ���� ����. */
	BYTE m_btStartHour;				/**< ���� �ð�. */
};
//> LTH-040419-KO.

typedef CWarTimeInfo* LPWARTIMEINFO;

/**
 * @struct	_tagCommanderSet.
 * @brief	��ɰ� ���� ����ü.
 */
//< LTH-040419-KO.
typedef struct _tagCommanderSet
{
	INT nLevelMin;		/**< �ּ� ����. */
	INT nLadderMin;		/**< �ּ� ���� ����. */
	INT nFameMin;		/**< �ּ� ��ġ. */
} tagCommander, *LPCOMMANDER;
//> LTH-040419-KO.

/**
 * @struct	_tagSquadSet.
 * @brief	�δ� ���� ����ü.
 */
//< LTH-040419-KO.
typedef struct _tagSquadSet
{
	INT nLeaderLevelMin;	/**< �δ��� �ּ� ����. */
	INT nLeaderLadderMin;	/**< �δ��� �ּ� ���� ����. */
	INT nLevelMin;			/**< �ּ� ����. */
	INT nLevelMax;			/**< �ִ� ����. */
	INT nPersonMin;			/**< �ּ� �ο�. */
	INT nPersonMax;			/**< �ִ� �ο�. */
	POINT xyStartingPoint;	/**< �ε� ����Ʈ. */
} tagSquad, *LPSQUADSET;
//> LTH-040419-KO.

/**
 * @class	CSoldierSet.
 * @brief	�δ� ���� class.
 */
//< LTH-040419-KO.
class CSoldierSet
{
public:
	CSoldierSet() : m_nNumOfSquad(5) {}
	~CSoldierSet() {}

public:
	INT m_nNumOfSquad;				/**< �δ� ��. */
	tagCommander m_tagCommander;	/**< ��ɰ� ���� ����ü. */
	tagSquad m_tagaSquad[5];		/**< �δ� ���� ����ü. */
};
//> LTH-040419-KO.

typedef CSoldierSet* LPSOLDIERSET;

/**
 * @class	CMapSetting.
 * @brief	������ �� ���� class.
 */
//< LTH-040419-KO.
class CMapSetting
{
public:
	CMapSetting() : m_nMoveLevelMin(0), m_nMoveLevelMax(0) {}
	~CMapSetting() {}

public:
	int m_nUserEntranceLimitTime;	/**< LTH-040510-KO ���� ������ �̵� ���� �ð�. */
	INT m_nMoveLevelMin;	/**< �̵����� �ּҷ���. */
	INT m_nMoveLevelMax;	/**< �̵����� �ִ뷹��. */
};
//> LTH-040419-KO.

typedef CMapSetting* LPMAPSETTING;

//-----------------------------------------------------------
/**
 * @interface	IWarfieldStateDefine
 * @brief		������ ���� class�� ���ʰ� �Ǵ� interface.
 */
//< LTH-040419-KO.
interface IWarfieldStateDefine
{
	STDMETHOD_(VOID, Init)(THIS_ INT nWarfieldNo) PURE;
	STDMETHOD_(VOID, SetRemainTime)(THIS_ __int64 n64RemainTime) PURE;
	STDMETHOD_(__int64, GetRemainTime)(THIS) PURE;
	STDMETHOD_(VOID, SetLoopTime)(THIS_ DWORD n64LoopTime) PURE;
	STDMETHOD_(DWORD, GetLoopTime)(THIS) PURE;
	STDMETHOD(Update)(THIS) PURE;

protected:
	DWORD m_dwTerm;				/**< ���� ������ ���� �Ⱓ. */
	DWORD m_dwLoopTime;			/**< ���� ���°� ������ �������� �ð�. */
	__int64 m_n64RemainTime;	/**< ���� ������ ���� �ð�. */
	INT m_nWarfieldNo;			/**< ������ ��ȣ. */
};
//> LTH-040419-KO.

typedef IWarfieldStateDefine * LPWARFIELDSTATEDEFINE;

//-----------------------------------------------------------

#include "GuardInfo.h"
#include "TeamInfo.h"

/**
 * @struct	_tagGetLivePoint.
 * @brief	�δ� �ε� ����Ʈ ���� ����ü. �޽��� ���޿� ��� �ȴ�.
 */
//< LTH-040419-KO.
typedef struct _tagGetLivePoint
{
	LPCHARLIST lpChar;	/**< �ش� �ε� ����Ʈ�� ã������ ĳ����. */
	LPPOINT lpPoint;	/**< �ε� ����Ʈ. */
} tagGetLivePoint;
//> LTH-040419-KO.

/**
 * @struct	_tagSendSquadChat.
 * @brief	�δ� ä�� ���� ���� ����ü. �޽��� ���޿� ��� �ȴ�.
 */
//< LTH-040419-KO.
typedef struct _tagSendSquadChat
{
	LPCHARLIST lpChar;	/**< �޽����� ���� ĳ����. */
	t_packet* p;		/**< ��Ŷ ����. */
} tagSendSquadChat;
//> LTH-040419-KO.

/**
 * @struct	_tagOpponent.
 * @brief	������ �Ǻ��ϱ� ���� ����ü. �޽��� ���޿� ��� �ȴ�.
 */
//< LTH-040419-KO.
typedef struct _tagOpponent
{
	LPCHARLIST lpCaster;	/**< ���ϱ� ���� ĳ����. */
	LPCHARLIST lpTarget;	/**< �� ��� ĳ����. */
} tagOpponent;
//> LTH-040419-KO.

/**
 * @struct	_tagSquadCount.
 * @brief	�δ� �ο� ������ ���� ����ü. �޽��� ���޿� ��� �ȴ�.
 */
//< LTH-040419-KO.
typedef struct _tagSquadCount
{
	INT nSquadNo;					/**< �δ� ��ȣ. */
	INT nCurrentSquadMemberCount;	/**< �ش� �δ��� �δ�� ��. */
} tagSquadCount;
//> LTH-040419-KO.

/**
 * @interface	IWarfieldDefine
 * @brief		������ class�� ���ʰ� �Ǵ� interface.
 */
//< LTH-040419-KO.
interface IWarfieldDefine
{
	STDMETHOD(Init) (THIS_ INT nWarfieldNo) PURE;
	STDMETHOD_(VOID, SetStatus)(THIS_ INT nState) PURE;
	STDMETHOD_(INT, GetStatus)(THIS) PURE;
	STDMETHOD_(VOID, SetRemainTime)(THIS_ __int64 dwRemainTime) PURE;
	STDMETHOD_(__int64, GetRemainTime)(THIS) PURE;
	STDMETHOD(Update)(THIS) PURE;
	STDMETHOD_(INT, GetSquadMemberCount)(THIS_ INT nSquadNo) PURE;
	STDMETHOD_(BOOL, CanAttackGuard)(THIS_ LPCHARLIST lpCaster, LPCHARLIST lpTarget) PURE;
	STDMETHOD_(VOID, InsertSquadMember)(THIS_ INT nCn) PURE;
	STDMETHOD_(VOID, DeleteSquadMember)(THIS_ INT nCn) PURE;
	STDMETHOD_(LPTEAMINFO, GetTeamInfo)(INT nTeamNo) PURE;
	STDMETHOD_(LPGUARDINFO, GetGuardInfo)(INT nTeamNo) PURE;
	STDMETHOD_(INT, GetTeamMemberCount)(THIS_ INT nTeamNo) PURE;
	STDMETHOD_(VOID, SendSquadChat)(THIS_ LPCHARLIST lpChar, t_packet* p) PURE;
	STDMETHOD_(POINT, GetLivePoint)(THIS_ LPCHARLIST lpChar) PURE;
	STDMETHOD_(VOID, GetTileDont)(THIS_ DONT_DATA* lpDontData) PURE;
	STDMETHOD_(VOID, CheckAndKickUser)(THIS_ INT nCn) PURE;
	STDMETHOD_(VOID, LoopTimeChange)(t_packet* p) PURE;
	STDMETHOD_(VOID, UpdateGuardStatus)(THIS_ LPCHARLIST lpCaster, LPCHARLIST lpTarget) PURE;
	STDMETHOD_(VOID, CountDeath)(THIS_ LPCHARLIST lpChar) PURE;
	STDMETHOD_(int, GetWarfieldNo)(THIS) PURE;
	STDMETHOD_(int*, GetJoinNation)(THIS) PURE;
};
//> LTH-040419-KO.

typedef IWarfieldDefine * LPWARFIELDDEFINE;