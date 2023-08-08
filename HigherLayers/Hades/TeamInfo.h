#pragma once

#include <list>
#include "NationSys.h"

/**
 * @def		enum _eTEAM.
 * @brief	���￡�� ���� team �ν���.
 */
//< LTH-040419-KO.
typedef enum _eTEAM
{
	TEAM1		= 0,	/**< �Ʊ� �� Attacker. */
	TEAM2		= 1,	/**< ���� �� Deffenser. */
	MAX_TEAM	= 2,	/**< �� ���� ����. */
} eTEAM;
//> LTH-040419-KO.

/**
 * @class	CSquad.
 * @brief	�����Ϳ��� ���� �δ뿡 ���� ���� ���� class.
 */
//< LTH-040419-KO.
typedef class CSquad
{
public:
	CSquad();
	virtual ~CSquad() { DeleteAllMember(); }

public:
	VOID RemoveArmor();
	VOID DeleteAllMember();
	VOID AddDeathCount(INT nNationNo);
	VOID GiveFame2Dual(INT nAddFame);
	VOID GiveFame(LPCHARLIST lpCaster, LPCHARLIST lpTarget, INT nRange, INT nAddFame);
	INT GetNationDeathCount(INT nNationNo);
	BOOL FindMember(INT nCn);
	VOID SendMessageAllMember(t_packet *p);
	VOID DeleteMember(INT nCn);
	VOID InsertMember(INT nCn);
	INT GetMemberCount();
	INT GetNationMemberCount(INT nNationNo);

	/**
	 * @fn		CSquad::SetLivePoint().
	 * @brief	�� �δ��� �ε� ����Ʈ ����.
	 * @param	POINT xyLivePoint. ���� �� �ε� ����Ʈ.
	 * @return	VOID.
	 */
	//< LTH-040419-KO.
	VOID SetLivePoint(POINT xyLivePoint) { m_xyLoadingPoint = xyLivePoint; }
	//> LTH-040419-KO.

	/**
	 * @fn		CSquad::GetLivePoint().
	 * @brief	�� �δ��� �ε� ����Ʈ.
	 * @return	POINT. �ε�����Ʈ ��ȯ.
	 */
	//< LTH-040419-KO.
	POINT GetLivePoint() { return m_xyLoadingPoint; }
	//< LTH-040419-KO.

	/**
	 * @fn		CSquad::SetSquadNo().
	 * @brief	�� �δ��ȣ ����.
	 * @param	INT nSquadNo. ���� �� �δ� ��ȣ.
	 * @return	VOID.
	 */
	//< LTH-040419-KO.
	VOID SetSquadNo(INT nSquadNo) { m_nSquadNo = nSquadNo; }
	//> LTH-040419-KO.

protected:
	/**
	 * @def		std::list<SquadMember*> LTSQUAD;.
	 * @brief	�δ���� ���� �� ����Ʈ ����.
	 */
	//< LTH-040419-KO.
	typedef std::list<SquadMember*> LTSQUAD;
	//> LTH-040419-KO.
	/**
	 * @def		LTSQUAD::iterator LTSQUADIT;.
	 * @brief	�δ���� ���� �� ����Ʈ�� �ݺ���.
	 */
	//< LTH-040419-KO.
	typedef LTSQUAD::iterator LTSQUADIT;
	//> LTH-040419-KO.

	INT m_nSquadNo;					/**< �� �δ��� ��ȣ. */
	LTSQUAD m_ltSquad;				/**< �δ���� ���� �� ����Ʈ */
	INT m_nSquadLeader;				/**< �δ���. */
	POINT m_xyLoadingPoint;			/**< �� �δ��� �ε� ����Ʈ. */
	INT m_naNumOfDeathNation[3];	/**< �� ������ ���� ��� ��. */
	INT m_naNumOfJoinNation[3];		/**< �� ������ ���� �ο� ��. */
} *LPSQUAD;							/**< ������ �� ���� ����. */
//> LTH-040419-KO.

