/**
 * @file	HWState.cpp.
 */
//#include "..\stdafx.h"
#include "StdAfx.h"	//060109_kch ������ �ð��� 20���� �ɷ���, ����ȭ �۾�

#include "HWState.h"
#include "WarfieldInfo.h"
#include "LogManager.h"

extern void UpdateWarTime();
extern void SendCMD_UPDATE_WARTIME(const int WarfieldNo, const int Status, const DWORD RemainTime);

extern LPWARFIELDINFO g_pcWarfieldInfo;
extern DWORD g_dwCurrWeekElapsedSec;

//--------------------------------------------
CHWPeaceState::CHWPeaceState()
{
	m_dwTerm = 0;
	m_n64RemainTime = 0;
	m_dwLoopTime = 0;
}

/**
 * @fn		CHWPeaceState::Init().
 * @brief	�ʱ�ȭ.
 * @param	INT nWarfieldNo. ������ ��ȣ.
 * @return	STDMETHODIMP_(VOID).
 */
//< LTH-040419-KO.
STDMETHODIMP_(VOID) CHWPeaceState::Init(INT nWarfieldNo)
{
	m_nWarfieldNo = nWarfieldNo;
	::UpdateWarTime();
	INT nIndex = g_pcWarfieldInfo->GetThisWarIndex(m_nWarfieldNo, g_dwCurrWeekElapsedSec);
	CWarTimeInfo cWarTime = g_pcWarfieldInfo->GetWarTimeInfo(m_nWarfieldNo, nIndex);
	m_dwTerm = 0;
	m_dwLoopTime = g_dwCurrWeekElapsedSec + m_dwTerm;
	m_n64RemainTime = (__int64)m_dwLoopTime - (__int64)g_dwCurrWeekElapsedSec;
	::SendCMD_UPDATE_WARTIME(m_nWarfieldNo, NW_PEACE, GetRemainTime());

	//< LTH-040323-KO �α� ��ȭ
	g_pLogManager->SaveLogNeoNationWar(NNT_STATE_INFO, "Peace State!! Active!! RemainTime : %ld", m_n64RemainTime);
	//> LTH-040323-KO
}	//> LTH-040419-KO.

/**
 * @fn		CHWPeaceState::SetRemainTime().
 * @brief	���� �ð� ����.
 * @param	__int64 dwRemainTime. ���� �� ���� �ð�.
 * @return	STDMETHODIMP_(VOID).
 */
//< LTH-040419-KO.
STDMETHODIMP_(VOID) CHWPeaceState::SetRemainTime(__int64 dwRemainTime)
{
	m_n64RemainTime = dwRemainTime;
}	//> LTH-040419-KO.

/**
 * @fn		CHWPeaceState::GetRemainTime().
 * @brief	�����ð� ��ȯ.
 * @return	STDMETHODIMP_(__int64).
 */
//< LTH-040419-KO.
STDMETHODIMP_(__int64) CHWPeaceState::GetRemainTime()
{
	::UpdateWarTime();
	//< LTH-040419-KO ���� �ð��� ���� ���� ���� �ð��� �����ٸ� ���������� 0�� ������ �������� �Ѵ�.
	if (m_dwLoopTime < g_dwCurrWeekElapsedSec)
	{
		m_dwLoopTime = 0;
		return (__int64)m_dwLoopTime; //return m_dwLoopTime - g_dwCurrWeekElapsedSec;//-g_curr_time; //060430_kch ���� �ð� -������ ���� �ȳ����� ���� �ذ��� ����
	}
	//> LTH-040419-KO.

	return (__int64)m_dwLoopTime - (__int64)g_dwCurrWeekElapsedSec;
}	//> LTH-040419-KO.

/**
 * @fn		CHWPeaceState::SetLoopTime().
 * @brief	���������� ����ð��� �����Ѵ�.
 * @param	DWORD dwLoopTime. ���� ���� ����ð�.
 * @return	STDMETHODIMP_(VOID).
 */
