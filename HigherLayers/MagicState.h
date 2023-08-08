// MagicState.h: interface for the CMagicState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAGICSTATE_H__1253A149_5DFB_439E_9CEE_DA046405F173__INCLUDED_)
#define AFX_MAGICSTATE_H__1253A149_5DFB_439E_9CEE_DA046405F173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////////////////////////////////////////////////////////////
// ���� ���� ����� ���� Ŭ����
class CCharState
{
public:
	CCharState() { Clear(); }
	
public:
	void Clear()
	{	// ���� �ʱ�ȭ 
		m_dwTime = 0, m_nRatio = 0;
	}
	
	BYTE GetRatio() const { return m_nRatio; }
	
	void SetState(DWORD dwTime, BYTE nRatio)
	{	// ���� �缳�� 
		m_dwTime = dwTime, m_nRatio = nRatio;
	}
	
	int Convert(int nValue) const 
	{	// �Է°��� ������ ȯ��
		return nValue*m_nRatio/100; 
	}
	
	bool IsMax() const 
	{
		return (m_dwTime > 0 && m_nRatio == 100) ? true:false;
	}
	
	bool IsContinue() const
	{	// ���� ���� ���� �˻�
		return (m_dwTime > 0) ? true:false; 
	}
	
	bool IsContinue(DWORD dwTime) const 
	{	// ���� ���� ���� �˻�
		return (m_dwTime > dwTime) ? true:false; 
	}
	
	bool IsBound() const 
	{ // ����(0 ~ 100%) �˻�
		return (m_nRatio >= 0 && m_nRatio <= 100) ? true:false; 
	}
	
private:
	DWORD  m_dwTime; // ���ӽð�
	BYTE   m_nRatio; // ����(0 ~ 100%)
};

//
///////////////////////////////////////////////////////////////////////////////
#define NAT_SPEED_UP  0
#define NAT_STATUS_UP 1
#define NAT_LIFE_UP   2
#define NAT_NORMAL    3
#define DELAY         4
///////////////////////////////////////////////////////////////////////////////
// ������ ������ �� �ִ� �ð���
struct MAGIC_DURATION
{	//< CSD-TW-030606
	CCharState apShort;     // �ܰŸ� ������ ���ݷ�
	CCharState apMiddle;    // �߰Ÿ� ������ ���ݷ�
	CCharState apLong;      // ��Ÿ� ������ ���ݷ�
	
	CCharState dpShort;     // �ܰŸ� ������ ����
	CCharState dpMiddle;    // �߰Ÿ� ������ ����
	CCharState dpLong;      // ��Ÿ� ������ ����
	
	CCharState dpFire;      // �Ұ迭 ���ݸ���  ����
	CCharState dpIce;       // �����迭 ���ݸ��� ����
	CCharState dpElect;     // ���ݰ迭 ���ݸ��� ����
	CCharState dpHoly;      // �ŷ°迭 ���ݸ��� ����
	
	CCharState dpCurse1;    // ���� 1�迭 ���� ����
	CCharState dpCurse2;    // ���� 2�迭 ���� ����
	CCharState dpCurse3;    // ���� 3�迭 ���� ����
	CCharState dpCurse4;    // ���� 4�迭 ���� ����
	CCharState dpCurse5;    // ���� 5�迭 ���� ����
	CCharState dpFreeze;    // CSD-021216 : �� ���� ���� ����
    
	CCharState amplify;     // ���� ���� ������
	CCharState speedUp;     // �̵��ӵ� ����   
	CCharState speedDown;   // �̵��ӵ� ����  
	
	CCharState avoid;       // ȸ����
	CCharState agility;     // ��ø��
	
	DWORD dwCurse1;             // ���� 1�迭 ���� ���� 
	DWORD dwCurse2;             // ���� 2�迭 ���� ���� 
	DWORD dwCurse3;             // ���� 3�迭 ���� ���� 
	DWORD dwCurse4;             // ���� 4�迭 ���� ���� 
	DWORD dwFreeze;             // CSD-021024 : �� ���� ���� ����
	
