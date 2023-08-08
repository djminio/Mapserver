/**
 * @file	WarfieldFactory.cpp.
 *			implementation of the CWarfieldFactory class.
 */

//#include "..\stdafx.h"
#include "StdAfx.h"	// 컴파일 시간이 20여분 걸려서, 최적화 작업

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
 * @brief	IWarfieldDefine interface를 아이디(nObjectID)에 따라 특정 전쟁터로 생성시키는 함수.
 * @param	INT nObjectID. 전쟁터 식별 ID.
 * @param	VOID** ppVoid. 전쟁터를 생성하여 반환 할 포인터.
 * @return	STDMETHODIMP. 생성 성공 여부 반환.
 */
STDMETHODIMP CWarfieldFactory::Create(INT nObjectID, VOID** ppVoid)
{
	LPWARFIELDDEFINE lpWarfield = NULL;
	
	switch(nObjectID)
	{
	case WI_HADES_WARFIELD:		// 지하 전쟁터.
		lpWarfield = new CHadesWarfield;
		break;

	default:					// 아이디가 틀리면 생성 실패.
		::JustMsg("NO Warfield ID!! %d", nObjectID);
		return E_FAIL;
	}

	_ASSERT(NULL != lpWarfield);

	*ppVoid = (LPVOID)lpWarfield;

	return S_OK;
} 