#pragma once

#include "IFactoryDefine.h"

/**
 * @class	CHWStateFactory.
 * @brief	전쟁터 상태를 생성하기 위한 factory class.
 *			IFactoryDefine interface를 상속 받는다.
 */
//< LTH-040419-KO.
class CHWStateFactory : public IFactoryDefine  
{
public:
	CHWStateFactory() {}
	virtual ~CHWStateFactory() {}

public:
	STDMETHOD(Create)(THIS_ INT nObjectID, VOID** ppVoid);
};
//> LTH-040419-KO.

typedef CHWStateFactory * LPHWSTATEFACTORY;