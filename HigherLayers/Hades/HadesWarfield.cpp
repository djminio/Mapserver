/**
 * @file	HadesWarfield.cpp
 *			implementation of the CHadesWarfield class.
 */
//#include "..\stdafx.h"
#include "stdafx.h"	//060109_kch 컴파일 시간이 20여분 걸려서, 최적화 작업

#include "HadesWarfield.h"
#include "HWStateFactory.h"
#include "WarfieldInfo.h"

//#include "DefaultHeader.h"
#include "UserManager.h"
#include "LogManager.h"

extern LPWARFIELDINFO g_pcWarfieldInfo;

//< LTH-040318-KO 남은 가드(성문/결계석) 수를 체크하여 보낸다
void SendCMD_CHECK_REMAIN_GUARD(int nWarfieldNo, DWORD dwRemainTime, int aRemainGuard[MAX_TEAM][GS_MAX_GUARD_SPECIES])
{
	t_packet packet;
	packet.h.header.type = CMD_CHECK_REMAIN_GUARD;
	packet.u.NationWar.RemainGuard.nWarfieldNo = nWarfieldNo;
	packet.u.NationWar.RemainGuard.dwRemainTime = dwRemainTime;
	int nJ, nI;
	for (nJ = 0; nJ < MAX_TEAM; ++nJ)
	{
		for (nI = 0; nI < GS_MAX_GUARD_SPECIES; ++nI)
		{
			packet.u.NationWar.RemainGuard.aRemainGuardCount[nJ][nI] = aRemainGuard[nJ][nI];
		}
	}
	packet.h.header.size = sizeof(REMAIN_GUARD);
	g_pUserManager->SendPacket(&packet);
}
//> LTH-040318-KO

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHadesWarfield::CHadesWarfield()
: m_nWarfieldNo(-1)
, m_lpGuard(NULL)
, m_lpTeam(NULL)
, m_bIsVictory(FALSE)
, m_nNumOfTeam(0)
, m_lpWarfieldState(NULL)
{
	m_nWarfieldState = NW_PEACE;
	
	LPFACTORYDEFINE lpStateFactory = NULL;
	lpStateFactory = new CHWStateFactory;
	if (FAILED(lpStateFactory->Create(m_nWarfieldState, (LPVOID*)&m_lpWarfieldState)))
	{
		::MyLog(LOG_FATAL, "CHadesWarfield::SetStatus() lpStateFactory->Create() 실패");
		return;
	}
	SAFE_DELETE(lpStateFactory);

	int nI;
	for (nI = 0; nI < NW_NATION_COUNT; ++nI)
	{
		m_bJoinNation[nI] = FALSE;
		m_aSumNationPoint[nI] = 0;
	}
}

CHadesWarfield::~CHadesWarfield()
{
	SAFE_DELETE_ARRAY(m_lpGuard);
	SAFE_DELETE_ARRAY(m_lpTeam);
	SAFE_DELETE(m_lpWarfieldState);
}

STDMETHODIMP CHadesWarfield::Init(INT nWarfieldNo)
{
	m_nWarfieldNo = nWarfieldNo;
	g_pcWarfieldInfo->LoadWarTimeInfo(m_nWarfieldNo);

	SAFE_DELETE(m_lpWarfieldState);
	LPFACTORYDEFINE lpStateFactory = NULL;
	lpStateFactory = new CHWStateFactory;
	if (FAILED(lpStateFactory->Create(m_nWarfieldState, (LPVOID*)&m_lpWarfieldState)))
	{
		::MyLog(LOG_FATAL, "CHadesWarfield::SetStatus() lpStateFactory->Create() 실패");
		return E_FAIL;
	}
	SAFE_DELETE(lpStateFactory);
	
	SAFE_DELETE_ARRAY(m_lpGuard);
	SAFE_DELETE_ARRAY(m_lpTeam);

	m_nNumOfTeam = MAX_TEAM;
	m_lpTeam = new CTeamInfo[m_nNumOfTeam];
	m_lpGuard = new CGuardInfo[m_nNumOfTeam];

	m_lpTeam[TEAM1].SetTeamNo(TEAM1);
	m_lpTeam[TEAM2].SetTeamNo(TEAM2);
	m_lpGuard[TEAM1].SetWarfieldNo(m_nWarfieldNo);
	m_lpGuard[TEAM1].SetTeamNo(TEAM1);
	m_lpGuard[TEAM2].SetWarfieldNo(m_nWarfieldNo);
	m_lpGuard[TEAM2].SetTeamNo(TEAM2);
	m_lpGuard[TEAM2].LoadData();

	// TEAM1은 유저팀, TEAM2는 몬스터팀이다. 다른 전쟁터와 같이 구분 짓기위해 만들었을 뿐이다
	// 지하전쟁터의 아군은 부대가 4개이다 0번 부대는 부대가 없는 일반인이라는 기존 소스와 동일하게...
	if (FAILED(m_lpTeam[TEAM1].Init(NW_SQUAD_MAX)))
	{
		::MyLog(LOG_FATAL, "CHadesWarfield::Init()의 m_lpTeam[TEAM1].Init() 실행 실패");
		return E_FAIL;
	}
	m_lpTeam[TEAM2].Init(1);				// LTH-040212-KO 지하전쟁터의 유저팀은 하나이다. Error를 피하기 위해 빈부대 하나를 넣는다
	m_lpGuard[TEAM2].FirstMakeNPCPtr();		// LTH-040212-KO 수호석은 몬스터 팀만 가지고있다

	SetStatus(NW_PEACE);

	if (FALSE == LoadWarfieldData())
	{
		::MyLog(LOG_FATAL, "CHadesWarfield::Init()의 LoadWarfieldData() 실행 실패");
		return E_FAIL;
	}
	
	return S_OK;
}

