#pragma once

#include "IWarfieldDefine.h"

/**
 * @class	CWarfieldMgr.
 * @brief	���� ������ ����� �ܺ����.
 *			�ʼ����� ���� ������ ����� �ܺηκ��� �ϳ��� ��θ� �����ϴ� Ŭ����.
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
		WPM_SET_REMAINTIME = 4,			/**< ���� state�� ���� �ð��� �����Ѵ�. */
		WPM_GET_REMAINTIME = 5,			/**< ���� state�� ���� �ð��� ��ȯ�Ѵ�. */
		WPM_UPDATE = 6,					/**< Warfield MapServer Update routine. */
		WPM_GET_SQUAD_MEMBER_COUNT = 7,	/**< �δ� �ο����� ��ȯ�Ѵ�. */
		WPM_CAN_ATTACK_GUARD = 8,		/**< ��ȣ���̳� ������ ������ ���ִ´���ΰ� ��ȯ. */
		WPM_INSERT_SQUAD_MEMBER = 9,	/**< ������ �δ� ����� �����Ѵ�. */
		WPM_DELETE_SQUAD_MEMBER = 10,	/**< ������ �δ� ������� �����Ѵ�. */
		WPM_GET_WARFIELDDATA = 11,		/**< Guard��(����, ��ȣ����)�� ���� �� Team ������ ��ȯ. */
		WPM_GET_TEAM_MEMBER_COUNT = 12,	/**< �� �������� ���� ���ڸ� ����. */
		WPM_SEND_SQUAD_CHAT = 13,		/**< �δ� ä�� ����. */
		WPM_GET_LIVE_POINT = 14,		/**< ��Ȱ ��ġ ��ȯ. */
		WPM_GET_DONT_DATA = 15,			/**< Dont Tile Data ��ȯ. */
		WPM_CHECK_AND_KICK_USER = 16,	/**< ������ üũ�Ͽ� �й� �ߴٸ� ������ ����������. */
		WPM_SET_LOOPTIME_CHANGE = 17,	/**< ���� ������ ���ӽð��� �缳���Ѵ�. */
		WPM_UPDATE_GUARD_STATUS = 18,	/**< ��ȣ���̳� ������ ���� ���¸� �����Ѵ�. */
		WPM_INC_DEATH_MEMBER = 19,		/**< ������ ���� �ο��� ���� ��Ų��. */
		WPM_CHECK_JOIN_NATION = 20,		/**< �������� ������ ���� ���� üũ. */
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