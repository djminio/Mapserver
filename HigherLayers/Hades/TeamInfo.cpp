/**
 * @file	TeamInfo.cpp.
 *			implementation of the CTeamInfo class.
 */
//#include "..\stdafx.h"
#include "StdAfx.h"	// 컴파일 시간이 20여분 걸려서, 최적화 작업

#include "TeamInfo.h"
#include "WarfieldInfo.h"
#include "LogManager.h"

CSquad::CSquad()
: m_nSquadLeader(-1)
, m_nSquadNo(-1)
{
	m_ltSquad.clear();
	m_xyLoadingPoint.x = 0;
	m_xyLoadingPoint.y = 0;
	INT nI;
	for (nI = 0; nI < 3; ++nI)
	{
		m_naNumOfJoinNation[nI] = 0;
		m_naNumOfDeathNation[nI] = 0;
	}
}

/**
 * @fn		CSquad::GetNationMemberCount().
 * @brief	각 국가별 인원 수를 반환 한다.
 * @param	INT nNationNo. 특정 국가.
 * @return	INT. 특정 국가의 인원 수.
 */
INT CSquad::GetNationMemberCount(INT nNationNo)
{
	switch(nNationNo)
	{
	case NW_BY:
		return m_naNumOfJoinNation[0];

	case NW_ZY:
		return m_naNumOfJoinNation[1];

	case NW_YL:
		return m_naNumOfJoinNation[2];
	}
	
	return 0;
}	

/**
 * @fn		CSquad::GetMemberCount().
 * @brief	이 부대의 총 인원 수 반환.
 * @return	INT. 이 부대의 총 인원 수.
 */
INT CSquad::GetMemberCount()
{
	INT nMemberCount = m_ltSquad.size();
	return nMemberCount;
}	

/**
 * @fn		CSquad::InsertMember().
 * @brief	부대원 추가하는 함수.
 * @param	INT nCn. 유저 인식 번호.
 * @return	VOID.
 */
VOID CSquad::InsertMember(INT nCn)
{
	SquadMember* lpSquadMember = new SquadMember;
	lpSquadMember->SetData(nCn);
	m_ltSquad.push_back(lpSquadMember);

	switch (connections[nCn].chrlst.name_status.nation)
	{
	case NW_BY:
		++m_naNumOfJoinNation[0];
		break;

	case NW_ZY:
		++m_naNumOfJoinNation[1]; 
		break;

	case NW_YL:
		++m_naNumOfJoinNation[2];
		break;
	}
	connections[nCn].chrlst.NWCharacter.SquadNo = (DWORD)m_nSquadNo;
	//< 로그 강화.
	g_pLogManager->SaveLogNeoNationWar(NNT_CHARACTER_INFO, "%s Join in Squad %d, Nation %d", connections[nCn].name, \
		m_nSquadNo, connections[nCn].chrlst.name_status.nation);
	g_pLogManager->SaveLogNeoNationWar(NNT_CHARACTER_INFO, "Number Of %d Squad Member : %d", m_nSquadNo, \
		m_ltSquad.size());
	//> 
}	

/**
 * @fn		CSquad::DeleteMember().
 * @brief	부대원 제거.
 * @param	INT nCn. 유저 인식 번호.
 * @return	VOID.
 */
VOID CSquad::DeleteMember(INT nCn)
{
	INT nCheckID;
	SquadMember* lpSquadMember;
	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();
	while (ltSquadIt != ltSquadItEnd)
	{ 
		nCheckID = (*ltSquadIt)->GetData();
		if (nCheckID == nCn)
		{
			switch (connections[nCn].chrlst.name_status.nation)
			{
			case NW_BY:
				--m_naNumOfJoinNation[0];
				break;

			case NW_ZY:
				--m_naNumOfJoinNation[1];
				break;

			case NW_YL:
				--m_naNumOfJoinNation[2];
				break;
			}
			//< 로그 추가!!
			connections[nCn].chrlst.NWCharacter.SquadNo = 0;
			g_pLogManager->SaveLogNeoNationWar(NNT_CHARACTER_INFO, "%s Withdrew from Squad %d, Nation %d", connections[nCn].name, \
				m_nSquadNo, connections[nCn].chrlst.name_status.nation);
			g_pLogManager->SaveLogNeoNationWar(NNT_CHARACTER_INFO, "Number Of %d Squad Member : %d", m_nSquadNo, m_ltSquad.size() - 1);
			//> 

			lpSquadMember = (*ltSquadIt);
			m_ltSquad.remove(lpSquadMember);
			SAFE_DELETE(lpSquadMember);
			connections[nCn].chrlst.NWCharacter.SquadNo = 0;
			break;
		}
		else
			ltSquadIt++; 
	}
}	

