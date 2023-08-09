/**
 * @file	WarfieldInfo.cpp.
 *			implementation of the CWarfieldInfo class.
 */
//#include "..\stdafx.h"
#include "../../StdAfx.h"	// 컴파일 시간이 20여분 걸려서, 최적화 작업

#include "WarfieldInfo.h"
#include "../LogManager.h"


/**
 * @fn		CWarfieldInfo::LoadSoldierInfo().
 * @brief	전쟁터 부대정보를 MapServerConfig.ini 파일에서 읽어와 세팅.
 * @param	INT nWarfieldNo. 전쟁터 번호.
 * @return	VOID.
 */
VOID CWarfieldInfo::LoadSoldierInfo(INT nWarfieldNo)
{
	char szTemp[MAX_PATH];
	sprintf(szTemp, "WarfieldNo%dSoldierInfo", nWarfieldNo);
	m_acSoldierSet[nWarfieldNo].m_tagCommander.nLevelMin = ::GetPrivateProfileIntA(szTemp, "CommanderLevelMin", \
		70, MapServerConfigFileName);
	m_acSoldierSet[nWarfieldNo].m_tagCommander.nLadderMin = ::GetPrivateProfileIntA(szTemp, "CommanderLadderMin", \
		2000, MapServerConfigFileName);
	m_acSoldierSet[nWarfieldNo].m_tagCommander.nFameMin = ::GetPrivateProfileIntA(szTemp, "CommanderFameMin", \
		1200, MapServerConfigFileName);

	INT nI;
	INT nIEnd = m_acSoldierSet[nWarfieldNo].m_nNumOfSquad;
	char szTemp2[MAX_PATH];
	for (nI = 0; nI < nIEnd; ++nI)
	{
		sprintf(szTemp2, "Squad%dLeaderLevelMin", nI + 1);
		m_acSoldierSet[nWarfieldNo].m_tagaSquad[nI].nLeaderLevelMin = ::GetPrivateProfileIntA(szTemp, szTemp2, 0, MapServerConfigFileName);
		sprintf(szTemp2, "Squad%dLeaderLadderMin", nI + 1);
		m_acSoldierSet[nWarfieldNo].m_tagaSquad[nI].nLeaderLadderMin = ::GetPrivateProfileIntA(szTemp, szTemp2, 0, MapServerConfigFileName);
		sprintf(szTemp2, "Squad%dLevelMin", nI + 1);
		m_acSoldierSet[nWarfieldNo].m_tagaSquad[nI].nLevelMin = ::GetPrivateProfileIntA(szTemp, szTemp2, 0, MapServerConfigFileName);
		sprintf(szTemp2, "Squad%dLevelMax", nI + 1);
		m_acSoldierSet[nWarfieldNo].m_tagaSquad[nI].nLevelMax = ::GetPrivateProfileIntA(szTemp, szTemp2, 0, MapServerConfigFileName);
		sprintf(szTemp2, "Squad%dMinJoin", nI + 1);
		m_acSoldierSet[nWarfieldNo].m_tagaSquad[nI].nPersonMin = ::GetPrivateProfileIntA(szTemp, szTemp2, 0, MapServerConfigFileName);
		sprintf(szTemp2, "Squad%dMaxJoin", nI + 1);
		m_acSoldierSet[nWarfieldNo].m_tagaSquad[nI].nPersonMax = ::GetPrivateProfileIntA(szTemp, szTemp2, 0, MapServerConfigFileName);
		sprintf(szTemp2, "Squad%dStartingPointX", nI + 1);
		m_acSoldierSet[nWarfieldNo].m_tagaSquad[nI].xyStartingPoint.x = ::GetPrivateProfileIntA(szTemp, szTemp2, 0, MapServerConfigFileName);
		sprintf(szTemp2, "Squad%dStartingPointY", nI + 1);
		m_acSoldierSet[nWarfieldNo].m_tagaSquad[nI].xyStartingPoint.y = ::GetPrivateProfileIntA(szTemp, szTemp2, 0, MapServerConfigFileName);
	}
}	