	DWORD dwNormalProtect;      // �Ϲ� ��ȣ�迭 ���� ����
	DWORD dwSpecialProtect;     // Ư�� ��ȣ�迭 ���� ���� 
	DWORD dwExceptProtect;      // ���� ��ȣ�迭(��� ������ ����) ���� ����
	DWORD dwAttackDelay;	      // ���� �ӵ� ����(ĳ���Ͱ� ���� �Ҽ� �ִ� ����)
	DWORD dwDontMove;           // �̵��� ���� ����
	DWORD dwDontAttack;		      // �Ϲ����� ������ ���� ����
	DWORD dwDontCasting;		    // ���� ĳ������ ���� ����
	DWORD dwDontMiss;           // ��� ������ ���ݰ� ������ ����
	DWORD dwBlocking;           // �ܺο� ���ܵǴ� ����
	DWORD dwLight;              // ������ ���� ������ ����
	DWORD dwMagicDamageToMana;  // ����� ���� ������ ������ �Ҹ��Ͽ� ���Ƴ�
	DWORD dwReturnMagic;		    // ������ ȿ���� �����ڿ��� �ǵ���
	DWORD dwTransparency;		    // ĳ���Ͱ� �����ϰ� �� 
	DWORD dwLifeUp;             // ���� �ð����� Life�� �ö�
	DWORD dwStrikeReflect;      // CSD-021015 : �������� ������ �ݻ�
	DWORD dwMagicReflect;       // CSD-021015 : �������� ������ �ݻ�
	DWORD dwNature[NAT_NORMAL]; // ���� ��ȭ ����  
	DWORD dwCombatState;        // ������ų �Ӽ� ����
	DWORD dwUpDivineMana;		// ������ �ø���.	// 030415 kyo 
	DWORD dwCombatRecovery;		//cp�� �ø��� hp�� ���δ�.	// 030415 kyo 
};	//> CSD-TW-030606
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ���� ���¿� ���� Ŭ����
class CMagicState : public MAGIC_DURATION
{ 
public:
	enum 
	{	//< CSD-021216
		CURSE_NONE = 0x00,   // 000000
		CURSE_1 = 0x01,      // 000001
		CURSE_2 = 0x02,      // 000010
		CURSE_3 = 0x04,      // 000100
		CURSE_4 = 0x08,      // 001000
		CURSE_5 = 0x10,      // 010000
		CURSE_FREEZE  = 0x20 // 100000
	};	//> CSD-021216
	
public:
	CMagicState()
	{
		m_nExecuteMagic = 0; // Last executed spell
		m_nCastMagic = 0;
		m_dwExecuteTime = 0; // Time last spell was executed
		m_cResultMismatch = 0;
		m_cMagicResult = 0;
	}
	
public:
	void Clear();
	void Recovery(DWORD dwNow);
	
	bool CheckAttack(BYTE nAttack, DWORD dwNow);
	bool CheckStart(BYTE nMagic, DWORD dwNow);
	bool CheckDoing(BYTE nMagic, DWORD dwNow);
	bool CheckEnd(BYTE nMagic, DWORD dwNow);
	bool CheckDelay(BYTE nMagic, DWORD dwNow);
	bool CheckCombat(BYTE nCombat, DWORD dwNow);
	bool CheckMultiEffect(BYTE nMagic); //Antispellhack - Thralas

	void InitCurse();
	void ClearCurse(BYTE nType);
	void ApplyCurse(BYTE nType, BYTE nState, DWORD dwTime = 0);
	
	int GetAvailRange(BYTE nMagic) const;
	int GetCastReady(BYTE nMagic) const;
	int GetCastContinue(BYTE nMagic) const;
	int GetDualStep(BYTE nMagic) const; // 030415 kyo 
	