/**
 * @fn		CSquad::SendMessageAllMember().
 * @brief	전 부대원에게 채팅 메시지 보낸다.
 * @param	t_packet * p. 패킷 변수.
 * @return	VOID.
 */
VOID CSquad::SendMessageAllMember(t_packet *p)
{
	INT nCn = -1;
	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();
	for (; ltSquadIt != ltSquadItEnd; ltSquadIt++)
	{
		nCn = (*ltSquadIt)->GetData();
		QueuePacket(connections, nCn, p, 1);
	}
}

/**
 * @fn		CSquad::FindMember().
 * @brief	부대원 찾기.
 * @param	INT nCn. 유저 인식 번호.
 * @return	BOOL. 찾았으면 TRUE.
 */
BOOL CSquad::FindMember(INT nCn)
{
	INT nID = -1;
	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();
	BOOL bFind = FALSE;
	for (; ltSquadIt != ltSquadItEnd; ltSquadIt++)
	{
		nID = (*ltSquadIt)->GetData();
		if (nID == nCn)
		{
			bFind = TRUE;
			break;
		}
	}

	return bFind;
}	

/**
 * @fn		CSquad::GetNationDeathCount().
 * @brief	특정 국가의 죽은 사람 수 반환.
 * @param	INT nNationNo. 특정 국가 번호.
 * @return	INT. 죽은 사람 수.
 */
INT CSquad::GetNationDeathCount(INT nNationNo)
{
	switch(nNationNo)
	{
	case NW_BY:
		return m_naNumOfDeathNation[0];

	case NW_ZY:
		return m_naNumOfDeathNation[1];

	case NW_YL:
		return m_naNumOfDeathNation[2];
	}
	
	return 0;
}

extern void SendFameChange(LPCHARLIST lpChar,int AddFame);

/**
 * @fn		CSquad::GiveFame().
 * @brief	타겟 지점으로부터 일정 거리에 있는 사람에게 해당 명성치를 준다.
 * @param	LPCHARLIST lpCaster. 명성치를 받는데 제외 될 사람,
 * @param	LPCHARLIST lpTarget. 타겟.
 * @param	INT nRange. 일정 거리
 * @param	INT nAddFame. 받을 명성치.
 * @return	VOID.
 */
VOID CSquad::GiveFame(LPCHARLIST lpCaster, LPCHARLIST lpTarget, INT nRange, INT nAddFame)
{
	INT nCn;
	DWORD dwTileRange = (nRange * TILE_SIZE) * (nRange * TILE_SIZE);
	DWORD dwTargetRange = 0;
	INT nSx = lpTarget->X;
	INT nSy = lpTarget->Y;
	INT nDx, nDy;
	LPCHARLIST	lpChar;
	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();
	for (; ltSquadIt != ltSquadItEnd; ltSquadIt++)
	{
		nCn = (*ltSquadIt)->GetData();
		if (lpCaster->GetServerID() != nCn)
		{
			lpChar = &connections[nCn].chrlst;
			nDx = lpChar->X;
			nDy = lpChar->Y;
			dwTargetRange = (nSx - nDx) * (nSx - nDx) + (nSy - nDy) * (nSy - nDy);
			if (dwTileRange > dwTargetRange)
			{
				g_pLogManager->SaveLogChange_Fame(lpChar, lpChar->fame, lpChar->fame + nAddFame, LF_NATIONWAR);
				g_pLogManager->SaveLogNeoNationWar(NNT_FAME_INFO, "Fame Change, Name : %s, OldFame : %d, NewFame : %d, Gap : %d", \
					lpChar->Name, lpChar->fame, lpChar->fame + nAddFame, nAddFame);
				lpChar->fame += nAddFame;
				::SendFameChange(lpChar, nAddFame);
			}
		}
	}
}