STDMETHODIMP_(INT) CHadesWarfield::GetStatus()
{
	return m_nWarfieldState;
}

extern INT g_naWarfieldState[WI_MAX_WARFIELD];
extern void SendNewWarEnd(INT nWarfieldNo);

STDMETHODIMP_(VOID) CHadesWarfield::SetStatus(INT nState)
{
	m_nWarfieldState = nState;
	
	SAFE_DELETE(m_lpWarfieldState);
	LPFACTORYDEFINE lpStateFactory = NULL;
	lpStateFactory = new CHWStateFactory;
	if (FAILED(lpStateFactory->Create(m_nWarfieldState, (LPVOID*)&m_lpWarfieldState)))
	{
		::MyLog(LOG_FATAL, "CHadesWarfield::SetStatus() lpStateFactory->Create() 실패");
		return;
	}
	SAFE_DELETE(lpStateFactory);

	m_lpWarfieldState->Init(m_nWarfieldNo);

	INT nI;
	switch(m_nWarfieldState)
	{
	case NW_PEACE:
		{
		}
		break;

	case NW_WAR:
		{
			CheckWarStartTeam();
			SendMonsterRaidMsg(TRUE);
			
			for (nI = 0; nI < MAX_TEAM; ++nI)
				m_lpGuard[nI].MakeNPCPtr();

			//< LTH-040318-KO 남은 가드 수를 전쟁 시작 하자마자 보낸다.
			int aRemainGuard[MAX_TEAM][GS_MAX_GUARD_SPECIES];
			int nI, nJ;
			for (nJ = 0; nJ < MAX_TEAM; ++nJ)
			{
				for (nI = 0; nI < GS_MAX_GUARD_SPECIES; ++nI)
				{
					aRemainGuard[nJ][nI] = m_lpGuard[TEAM2].GetAliveGuardCount(nI);
				}
			}
			::SendCMD_CHECK_REMAIN_GUARD(m_nWarfieldNo, m_lpWarfieldState->GetRemainTime(), aRemainGuard);
			KickAllUser2Home();
			//> LTH-040318-KO
		}
		break;
	case NW_SOPEN	: 
		{
			//< LTH-040518-KO 비밀지역 오픈때 남은 시간을 정확히 보내려고 기존에 있던 패킷처리를 함 한다 -_-;.
			int aRemainGuard[MAX_TEAM][GS_MAX_GUARD_SPECIES];
			int nI, nJ;
			for (nJ = 0; nJ < MAX_TEAM; ++nJ)
			{
				for (nI = 0; nI < GS_MAX_GUARD_SPECIES; ++nI)
				{
					aRemainGuard[nJ][nI] = m_lpGuard[TEAM2].GetAliveGuardCount(nI);
				}
			}
			::SendCMD_CHECK_REMAIN_GUARD(m_nWarfieldNo, m_lpWarfieldState->GetRemainTime(), aRemainGuard);
			//> LTH-040518-KO
			::SendNewWarEnd(m_nWarfieldNo);// End Process
			//< LTH-040323-KO 로그 강화
			g_pLogManager->SaveLogNeoNationWar(NNT_STATE_INFO, "Hades War End!!");
			//> LTH-040323-KO
			for (nI = 0; nI < MAX_TEAM; ++nI)
			{
				m_lpTeam[nI].RemoveArmor();
			}
		}
		break;
	}

	t_packet packet; 
	packet.h.header.type = CMD_NWARFIELD_STATUS_CHANGE;
	packet.u.NationWar.WarfieldStatusChange.WarfieldNo = m_nWarfieldNo;
	packet.u.NationWar.WarfieldStatusChange.Status = m_nWarfieldState;
	packet.h.header.size = sizeof(t_WarfieldStatusChange) ;
	g_naWarfieldState[m_nWarfieldNo] = m_nWarfieldState;
	SendPacket2Maps(&packet);
}

