#pragma once

#include "IWarfieldDefine.h"
#include "../LogManager.h"

int const LIMITNATIONPOINT	=	30;	/**< LTH-040412-KO 몬스터 국가전 참가 가능 포인트. */

extern WORD g_wMapServerPort;

/**
 * @def		enum _eSQUAD.
 * @brief	각 부대를 식별하기 위한 식별자.
 */
//< LTH-040414-KO.
typedef enum _eSQUAD
{
	NO_SQUAD = 0,
	SQUAD1 = 1,
	SQUAD2 = 2,
	SQUAD3 = 3,
	SQUAD4 = 4,
	MAX_SQUAD = 5,
} eSQUAD;
//> LTH-040414-KO.

/**
 * @class	CWarfieldInfo.
 * @brief	전쟁 관련 각종 설정을 저장 및 처리 하는 class.
 */
//< LTH-040414-KO.
typedef class CWarfieldInfo  
{
protected:
	VOID LoadSoldierInfo(INT nWarfieldNo);
	VOID LoadMapMoveInfo(INT nWarfieldNo);
	void LoadYlseWarfieldMoveMoney();
	void LoadUserGoOutsideInfo();

public:
	CWarfieldInfo() : m_btHowManyTimesWeek(0) {}
	virtual ~CWarfieldInfo() { Release(); }
	
public:
	VOID Init(INT nNumOfWarfield);
	VOID Release();
	VOID LoadWarTimeInfo(INT nWarfieldNo);
	INT GetThisWarIndex(INT nWarfieldNo, DWORD dwCurrTime);

	/**
	 * @fn		CWarfieldInfo::GetHowManyTimesWeek().
	 * @brief	해당 한 주에 몇번 열리는 지 얻어오는 함수.
	 * @return	BYTE.
	 * @Warning	현재 하나의 전쟁터만 다루기때문에 m_btHowManyTimesWeek 멤버 변수가 배열이 아니지만
	 *			또다른 Type의 전쟁터가 생긴다면 반드시 변경되어야하는 변수와 함수이당... -_-;.
	 */
	//< LTH-040419-KO.
	BYTE GetHowManyTimesWeek() { return m_btHowManyTimesWeek; }
	//> LTH-040419-KO.

	/**
	 * @fn		CWarfieldInfo::GetWarTimeInfo().
	 * @brief	전쟁 시간 설정을 얻어오는 함수.
	 * @param	INT nWarfieldNo. 전쟁터 번호.
	 * @param	BYTE btIndex. 해당 전쟁의 몇번째 전쟁인가 일주일에도 몇번 일어날 수 있으므로.
	 * @return	CWarTimeInfo. 통째로 반환.
	 */
	//< LTH-040419-KO.
	CWarTimeInfo GetWarTimeInfo(INT nWarfieldNo, BYTE btIndex) { return m_atagWarTimeInfo[nWarfieldNo][btIndex]; }
	//> LTH-040419-KO.

	/**
	 * @fn		GetSoldierSet().
	 * @brief	전쟁터 부대 설정을 얻어오는 함수.
	 * @param	INT nWarfieldNo. 전쟁터 번호.
	 * @return	CSoldierSet. 통째로 반환.
	 */
	//< LTH-040419-KO.
	CSoldierSet GetSoldierSet(INT nWarfieldNo) { return m_acSoldierSet[nWarfieldNo]; }
	//> LTH-040419-KO.

	/**
	 * @fn		GetMapSetting().
	 * @brief	전쟁터 맵의 제한사항 설정을 얻어오는 함수.
	 * @param	INT nWarfieldNo. 전쟁터 번호.
	 * @return	CMapSetting. 통째로 반환.
	 */
	//< LTH-040419-KO.
	CMapSetting GetMapSetting(INT nWarfieldNo) { return m_acMapSetting[nWarfieldNo]; }
	//> LTH-040419-KO.
	
	/**
	 * @fn		CWarfieldInfo::GetYlseWarfieldMoveMoney().
	 * @brief	일스국가 유저의 평화 기간 전쟁터 이동 요금 반환.
	 * @return	DWORD.
	 */
	//< LTH-040429-KO.
	DWORD GetYlseWarfieldMoveMoney() { return m_dwYlWarfieldMoveMoney; }
	//> LTH-040429-KO.

	/**
	 * @fn		CWarfieldInfo::GetGoOutsideBBSTime().
	 * @brief	투표 기간에 전쟁터의 유저 방출 공지 간격.
	 * @return	int. 유저 방출 공지 간격.
	 */
	//< LTH-040507-KO.
	int CWarfieldInfo::GetGoOutsideBBSTime() { return m_nGoOutsideBBSTime; }
	//> LTH-040507-KO

	/**
	 * @fn		CWarfieldInfo::GetNumOfGoOutsideUser().
	 * @brief	전쟁터에서 한번에 방출할 유저의 수.
	 * @return	int.
	 */
	//< LTH-040507-KO.
	int CWarfieldInfo::GetNumOfGoOutsideUser() { return m_nNumOfGoOutsideUser; }
	//> LTH-040507-KO.
	
protected:
	INT m_nNumOfWarfield;								/**< 전쟁터의 총 개수. */
	BYTE m_btHowManyTimesWeek;							/**< 한 주에 몇번 열리는지. */
	CWarTimeInfo* m_atagWarTimeInfo[5];	/**< 전쟁 시간 설정. */
	CSoldierSet	m_acSoldierSet[5];		/**< 전쟁터 부대 설정. */
	CMapSetting	m_acMapSetting[5];		/**< 전쟁터 맵 설정. */
	DWORD m_dwYlWarfieldMoveMoney;						/**< LTH-040429-KO 일스 유저의 평화간 전쟁터 이동 요금. */
	int m_nGoOutsideBBSTime;							/**< LTH-040507-KO 투표기간 전쟁터 유저 방출 공지 표시 간격. */
	int m_nNumOfGoOutsideUser;							/**< LTH-040507-KO 한번에 전쟁터에서 방출시킬 유저의 수. */
} *LPWARFIELDINFO;	/**< CWarfieldInfo class의 Pointer형 정의. */
//> LTH-040414-KO.