//< LTH-040419-KO.
STDMETHODIMP_(VOID) CHWPeaceState::SetLoopTime(DWORD dwLoopTime)
{
	//< LTH-040310-KO
	::UpdateWarTime();
	m_dwLoopTime = g_dwCurrWeekElapsedSec + dwLoopTime;
	//> LTH-040310-KO
}	//> LTH-040419-KO.

/**
 * @fn		CHWPeaceState::GetLoopTime().
 * @brief	���� ������ ����ð��� ��ȯ�Ѵ�.
 * @return	STDMETHODIMP_(DWORD).
 */
//< LTH-040419-KO.
STDMETHODIMP_(DWORD) CHWPeaceState::GetLoopTime()
{
	return m_dwLoopTime;
}	//> LTH-040419-KO.

/**
 * @fn		CHWPeaceState::Update().
 * @brief	���� ���� �ð��� �ٽ� ����ϸ� ���� ���¿� �ؾ������� ������Ʈ �Ѵ� �����ð��� ���̳ʽ��̸� ������¸� �����Ѵ�.
 * @return	STDMETHODIMP.
 */
//< LTH-040419-KO.
STDMETHODIMP CHWPeaceState::Update()
{
	return S_OK;
}	//> LTH-040419-KO.

//----- ���� ���� class�� ��������� ���� ������ ����̴�. -----
CHWWarState::CHWWarState()
{
	m_dwTerm = 0;
	m_n64RemainTime = 0;
	m_dwLoopTime = 0;
}

STDMETHODIMP_(VOID) CHWWarState::Init(INT nWarfieldNo)
{
	m_nWarfieldNo = nWarfieldNo;
	::UpdateWarTime();
	INT nIndex = g_pcWarfieldInfo->GetThisWarIndex(m_nWarfieldNo, g_dwCurrWeekElapsedSec);
	CWarTimeInfo cWarTime = g_pcWarfieldInfo->GetWarTimeInfo(m_nWarfieldNo, nIndex);
	m_dwTerm = cWarTime.m_dwWarTime;
	m_dwLoopTime = g_dwCurrWeekElapsedSec + m_dwTerm;
	m_n64RemainTime = (__int64)m_dwLoopTime - (__int64)g_dwCurrWeekElapsedSec;
	::SendCMD_UPDATE_WARTIME(m_nWarfieldNo, NW_WAR, GetRemainTime());

	//< LTH-040323-KO �α� ��ȭ
	g_pLogManager->SaveLogNeoNationWar(NNT_STATE_INFO, "War State!! Active!! RemainTime : %ld", m_n64RemainTime);
	//> LTH-040323-KO
}

STDMETHODIMP_(VOID) CHWWarState::SetRemainTime(__int64 dwRemainTime)
{
	m_n64RemainTime = dwRemainTime;
}

STDMETHODIMP_(__int64) CHWWarState::GetRemainTime()
{
	::UpdateWarTime();
	if (m_dwLoopTime < g_dwCurrWeekElapsedSec)
	{
		m_dwLoopTime = 0;
		return (__int64)m_dwLoopTime;
	}

	return (__int64)m_dwLoopTime - (__int64)g_dwCurrWeekElapsedSec;
}

STDMETHODIMP_(VOID) CHWWarState::SetLoopTime(DWORD dwLoopTime)
{
	//< LTH-040310-KO
	::UpdateWarTime();
	m_dwLoopTime = g_dwCurrWeekElapsedSec + dwLoopTime;
	//> LTH-040310-KO
}

STDMETHODIMP_(DWORD) CHWWarState::GetLoopTime()
{
	return m_dwLoopTime;
}

