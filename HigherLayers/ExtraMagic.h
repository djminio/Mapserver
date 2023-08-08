// ExtraMagic.h: interface for the CExtraMagic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXTRAMAGIC_H__CBC255C8_0BBD_42E9_B761_616AD99FCDC4__INCLUDED_)
#define AFX_EXTRAMAGIC_H__CBC255C8_0BBD_42E9_B761_616AD99FCDC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Battle.h"
///////////////////////////////////////////////////////////////////////////////
// ��Ÿ�迭 ���� 
class CExtraMagic : public TBinder<CMagic, CExtraMagic>
{ 
public:
	CExtraMagic();
	virtual ~CExtraMagic();
	
public:
	virtual bool Bind();
	
public:
	virtual bool Execute() 
	{ 
		return (!IsExist(m_nIndex)) ? false:(*this.*m_tblHash[m_nIndex])(); 
	}
	
	virtual bool Elapse(CHARLIST* pTarget) 
	{ 
		return true; 
	}
	
public:
	bool Phasing();             // �ð� �迭 ����
	bool Teleport();
	bool MemorizingLocation();
	bool TownPortal();
	bool MultiPort();
	bool VampireDodge();
	bool LowMonsterRecall();    // ��ȯ �迭 ����
	bool MiddleMonsterRecall();
	bool SummoningSkeleton();
	bool SummoningUndead();
	bool RecallFollow();
	bool MagicalTrap();         // ��Ÿ �迭 ����
	bool MagicDetect();
	bool Anthem();
	bool InfluenceDivine();
	bool VoiceSoul();
	bool Appreciate();
	bool Pray();				// ���� �ø��� �迭 ���� // 030415 kyo
	
protected:
	enum {MAX_COUNT = 10};
	void GetArea(int& rX, int& rY);
	bool GetRecallPlace(int nSrcX, int nSrcY, int& rDstX, int& rDstY); // CSD-030324
};
//
///////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_EXTRAMAGIC_H__CBC255C8_0BBD_42E9_B761_616AD99FCDC4__INCLUDED_)
