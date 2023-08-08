#pragma once

#include "IFactoryDefine.h"
#include "IWarfieldDefine.h"

/**
 * @class	CWarfieldFactory.
 * @brief	IWarfieldDefine interface를 특정 전쟁터로 생성 시키는 Factory class.
 *			역시 IFactoryDefine에게서 상속 받았다 나중에 Factory Manager class를 위해.
 */
//< LTH-040419-KO.
class CWarfieldFactory : public IFactoryDefine  
{
public:
	CWarfieldFactory();
	virtual ~CWarfieldFactory();

public:
	STDMETHOD(Create)(THIS_ INT nObjectID, VOID** ppVoid);
};
//> LTH-040419-KO.

/**
 * @def		CWarfieldFactory * LPWARFIELDFACTORY.
 * @brief	포인터 변수의 편리한 사용을 위해 정의.
 */
//< LTH-040419-KO.
typedef CWarfieldFactory * LPWARFIELDFACTORY;
//> LTH-040419-KO.