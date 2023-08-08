// GMMgr.h: interface for the CGMMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMMGR_H__53127C18_C708_4D19_96E4_BAA47D361D6F__INCLUDED_)
#define AFX_GMMGR_H__53127C18_C708_4D19_96E4_BAA47D361D6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Dr_Network.h"

class CGMMgr  
{
public:
	CGMMgr();
	virtual ~CGMMgr();
public:
	int		CanGmRegist( const int iGmIndex, CHARLIST *ch );
	bool	IsMerchant(CHARLIST *ch)const;
	int		IsAllGM(CHARLIST *ch)const;//1�� 2�� �� ����?
	int		IsSkillMaster(CHARLIST *ch)const;//�⼺�ΰ�? �⼺�̸� ��ų �ѹ��� �Ѱܶ�
};
extern CGMMgr GMMgr;
#endif // !defined(AFX_GMMGR_H__53127C18_C708_4D19_96E4_BAA47D361D6F__INCLUDED_)