/**
 * @fn		CWarfieldInfo::LoadMapMoveInfo().
 * @brief	전쟁터 이동정보 MapServerConfig.ini 파일에서 읽어와 세팅.
 * @param	INT nWarfieldNo. 전쟁터 번호.
 * @return	VOID.
 */
VOID CWarfieldInfo::LoadMapMoveInfo(INT nWarfieldNo)
{
	char szTemp[MAX_PATH];
	sprintf(szTemp, "WarfieldNo%dMapMove", nWarfieldNo);
	m_acMapSetting[nWarfieldNo].m_nMoveLevelMin = ::GetPrivateProfileIntA(szTemp, "LevelMin", 0, MapServerConfigFileName);
	m_acMapSetting[nWarfieldNo].m_nMoveLevelMax = ::GetPrivateProfileIntA(szTemp, "LevelMax", 0, MapServerConfigFileName);
	m_acMapSetting[nWarfieldNo].m_nUserEntranceLimitTime = ::GetPrivateProfileIntA(szTemp, "UserEntranceLimitTime", 1800, MapServerConfigFileName);	// LTH-040510-KO 유저 전쟁터 이동 제한 시간 읽어오기
}	

//extern HDBC hDBC;

/**
 * @fn		CWarfieldInfo::LoadWarTimeInfo().
 * @brief	전쟁 시간정보 MapServerConfig.ini 파일에서 읽어와 세팅.
 * @param	INT nWarfieldNo. 전쟁터 번호.
 * @return	VOID.
 */
