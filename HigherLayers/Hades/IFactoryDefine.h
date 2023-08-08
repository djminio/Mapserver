#pragma once

/**
 * @interface	IFactoryDefine
 * @brief		������ Factory class�� ���ʰ� �Ǵ� interface.
 */
//< LTH-040419-KO.
interface IFactoryDefine
{
public:
	STDMETHOD(Create)(THIS_ INT nObjectID, VOID** ppVoid) PURE;
};
//> LTH-040419-KO.

typedef IFactoryDefine * LPFACTORYDEFINE;