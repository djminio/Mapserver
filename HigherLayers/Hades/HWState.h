#pragma once


#include "IWarfieldDefine.h"

/**
 * @class	CHWPeaceState.
 * @brief	평화 상태를 담당하는 class. IWarfieldStateDefine를 상속 받는다.
 */
//< LTH-040419-KO.
class CHWPeaceState : public IWarfieldStateDefine
{
public:
	CHWPeaceState();
	~CHWPeaceState() {}

	STDMETHOD_(VOID, Init)(THIS_ INT nWarfieldNo);
	STDMETHOD_(VOID, SetRemainTime)(THIS_ __int64 n64RemainTime);
	STDMETHOD_(__int64, GetRemainTime)(THIS);
	STDMETHOD_(VOID, SetLoopTime)(THIS_ DWORD dwLoopTime);
	STDMETHOD_(DWORD, GetLoopTime)(THIS);
	STDMETHOD(Update)(THIS);
};
//> LTH-040419-KO.

//--------------------------------------------------------------------
/**
 * @class	CHWWarState.
 * @brief	전쟁 상태를 담당하는 class. IWarfieldStateDefine를 상속 받는다.
 */
//< LTH-040419-KO.
class CHWWarState : public IWarfieldStateDefine
{
public:
	CHWWarState();
	~CHWWarState() {}

	STDMETHOD_(VOID, Init)(THIS_ INT nWarfieldNo);
	STDMETHOD_(VOID, SetRemainTime)(THIS_ __int64 n64RemainTime);
	STDMETHOD_(__int64, GetRemainTime)(THIS);
	STDMETHOD_(VOID, SetLoopTime)(THIS_ DWORD dwLoopTime);
	STDMETHOD_(DWORD, GetLoopTime)(THIS);
	STDMETHOD(Update)(THIS);
};
//> LTH-040419-KO.

//-----------------------------------------------------------------
/**
 * @class	CHWSOpenState.
 * @brief	비밀 지역 오픈 상태를 담당하는 class. IWarfieldStateDefine를 상속 받는다.
 */
//< LTH-040419-KO.
class CHWSOpenState : public IWarfieldStateDefine
{
public:
	CHWSOpenState();
	~CHWSOpenState() {}

	STDMETHOD_(VOID, Init)(THIS_ INT nWarfieldNo);
	STDMETHOD_(VOID, SetRemainTime)(THIS_ __int64 n64RemainTime);
	STDMETHOD_(__int64, GetRemainTime)(THIS);
	STDMETHOD_(VOID, SetLoopTime)(THIS_ DWORD dwLoopTime);
	STDMETHOD_(DWORD, GetLoopTime)(THIS);
	STDMETHOD(Update)(THIS);
};
//> LTH-040419-KO.