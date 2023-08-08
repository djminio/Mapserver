/**
 * @file	WarfieldFactory.cpp.
 *			implementation of the CWarfieldFactory class.
 */

//#include "..\stdafx.h"
#include "StdAfx.h"	// ������ �ð��� 20���� �ɷ���, ����ȭ �۾�

#include "WarfieldFactory.h"
#include "HadesWarfield.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWarfieldFactory::CWarfieldFactory()
{
}

CWarfieldFactory::~CWarfieldFactory()
{
}

/**
 * @fn		CWarfieldFactory::Create().
 * @brief	IWarfieldDefine interface�� ���̵�(nObjectID)�� ���� Ư�� �����ͷ� ������Ű�� �Լ�.
 * @param	INT nObjectID. ������ �ĺ� ID.
 * @param	VOID** ppVoid. �����͸� �����Ͽ� ��ȯ �� ������.
 * @return	STDMETHODIMP. ���� ���� ���� ��ȯ.
 */
STDMETHODIMP CWarfieldFactory::Create(INT nObjectID, VOID** ppVoid)
{
	LPWARFIELDDEFINE lpWarfield = NULL;
	
	switch(nObjectID)
	{
	case WI_HADES_WARFIELD:		// ���� ������.
		lpWarfield = new CHadesWarfield;
		break;

	default:					// ���̵� Ʋ���� ���� ����.
		::JustMsg("NO Warfield ID!! %d", nObjectID);
		return E_FAIL;
	}

	_ASSERT(NULL != lpWarfield);

	*ppVoid = (LPVOID)lpWarfield;

	return S_OK;
} 