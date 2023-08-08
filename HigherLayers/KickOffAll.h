// KickOffAll.h: interface for the CKickOffAll class.
//
// ������ : eSofnet DR����� ������ ���� �躴��
// ���� ����: �ʼ������� �ܰ��� �������� �ϱ� ���� ���۵�
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KICKOFFALL_H__B9C861E8_F427_438E_8462_41AC54A785DD__INCLUDED_)
#define AFX_KICKOFFALL_H__B9C861E8_F427_438E_8462_41AC54A785DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKickOffAll  
{
public:
	bool StopKicking();
	bool IsKicking() { return m_bIsKicking; };
	void KickOffSeverlUser();
	bool InitKickOffUserAll();
	CKickOffAll();
	virtual ~CKickOffAll();

protected:
	bool m_bIsAllKick;		// BBD 040401
	int m_nKickAmount1Time;
	bool m_bIsKicking;
};

#endif // !defined(AFX_KICKOFFALL_H__B9C861E8_F427_438E_8462_41AC54A785DD__INCLUDED_)
