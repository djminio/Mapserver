#pragma once

#include <list>
#include "NationSys.h"

/**
 * @def		enum _eTEAM.
 * @brief	전쟁에서 쓰일 team 인식자.
 */
//< LTH-040419-KO.
typedef enum _eTEAM
{
	TEAM1		= 0,	/**< 아군 및 Attacker. */
	TEAM2		= 1,	/**< 적군 및 Deffenser. */
	MAX_TEAM	= 2,	/**< 총 팀의 개수. */
} eTEAM;
//> LTH-040419-KO.

/**
 * @class	CSquad.
 * @brief	전쟁터에서 쓰일 부대에 관한 정보 관련 class.
 */
//< LTH-040419-KO.
typedef class CSquad
{
public:
	CSquad();
	virtual ~CSquad() { DeleteAllMember(); }

public:
	VOID RemoveArmor();
	VOID DeleteAllMember();
	VOID AddDeathCount(INT nNationNo);
	VOID GiveFame2Dual(INT nAddFame);
	VOID GiveFame(LPCHARLIST lpCaster, LPCHARLIST lpTarget, INT nRange, INT nAddFame);
	INT GetNationDeathCount(INT nNationNo);
	BOOL FindMember(INT nCn);
	VOID SendMessageAllMember(t_packet *p);
	VOID DeleteMember(INT nCn);
	VOID InsertMember(INT nCn);
	INT GetMemberCount();
	INT GetNationMemberCount(INT nNationNo);

	/**
	 * @fn		CSquad::SetLivePoint().
	 * @brief	이 부대의 로딩 포인트 설정.
	 * @param	POINT xyLivePoint. 설정 될 로딩 포인트.
	 * @return	VOID.
	 */
	//< LTH-040419-KO.
	VOID SetLivePoint(POINT xyLivePoint) { m_xyLoadingPoint = xyLivePoint; }
	//> LTH-040419-KO.

	/**
	 * @fn		CSquad::GetLivePoint().
	 * @brief	이 부대의 로딩 포인트.
	 * @return	POINT. 로딩포인트 반환.
	 */
	//< LTH-040419-KO.
	POINT GetLivePoint() { return m_xyLoadingPoint; }
	//< LTH-040419-KO.

	/**
	 * @fn		CSquad::SetSquadNo().
	 * @brief	이 부대번호 설정.
	 * @param	INT nSquadNo. 설정 할 부대 번호.
	 * @return	VOID.
	 */
	//< LTH-040419-KO.
	VOID SetSquadNo(INT nSquadNo) { m_nSquadNo = nSquadNo; }
	//> LTH-040419-KO.

protected:
	/**
	 * @def		std::list<SquadMember*> LTSQUAD;.
	 * @brief	부대원을 관리 할 리스트 정의.
	 */
	//< LTH-040419-KO.
	typedef std::list<SquadMember*> LTSQUAD;
	//> LTH-040419-KO.
	/**
	 * @def		LTSQUAD::iterator LTSQUADIT;.
	 * @brief	부대원을 관리 할 리스트의 반복자.
	 */
	//< LTH-040419-KO.
	typedef LTSQUAD::iterator LTSQUADIT;
	//> LTH-040419-KO.

	INT m_nSquadNo;					/**< 이 부대의 번호. */
	LTSQUAD m_ltSquad;				/**< 부대원을 관리 할 리스트 */
	INT m_nSquadLeader;				/**< 부대장. */
	POINT m_xyLoadingPoint;			/**< 이 부대의 로딩 포인트. */
	INT m_naNumOfDeathNation[3];	/**< 각 국가별 죽은 사람 수. */
	INT m_naNumOfJoinNation[3];		/**< 각 국가별 참여 인원 수. */
} *LPSQUAD;							/**< 포인터 형 변수 정의. */
//> LTH-040419-KO.

/**
 * @class	CTeamInfo.
 * @brief	전쟁에서의 팀을 관리 하기 위한 class.
 */
//< LTH-040419-KO.
typedef class CTeamInfo  
{
public:
	CTeamInfo() : m_lpSquad(NULL), m_nCommander(-1), m_nNumOfSquad(-1), m_nTeamNo(-1) {}
	virtual ~CTeamInfo() {}

public:
	VOID RemoveArmor();
	VOID GiveFame(LPCHARLIST lpCaster, LPCHARLIST lpTarget, INT nRange, INT nAddFame);
	INT GetNationDeathCount(INT nNation);
	BOOL KickUser(INT nCn);
	POINT GetLivePoint(LPCHARLIST lpChar);
	VOID DeleteSquadMember(INT nWarfieldNo, INT nCn);
	VOID InsertSquadMember(INT nWarfieldNo, INT nCn);
	HRESULT Init(INT nNumOfSquad);
	INT CheckSquadOfCharacter(INT nWarfieldNo, INT nCharLv);
	INT GetNationMemberCount(INT nNationNo);
	INT GetSquadMemberCount(INT nSquadNo);
	VOID SendMessageAllMember(t_packet *p);
	VOID GiveFame2Dual(INT nAddFame);
	VOID Clear();

	/**
	 * @fn		CTeamInfo::SetLivePoint().
	 * @brief	각 부대 로딩포인트 설정.
	 * @param	INT nSquadNo. 부대 번호.
	 * @param	POINT xyLivePoint. 로딩 포인트.
	 * @return	VOID.
	 */
	//< LTH-040419-KO.
	VOID SetLivePoint(INT nSquadNo, POINT xyLivePoint) { m_lpSquad[nSquadNo].SetLivePoint(xyLivePoint); }
	//> LTH-040419-KO.

	/**
	 * @fn		CTeamInfo::AddDeathCount().
	 * @brief	죽은 사람 수.
	 * @param	INT nNationNo. 죽은 사람의 국가.
	 * @param	INT nSquadNo. 죽은 사람의 부대.
	 * @return	VOID.
	 */
	//< LTH-040419-KO.
	VOID AddDeathCount(INT nNationNo, INT nSquadNo) { m_lpSquad[nSquadNo].AddDeathCount(nNationNo); }
	//> LTH-040419-KO.

	/**
	 * @fn		CTeamInfo::SetTeamNo().
	 * @brief	이 팀의 번호 설정.
	 * @param	INT nTeamNo. 설정 할 번호.
	 * @return	VOID.
	 */
	//< LTH-040419-KO.
	VOID SetTeamNo(INT nTeamNo) { m_nTeamNo = nTeamNo; }
	//> LTH-040419-KO.

	/**
	 * @fn		CTeamInfo::GetNumOfSquad().
	 * @brief	부대 수 반환.
	 *			반드시 필요하다. 부대 수를 알아내어 그만큼 루프를 돌아야하니까...
	 * @return	INT.
	 */
	//< LTH-040304-KO.
	INT GetNumOfSquad() { return m_nNumOfSquad; }
	//> LTH-040304-KO.
	
protected:
	INT m_nTeamNo;		/**< 이 팀의 번호. 주로 enum eTEAM 값을 사용 한다. */
	INT m_nNumOfSquad;	/**< 이 팀의 부대 수. 안전하도록 적어도 한 팀 이상으로 한다. */
	INT m_nCommander;	/**< 이 팀의 사령관. */
	LPSQUAD m_lpSquad;	/**< 이 팀의 부대들을 관리 하기 위한 리스트. */
} *LPTEAMINFO;			/**< 포인터 형 변수 정의. */
//< LTH-040419-KO.