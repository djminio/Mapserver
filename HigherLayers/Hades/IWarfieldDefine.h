#pragma once

/**
 * @class	CWarTimeInfo.
 * @brief	전쟁터 관련 설정을 관리하는 class.
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
	DWORD m_dwPrepareTime;			/**< 전쟁 준비기간 시간. */
	DWORD m_dwWarTime;				/**< 전쟁 기간 시간. */
	DWORD m_dwSecretAreaOpenTime;	/**< 비밀지역 오픈 시간. */
	BYTE m_btStartDay;				/**< 시작 요일. */
	BYTE m_btStartHour;				/**< 시작 시간. */
};
//> LTH-040419-KO.

typedef CWarTimeInfo* LPWARTIMEINFO;

/**
 * @struct	_tagCommanderSet.
 * @brief	사령관 설정 구조체.
 */
//< LTH-040419-KO.
typedef struct _tagCommanderSet
{
	INT nLevelMin;		/**< 최소 레벨. */
	INT nLadderMin;		/**< 최소 레더 점수. */
	INT nFameMin;		/**< 최소 명성치. */
} tagCommander, *LPCOMMANDER;
//> LTH-040419-KO.

/**
 * @struct	_tagSquadSet.
 * @brief	부대 설정 구조체.
 */
//< LTH-040419-KO.
typedef struct _tagSquadSet
{
	INT nLeaderLevelMin;	/**< 부대장 최소 레벨. */
	INT nLeaderLadderMin;	/**< 부대장 최소 레더 점수. */
	INT nLevelMin;			/**< 최소 레벨. */
	INT nLevelMax;			/**< 최대 레벨. */
	INT nPersonMin;			/**< 최소 인원. */
	INT nPersonMax;			/**< 최대 인원. */
	POINT xyStartingPoint;	/**< 로딩 포인트. */
} tagSquad, *LPSQUADSET;
//> LTH-040419-KO.

/**
 * @class	CSoldierSet.
 * @brief	부대 설정 class.
 */
//< LTH-040419-KO.
class CSoldierSet
{
public:
	CSoldierSet() : m_nNumOfSquad(5) {}
	~CSoldierSet() {}

public:
	INT m_nNumOfSquad;				/**< 부대 수. */
	tagCommander m_tagCommander;	/**< 사령관 설정 구조체. */
	tagSquad m_tagaSquad[5];		/**< 부대 설정 구조체. */
};
//> LTH-040419-KO.

typedef CSoldierSet* LPSOLDIERSET;

/**
 * @class	CMapSetting.
 * @brief	전쟁터 맵 설정 class.
 */
//< LTH-040419-KO.
class CMapSetting
{
public:
	CMapSetting() : m_nMoveLevelMin(0), m_nMoveLevelMax(0) {}
	~CMapSetting() {}

public:
	int m_nUserEntranceLimitTime;	/**< LTH-040510-KO 유저 전쟁터 이동 제한 시간. */
	INT m_nMoveLevelMin;	/**< 이동가능 최소레벨. */
	INT m_nMoveLevelMax;	/**< 이동가능 최대레벨. */
};
//> LTH-040419-KO.

typedef CMapSetting* LPMAPSETTING;

//-----------------------------------------------------------
/**
 * @interface	IWarfieldStateDefine
 * @brief		전쟁터 상태 class의 기초가 되는 interface.
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
	DWORD m_dwTerm;				/**< 현재 상태의 지속 기간. */
	DWORD m_dwLoopTime;			/**< 현재 상태가 끝나는 실질적인 시간. */
	__int64 m_n64RemainTime;	/**< 현재 상태의 남은 시간. */
	INT m_nWarfieldNo;			/**< 전쟁터 번호. */
};
//> LTH-040419-KO.

typedef IWarfieldStateDefine * LPWARFIELDSTATEDEFINE;

//-----------------------------------------------------------

#include "GuardInfo.h"
#include "TeamInfo.h"

/**
 * @struct	_tagGetLivePoint.
 * @brief	부대 로딩 포인트 관련 구조체. 메시지 전달에 사용 된다.
 */
//< LTH-040419-KO.
typedef struct _tagGetLivePoint
{
	LPCHARLIST lpChar;	/**< 해당 로딩 포인트를 찾기위한 캐릭터. */
	LPPOINT lpPoint;	/**< 로딩 포인트. */
} tagGetLivePoint;
//> LTH-040419-KO.

/**
 * @struct	_tagSendSquadChat.
 * @brief	부대 채팅 전송 관련 구조체. 메시지 전달에 사용 된다.
 */
//< LTH-040419-KO.
typedef struct _tagSendSquadChat
{
	LPCHARLIST lpChar;	/**< 메시지를 보낸 캐릭터. */
	t_packet* p;		/**< 패킷 변수. */
} tagSendSquadChat;
//> LTH-040419-KO.

/**
 * @struct	_tagOpponent.
 * @brief	적인지 판별하기 위한 구조체. 메시지 전달에 사용 된다.
 */
//< LTH-040419-KO.
typedef struct _tagOpponent
{
	LPCHARLIST lpCaster;	/**< 비교하기 위한 캐릭터. */
	LPCHARLIST lpTarget;	/**< 비교 대상 캐릭터. */
} tagOpponent;
//> LTH-040419-KO.

/**
 * @struct	_tagSquadCount.
 * @brief	부대 인원 저장을 위한 구조체. 메시지 전달에 사용 된다.
 */
//< LTH-040419-KO.
typedef struct _tagSquadCount
{
	INT nSquadNo;					/**< 부대 번호. */
	INT nCurrentSquadMemberCount;	/**< 해당 부대의 부대원 수. */
} tagSquadCount;
//> LTH-040419-KO.

/**
 * @interface	IWarfieldDefine
 * @brief		전쟁터 class의 기초가 되는 interface.
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