VOID CWarfieldInfo::LoadWarTimeInfo(INT nWarfieldNo)
{
	HSTMT	hStmt=NULL;
	RETCODE	ret;
	char	query_stmt[80] = {0,};
	SDWORD	cbValue;

	// 일주일 간 해당 type의 전쟁이 일어나는 횟수 읽어오기.
	SQLAllocStmt(hDBC, &hStmt);

	wsprintfA(query_stmt,"select count(*) as NumDayHour from WarStartupTBL where Type=3");   

	ret = SQLExecDirectA(hStmt, (UCHAR*)query_stmt, SQL_NTS);
 
	if (ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS)
	{
		::MyLog(LOG_FATAL, "CWarfieldInfo::LoadWarTimeInfo(), WarField Table Query Error!!");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}

	ret = SQLFetch(hStmt);
	if (ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS)
	{
		::MyLog(LOG_FATAL,"CWarfieldInfo::LoadWarTimeInfo(), WarField Table Fetch Error!!");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}

	ret = SQLGetData(hStmt, 1, SQL_C_SLONG, &m_btHowManyTimesWeek, sizeof(INT), &cbValue);
	if (ret != SQL_SUCCESS_WITH_INFO && ret!=SQL_SUCCESS)
	{
		::MyLog(LOG_FATAL,"CWarfieldInfo::LoadWarTimeInfo(), Warfield Table SQL Return Error(%d)!!",ret);
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}

	SQLFreeStmt(hStmt,SQL_DROP);

	m_atagWarTimeInfo[nWarfieldNo] = new CWarTimeInfo[m_btHowManyTimesWeek];

	// 일주일간 일어나는 전쟁의 시간을 전쟁터에 따라 로딩.
	SQLAllocStmt(hDBC, &hStmt);

	wsprintfA(query_stmt,"select * from WarStartupTBL where Type=3 ORDER BY DayofWeek, DHour");   

	ret = SQLExecDirectA(hStmt, (UCHAR*)query_stmt, SQL_NTS);
 
	if (ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS)
	{
		::MyLog(LOG_FATAL, "CWarfieldInfo::LoadWarTimeInfo(), WarField Table Query Error!!");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}

	ret = SQLFetch(hStmt);
	if (ret != SQL_SUCCESS_WITH_INFO && ret != SQL_SUCCESS)
	{
		::MyLog(LOG_FATAL,"CWarfieldInfo::LoadWarTimeInfo(), WarField Table Fetch Error!!");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}

	::MyLog(LOG_NORMAL, "<!-- HADES WARFIELD WAR Startup Information -->");

	INT nIndex = 0, index = 0;
	char szTemp[MAX_PATH];
	sprintf(szTemp, "WarfieldNo%dLoopTimeInfo", nWarfieldNo);
	
	DWORD dwPrepareTime = 0;
	DWORD dwWarTime = (DWORD)::GetPrivateProfileIntA(szTemp, "WarTime", 0, MapServerConfigFileName);
	DWORD dwSecretAreaOpenTime = (DWORD)::GetPrivateProfileIntA(szTemp, "SecurityAreaOpenTime", 0, MapServerConfigFileName);

	while (ret == SQL_SUCCESS)
	{
		ret=SQLGetData(hStmt, 1, SQL_C_SLONG, &nIndex, 0, &cbValue);
		ret=SQLGetData(hStmt, 3, SQL_C_SLONG, &m_atagWarTimeInfo[nWarfieldNo][index].m_btStartDay, sizeof(INT), &cbValue);
		ret=SQLGetData(hStmt, 4, SQL_C_SLONG, &m_atagWarTimeInfo[nWarfieldNo][index].m_btStartHour, sizeof(INT), &cbValue);
		if (ret!=SQL_SUCCESS_WITH_INFO && ret!=SQL_SUCCESS)
		{
			::MyLog(0,"CWarfieldInfo::LoadWarTimeInfo(), Warfield Table SQL Return Error(%d)!!",ret);
			SQLFreeStmt(hStmt,SQL_DROP);
			return;
		}

		if (m_atagWarTimeInfo[nWarfieldNo][index].m_btStartDay < 0 || \
			m_atagWarTimeInfo[nWarfieldNo][index].m_btStartDay > 6)
		{
			::JustMsg("Failed Day Setting (CWarfieldInfo::LoadWarTimeInfo() DB)");
			return;
		}

		if (m_atagWarTimeInfo[nWarfieldNo][index].m_btStartHour < 0 || \
			m_atagWarTimeInfo[nWarfieldNo][index].m_btStartHour > 23)
		{
			::JustMsg("Failed Time Setting (CWarfieldInfo::LoadWarTimeInfo() DB)");
			return;
		}

		m_atagWarTimeInfo[nWarfieldNo][index].m_dwPrepareTime = dwPrepareTime;
		m_atagWarTimeInfo[nWarfieldNo][index].m_dwWarTime = dwWarTime;
		m_atagWarTimeInfo[nWarfieldNo][index].m_dwSecretAreaOpenTime = dwSecretAreaOpenTime;

		//< 전쟁 끝나는 시간 계산
		DWORD dwWarEndTime = (m_atagWarTimeInfo[nWarfieldNo][index].m_btStartDay * 24 + \
			m_atagWarTimeInfo[nWarfieldNo][index].m_btStartHour + (dwWarTime / 3600));
		//> 

		::MyLog(LOG_NORMAL, "[%d]%s(%02d:%02d - %02d:%02d)", 
			  nIndex,
			  (CLogManager::Pointer())->ConvertToDay(m_atagWarTimeInfo[nWarfieldNo][index].m_btStartDay),
			  m_atagWarTimeInfo[nWarfieldNo][index].m_btStartHour, 
			  0, 
			  dwWarEndTime % 24, 
			  0);

		++index;
		ret = SQLFetch(hStmt);
	}

    SQLFreeStmt(hStmt,SQL_DROP);
}	

/**
 * @fn		CWarfieldInfo::Init().
 * @brief	전쟁터 초기정보를 MapServerConfig.ini 파일에서 읽어와 세팅.
 * @param	INT nNumOfWarfield. 최대 전쟁터맵의 개수.
 * @return	VOID.
 */