STDMETHODIMP_(VOID) CHadesWarfield::SetRemainTime(__int64 dwRemainTime)
{
	m_lpWarfieldState->SetRemainTime(dwRemainTime);
}

STDMETHODIMP_(__int64) CHadesWarfield::GetRemainTime()
{
	return m_lpWarfieldState->GetRemainTime();
}

STDMETHODIMP CHadesWarfield::Update()
{
	if (NULL == m_lpWarfieldState)
		return E_FAIL;
	
	if (FAILED(m_lpWarfieldState->Update()))
	{
		switch(m_nWarfieldState)
		{
		case NW_PEACE:
			break;

		case NW_WAR:
			{	//< LTH-040314-KO 이곳은 시간이 다되어 유저가 패했을 경우다
				SendMonsterRaidMsg(FALSE);
				CheckWinTeam();
				if (FALSE == m_bIsVictory)
				{
					m_lpTeam[TEAM1].GiveFame2Dual(2);

					//+[YonMy;map1; 20070625 : 유저가 패배했다는 로그를 남겨준다]+
					g_pLogManager->SaveLogNeoNationWar(NNT_WAR_INFO, "[Monster War Result] User Lost!!");
				}

				SendWarResult();

				//< LTH-040226-KO 한 타임 전쟁이 끝난후에 전쟁 참여 가능 국가를 초기화
				UpdateNationPoint(m_aSumNationPoint);
				INT nI;
				for (nI = 0; nI < NW_NATION_COUNT; ++nI)
					m_bJoinNation[nI] = FALSE;
				//> LTH-040226-KO

				SetStatus(NW_SOPEN);
			}	//> LTH-040314-KO
			break;

		case NW_SOPEN:
			{
				KickAllUser2Home();
				SetStatus(NW_PEACE);
			}
			break;
		}
	}
	else
	{
		switch(m_nWarfieldState)
		{
		case NW_WAR:
			if (TRUE == m_lpGuard[TEAM2].IsAllBroken())
			{	//< LTH-040314-KO 이곳은 유저가 승리했을 경우다
				SendMonsterRaidMsg(FALSE);
				m_bIsVictory = TRUE;
				m_lpTeam[TEAM1].GiveFame2Dual(4);

				//+[YonMy;map1; 20070621 : 유저가 승리했다는 로그를 남겨준다]+
				g_pLogManager->SaveLogNeoNationWar(NNT_WAR_INFO, "[Monster War Result] User Win!!");
				
				SendWarResult();
				
				//< LTH-040226-KO 한 타임 전쟁이 끝난후에 전쟁 참여 가능 국가를 초기화
				UpdateNationPoint(m_aSumNationPoint);
				INT nI;
				for (nI = 0; nI < NW_NATION_COUNT; ++nI)
					m_bJoinNation[nI] = FALSE;
				//> LTH-040226-KO

				SetStatus(NW_SOPEN);
			}	//> LTH-040314-KO
			break;
		}
	}

	return S_OK;
}

STDMETHODIMP_(INT) CHadesWarfield::GetSquadMemberCount(INT nSquadNo)
{
	//< LTH-040304-KO 팀이 늘어나면 함수 인자에 팀도 받아야한다
	// 1.4 패치의 신규국가전에 국한되어있다
	return m_lpTeam[TEAM1].GetSquadMemberCount(nSquadNo);
	//> LTH-040304-KO
}

BOOL CHadesWarfield::LoadWarfieldData()
{
	CSoldierSet cSoldier = g_pcWarfieldInfo->GetSoldierSet(m_nWarfieldNo);
	INT nI;
	for (nI = 0; nI < MAX_SQUAD; ++nI)
		m_lpTeam[TEAM1].SetLivePoint(nI, cSoldier.m_tagaSquad[nI].xyStartingPoint);

	return TRUE;
}

