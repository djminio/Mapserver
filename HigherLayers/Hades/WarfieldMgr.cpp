#include "../../StdAfx.h"	//������ �ð��� 20���� �ɷ���, ����ȭ �۾�
/**
 * @file	WarfieldMgr.cpp.
 *			implementation of the CWarfieldMgr class.
 */

#include "WarfieldMgr.h"
#include "WarfieldFactory.h"
#include "WarfieldInfo.h"

/**
 * @fn		CWarfieldMgr::ExecMsg().
 * @brief	�ܺ� ������ Message�� ó���Ѵ�.
 * @param	CWarfieldMgr::eWARFIELD_PROC_MSG eWarfieldProcMsg. �ܺ� ������ Message.
 * @param	LPVOID lpVoid. �ʿ��ϴٸ� ��ȯ�ϱ� ���� ����. ���ٸ� Default�� NULL�̴�.
 * @return	HRESULT. Message ���� �� �����.
 * @warning	���⿡ ������� ���� Message�� ���� ��ȯ�Ͽ� �̰��� �ٽ� �������� ��ƾ�� �������Ѵ�. ������ ����!!.
 */
HRESULT CWarfieldMgr::ExecMsg(CWarfieldMgr::eWARFIELD_PROC_MSG eWarfieldProcMsg, LPVOID lpVoid)
{
	switch(eWarfieldProcMsg)
	{
	case CWarfieldMgr::WPM_CREATE_WARFIELD:
		{
			// ÷�ڷ� ���� ������ ��ȣ�� Null�� �ƴϸ�...
			if (NULL != lpVoid)
			{
				CreateWarfield(*((INT*)lpVoid));	// ������ ����.
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
			//< �����Ͱ� ������ ���� �ʾҴµ� ���� ���ϵ��� �Ѵ�.
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
			lpWarfieldData->dwRemainTime = static_cast<DWORD>(m_lpWarfield->GetRemainTime());	//060327_kch RemainTime Bug (DWORD �� __int64���� type��ȭ���� �߻��ϴ� ����)
			lpWarfieldData->nWarfieldNo = m_lpWarfield->GetWarfieldNo();		// LTH-040311-KO
			INT nI, nJ;
			for (nI = 0; nI < MAX_TEAM; ++nI)
			{
				lpGuardInfo = m_lpWarfield->GetGuardInfo(nI);
				lpTeamInfo = m_lpWarfield->GetTeamInfo(nI);

				//< üũ��ȭ 5994map Crash (TEAM1 �������϶��� ���彺�� ����, �����ϴµ�, ó���ϴºκ� �������� ����ϹǷ� �����߻��Ѱ����� ����)
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
 * @brief	�����͸� �����ϴ� �Լ�.
 * @param	INT nWarfieldId. ������ ��ȣ.
 * @return	HRESULT. ���� ��ȯ.
 */
HRESULT CWarfieldMgr::CreateWarfield(INT nWarfieldId)
{
	// ������ ���丮�� ����� �����͸� �����Ѵ�.
	LPFACTORYDEFINE lpWarfieldFactory = NULL;
	lpWarfieldFactory = new CWarfieldFactory;
	if (FAILED(lpWarfieldFactory->Create(nWarfieldId, (VOID**)&m_lpWarfield)))
	{
		::JustMsg("CWarfieldMgr::CreateWarfield() lpWarfieldFactory->Create() ����");
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