	void ClearTransMap();
	void GetTransMap(int& rPort, int& rX, int& rY) const;
	void SetTransMap(int nPort, int nX, int nY);
	
	void ClearCombat(BYTE nSelect = 0);
	void SetActiveCombat(BYTE nCombat, int nCount);
	void SetPassiveCombat(BYTE nCombat, DWORD dwPeriod);
	void SetRecoveryCombat(BYTE nCombat, DWORD dwPeriod); // 030415 kyo 
	
	void SetPhysicalAttack(DWORD dwTime, BYTE nShort, BYTE nMiddle, BYTE nLong);
	void SetPhysicalDefense(DWORD dwTime, BYTE nShort, BYTE nMiddle, BYTE nLong);
	void SetMagicalDefense(DWORD dwTime, BYTE nFire, BYTE nIce, BYTE nElect, BYTE nHoly);
	void SetCurseDefense(DWORD dwTime, BYTE nSet);
	
	void ClearNpcRun();
	void ClearNpcStatusUp();
	void ClearNpcRecovery();
	void SetNpcRun(DWORD dwTime, int nSpeed);
	void SetNpcStatusUp(DWORD dwTime, int nAttack, int nDefense, int nSpeed);
	void SetNpcRecovery(DWORD dwTime, int nLife);
	
	void CorrectShortDamage(int& rDamage, int nPlus = 0, int nMinus = 0) const;
	void CorrectMiddleDamage(int& rDamage, int nPlus = 0, int nMinus = 0) const;
	void CorrectLongDamage(int& rDamage, int nPlus = 0, int nMinus = 0) const;
	
	void CorrectFireDamage(int& rDamage, int nPlus = 0, int nMinus = 0) const;
	void CorrectIceDamage(int& rDamage, int nPlus = 0, int nMinus = 0) const;
	void CorrectElectDamage(int& rDamage, int nPlus = 0, int nMinus = 0) const;
	void CorrectHolyDamage(int& rDamage, int nPlus = 0, int nMinus = 0) const;
	void CorrectMovePlus(int& rMove, int nPlus) const;
	void CorrectMoveMinus(int& rMove, int nMinus) const;
	
public:
	BYTE GetMagic() const { return m_nMagic; }
	BYTE GetActiveCombat() const  { return m_nActive; }
	BYTE GetPassiveCombat() const { return m_nPassive; }
	BYTE GetCombatCount() const { return m_nCount; }
	BYTE GetRecoveryCombat() const { return m_nRecovery; }// 030415 kyo 
	DWORD GetRecoveryCombatTime() const { return dwCombatRecovery;}// 030415 kyo 
	int	 GetRecoveryCombatDecHPRate(int nLevel); // 030514 kyo 5:5%,7:10%,10:15%
	
	int IncCombatCount() { return ++m_nCount; }
	int DecCombatCount() { return --m_nCount; }
	
	void ClearMagic() { m_nMagic = 0; }
	void ClearMagic(bool bLock) { m_bLock = bLock; }

	void InitActiveCombat() { m_nActive = 0; } // CSD-TW-030623
	void InitPassiveCombat() { m_nPassive = 0; } // CSD-TW-030623
	void InitRecoveryCombat() { m_nRecovery = 0; } // CSD-TW-030623

	void ClearActiveState() { m_nCount = 0; } // CSD-TW-030623
	void ClearPassiveState() { dwCombatState = 0; } // CSD-TW-030623
	void ClearRecoveryState() { dwCombatRecovery = 0, m_nRecoveryPoint = 0; } // CSD-TW-030623
	