STDMETHODIMP_(BOOL) CHadesWarfield::CanAttackGuard(LPCHARLIST lpCaster, LPCHARLIST lpTarget)
{
	INT nCasterTeamNo = GetTeamNo(lpCaster); 
	INT nTargetTeamNo = 0;
	if (m_lpGuard[TEAM2].CheckNPC(lpTarget->GetServerID())) 
		nTargetTeamNo = TEAM2;

	if (nCasterTeamNo == nTargetTeamNo)		// 같은 팀이다.. 
		return FALSE;

	BOOL bIsBroken = FALSE;
	switch (lpTarget->SprNo)
	{
	case 64:	// 최종 수호석
		bIsBroken = (BOOL)m_lpGuard[nTargetTeamNo].CheckTypeAllBroke(GS_INNER_GUARD_STONE);
		if (FALSE == bIsBroken)
			m_lpGuard[nTargetTeamNo].SendCanNotBrokeBBS(GS_INNER_GUARD_STONE);
		return bIsBroken;

	case 63:	// 내성 수호석. 성문 다 부셔야 부실수 있도록 해야한다
		bIsBroken = (BOOL)m_lpGuard[nTargetTeamNo].CheckTypeAllBroke(GS_GATE);
		if (FALSE == bIsBroken)
			m_lpGuard[nTargetTeamNo].SendCanNotBrokeBBS(GS_GATE);
		return bIsBroken;
	
	case 177:	// 성문
		bIsBroken = (BOOL)m_lpGuard[nTargetTeamNo].CheckTypeAllBroke(GS_OUTER_GUARD_STONE);
		if (FALSE == bIsBroken)
			m_lpGuard[nTargetTeamNo].SendCanNotBrokeBBS(GS_OUTER_GUARD_STONE);
		return bIsBroken;
		
	case 178:	// 외성 수호석.
		return TRUE;
	}

	::MyLog(LOG_FATAL,"CHadesWarfield CanAttackGuard(), illegal SprNo : %d",lpTarget->SprNo);
	return FALSE;
}

INT CHadesWarfield::GetTeamNo(LPCHARLIST lpChar)
{
	switch(lpChar->name_status.nation)
	{
	case NW_BY:
	case NW_ZY:
	case NW_YL:
		return TEAM1;
	}

	//< LTH-040329-KO 로그 강화
	::MyLog(0,"CHadesWarfield GetTeamNo(),illegal Nation : %d, SprNo : %d",lpChar->name_status.nation, lpChar->SprNo);
	//> LTH-040329-KO
	return TEAM2;
}

extern void SendCMD_UPDATE_WARTIME(const int WarfieldNo, const int Status, const DWORD RemainTime);

STDMETHODIMP_(VOID) CHadesWarfield::InsertSquadMember(INT nCn)
{
	//< LTH-040304-KO 1.4 패치에 국한. 유저팀에만 맴버추가가능
	if (NW_WAR == m_nWarfieldState)
	{
		//< LTH-040318-KO 남은 가드 수를 전쟁 참여 하자마자 보낸다.
		int aRemainGuard[MAX_TEAM][GS_MAX_GUARD_SPECIES];
		int nI, nJ;
		for (nJ = 0; nJ < MAX_TEAM; ++nJ)
		{
			for (nI = 0; nI < GS_MAX_GUARD_SPECIES; ++nI)
			{
				aRemainGuard[nJ][nI] = m_lpGuard[TEAM2].GetAliveGuardCount(nI);
			}
		}
		::SendCMD_CHECK_REMAIN_GUARD(m_nWarfieldNo, m_lpWarfieldState->GetRemainTime(), aRemainGuard);
		::SendCMD_UPDATE_WARTIME(m_nWarfieldNo, NW_WAR, m_lpWarfieldState->GetRemainTime());
		//> LTH-040318-KO
		m_lpTeam[TEAM1].InsertSquadMember(m_nWarfieldNo, nCn);
	}
	//> LTH-040304-KO
}

STDMETHODIMP_(VOID) CHadesWarfield::DeleteSquadMember(INT nCn)
{
	//< LTH-040326-KO 1.4 패치에 국한. 유저팀에만 맴버삭제가능. 전쟁중에만 부대 멤버를 제거
	if (NW_WAR == m_nWarfieldState)
		m_lpTeam[TEAM1].DeleteSquadMember(m_nWarfieldNo, nCn);
	//> LTH-040326-KO
}

STDMETHODIMP_(LPGUARDINFO) CHadesWarfield::GetGuardInfo(INT nTeamNo)
{
	//<060327_kch 체크강화
	if (0 > nTeamNo) return NULL;
	if (NULL == m_lpGuard) return NULL; 
	//>060327_kch

	if ((nTeamNo < 0) && (nTeamNo > MAX_TEAM))
		return NULL;

	return &m_lpGuard[nTeamNo];
}

STDMETHODIMP_(LPTEAMINFO) CHadesWarfield::GetTeamInfo(INT nTeamNo)
{
	if ((nTeamNo < 0) && (nTeamNo > MAX_TEAM))
		return NULL;

	return &m_lpTeam[nTeamNo];
}

STDMETHODIMP_(INT) CHadesWarfield::GetTeamMemberCount(INT nTeamNo)
{
	//< LTH-040304-KO 안전을 위해 부대수를 확인한다.
	INT nNumOfSquad = m_lpTeam[nTeamNo].GetNumOfSquad();
	INT nI, nCount = 0;
	for (nI = 0; nI < nNumOfSquad; ++nI)
		nCount += m_lpTeam[nTeamNo].GetSquadMemberCount(nI);
	//> LTH-040304-KO
	
	return nCount;
}

