#pragma once

/**
 * @interface	IFactoryDefine
 * @brief		전쟁터 Factory class의 기초가 되는 interface.
 */
//< LTH-040419-KO.
interface IFactoryDefine
{
public:
	STDMETHOD(Create)(THIS_ INT nObjectID, VOID** ppVoid) PURE;
};
//> LTH-040419-KO.

typedef IFactoryDefine * LPFACTORYDEFINE;