STDMETHODIMP CHWWarState::Update()
{
	::UpdateWarTime();

	//+[YonMy;map1; 20070625 ����]------------------------------------------------+
	m_n64RemainTime = GetRemainTime();
	if ( !m_n64RemainTime )	return E_FAIL;
	//-----------------------------------------------------------------------------

	if (m_n64RemainTime % NW_REMAIN_TIME_UPDATE == 0) 
		::SendCMD_UPDATE_WARTIME(m_nWarfieldNo, NW_WAR, GetRemainTime());

	//< LTH-040322-KO 10�а������� ���� �ð��� �α׷� �����ڱ�!!
	if ((m_n64RemainTime % 600) == 0)
		g_pLogManager->SaveLogNeoNationWar(NNT_TIME_INFO, "[Current RemainTime] = LoopTime(%ld) - CurrTime(%ld) = %ld", \
		m_dwLoopTime, g_dwCurrWeekElapsedSec, m_n64RemainTime);
	//> LTH-040322-KO

	return S_OK;
}

//--------------------------------------------
CHWSOpenState::CHWSOpenState()
{
	m_dwTerm = 0;
	m_n64RemainTime = 0;
	m_dwLoopTime = 0;
}

STDMETHODIMP_(VOID) CHWSOpenState::Init(INT nWarfieldNo)
{
	m_nWarfieldNo = nWarfieldNo;
	::UpdateWarTime();
	INT nIndex = g_pcWarfieldInfo->GetThisWarIndex(m_nWarfieldNo, g_dwCurrWeekElapsedSec);
	CWarTimeInfo cWarTime = g_pcWarfieldInfo->GetWarTimeInfo(m_nWarfieldNo, nIndex);
	m_dwTerm = cWarTime.m_dwSecretAreaOpenTime;
	m_dwLoopTime = g_dwCurrWeekElapsedSec + m_dwTerm;
	m_n64RemainTime = (__int64)m_dwLoopTime - (__int64)g_dwCurrWeekElapsedSec;
	::SendCMD_UPDATE_WARTIME(m_nWarfieldNo, NW_SOPEN, GetRemainTime());

	//< LTH-040323-KO �α� ��ȭ
	g_pLogManager->SaveLogNeoNationWar(NNT_STATE_INFO, "Secret Area Open State!! Active!! RemainTime : %ld", \
		m_n64RemainTime);
	//> LTH-040323-KO
}

STDMETHODIMP_(VOID) CHWSOpenState::SetRemainTime(__int64 dwRemainTime)
{
	m_n64RemainTime = dwRemainTime;
}

STDMETHODIMP_(__int64) CHWSOpenState::GetRemainTime()
{
	::UpdateWarTime();
	if (m_dwLoopTime < g_dwCurrWeekElapsedSec)
	{
		m_dwLoopTime = 0;
		return (__int64)m_dwLoopTime;
	}

	return (__int64)m_dwLoopTime - (__int64)g_dwCurrWeekElapsedSec;
}

STDMETHODIMP_(VOID) CHWSOpenState::SetLoopTime(DWORD dwLoopTime)
{
	//< LTH-040310-KO
	::UpdateWarTime();
	m_dwLoopTime = g_dwCurrWeekElapsedSec + dwLoopTime;
	//> LTH-040310-KO
}

STDMETHODIMP_(DWORD) CHWSOpenState::GetLoopTime()
{
	return m_dwLoopTime;
}

STDMETHODIMP CHWSOpenState::Update()
{
	::UpdateWarTime();

	//+[YonMy;map1; 20070625 ����]------------------------------------------------+
	m_n64RemainTime = GetRemainTime();	
	if ( !m_n64RemainTime )	return E_FAIL;
	//-----------------------------------------------------------------------------
	
	if (m_n64RemainTime % NW_REMAIN_TIME_UPDATE == 0) 
		::SendCMD_UPDATE_WARTIME(m_nWarfieldNo, NW_SOPEN, GetRemainTime());

	//< LTH-040322-KO 10�а������� ���� �ð��� �α׷� �����ڱ�!!
	if ((m_n64RemainTime % 600) == 0)
		g_pLogManager->SaveLogNeoNationWar(NNT_TIME_INFO, "[Current RemainTime] = LoopTime(%ld) - CurrTime(%ld) = %ld", \
		m_dwLoopTime, g_dwCurrWeekElapsedSec, m_n64RemainTime);
	//> LTH-040322-KO

	return S_OK;
}