STDMETHODIMP_(VOID) CHadesWarfield::SendSquadChat(LPCHARLIST lpChar, t_packet *p)
{
	INT nTeamNo = GetTeamNo(lpChar);
	m_lpTeam[nTeamNo].SendMessageAllMember(p);
}

STDMETHODIMP_(POINT) CHadesWarfield::GetLivePoint(LPCHARLIST lpChar)
{
	INT nTeamNo = GetTeamNo(lpChar);
	return m_lpTeam[nTeamNo].GetLivePoint(lpChar);
}

STDMETHODIMP_(VOID) CHadesWarfield::GetTileDont(DONT_DATA *lpDontData)
{
	DONT_DATA	TeamData;
	INT nI, nTotalSize, nIndex;

	m_lpGuard[TEAM2].GetTileDont(&TeamData);

	nTotalSize = lpDontData->Size = TeamData.Size;
	
	nIndex = 0;
	for (nI = 0; nI < TeamData.Size; nI++)
	{
		lpDontData->DontNo[nIndex] = TeamData.DontNo[nI];
		lpDontData->Status[nIndex] = TeamData.Status[nI];
		nIndex++;
	}
}

extern int MapMove(int idUser, const char* pMapName, int nX, int nY);

STDMETHODIMP_(VOID) CHadesWarfield::CheckAndKickUser(INT nCn)
{
	LPCHARLIST lpChar = ::CheckServerId(nCn);
	
	if (lpChar == NULL)
	{	
		return; 	
	}
	
	const INT nTeamNo = GetTeamNo(lpChar);
	
	if (FALSE == m_bIsVictory)
	{
		if (TRUE == m_lpTeam[nTeamNo].KickUser(nCn))
		{	//< LTH-040322-KO MoveToVillage()는 초보자를 위한 죽었을때 살리는 함수당 비웅아!!
			switch (connections[nCn].chrlst.name_status.nation)
			{
			case NW_BY:
				::MapMove(nCn,"MA-IN",245,115);
				break;
			case NW_ZY: 
				::MapMove(nCn,"RENES_C",210,175);	
				break;
			case NW_YL: 
				::MapMove(nCn,"BARANTAN",325,98);	
				break;
			}
		}	//> LTH-040322-KO
	}
}

STDMETHODIMP_(VOID) CHadesWarfield::LoopTimeChange(t_packet *p)
{
	m_lpWarfieldState->SetLoopTime(p->u.NationWar.WarLoopTime.LoopTime);
	//< LTH-040323-KO 로그 강화
	g_pLogManager->SaveLogNeoNationWar(NNT_TIME_INFO, "[LoopTime Change] = %d",p->u.NationWar.WarLoopTime.LoopTime);
	//> LTH-040323-KO
}

VOID CHadesWarfield::CheckWinTeam()
{
	m_bIsVictory = m_lpGuard[TEAM2].IsAllBroken();
}

#ifndef SUM_TYPE_NUM
const INT SUM_TYPE_NUM = 99;
#endif

VOID CHadesWarfield::UpdateNationPoint(INT nScore[NW_NATION_COUNT])
{
	HSTMT hStmt = NULL;
	RETCODE retCode;
	char szQuery[256] = {0,};
	
	int nI;
	for (nI = 0; nI < NW_NATION_COUNT; ++nI)
	{
		if (m_bJoinNation[nI] == TRUE)
			nScore[nI] -= LIMITNATIONPOINT;
	}
	
	wsprintfA(szQuery, "EXEC dbo.up_set_nation_rank_point %d, %d, %d, %d", SUM_TYPE_NUM, nScore[0], \
		nScore[1], nScore[2]);

	SQLAllocStmt(g_hDBC_DragonDB, &hStmt);
	
	retCode = SQLExecDirectA(hStmt, (UCHAR*)szQuery, SQL_NTS);
	if(retCode != SQL_SUCCESS && retCode != SQL_SUCCESS_WITH_INFO)
	{
		::MyLog(LOG_FATAL,"UpdateNationPoint, NWarStartUpTBL Table Query Error!!");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}

	SQLFreeStmt(hStmt, SQL_DROP);

	//< LTH-040323-KO 로그 강화
	g_pLogManager->SaveLogNeoNationWar(NNT_WAR_INFO, "After War Nation Sum Point Vy : %d Zy : %d Yl : %d", \
		nScore[0], nScore[1], nScore[2]);
	//> LTH-040323-KO
}