	int GetShortAttack() const { return apShort.GetRatio(); }
	int GetMiddleAttack() const { return apMiddle.GetRatio(); }
	int GetLongAttack() const { return apLong.GetRatio(); }
	int GetShortDefense() const { return dpShort.GetRatio(); }
	int GetMiddleDefense() const { return dpMiddle.GetRatio(); }
	int GetLongDefense() const { return dpLong.GetRatio(); }
	int GetMagicAmplify() const { return amplify.GetRatio(); }
	int GetFireDefense() const { return dpFire.GetRatio(); }
	int GetIceDefense() const { return dpIce.GetRatio(); }
	int GetElectDefense() const { return dpElect.GetRatio(); }
	int GetHolyDefense() const { return dpHoly.GetRatio(); }
	
	BYTE GetNature() const { return m_nNature; }
	BYTE GetState() const { return m_nState; }
	void SetState(BYTE nState) { m_nState = nState; }
	void AddState(BYTE nState) { m_nState |= nState; }
	void DelState(BYTE nState) { m_nState &= ~nState; }
	// Life ������
	int GetLifeUp() const { return m_nLifeUp; }
	// �ߵ��Ǿ��� �� HP�� ���ҵǴ� �� ���
	WORD GetPoisonedPoint() const { return m_wPoisonedPoint; }
	WORD GetPoisonedCount() const { return m_wPoisonedCount; }
	// �ߵ��Ǿ��� �� HP�� ���ҵǴ� �� ����
	void SetPoisonedPoint(WORD wPoint = 0) { m_wPoisonedPoint = wPoint; }
	void SetPoisonedCount(WORD wCount = 0) { m_wPoisonedCount = wCount; }
	void IncPoisonedCount() { ++m_wPoisonedCount; }
	void DecPoisonedCount() { --m_wPoisonedCount; }
	
	// �ڵ� hp�ٿ� 
	int	 GetRecoveryCPCount() const { return m_nRecoveryPoint;} // 030415 kyo 
	void SetRecoveryCPCount(int nCount = 0) { m_nRecoveryPoint = nCount; } // 030415 kyo 
	void IncRecoveryCPCount() { ++m_nRecoveryPoint; } // 030415 kyo 
	void DecRecoveryCPCount() { --m_nRecoveryPoint; } // 030415 kyo 

	bool IsState(BYTE nState) const { return (m_nState == nState) ? true:false; }
	bool IsPhysicalDamage() const
	{	// ������ �������� 100% ����ϴ��� ����
		return (dpShort.IsMax() && dpMiddle.IsMax() && dpLong.IsMax()) ? false:true;
	}  
	// ������ ��� �������� ���� �˻�
	bool IsPerfect() const { return (dwExceptProtect > 0) ? true:false; }
	// ȸ���� �Ǵ� �������� ���� �˻�
	bool IsReturn() const { return (dwReturnMagic > 0) ? true:false; }
	// �⵵ �������� ���� �˻�
	bool IsDivineUp() const { return (dwUpDivineMana > 0) ? true:false; } // CSD-TW-030606
	// ��ȭ �������� ���� �˻�
	bool IsStone() const { return (dwBlocking > 0) ? true:false; }
	// �� ���� ���� ���� �˻�
	bool IsFreeze() const { return (dwAttackDelay > 0) ? true:false; }
	// �����Ұ� �������� ���� �˻�
	bool IsCasting() const { return (dwDontCasting > 0) ? false:true; }
	// NPC�� ��� ���� ����� �������� ���� �˻�
	bool IsCasting(DWORD dwNow) const { return (m_dwCasting > dwNow) ? false:true; }
	// CSD-021015 : ���� �ð����� Life�� �ö�
	bool IsLifeUp() const { return (dwLifeUp > 0) ? true:false; }
	// CSD-021015 : �������� �ݻ� ���� �˻�
	bool IsStrikeReflect() const { return (dwStrikeReflect > 0) ? true:false; }
	// CSD-021015 : �������� �ݻ� ���� �˻�
	bool IsMagicReflect() const { return (dwMagicReflect > 0) ? true:false; }
	// ������ų �Ӽ� ���� ����
	bool IsPassiveCombatState() const { return (dwCombatState <= 0) ? false:true; } // CSD-TW-030606
	bool IsRecoveryCombatState() const { return (dwCombatRecovery <= 0) ? false:true; } // CSD-TW-030606
	// ���� ������ �ִ��� ���� �˻�
	bool IsCurseDefense(BYTE nType) const
	{
		switch (nType)
		{ //< CSD-021216
		case 41: return (dpCurse1.IsContinue()) ? true:false;
		case 42: return (dpCurse2.IsContinue()) ? true:false;
		case 43: return (dpCurse3.IsContinue()) ? true:false;
		case 44: return (dpCurse4.IsContinue()) ? true:false;
		case 45: return (dpCurse5.IsContinue()) ? true:false;
		case 46: return (dpFreeze.IsContinue()) ? true:false; 
		} //> CSD-021216
		
		return false;
	}
	// ���ְ迭 ���� �������� ���� �˻�
	bool IsCurse(BYTE nType) const
	{	//< CSD-021024 
		switch (nType)
		{
		case 1: return (dwCurse1 > 0) ? true:false;
		case 2: return (dwCurse2 > 0) ? true:false;
		case 3: return (dwCurse3 > 0) ? true:false;
		case 4: return (dwCurse4 > 0) ? true:false;
		case 6: return (dwFreeze > 0) ? true:false;
		}
		
		return false;
	}	//> CSD-021024
	