#include "Scrp_exe.h"
/* g_pLogManager로 이동(정리목적)
extern void SaveLogChange_DualFame( CHARLIST *ch, const int nOldDualFame, const int nNewDualFame, eLDF_TYPE type);
*/

/**
 * @fn		CSquad::GiveFame2Dual().
 * @brief	듀얼 명성치를 준다.
 * @param	INT nAddFame. 받을 명성치.
 * @return	VOID.
 */
VOID CSquad::GiveFame2Dual(INT nAddFame)
{
	INT nCn = 0;
	LPCHARLIST lpChar = NULL;

	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();
	for (; ltSquadIt != ltSquadItEnd; ltSquadIt++)
	{
		nCn = (*ltSquadIt)->GetData();
		lpChar = &connections[nCn].chrlst;
		if (NULL == lpChar)
			continue;
		if (lpChar->IsDual())
		{
			g_pLogManager->SaveLogChange_DualFame(lpChar, lpChar->fame, lpChar->fame + nAddFame, LDF_NEOWAR);
			g_pLogManager->SaveLogNeoNationWar(NNT_FAME_INFO, "Fame Change, Name : %s, OldFame : %d, NewFame : %d, Gap : %d", \
				lpChar->Name, lpChar->fame, lpChar->fame + nAddFame, nAddFame);
			lpChar->fame += nAddFame;
			::SendFameChange(lpChar, nAddFame);
		}
	}
}	

/**
 * @fn		CSquad::AddDeathCount().
 * @brief	특정 국가에 죽은 사람수 추가.
 * @param	INT nNationNo. 특정 국가 번호.
 * @return	VOID.
 */
VOID CSquad::AddDeathCount(INT nNationNo)
{
	switch(nNationNo)
	{
	case NW_BY:
		++m_naNumOfDeathNation[0];
		break;

	case NW_ZY:
		++m_naNumOfDeathNation[1];
		break;

	case NW_YL:
		++m_naNumOfDeathNation[2];
		break;
	}
}	

/**
 * @fn		CSquad::DeleteAllMember().
 * @brief	모든 부대원 제거.
 * @return	VOID.
 */
VOID CSquad::DeleteAllMember()
{
	SquadMember* lpSquadMember;
	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();
	while (ltSquadIt != ltSquadItEnd)
	{
		lpSquadMember = (*ltSquadIt);
		m_ltSquad.remove(lpSquadMember);
		SAFE_DELETE(lpSquadMember);

		ltSquadIt++;
	}

	m_nSquadLeader = -1;
	m_ltSquad.clear();
	INT nI;
	for (nI = 0; nI < 3; ++nI)
	{
		m_naNumOfJoinNation[nI] = 0;
		m_naNumOfDeathNation[nI] = 0;
	}
}	

/**
 * @fn		CSquad::RemoveArmor().
 * @brief	갑옷을 벗긴다.
 * @return	VOID.
 */
VOID CSquad::RemoveArmor()
{
	INT nID;
	LTSQUADIT ltSquadIt = m_ltSquad.begin();
	LTSQUADIT ltSquadItEnd = m_ltSquad.end();

	while (ltSquadIt != ltSquadItEnd)
	{
		nID = (*ltSquadIt)->GetData();
		::CheckAndSendChangeEquip(&connections[nID].chrlst, 1);
		ltSquadIt++;
	}
}

//----------------------------------------------------------------------------------

/**
 * @fn		CTeamInfo::GetNationMemberCount().
 * @brief	특정 국가의 멤버수를 반환.
 * @param	INT nNationNo. 특정 국가 번호.
 * @return	INT. 특정 국가의 멤버 수.
 */