VOID GetSumNationPoint(INT nSumPoint[NW_NATION_COUNT])
{
	HSTMT hStmt = NULL;
	RETCODE retCode;
	SDWORD cbValue;
	char szQuery[256] = {0,};

	wsprintfA(szQuery, "EXEC dbo.up_get_nation_rank_point %d", SUM_TYPE_NUM);

	SQLAllocStmt(g_hDBC_DragonDB, &hStmt);

	retCode = SQLExecDirectA(hStmt, (UCHAR*)szQuery, SQL_NTS);
	if(retCode != SQL_SUCCESS && retCode != SQL_SUCCESS_WITH_INFO)
	{
		::MyLog(LOG_FATAL,"CheckWarStartTeam, WarStartUpTBL Table Query Error!!");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}

	retCode = SQLFetch( hStmt );
	if(retCode != SQL_SUCCESS && retCode != SQL_SUCCESS_WITH_INFO)
	{
		::MyLog(LOG_FATAL,"CheckWarStartTeam, WarStartUpTBL Table Fetch Error!!");
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}

	nSumPoint[0] = nSumPoint[1] = nSumPoint[2] = 0;
	INT nI;
	for (nI = 0; nI < NW_NATION_COUNT; ++nI)
		retCode = SQLGetData(hStmt, nI + 1, SQL_C_ULONG, &nSumPoint[nI], sizeof(INT), &cbValue);

	if(retCode != SQL_SUCCESS && retCode != SQL_SUCCESS_WITH_INFO)
	{
		::MyLog(LOG_FATAL,"GetSumNationPoint, WarStartUpTBL Table SQL Return Error!!(%d)", retCode);
		SQLFreeStmt(hStmt,SQL_DROP);
		return;
	}

	SQLFreeStmt(hStmt, SQL_DROP);
}

VOID CheckWarStartNation(INT nSumPoint[NW_NATION_COUNT], BOOL bJoinNation[NW_NATION_COUNT])
{
	INT nJ;
	for (nJ = 0; nJ < NW_NATION_COUNT; ++nJ)
	{
		// LTH-040224-KO 1.4 Patch. Hades 전쟁 시작 조건
		if (nSumPoint[nJ] >= LIMITNATIONPOINT)
			bJoinNation[nJ] = TRUE;
		else
			bJoinNation[nJ] = FALSE;
	}
}

VOID CHadesWarfield::CheckWarStartTeam()
{
	// DB에서 현재 각 국가의 포인트 합의 배열을 불러온다
	::GetSumNationPoint(m_aSumNationPoint);
	//< LTH-040323-KO 로그 강화
	g_pLogManager->SaveLogNeoNationWar(NNT_WAR_INFO, "Before Nation Sum Point Vy : %d Zy : %d Yl : %d", \
		m_aSumNationPoint[0], m_aSumNationPoint[1], m_aSumNationPoint[2]);
	//> LTH-040323-KO
	// 전쟁 참여 가능 국가를 판별한다
	::CheckWarStartNation(m_aSumNationPoint, m_bJoinNation);

	INT nJ;
	for (nJ = 0; nJ < NW_NATION_COUNT; ++nJ)
	{	//< LTH-040323-KO 로그 강화
		if (TRUE == m_bJoinNation[nJ])
			g_pLogManager->SaveLogNeoNationWar(NNT_WAR_INFO, "%d Nation Join in Monster War (0:Vy, 1:Zy, 2:Yl)", nJ);
	}	//> LTH-040323-KO
}

#include "RegenManager.h"

extern void SendPacket2NationMaps(const int Nation, t_packet* p);
extern void	SendPacket2NationClients(const int Nation,t_packet* p);

