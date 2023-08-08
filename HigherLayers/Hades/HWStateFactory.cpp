/**
 * @file	HWStateFactory.cpp.
 *			implementation of the CHWStateFactory class.
 */
//#include "..\stdafx.h"
#include "StdAfx.h"	//060109_kch ������ �ð��� 20���� �ɷ���, ����ȭ �۾�

#include "HWStateFactory.h"
#include "HWState.h"

/**
 * @fn		CHWStateFactory::Create().
 * @brief	������ ���¸� �����ϱ����� �Լ�.
 * @param	INT nObjectID. ���� �ĺ� ID.
 * @param	VOID** ppVoid. Ư�� ���·� �����Ǿ� ��ȯ �Ǵ� ������.
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