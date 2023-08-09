#pragma once

#include "IWarfieldDefine.h"
#include "../LogManager.h"

int const LIMITNATIONPOINT	=	30;	/**< LTH-040412-KO ���� ������ ���� ���� ����Ʈ. */

extern WORD g_wMapServerPort;

/**
 * @def		enum _eSQUAD.
 * @brief	�� �δ븦 �ĺ��ϱ� ���� �ĺ���.
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
 * @brief	���� ���� ���� ������ ���� �� ó�� �ϴ� class.
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
	 * @brief	�ش� �� �ֿ� ��� ������ �� ������ �Լ�.
	 * @return	BYTE.
	 * @Warning	���� �ϳ��� �����͸� �ٷ�⶧���� m_btHowManyTimesWeek ��� ������ �迭�� �ƴ�����
	 *			�Ǵٸ� Type�� �����Ͱ� ����ٸ� �ݵ�� ����Ǿ���ϴ� ������ �Լ��̴�... -_-;.
	 */
	//< LTH-040419-KO.
	BYTE GetHowManyTimesWeek() { return m_btHowManyTimesWeek; }
	//> LTH-040419-KO.

	/**
	 * @fn		CWarfieldInfo::GetWarTimeInfo().
	 * @brief	���� �ð� ������ ������ �Լ�.
	 * @param	INT nWarfieldNo. ������ ��ȣ.
	 * @param	BYTE btIndex. �ش� ������ ���° �����ΰ� �����Ͽ��� ��� �Ͼ �� �����Ƿ�.
	 * @return	CWarTimeInfo. ��°�� ��ȯ.
	 */
	//< LTH-040419-KO.
	CWarTimeInfo GetWarTimeInfo(INT nWarfieldNo, BYTE btIndex) { return m_atagWarTimeInfo[nWarfieldNo][btIndex]; }
	//> LTH-040419-KO.

	/**
	 * @fn		GetSoldierSet().
	 * @brief	������ �δ� ������ ������ �Լ�.
	 * @param	INT nWarfieldNo. ������ ��ȣ.
	 * @return	CSoldierSet. ��°�� ��ȯ.
	 */
	//< LTH-040419-KO.
	CSoldierSet GetSoldierSet(INT nWarfieldNo) { return m_acSoldierSet[nWarfieldNo]; }
	//> LTH-040419-KO.

	/**
	 * @fn		GetMapSetting().
	 * @brief	������ ���� ���ѻ��� ������ ������ �Լ�.
	 * @param	INT nWarfieldNo. ������ ��ȣ.
	 * @return	CMapSetting. ��°�� ��ȯ.
	 */
	//< LTH-040419-KO.
	CMapSetting GetMapSetting(INT nWarfieldNo) { return m_acMapSetting[nWarfieldNo]; }
	//> LTH-040419-KO.
	
	/**
	 * @fn		CWarfieldInfo::GetYlseWarfieldMoveMoney().
	 * @brief	�Ͻ����� ������ ��ȭ �Ⱓ ������ �̵� ��� ��ȯ.
	 * @return	DWORD.
	 */
	//< LTH-040429-KO.
	DWORD GetYlseWarfieldMoveMoney() { return m_dwYlWarfieldMoveMoney; }
	//> LTH-040429-KO.

	/**
	 * @fn		CWarfieldInfo::GetGoOutsideBBSTime().
	 * @brief	��ǥ �Ⱓ�� �������� ���� ���� ���� ����.
	 * @return	int. ���� ���� ���� ����.
	 */
	//< LTH-040507-KO.
	int CWarfieldInfo::GetGoOutsideBBSTime() { return m_nGoOutsideBBSTime; }
	//> LTH-040507-KO

	/**
	 * @fn		CWarfieldInfo::GetNumOfGoOutsideUser().
	 * @brief	�����Ϳ��� �ѹ��� ������ ������ ��.
	 * @return	int.
	 */
	//< LTH-040507-KO.
	int CWarfieldInfo::GetNumOfGoOutsideUser() { return m_nNumOfGoOutsideUser; }
	//> LTH-040507-KO.
	
protected:
	INT m_nNumOfWarfield;								/**< �������� �� ����. */
	BYTE m_btHowManyTimesWeek;							/**< �� �ֿ� ��� ��������. */
	CWarTimeInfo* m_atagWarTimeInfo[5];	/**< ���� �ð� ����. */
	CSoldierSet	m_acSoldierSet[5];		/**< ������ �δ� ����. */
	CMapSetting	m_acMapSetting[5];		/**< ������ �� ����. */
	DWORD m_dwYlWarfieldMoveMoney;						/**< LTH-040429-KO �Ͻ� ������ ��ȭ�� ������ �̵� ���. */
	int m_nGoOutsideBBSTime;							/**< LTH-040507-KO ��ǥ�Ⱓ ������ ���� ���� ���� ǥ�� ����. */
	int m_nNumOfGoOutsideUser;							/**< LTH-040507-KO �ѹ��� �����Ϳ��� �����ų ������ ��. */
} *LPWARFIELDINFO;	/**< CWarfieldInfo class�� Pointer�� ����. */
//> LTH-040414-KO.
