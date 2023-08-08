#pragma once

#include "IWarfieldDefine.h"

/**
 * @class	CWarfieldMgr.
 * @brief	전쟁 관리자 모듈의 외부통로.
 *			맵서버의 전쟁 관리자 모듈의 외부로부터 하나의 통로를 제공하는 클래스.
 */
//< LTH-031219-KO.
class CWarfieldMgr  
{
public:
	/**
	 * @def		enum _eWARFIELD_PROC_MSG.
	 * @brief	message of Outside Module.
	 */
	//< LTH-031222-KO.
	typedef enum _eWARFIELD_PROC_MSG
	{
		WPM_NOT_WARFIELD_PROC_MSG = 0,	/**< Not Warfield process message. */
		WPM_CREATE_WARFIELD = 1,		/**< Create Warfield MapServer. */
		WPM_GET_WARFIELD_STATE = 2,		/**< Get Current Warfield Status. */
		WPM_SET_WARFIELD_STATE = 3,		/**< Set Current Warfield Status. */
		WPM_SET_REMAINTIME = 4,			/**< 현재 state의 남은 시간을 설정한다. */
		WPM_GET_REMAINTIME = 5,			/**< 현재 state의 남은 시간을 반환한다. */
		WPM_UPDATE = 6,					/**< Warfield MapServer Update routine. */
		WPM_GET_SQUAD_MEMBER_COUNT = 7,	/**< 부대 인원수를 반환한다. */
		WPM_CAN_ATTACK_GUARD = 8,		/**< 수호석이나 성문이 공격할 수있는대상인가 반환. */
		WPM_INSERT_SQUAD_MEMBER = 9,	/**< 유저를 부대 멤버로 삽입한다. */
		WPM_DELETE_SQUAD_MEMBER = 10,	/**< 유저를 부대 멤버에서 제거한다. */
		WPM_GET_WARFIELDDATA = 11,		/**< Guard들(성문, 수호석등)의 정보 및 Team 정보를 반환. */
		WPM_GET_TEAM_MEMBER_COUNT = 12,	/**< 각 팀마다의 유저 숫자를 센다. */
		WPM_SEND_SQUAD_CHAT = 13,		/**< 부대 채팅 전송. */
		WPM_GET_LIVE_POINT = 14,		/**< 부활 위치 반환. */
		WPM_GET_DONT_DATA = 15,			/**< Dont Tile Data 반환. */
		WPM_CHECK_AND_KICK_USER = 16,	/**< 유저를 체크하여 패배 했다면 마을로 돌려보낸다. */
		WPM_SET_LOOPTIME_CHANGE = 17,	/**< 현재 상태의 지속시간을 재설정한다. */
		WPM_UPDATE_GUARD_STATUS = 18,	/**< 수호석이나 성문의 현재 상태를 갱신한다. */
		WPM_INC_DEATH_MEMBER = 19,		/**< 국가별 죽은 인원을 증가 시킨다. */
		WPM_CHECK_JOIN_NATION = 20,		/**< 국가전에 참여할 국가 정보 체크. */
		WPM_MAX_WARFIELD_PROC_MSG,		/**< Max Value of number of message. */
	} eWARFIELD_PROC_MSG;				/**< CWarfieldMgr::eWARFIELD_PROC_MSG. */
	//> LTH-031222-KO

protected:
	HRESULT CreateWarfield(INT wWarfieldId);

public:
	virtual HRESULT ExecMsg(CWarfieldMgr::eWARFIELD_PROC_MSG eWarfieldProcMsg, LPVOID lpVoid = NULL);

public:
	CWarfieldMgr() : m_lpWarfield(NULL) {}
	virtual ~CWarfieldMgr() { SAFE_DELETE(m_lpWarfield); }

protected:
	LPWARFIELDDEFINE	m_lpWarfield;	/**< Warfield class Interface. */
};	//> LTH-031219-KO