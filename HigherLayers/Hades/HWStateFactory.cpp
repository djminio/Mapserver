/**
 * @file	HWStateFactory.cpp.
 *			implementation of the CHWStateFactory class.
 */
//#include "..\stdafx.h"
#include "StdAfx.h"	//060109_kch 컴파일 시간이 20여분 걸려서, 최적화 작업

#include "HWStateFactory.h"
#include "HWState.h"

/**
 * @fn		CHWStateFactory::Create().
 * @brief	전쟁터 상태를 생성하기위한 함수.
 * @param	INT nObjectID. 상태 식별 ID.
 * @param	VOID** ppVoid. 특정 상태로 생성되어 반환 되는 포인터.
 * @return	STDMETHODIMP.
 */
//< LTH-040419-KO.
STDMETHODIMP CHWStateFactory::Create(INT nObjectID, VOID** ppVoid)
{
	LPWARFIELDSTATEDEFINE lpWarfieldState = NULL;
	
	switch(nObjectID)
	{
	case NW_PEACE:
		lpWarfieldState = new CHWPeaceState;
		break;

	case NW_WAR:
		lpWarfieldState = new CHWWarState;
		break;

	case NW_SOPEN:
		lpWarfieldState = new CHWSOpenState;
		break;

	default:
		::JustMsg("NO Warfield State ID!! %d", nObjectID);
		return E_FAIL;
	}

	_ASSERT(NULL != lpWarfieldState);
		
	*ppVoid = (LPVOID)lpWarfieldState;

	return S_OK;
} //> LTH-040419-KO.