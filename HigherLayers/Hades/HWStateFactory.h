#pragma once

#include "IFactoryDefine.h"

/**
 * @class	CHWStateFactory.
 * @brief	������ ���¸� �����ϱ� ���� factory class.
 *			IFactoryDefine interface�� ��� �޴´�.
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