	bool IsCurse(BYTE nType, DWORD dwNow) const
	{	//> CSD-021024
		switch (nType)
		{
		case 1: return (dwCurse1 < dwNow) ? true:false;
		case 2: return (dwCurse2 < dwNow) ? true:false;
		case 3: return (dwCurse3 < dwNow) ? true:false;
		case 4: return (dwCurse4 < dwNow) ? true:false;
		case 6: return (dwFreeze < dwNow) ? true:false;
		}
		
		return false;
	}	//> CSD-021024
	// �Ϲ� ��ȣ�迭 �������� ���� �˻�
	bool IsNormalProtect() const { return (dwNormalProtect > 0) ? true:false; }
	// Ư�� ��ȣ�迭 �������� ���� �˻�
	bool IsSpecialProtect() const { return (dwSpecialProtect > 0) ? true:false; }
	// �̵� ��� ����� �����Ǿ����� ���� �˻�
	bool IsTransMap() const { return (m_nTransPort > 0) ? true:false; }
	// ������ų ��� ���� ȸ�� �˻�
	bool IsCount() const { return (m_nCount > 0) ? true:false; }
	// ����̱� ���� �˻�
	bool IsTamedNpc() const { return m_bTamed; }
	void SetTamed(bool bTamed) { m_bTamed = bTamed; }
	// ��ȯ ���� ���� �˻�
	bool IsSummonMonster() const { return m_bSummon; }
	void SetSummonMonster(bool bSummon) { m_bSummon = bSummon; }
	
public:
	/* Testing
	BYTE  m_nAttack;		   // 020425 YGI from acer
	BYTE  m_nMagic;        // ���� ��ȣ   
	BYTE  m_nActive;       // �ܹ߼��� ������ų ��ȣ
	BYTE  m_nPassive;      // �������� ������ų ��ȣ
	BYTE  m_nRecovery;		// ȸ�� ������ų  // 030415 kyo 
	BYTE  m_nCount;        // ������ų ��� ȸ�� 
	DWORD m_dwAttack;		   // 020425 YGI from acer
	DWORD m_dwCasting;     // ���� ���� ���� �ð�
	DWORD m_dwContinue;		// ���� ������ ������ �ð�
	*/

	BYTE  m_nExecuteMagic; // Last executed spell
	BYTE  m_nCastMagic;
	DWORD m_dwExecuteTime; // Time last spell was executed
	int m_cResultMismatch;
	int m_cMagicResult;

	class XSummonMgr
	{	// ��ȯ�� ���� ���� Ŭ����
		typedef vector<WORD> VECTOR;
		