INT CTeamInfo::GetNationMemberCount(INT nNationNo)
{
	INT nNationMember = 0;
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
	{
		nNationMember += m_lpSquad[nI].GetNationMemberCount(nNationNo);
	}

	return nNationMember;
}	

/**
 * @fn		CTeamInfo::GetSquadMemberCount().
 * @brief	특정 부대의 부대원 수.
 * @param	INT nSquadNo. 특정 부대 번호.
 * @return	INT. 특정 부대의 부대원 수.
 */
INT CTeamInfo::GetSquadMemberCount(INT nSquadNo)
{
	// 부대가 없는 팀은 없는 것과 마찬가지 이므로...
	if (m_nNumOfSquad == 0)
		return 0;

	INT nSquadMember = m_lpSquad[nSquadNo].GetMemberCount();
	return nSquadMember;
}	

extern LPWARFIELDINFO g_pcWarfieldInfo;

/**
 * @fn		CTeamInfo::CheckSquadOfCharacter().
 * @brief	특정 유저의 레벨이 해당 전쟁에서는 어느 부대인가 반환.
 * @param	INT nWarfieldNo. 현재 전쟁터 번호.
 * @param	INT nCharLv. 특정 유저의 레벨.
 * @return	INT. 어느 부대.
 */
INT CTeamInfo::CheckSquadOfCharacter(INT nWarfieldNo, INT nCharLv)
{
	CSoldierSet cSoldier = g_pcWarfieldInfo->GetSoldierSet(nWarfieldNo);
	INT nSquadNo = -1;
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
	{
		if ((nCharLv >= cSoldier.m_tagaSquad[nI].nLevelMin) && (nCharLv <= cSoldier.m_tagaSquad[nI].nLevelMax))
			break;
	}
	nSquadNo = nI;

	return nSquadNo;
}	

/**
 * @fn		CTeamInfo::Init().
 * @brief	CTeamInfo class 초기화.
 * @param	INT nNumOfSquad. 총 부대 수.
 * @return	HRESULT.
 */
HRESULT CTeamInfo::Init(INT nNumOfSquad)
{
	m_nNumOfSquad = nNumOfSquad;
	//< 적어도 한 부대는 있어야한다
	if (m_nNumOfSquad == 0)
		return E_FAIL;
	//> 
	m_lpSquad = new CSquad[m_nNumOfSquad];
	_ASSERT(NULL != m_lpSquad);

	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
		m_lpSquad[nI].SetSquadNo(nI);
	return S_OK;
}	

/**
 * @fn		CTeamInfo::InsertSquadMember().
 * @brief	부대원 추가.
 * @param	INT nWarfieldNo. 전쟁터 번호.
 * @param	INT nCn. 유저 인식 번호.
 * @return	VOID.
 */
VOID CTeamInfo::InsertSquadMember(INT nWarfieldNo, INT nCn)
{
	//< 운영자 캐릭은 부대에 포한 시키지 않으려고 추가
	LPCHARLIST lpChar = ::CheckServerId(nCn);
	if (lpChar == NULL)
		return;
	if (lpChar->IsCounselor()) 
		return;
	//>

	INT nCharLv = connections[nCn].chrlst.GetLevel();
	INT nSquadNo = CheckSquadOfCharacter(nWarfieldNo, nCharLv);
	m_lpSquad[nSquadNo].InsertMember(nCn);
}	

/**
 * @fn		CTeamInfo::DeleteSquadMember().
 * @brief	부대원 제거.
 * @param	INT nWarfieldNo. 전쟁터번호.
 * @param	INT nCn. 유저 인식 번호.
 * @return	VOID.
 */
VOID CTeamInfo::DeleteSquadMember(INT nWarfieldNo, INT nCn)
{
	//< 운영자 캐릭은 부대에 포한 시키지 않으려고 추가
	LPCHARLIST lpChar = ::CheckServerId(nCn);
	if (lpChar == NULL)
		return;
	if (lpChar->IsCounselor()) 
		return;
	//> 
	
	INT nCharLv = connections[nCn].chrlst.GetLevel();
	INT nSquadNo = CheckSquadOfCharacter(nWarfieldNo, nCharLv);
	m_lpSquad[nSquadNo].DeleteMember(nCn);
}	