VOID CHadesWarfield::SendMonsterRaidMsg(BOOL bIsStart)
{
	t_packet packet;

	if (TRUE == bIsStart)
	{
		packet.h.header.type = CMD_MONSTER_RAID_START;
		g_pRegenManager->Remove(CGroupInfo::ET_NORMAL); // CSD-040324 일반 몬스터 제거
		g_pRegenManager->Ready(CGroupInfo::ET_HADES); // CSD-040324 전쟁이 시작되면 지하전쟁터의 몬스터 그룹이 활성화 된다
		//< LTH-040323-KO 로그 강화
		g_pLogManager->SaveLogNeoNationWar(NNT_WAR_INFO, "<--- Monster Raid Start Infomation --->");
		//> LTH-040323-KO
	}
	else
	{
		packet.h.header.type = CMD_MONSTER_RAID_END;
		g_pRegenManager->Remove(CGroupInfo::ET_HADES); // CSD-040324 전쟁이 끝나면 지하전쟁터의 몬스터 그룹이 제거 된다
		g_pRegenManager->Ready(CGroupInfo::ET_NORMAL); // CSD-040324 일반 몬스터 그룹 활성화
		//< LTH-040323-KO 로그 강화
		g_pLogManager->SaveLogNeoNationWar(NNT_WAR_INFO, "<--- Monster Raid End Infomation --->");
		//> LTH-040323-KO
	}

	packet.h.header.size = 0;

	INT nI;
	for (nI = 0; nI < NW_NATION_COUNT; ++nI)
	{
		if (FALSE == m_bJoinNation[nI])
		{
			switch(nI)
			{
			case 0:
				::SendPacket2NationMaps(NW_BY, &packet);
				::SendPacket2NationClients(NW_BY, &packet);
				break;

			case 1:
				::SendPacket2NationMaps(NW_ZY, &packet);
				::SendPacket2NationClients(NW_ZY, &packet);
				break;

			case 2:
				::SendPacket2NationMaps(NW_YL, &packet);
				::SendPacket2NationClients(NW_YL, &packet);
				break;
			}

			if (TRUE == bIsStart)
			{
				//< LTH-040323-KO 로그 강화
				g_pLogManager->SaveLogNeoNationWar(NNT_WAR_INFO, "%d Nation was raided by Monster!! (0:Vy, 1:Zy, 2:Yl)", nI);
				//> LTH-040323-KO
			}
			else
			{
				//< LTH-040323-KO 로그 강화
				g_pLogManager->SaveLogNeoNationWar(NNT_WAR_INFO, "%d Nation repulsed Monster!! (0:Vy, 1:Zy, 2:Yl)", nI);
				//> LTH-040323-KO
			}
		}
	}
}

VOID CHadesWarfield::SendWarResult()
{
	t_packet packet;

	packet.h.header.type = CMD_WAR_RESULT;
	packet.u.NationWar.NeoWarResult.wWarfieldPort = WP_BASE_PORT + m_nWarfieldNo - 1;
	
	if (TRUE == m_bIsVictory)
		packet.u.NationWar.NeoWarResult.cVictoryTeam = TEAM1;
	else
		packet.u.NationWar.NeoWarResult.cVictoryTeam = TEAM2;

	packet.u.NationWar.NeoWarResult.nBYMemberCount = m_lpTeam[TEAM1].GetNationMemberCount(NW_BY);
	packet.u.NationWar.NeoWarResult.nZYMemberCount = m_lpTeam[TEAM1].GetNationMemberCount(NW_ZY);
	packet.u.NationWar.NeoWarResult.nYLMemberCount = m_lpTeam[TEAM1].GetNationMemberCount(NW_YL);
	packet.u.NationWar.NeoWarResult.nBYDeathCount = m_lpTeam[TEAM1].GetNationDeathCount(NW_BY);
	packet.u.NationWar.NeoWarResult.nZYDeathCount = m_lpTeam[TEAM1].GetNationDeathCount(NW_ZY);
	packet.u.NationWar.NeoWarResult.nYLDeathCount = m_lpTeam[TEAM1].GetNationDeathCount(NW_YL);
	//< LTH-040413-KO 모든 나라가 몬스터 습격을 받으면 결과창을 띄우지 않기 위해 이값을 실어 보낸다.
	bool bAllNationJoin = FALSE;
	int nI;
	for (nI = 0; nI < NW_NATION_COUNT; ++nI)
	{
		if (TRUE == m_bJoinNation[nI])
		{
			bAllNationJoin = TRUE;
			break;
		}
	}
	packet.u.NationWar.NeoWarResult.bAllNationJoin = bAllNationJoin;
	//> LTH-040413-KO
	packet.h.header.size=sizeof(NEO_WAR_RESULT);

	SendPacket2Maps(&packet);
	g_pUserManager->SendPacket(&packet);
}

extern void SendFameChange(LPCHARLIST lpChar,int AddFame);

