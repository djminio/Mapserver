#pragma once

#include "IWarfieldDefine.h"
#include "TeamInfo.h"	// Added by ClassView
#include "GuardInfo.h"

/**
 * @class	CHadesWarfield.
 * @brief	Hades �������� �ʰ�����.
 *			�������� Hades �������� ó�� Class�̴�.
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
	int m_aSumNationPoint[NW_NATION_COUNT];		/**< ������ ��ŷ ������ ��. */
	INT m_nNumOfTeam;							/**< ���� ��. */
	BOOL m_bJoinNation[NW_NATION_COUNT];		/**< ���� �������� �� �� �ִ� ���� ����. TRUE : ���ͱ����� FALSE : ����. */
	BOOL m_bIsVictory;							/**< �¸� �ߴ°�. ���ͱ������� �¸��� ������ �¸��� ���Ѵ�. */
	INT m_nWarfieldNo;							/**< ������ ��ȣ. */
	INT m_nWarfieldState;						/**< ���� �������� ����. */
	LPWARFIELDSTATEDEFINE m_lpWarfieldState;	/**< ���� ���� class�� �����. */
	LPGUARDINFO m_lpGuard;						/**< ���带 �����ϱ� ���� �迭. */
	LPTEAMINFO m_lpTeam;						/**< ���� �����ϱ� ���� �迭. */
};
//> LTH-031222-KO.