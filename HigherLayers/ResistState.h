// ResistState.h: interface for the CResistState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESISTSTATE_H__65B83583_1513_45FC_BFED_15B04DDE37F7__INCLUDED_)
#define AFX_RESISTSTATE_H__65B83583_1513_45FC_BFED_15B04DDE37F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////////////////////////////////////////////////////////////
// ���� ���¿� ���� Ŭ����
class CResistState
{
  enum {MIN = 0, MAX = 500};

public:
	CResistState();

public:
	void IncBasicResist(const eRESIST_TYPE RTType, short nVolume);
	void DecBasicResist(const eRESIST_TYPE RTType, short nVolume);
	void SetBasicResist(const eRESIST_TYPE RTType, short nVolume);
	short GetBasicResist(const eRESIST_TYPE RTType)const { return m_naBasicResist[RTType]; }

	void IncExtResist(const eRESIST_TYPE RTType, short nVolume);
	void DecExtResist(const eRESIST_TYPE RTType, short nVolume);
	void SetExtResist(const eRESIST_TYPE RTType, short nVolume);
	short GetExtResist(const eRESIST_TYPE RTType)const;

private:
	short m_naBasicResist[MAX_RESIST_TYPE];//DB�� ��� �Ǵ� ���̽� ���� ���� ��
	short m_naExtentionResist[MAX_RESIST_TYPE];//�������� �����ۿ� ���ؼ� �ö� �������� ��(�������� �ʴ� ��)
};

//
///////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_RESISTSTATE_H__65B83583_1513_45FC_BFED_15B04DDE37F7__INCLUDED_)