VOID CWarfieldInfo::Init(INT nNumOfWarfield)
{
	::GetPrivateProfileStringA("network", "path", "", NetworkDir, MAX_PATH, MAP_SERVER_INI_);
	sprintf(MapServerConfigFileName,"%s/data/MapServerConfig.ini",NetworkDir);

	m_nNumOfWarfield = nNumOfWarfield;

	INT nI;
	for (nI = 0; nI < m_nNumOfWarfield; ++nI)
	{
		switch(nI)
		{
		case WI_HADES_WARFIELD:
			{
				m_acSoldierSet[nI].m_nNumOfSquad = MAX_SQUAD;
				LoadSoldierInfo(nI);
				LoadMapMoveInfo(nI);
			}
			break;
		}
	}
	
	LoadYlseWarfieldMoveMoney();	// 일스의 평화기간 전쟁터 이동 요금 읽어오기
	LoadUserGoOutsideInfo();		// 유저 전쟁터 방출에 관한 정보 로딩
}

/**
 * @fn		CWarfieldInfo::Release().
 * @brief	전쟁터 정보를 안전하게 제거.
 * @return	VOID.
 */
VOID CWarfieldInfo::Release()
{
	INT nI;
	for (nI = 0; nI > m_nNumOfWarfield; ++nI)
	{
		SAFE_DELETE_ARRAY(m_atagWarTimeInfo[nI]);
	}
}

/**
 * @fn		CWarfieldInfo::GetThisWarIndex().
 * @brief	현재 진행되는 전쟁의 index가 몬지 알아 보는 함수.
 * @param	INT nWarfieldNo. 전쟁터번호.
 * @param	DWORD dwCurrTime. 현재 시간.
 * @return	INT. 현재 진행되는 전쟁의 index.
 */
INT CWarfieldInfo::GetThisWarIndex(INT nWarfieldNo, DWORD dwCurrTime)
{
	DWORD dwStartUpTime1 = 0;
	DWORD dwStartUpTime2 = 0;
	INT nI;
	if (m_btHowManyTimesWeek != 1)
	{
		for (nI = 0; nI < m_btHowManyTimesWeek - 1; ++nI)
		{
			dwStartUpTime1 = (m_atagWarTimeInfo[nWarfieldNo][nI].m_btStartDay * 86400) + \
				(m_atagWarTimeInfo[nWarfieldNo][nI].m_btStartHour * 3600);
			dwStartUpTime2 = (m_atagWarTimeInfo[nWarfieldNo][nI + 1].m_btStartDay * 86400) + \
				(m_atagWarTimeInfo[nWarfieldNo][nI + 1].m_btStartHour * 3600);

			if ((dwStartUpTime1 <= dwCurrTime) && (dwStartUpTime2 > dwCurrTime))
				break;
		}
	}
	else
		nI = 0;

	return nI;
} 

/**
 * @fn		CWarfieldInfo::LoadYlseWarfieldMoveMoney().
 * @brief	일스국가 유저의 평화 기간 전쟁터 이동 요금 읽어오기.
 * @return	void.
 */
void CWarfieldInfo::LoadYlseWarfieldMoveMoney()
{
	m_dwYlWarfieldMoveMoney = ::GetPrivateProfileIntA("WarfieldMapMove", "YlseWarfieldMoveMoney", 5000000, MapServerConfigFileName);
}	

/**
 * @fn		CWarfieldInfo::LoadUserGoOutsideInfo().
 * @brief	전쟁터에서의 유저 방출 정보 읽어오기.
 * @return	void.
 */
void CWarfieldInfo::LoadUserGoOutsideInfo()
{
	m_nGoOutsideBBSTime = ::GetPrivateProfileIntA("WarfieldMapMove", "UserGoOutsideBBSTime", 60, MapServerConfigFileName);
	m_nNumOfGoOutsideUser = ::GetPrivateProfileIntA("WarfieldMapMove", "UserGoOutsideOneTimePersonnel", 20, MapServerConfigFileName);
}