VOID CHadesWarfield::GiveFame(INT TeamNo, LPCHARLIST lpCaster, LPCHARLIST lpTarget)
{
	INT nRange = GIVE_FAME_RANGE;

	short int sOldFame = 0;

	switch (lpTarget->SprNo)
	{
	case 64 :	
		//< LTH-040324-KO Fame 로그 강화
		g_pLogManager->SaveLogChange_Fame(lpCaster, lpCaster->fame, lpCaster->fame + 20, LF_NATIONWAR);
		sOldFame = lpCaster->fame;
		lpCaster->fame += 20; 	
		g_pLogManager->SaveLogNeoNationWar(NNT_FAME_INFO, "%s Fame Change : Old Fame = %d, Current Fame = %d, Add Fame = %d", \
			lpCaster->Name, sOldFame, lpCaster->fame, 20);
		//> LTH-040324-KO
		::SendFameChange(lpCaster, 20);
		m_lpTeam[TeamNo].GiveFame(lpCaster, lpTarget, nRange, 4);
		break;

	case 63 :
		//< LTH-040324-KO Fame 로그 강화
		g_pLogManager->SaveLogChange_Fame(lpCaster, lpCaster->fame, lpCaster->fame + 15, LF_NATIONWAR);
		sOldFame = lpCaster->fame;
		lpCaster->fame += 15; 									
		g_pLogManager->SaveLogNeoNationWar(NNT_FAME_INFO, "%s Fame Change : Old Fame = %d, Current Fame = %d, Add Fame = %d", \
			lpCaster->Name, sOldFame, lpCaster->fame, 15);
		//> LTH-040324-KO
		::SendFameChange(lpCaster, 15);
		m_lpTeam[TeamNo].GiveFame(lpCaster, lpTarget, nRange, 3);
		break;

	case 177 :
		//< LTH-040315-KO 성문은 두개 다깨도 한번만 Fame을 받도록...
		if (TRUE == m_lpGuard[TEAM2].IsTargetBroken(lpTarget, GS_GATE))
		{	//< LTH-040324-KO Fame 로그 강화
			g_pLogManager->SaveLogChange_Fame(lpCaster, lpCaster->fame, lpCaster->fame + 10, LF_NATIONWAR);
			sOldFame = lpCaster->fame;
			lpCaster->fame += 10;
			g_pLogManager->SaveLogNeoNationWar(NNT_FAME_INFO, "%s Fame Change : Old Fame = %d, Current Fame = %d, Add Fame = %d", \
				lpCaster->Name, sOldFame, lpCaster->fame, 10);
			//> LTH-040324-KO
			::SendFameChange(lpCaster, 10);
			m_lpTeam[TeamNo].GiveFame(lpCaster, lpTarget,nRange, 3);
		}
		//> LTH-040315-KO
		break;
		
	case 178 :
		//< LTH-040324-KO Fame 로그 강화
		g_pLogManager->SaveLogChange_Fame(lpCaster, lpCaster->fame, lpCaster->fame + 15, LF_NATIONWAR);
		sOldFame = lpCaster->fame;
		lpCaster->fame += 15; 									
		g_pLogManager->SaveLogNeoNationWar(NNT_FAME_INFO, "%s Fame Change : Old Fame = %d, Current Fame = %d, Add Fame = %d", \
			lpCaster->Name, sOldFame, lpCaster->fame, 15);
		//> LTH-040324-KO
		::SendFameChange(lpCaster, 15);
		m_lpTeam[TeamNo].GiveFame(lpCaster, lpTarget, nRange, 3);
		break;
	}
}

extern void SendGuardKiller(LPCHARLIST pCaster,LPCHARLIST pTarget);

STDMETHODIMP_(VOID) CHadesWarfield::UpdateGuardStatus(LPCHARLIST lpCaster, LPCHARLIST lpTarget)
{
	if (m_lpGuard[TEAM2].CheckAndUpdateStatus(lpTarget))
	{	
		if (lpCaster == NULL)
			return;

		GiveFame(TEAM1, lpCaster, lpTarget);
		::SendGuardKiller(lpCaster, lpTarget);
		return;
	}

	::MyLog(LOG_FATAL, "CHadesWarfield UpdateGuardStoneStatus() Error!!, NPC Index : %d,SprNo : %d", \
		lpTarget->GetServerID(), lpTarget->SprNo);
}

STDMETHODIMP_(VOID) CHadesWarfield::CountDeath(LPCHARLIST lpChar)
{
	INT nTeamNo = GetTeamNo(lpChar);
	INT nSquadNo = lpChar->NWCharacter.SquadNo;
	INT nNationNo = (INT)lpChar->name_status.nation;
	m_lpTeam[nTeamNo].AddDeathCount(nNationNo, nSquadNo);
}

VOID CHadesWarfield::KickAllUser2Home()
{
	INT nI;
	for(nI = DRAGON_CONNECTIONS_START; nI < DRAGON_MAX_CONNECTIONS; ++nI)
	{
		if (::CheckServerId(nI))
		{
			switch (connections[nI].chrlst.name_status.nation)
			{
			case NW_BY:
				::MapMove(nI,"MA-IN",245,115);
				break;
			case NW_ZY: 
				::MapMove(nI,"RENES_C",210,175);	
				break;
			case NW_YL: 
				::MapMove(nI,"BARANTAN",325,98);	
				break;
			}
		}
	}
}

STDMETHODIMP_(int) CHadesWarfield::GetWarfieldNo()
{
	return m_nWarfieldNo;
}

STDMETHODIMP_(int*) CHadesWarfield::GetJoinNation()
{
	return m_bJoinNation;
}