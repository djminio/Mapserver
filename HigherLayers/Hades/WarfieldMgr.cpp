#include "../../StdAfx.h"	//컴파일 시간이 20여분 걸려서, 최적화 작업
/**
 * @file	WarfieldMgr.cpp.
 *			implementation of the CWarfieldMgr class.
 */

#include "WarfieldMgr.h"
#include "WarfieldFactory.h"
#include "WarfieldInfo.h"

/**
 * @fn		CWarfieldMgr::ExecMsg().
 * @brief	외부 모듈과의 Message를 처리한다.
 * @param	CWarfieldMgr::eWARFIELD_PROC_MSG eWarfieldProcMsg. 외부 모듈과의 Message.
 * @param	LPVOID lpVoid. 필요하다면 반환하기 위한 인자. 없다면 Default는 NULL이다.
 * @return	HRESULT. Message 수행 후 결과값.
 * @warning	여기에 기술되지 않은 Message는 따로 변환하여 이곳에 다시 전해지는 루틴을 만들어야한다. 포인터 주의!!.
 */
HRESULT CWarfieldMgr::ExecMsg(CWarfieldMgr::eWARFIELD_PROC_MSG eWarfieldProcMsg, LPVOID lpVoid)
{
	switch(eWarfieldProcMsg)
	{
	case CWarfieldMgr::WPM_CREATE_WARFIELD:
		{
			// 첨자로 받은 전쟁터 번호가 Null이 아니면...
			if (NULL != lpVoid)
			{
				CreateWarfield(*((INT*)lpVoid));	// 전쟁터 생성.
			}
			else
			{
				::JustMsg("Warfield Number %d is NULL", *((INT*)lpVoid));
				return E_FAIL;
			}
		}
		break;

	case CWarfieldMgr::WPM_GET_WARFIELD_STATE:
		{
			INT* pState = (INT*)lpVoid;
			*pState = m_lpWarfield->GetStatus();
			lpVoid = (LPVOID)pState;
		}
		break;

	case CWarfieldMgr::WPM_SET_WARFIELD_STATE:
		{
			INT nState = (*((INT*)lpVoid));
			m_lpWarfield->SetStatus(nState);
		}
		break;

	case CWarfieldMgr::WPM_SET_REMAINTIME:
		{
			DWORD dwRemainTime = (DWORD)&lpVoid;
			m_lpWarfield->SetRemainTime(dwRemainTime);
		}
		break;

	case CWarfieldMgr::WPM_GET_REMAINTIME:
		{
			__int64* p64RemainTime = (__int64*)lpVoid;
			*p64RemainTime = m_lpWarfield->GetRemainTime();
			lpVoid = (LPVOID)p64RemainTime;
		}
		break;

	case CWarfieldMgr::WPM_UPDATE:
		{
			//< 전쟁터가 생성도 되지 않았는데 읽지 못하도록 한다.
			if (NULL == m_lpWarfield)
				return E_FAIL;
			//> 

			if (FAILED(m_lpWarfield->Update()))
				return E_FAIL;
		}
		break;

	case CWarfieldMgr::WPM_GET_SQUAD_MEMBER_COUNT:
		{
			tagSquadCount* lpSquadCount = (tagSquadCount*)lpVoid;
			lpSquadCount->nCurrentSquadMemberCount = m_lpWarfield->GetSquadMemberCount(lpSquadCount->nSquadNo);
			lpVoid = (LPVOID)lpSquadCount;
		}
		break;

	case CWarfieldMgr::WPM_CAN_ATTACK_GUARD:
		{
			tagOpponent* lpOpp = (tagOpponent*)lpVoid;
			if (FALSE == m_lpWarfield->CanAttackGuard(lpOpp->lpCaster, lpOpp->lpTarget))
				return E_FAIL;
		}
		break;

	case CWarfieldMgr::WPM_INSERT_SQUAD_MEMBER:
		{
			INT nCn = *((INT*)lpVoid);
			m_lpWarfield->InsertSquadMember(nCn);
		}
		break;

	case CWarfieldMgr::WPM_DELETE_SQUAD_MEMBER:
		{
			INT nCn = *((INT*)lpVoid);
			m_lpWarfield->DeleteSquadMember(nCn);
		}
		break;

	case CWarfieldMgr::WPM_GET_WARFIELDDATA:
		{
			NEO_WARFIELD_DATA* lpWarfieldData = (NEO_WARFIELD_DATA*)lpVoid;
			LPGUARDINFO lpGuardInfo;
			LPTEAMINFO lpTeamInfo;
			lpWarfieldData->dwRemainTime = static_cast<DWORD>(m_lpWarfield->GetRemainTime());	//060327_kch RemainTime Bug (DWORD 와 __int64간의 type변화간에 발생하는 버그)
			lpWarfieldData->nWarfieldNo = m_lpWarfield->GetWarfieldNo();		// LTH-040311-KO
			INT nI, nJ;
			for (nI = 0; nI < MAX_TEAM; ++nI)
			{
				lpGuardInfo = m_lpWarfield->GetGuardInfo(nI);
				lpTeamInfo = m_lpWarfield->GetTeamInfo(nI);

				//< 체크강화 5994map Crash (TEAM1 공격자일때는 가드스톤 없고, 사용안하는데, 처리하는부분 공통으로 사용하므로 문제발생한것으로 추정)
				if (NULL != lpGuardInfo)
				{
					lpGuardInfo->GetStatus(lpWarfieldData->cGuardStatus[nI]);
					for (nJ = 0; nJ < GS_MAX_GUARD_SPECIES; ++nJ)
						lpWarfieldData->nRemainGuardCount[nI][nJ] = lpGuardInfo->GetAliveGuardCount(nJ);
				}
				//>

				lpWarfieldData->nTeamCount[nI] = 0;
				for (nJ = 0; nJ < NW_SQUAD_MAX; ++nJ)
					lpWarfieldData->nTeamCount[nI] += lpTeamInfo->GetSquadMemberCount(nJ);
			}
			lpVoid = (LPVOID)lpWarfieldData;
		}
		break;

	case CWarfieldMgr::WPM_SEND_SQUAD_CHAT:
		{
			tagSendSquadChat* lpSendSquadChat = (tagSendSquadChat*)lpVoid;
			m_lpWarfield->SendSquadChat(lpSendSquadChat->lpChar, lpSendSquadChat->p);
		}
		break;

	case CWarfieldMgr::WPM_GET_LIVE_POINT:
		{
			tagGetLivePoint* lpGetLivePoint = (tagGetLivePoint*)lpVoid;
			LPCHARLIST lpChar = lpGetLivePoint->lpChar;
			lpGetLivePoint->lpPoint = &(m_lpWarfield->GetLivePoint(lpChar));
		}
		break;

	case CWarfieldMgr::WPM_GET_DONT_DATA:
		{
			m_lpWarfield->GetTileDont((DONT_DATA*)lpVoid);
		}
		break;

	case CWarfieldMgr::WPM_CHECK_AND_KICK_USER:
		{
			INT nCn = (*((INT*)lpVoid));
			m_lpWarfield->CheckAndKickUser(nCn);
		}
		break;

	case CWarfieldMgr::WPM_SET_LOOPTIME_CHANGE:
		{
			t_packet* p = (t_packet*)lpVoid;
			m_lpWarfield->LoopTimeChange(p);
		}
		break;

	case CWarfieldMgr::WPM_UPDATE_GUARD_STATUS:
		{
			tagOpponent* lpOpp = (tagOpponent*)lpVoid;
			m_lpWarfield->UpdateGuardStatus(lpOpp->lpCaster, lpOpp->lpTarget);
		}
		break;

	case CWarfieldMgr::WPM_INC_DEATH_MEMBER:
		{
			LPCHARLIST lpChar = (LPCHARLIST)lpVoid;
			m_lpWarfield->CountDeath(lpChar);
		}
		break;

	case CWarfieldMgr::WPM_CHECK_JOIN_NATION:
		{
			int* pJoinNation = m_lpWarfield->GetJoinNation();
			lpVoid = (void*)pJoinNation;
		}
		break;
		
	default:
		{
			::JustMsg("%d Wrong Warfield Proc Message!!", eWarfieldProcMsg);
		}
		return E_FAIL;
	}

	return S_OK;
}

/**
 * @fn		CWarfieldMgr::CreateWarfield().
 * @brief	전쟁터를 생성하는 함수.
 * @param	INT nWarfieldId. 전쟁터 번호.
 * @return	HRESULT. 생성 반환.
 */
HRESULT CWarfieldMgr::CreateWarfield(INT nWarfieldId)
{
	// 전쟁터 팩토리를 만들어 전쟁터를 생성한다.
	LPFACTORYDEFINE lpWarfieldFactory = NULL;
	lpWarfieldFactory = new CWarfieldFactory;
	if (FAILED(lpWarfieldFactory->Create(nWarfieldId, (VOID**)&m_lpWarfield)))
	{
		::JustMsg("CWarfieldMgr::CreateWarfield() lpWarfieldFactory->Create() 실패");
		return E_FAIL;
	}
	SAFE_DELETE(lpWarfieldFactory);

	if (FAILED(m_lpWarfield->Init(nWarfieldId)))
	{
		::JustMsg("Failed CWarfieldMgr::ExecMsg(WPM_CREATE_WARFIELD) Initialize!!");
		return E_FAIL;
	}
	
	return S_OK;
}