	public:
		XSummonMgr() : m_nFollow(0), m_idMaster(0) {}
		
	public:
		BYTE GetFollow() const { return m_nFollow; }
		void SetFollow(BYTE nFollow) { m_nFollow = nFollow; }
		WORD GetMaster() const { return m_idMaster; }
		void SetMaster(WORD idMaster) { m_idMaster = idMaster; }
		// ��ȯ�� ������ �� ����
		void Increase(WORD wID) 
		{ 
			m_vtBuffer.push_back(wID); 
		}
		// ��ȯ�� ������ �� ����
		void Decrease(WORD wID)  
		{ 
			m_vtBuffer.erase(remove(m_vtBuffer.begin(), m_vtBuffer.end(), wID)); 
		}
		// ��ȯ ���Ϳ��� ���
		void Command(bool (*pFunc)(WORD, WORD))
		{
			pointer_to_binary_function<WORD, WORD, bool> pf(pFunc);
			for_each(m_vtBuffer.begin(), m_vtBuffer.end(), bind2nd(pf, m_idMaster));
		}
		// ��ȯ ���� ���� ����
		void Remove(void (*pFunc)(WORD))
		{
			for_each(m_vtBuffer.begin(), m_vtBuffer.end(), pFunc);
			m_vtBuffer.clear();
		}

		// ��ȯ�� ������ �� ���
		int Count() const { return m_vtBuffer.size(); }
		// ��ȯ�� ���Ͱ� �����ϴ��� ���� �˻�
		bool IsExist() const { return !m_vtBuffer.empty(); }
		
	private:
		VECTOR m_vtBuffer;
		BYTE   m_nFollow;
		WORD   m_idMaster;
	}	m_xSummon;
	
	WORD GetFollow() const { return m_xSummon.GetFollow(); }
	void SetFollow(BYTE nFollow) { m_xSummon.SetFollow(nFollow); }
	WORD GetMaster() const { return m_xSummon.GetMaster(); }
	void SetMaster(WORD idMaster) { m_xSummon.SetMaster(idMaster); }
	
protected:
	BYTE  m_nNature;        // ���� ����
	BYTE  m_nState;         // ���� ����
	WORD  m_wPoisonedPoint; // �ߵ��Ǿ��� �� HP�� ���ҵǴ� ��
	WORD  m_wPoisonedCount; // �ߵ��Ǿ��� �� HP�� ���� ��
	int	  m_nRecoveryPoint; // �ڵ�cpȸ������ ���ʴ� hp�� �����°�? // 030415 kyo 
	int   m_nTransPort;     // �̵��� �ʿ� ���� ����
	int   m_nTransX;        // �̵� ��ǥ
	int   m_nTransY;
	int   m_nLifeUp;        // Life ������
	bool  m_bTamed;         // ���̹� ����  
	bool  m_bSummon;        // ��ȯ ���� ����
		
private:
	bool  m_bLock;
	BYTE  m_nAttack;		   // 020425 YGI from acer
	BYTE  m_nMagic;        // ���� ��ȣ
	BYTE  m_nActive;       // �ܹ߼��� ������ų ��ȣ
	BYTE  m_nPassive;      // �������� ������ų ��ȣ
	BYTE  m_nRecovery;		// ȸ�� ������ų  // 030415 kyo 
	BYTE  m_nCount;        // ������ų ��� ȸ�� 
	DWORD m_dwAttack;		   // 020425 YGI from acer
	DWORD m_dwCasting;     // ���� ���� ���� �ð�
	DWORD m_dwContinue;		// ���� ������ ������ �ð�
	DWORD m_dwFireWall;    // ȭ������ �����Ǵ� �ð�
	DWORD m_dwIceWall;     // �������� �����Ǵ� �ð�
};
//
///////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_MAGICSTATE_H__1253A149_5DFB_439E_9CEE_DA046405F173__INCLUDED_)