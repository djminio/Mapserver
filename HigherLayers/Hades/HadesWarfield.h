#pragma once

#include "IWarfieldDefine.h"
#include "TeamInfo.h"	// Added by ClassView
#include "GuardInfo.h"

/**
 * @class	CHadesWarfield.
 * @brief	Hades 전쟁터의 맵관리자.
 *			실질적인 Hades 전쟁터의 처리 Class이다.
 */
//< LTH-031222-KO.
class CHadesWarfield : public IWarfieldDefine  
{
public:
	CHadesWarfield();
	virtual ~CHadesWarfield();

public:
	STDMETHOD(Init)(THIS_ INT nWarfieldNo);
	STDMETHOD_(VOID, SetStatus)(THIS_ INT nState);
	STDMETHOD_(INT, GetStatus)(THIS);
	STDMETHOD_(VOID, SetRemainTime)(THIS_ __int64 dwRemainTime);
	STDMETHOD_(__int64, GetRemainTime)(THIS);
	STDMETHOD(Update)(THIS);
	STDMETHOD_(INT, GetSquadMemberCount)(THIS_ INT nSquadNo);
	STDMETHOD_(BOOL, CanAttackGuard)(THIS_ LPCHARLIST lpCaster, LPCHARLIST lpTarget);
	STDMETHOD_(VOID, InsertSquadMember)(THIS_ INT nCn);
	STDMETHOD_(VOID, DeleteSquadMember)(THIS_ INT nCn);
	STDMETHOD_(LPTEAMINFO, GetTeamInfo)(THIS_ INT nTeamNo);
	STDMETHOD_(LPGUARDINFO, GetGuardInfo)(THIS_ INT nTeamNo);
	STDMETHOD_(INT, GetTeamMemberCount)(THIS_ INT nTeamNo);
	STDMETHOD_(VOID, SendSquadChat)(THIS_ LPCHARLIST lpChar, t_packet* p);
	STDMETHOD_(POINT, GetLivePoint)(THIS_ LPCHARLIST lpChar);
	STDMETHOD_(VOID, GetTileDont)(THIS_ DONT_DATA* lpDontData);
	STDMETHOD_(VOID, CheckAndKickUser)(THIS_ INT nCn);
	STDMETHOD_(VOID, LoopTimeChange)(t_packet* p);
	STDMETHOD_(VOID, UpdateGuardStatus)(THIS_ LPCHARLIST lpCaster, LPCHARLIST lpTarget);
	STDMETHOD_(VOID, CountDeath)(THIS_ LPCHARLIST lpChar);
	STDMETHOD_(int, GetWarfieldNo)(THIS);
	STDMETHOD_(int*, GetJoinNation)(THIS);
	
protected:
	BOOL LoadWarfieldData();
	VOID CheckWinTeam();
	VOID UpdateNationPoint(INT nScore[NW_NATION_COUNT]);
	VOID SendMonsterRaidMsg(BOOL bIsStart);
	VOID CheckWarStartTeam();
	INT GetTeamNo(LPCHARLIST lpChar);
	VOID SendWarResult();
	VOID GiveFame(INT TeamNo, LPCHARLIST lpCaster, LPCHARLIST lpTarget);
	VOID KickAllUser2Home();

protected:
	int m_aSumNationPoint[NW_NATION_COUNT];		/**< 국지전 랭킹 점수의 합. */
	INT m_nNumOfTeam;							/**< 팀의 수. */
	BOOL m_bJoinNation[NW_NATION_COUNT];		/**< 몬스터 국가전에 할 수 있는 국가 정보. TRUE : 몬스터국가전 FALSE : 습격. */
	BOOL m_bIsVictory;							/**< 승리 했는가. 몬스터국가전의 승리는 유저의 승리를 말한다. */
	INT m_nWarfieldNo;							/**< 전쟁터 변호. */
	INT m_nWarfieldState;						/**< 현재 전쟁터의 상태. */
	LPWARFIELDSTATEDEFINE m_lpWarfieldState;	/**< 현재 상태 class의 저장소. */
	LPGUARDINFO m_lpGuard;						/**< 가드를 관리하기 위한 배열. */
	LPTEAMINFO m_lpTeam;						/**< 팀을 관리하기 위한 배열. */
};
//> LTH-031222-KO.