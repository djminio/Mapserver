#pragma once

#include "IFactoryDefine.h"
#include "IWarfieldDefine.h"

/**
 * @class	CWarfieldFactory.
 * @brief	IWarfieldDefine interface�� Ư�� �����ͷ� ���� ��Ű�� Factory class.
 *			���� IFactoryDefine���Լ� ��� �޾Ҵ� ���߿� Factory Manager class�� ����.
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
 * @brief	������ ������ ���� ����� ���� ����.
 */
//< LTH-040419-KO.
typedef CWarfieldFactory * LPWARFIELDFACTORY;
//> LTH-040419-KO.