/**
 * @fn		CTeamInfo::SendMessageAllMember().
 * @brief	부대원 채팅 메지지 전달.
 * @param	t_packet * p. 패킷 변수.
 * @return	VOID.
 */
VOID CTeamInfo::SendMessageAllMember(t_packet *p)
{
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
		m_lpSquad[nI].SendMessageAllMember(p);
}	

/**
 * @fn		CTeamInfo::GetLivePoint().
 * @brief	특정 유저가 속한 부대의 로딩 포인트 얻어오기.
 * @param	LPCHARLIST lpChar. 특정 유저.
 * @return	POINT. 로딩 포인트.
 */
POINT CTeamInfo::GetLivePoint(LPCHARLIST lpChar)
{
	INT nI;
	POINT xyTemp = {0, 0};
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
	{
		if (m_lpSquad[nI].FindMember(lpChar->GetServerID()))
		{
			xyTemp = m_lpSquad[nI].GetLivePoint();
			break;
		}
	}

	return xyTemp;
}	

/**
 * @fn		CTeamInfo::KickUser().
 * @brief	특정 부대원 제거.
 * @param	INT nCn. 유저
 * @return	BOOL. 유저가 없으면 FALSE.
 */
BOOL CTeamInfo::KickUser(INT nCn)
{
	LPCHARLIST lpChar = ::CheckServerId((WORD)nCn);
	if (NULL == lpChar)
		return FALSE;

	BOOL bIsUser = FALSE;
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
	{
		//< 인자로 들어온 유저 아이디가 있자나 비웅아!! 함수를 또쓰냐 -_-;
		if (m_lpSquad[nI].FindMember(nCn))
		{
			m_lpSquad[nI].DeleteMember(nCn);
			bIsUser = TRUE;
			break;
		}
		//> 
	}

	return bIsUser;
}	

/**
 * @fn		CTeamInfo::GetNationDeathCount().
 * @brief	특정 국가의 죽은 사람 수를 반환.
 * @param	INT nNation. 특정 국가 번호.
 * @return	INT. 죽은 사람 수.
 */
INT CTeamInfo::GetNationDeathCount(INT nNation)
{
	INT nNationDeathMember = 0;
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
	{
		nNationDeathMember += m_lpSquad[nI].GetNationDeathCount(nNation);
	}

	return nNationDeathMember;
}	

/**
 * @fn		CTeamInfo::GiveFame2Dual().
 * @brief	듀얼 명성을 준다.
 * @param	INT nAddFame. 받을 명성치.
 * @return	VOID.
 */
VOID CTeamInfo::GiveFame2Dual(INT nAddFame)
{
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
		m_lpSquad[nI].GiveFame2Dual(nAddFame);
}	

/**
 * @fn		CTeamInfo::GiveFame().
 * @brief	특정 캐릭을 제외하고 일정 거리의 캐릭에게 명성치를 준다.
 * @param	LPCHARLIST lpCaster. 명성치를 받지 않을 캐릭.
 * @param	LPCHARLIST lpTarget. 타겟.
 * @param	INT nRange. 일정 거리.
 * @param	INT nAddFame. 받을 명성치.
 * @return	VOID.
 */
VOID CTeamInfo::GiveFame(LPCHARLIST lpCaster, LPCHARLIST lpTarget, INT nRange, INT nAddFame)
{
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
	{
		m_lpSquad[nI].GiveFame(lpCaster, lpTarget, nRange, nAddFame);
	}
}	

/**
 * @fn		CTeamInfo::Clear().
 * @brief	모든 부대원 제거.
 * @return	VOID.
 */
VOID CTeamInfo::Clear()
{
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
		m_lpSquad[nI].DeleteAllMember();
}	

/**
 * @fn		CTeamInfo::RemoveArmor().
 * @brief	갑옷 벗기기.
 * @return	VOID.
 */
VOID CTeamInfo::RemoveArmor()
{
	INT nI;
	for (nI = 0; nI < m_nNumOfSquad; ++nI)
		m_lpSquad[nI].RemoveArmor();
}	