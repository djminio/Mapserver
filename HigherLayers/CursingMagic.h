// CursingMagic.h: interface for the CCursingMagic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURSINGMAGIC_H__050B5373_6DBA_46BA_85D6_8BB356949B0B__INCLUDED_)
#define AFX_CURSINGMAGIC_H__050B5373_6DBA_46BA_85D6_8BB356949B0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000 

#include "Battle.h"
///////////////////////////////////////////////////////////////////////////////
// ���ְ迭 ����
class CCursingMagic : public TBinder<CMagic, CCursingMagic>
{
public:
	CCursingMagic();
	virtual ~CCursingMagic();
	
public:
	virtual bool Bind();
	virtual bool Elapse(CHARLIST* pTarget);
	
public:
	virtual bool Execute() 
	{ 
		return (!IsExist(m_nIndex)) ? false:(*this.*m_tblHash[m_nIndex])(); 
	}
	
public:
	bool Confusion();          // ���� 1�迭 ����
	bool AbsoluteParalysis();
	bool Stonely();
	bool Curse();
	bool AreaParalysis();
	bool AreaConfusion();
	bool Slow();               // ���� 2�迭 ����  
	bool SpiderWeb(); 
	bool AreaSlow();
	bool FeatherOfCurse();
	bool Intoxication();       // ���� 3�迭 ����
	bool ToxicCloud();
	bool VampirePoison();
	bool CurseOfHell();
	bool AreaPoison();
	bool LostSight();          // ���� 4�迭 ����
	bool AuthorityLostSight();
	bool DiseaseInduce();      // ���� 5�迭 ����
	bool VampireTouch();
	bool LifeDrain();
	bool Gazer(); // 030509 kyo
	
protected:
	bool CheckDeath(int nDamage);
	void CheckStun(CHARLIST* pTarget);   // CSD-021024
	void CheckSlow(CHARLIST* pTarget);   // CSD-021024
	void CheckPoison(CHARLIST* pTarget); // CSD-021024
	void CheckBlind(CHARLIST* pTarget);  // CSD-021024
	void CheckFreeze(CHARLIST* pTarget); // CSD-021024
	
private:
	bool IsReturn(CHARLIST* pTarget) const; // CSD-021104
};
//
///////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_CURSINGMAGIC_H__050B5373_6DBA_46BA_85D6_8BB356949B0B__INCLUDED_)