/**
 * @class	CTeamInfo.
 * @brief	���￡���� ���� ���� �ϱ� ���� class.
 */
//< LTH-040419-KO.
typedef class CTeamInfo  
{
public:
	CTeamInfo() : m_lpSquad(NULL), m_nCommander(-1), m_nNumOfSquad(-1), m_nTeamNo(-1) {}
	virtual ~CTeamInfo() {}

public:
	VOID RemoveArmor();
	VOID GiveFame(LPCHARLIST lpCaster, LPCHARLIST lpTarget, INT nRange, INT nAddFame);
	INT GetNationDeathCount(INT nNation);
	BOOL KickUser(INT nCn);
	POINT GetLivePoint(LPCHARLIST lpChar);
	VOID DeleteSquadMember(INT nWarfieldNo, INT nCn);
	VOID InsertSquadMember(INT nWarfieldNo, INT nCn);
	HRESULT Init(INT nNumOfSquad);
	INT CheckSquadOfCharacter(INT nWarfieldNo, INT nCharLv);
	INT GetNationMemberCount(INT nNationNo);
	INT GetSquadMemberCount(INT nSquadNo);
	VOID SendMessageAllMember(t_packet *p);
	VOID GiveFame2Dual(INT nAddFame);
	VOID Clear();

	/**
	 * @fn		CTeamInfo::SetLivePoint().
	 * @brief	�� �δ� �ε�����Ʈ ����.
	 * @param	INT nSquadNo. �δ� ��ȣ.
	 * @param	POINT xyLivePoint. �ε� ����Ʈ.
	 * @return	VOID.
	 */
	//< LTH-040419-KO.
	VOID SetLivePoint(INT nSquadNo, POINT xyLivePoint) { m_lpSquad[nSquadNo].SetLivePoint(xyLivePoint); }
	//> LTH-040419-KO.

	/**
	 * @fn		CTeamInfo::AddDeathCount().
	 * @brief	���� ��� ��.
	 * @param	INT nNationNo. ���� ����� ����.
	 * @param	INT nSquadNo. ���� ����� �δ�.
	 * @return	VOID.
	 */
	//< LTH-040419-KO.
	VOID AddDeathCount(INT nNationNo, INT nSquadNo) { m_lpSquad[nSquadNo].AddDeathCount(nNationNo); }
	//> LTH-040419-KO.

	/**
	 * @fn		CTeamInfo::SetTeamNo().
	 * @brief	�� ���� ��ȣ ����.
	 * @param	INT nTeamNo. ���� �� ��ȣ.
	 * @return	VOID.
	 */
	//< LTH-040419-KO.
	VOID SetTeamNo(INT nTeamNo) { m_nTeamNo = nTeamNo; }
	//> LTH-040419-KO.

	/**
	 * @fn		CTeamInfo::GetNumOfSquad().
	 * @brief	�δ� �� ��ȯ.
	 *			�ݵ�� �ʿ��ϴ�. �δ� ���� �˾Ƴ��� �׸�ŭ ������ ���ƾ��ϴϱ�...
	 * @return	INT.
	 */
	//< LTH-040304-KO.
	INT GetNumOfSquad() { return m_nNumOfSquad; }
	//> LTH-040304-KO.
	
protected:
	INT m_nTeamNo;		/**< �� ���� ��ȣ. �ַ� enum eTEAM ���� ��� �Ѵ�. */
	INT m_nNumOfSquad;	/**< �� ���� �δ� ��. �����ϵ��� ��� �� �� �̻����� �Ѵ�. */
	INT m_nCommander;	/**< �� ���� ��ɰ�. */
	LPSQUAD m_lpSquad;	/**< �� ���� �δ���� ���� �ϱ� ���� ����Ʈ. */
} *LPTEAMINFO;			/**< ������ �� ���� ����. */
//< LTH-040419-KO.