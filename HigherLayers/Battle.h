// Battle.h: interface for the CBattle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BATTLE_H__12C6402C_F88C_4B3B_ABC5_63EFDAF66C9D__INCLUDED_)
#define AFX_BATTLE_H__12C6402C_F88C_4B3B_ABC5_63EFDAF66C9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern MAGICTABLE Magic_Ref[Num_Of_Magic];
///////////////////////////////////////////////////////////////////////////////
// ���� ���̺� Ŭ����
class ISymbol
{ 
public:
	int GetMagicDamage(int nIndex) const { return Magic_Ref[nIndex].nHDPoint; } // CSD-030314
	int GetContinueTime(int nIndex) const { return Magic_Ref[nIndex].continue_Time; }
	int GetExhaustMana(int nIndex) const { return Magic_Ref[nIndex].exhaust_MP; }
	int GetRequireWidom(int nIndex) const { return Magic_Ref[nIndex].require_WP; }
	int GetRequireTactics(int nIndex) const { return Magic_Ref[nIndex].basic_magery; }
	int GetMagicType(int nIndex) const { return Magic_Ref[nIndex].magic_Type; }
	int GetResistType(int nIndex) const { return Magic_Ref[nIndex].nResist; }
	int GetSummonMax(int nIndex) const { return Magic_Ref[nIndex].nSummonMax; } // CSD-030314
	int GetRiseFall(int nIndex) const { return Magic_Ref[nIndex].nRiseFall; }
	int GetCombatAddition(int nIndex) const { return Magic_Ref[nIndex].nAddition; }
};
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ������ ���� Ŭ����
class CBattle : protected ISymbol
{ 
public:
	CBattle();
	virtual ~CBattle();
	
public:
	virtual bool Bind() = 0;
	virtual bool Elapse(CHARLIST* pTarget) = 0;
	virtual bool Execute() = 0;
	
public:
	int Relation(int nCaster, int nTarget) const;
	
public:
	void SetIndex(int nIndex) { m_nIndex = nIndex; }
	void SetBothID(WORD idCaster, WORD idTarget)
	{
		m_idCaster = idCaster;
		m_idTarget = idTarget;
	}
	
	void SetBothPtr(CHARLIST* pCaster, CHARLIST* pTarget)
	{
		m_pCaster = pCaster;
		m_pTarget = pTarget;
	}
	
	void SetCurrentTime(DWORD dwNow) { m_dwNow = dwNow; }
	void SetContinueTime(int nTime) { m_nContinue = nTime; }
	void SetPosition(int nX, int nY) { m_nX = nX, m_nY = nY; }
	
protected:
	void SendBattleDamage(WORD idTarget, BYTE nKind, int nDamage);
	void SendPacket(WORD idTarget);
	
protected:
	t_packet  m_packet;
	BYTE      m_nIndex;    
	WORD      m_idCaster;  // ������ ID
	WORD      m_idTarget;  // ����� ID
	CHARLIST* m_pCaster;   // ������
	CHARLIST* m_pTarget;   // �����
	DWORD     m_dwNow;     // ����ð�
	int       m_nContinue; // �����ð�          
	int       m_nX;        // ������ ����Ǵ� ��ġ�� X��ǥ
	int       m_nY;        // ������ ����Ǵ� ��ġ�� Y��ǥ
};
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ������ ���� Ŭ����
class CStrike : public CBattle
{ 
public:
	CStrike() { m_nType = 0; }
	virtual ~CStrike() {}
	
protected:
	int CalcAttack(BYTE nType) const;
	int CalcDefense(int nAttack) const;
	int CalcDamage(BYTE nType, int nDamage) const;
	
private:
	bool IsCurseEnable(CHARLIST* pTarget) const; // CSD-021024
	
private:
	int m_nType;
};
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ������ ���� Ŭ����
class CMagic : public CBattle
{ 
public:
  CMagic() { m_nType = 0; }
  virtual ~CMagic() {}

public:  
  void InitMagicResult(int nType);
  void SendMagicResult();

protected:
  int CalcPeriod() const;
  int CalcMaintain() const; // 030521 kyo
  int CalcHitDice() const;
  int CalcAttack(int nBase) const;
  int CalcDefense(int nAttack) const;
  int CalcDamage(BYTE nType, int nDamage) const;

private:
  int m_nType;
};
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ������ų�� ���� Ŭ����
class CCombat : public CBattle
{
public:
  CCombat() {}
  virtual ~CCombat() {}

public:
  bool AttackShort();          // �ܰŸ� ������ ����
  bool AttackMiddle();         // �߰Ÿ� ������ ����
  bool AttackLong(BYTE nType); // ��Ÿ� ������ ����

  void SendInit(BYTE nType, WORD idMaster); // CSD-TW-030606
  void SendResult(int nCmd, t_server_combat_result* pPacket);

protected:
    enum {ACTIVE = 0, PASSIVE = 1, RECOVERY = 2, }; // 030415 kyo

  int GetKind(CHARLIST* pSomeone) const;

  int CalcPeriod() const;
  int CalcMaintain() const;
  int CalcAttack(BYTE nType) const;
  int CalcDefense(int nAttack) const;
  int CalcDamage(BYTE nType, int nDamage) const;

  void Correct(BYTE nType, int& rDamage);
  bool Result(int nDamage, bool bAni=true); // 030415 kyo Ÿ���� �ൿ����
};
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ������ ���� Ŭ����
template<typename T1, typename T2> class TBinder : public T1
{ 
  typedef bool (T2::*LPFUNCTION)();
  typedef map<BYTE, LPFUNCTION> HASH;

public:
  void Resist(BYTE nNo, LPFUNCTION lpFunc)
  {
    m_tblHash.insert(HASH::value_type(nNo, lpFunc));
  }

  bool IsExist(BYTE nNo)
  {
    return (m_tblHash.find(nNo) != m_tblHash.end()) ? true:false;
  }

protected:
  HASH m_tblHash;
};
//
///////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_BATTLE_H__12C6402C_F88C_4B3B_ABC5_63EFDAF66C9D__INCLUDED_)