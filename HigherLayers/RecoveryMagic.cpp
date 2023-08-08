// RecoveryMagic.cpp: implementation of the CRecoveryMagic class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "RecoveryMagic.h"


#include "..\HigherLayers\OP_Magic.h"


///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////////////////////////////////////

CRecoveryMagic::CRecoveryMagic()
{
	
}

CRecoveryMagic::~CRecoveryMagic()
{
	
}

///////////////////////////////////////////////////////////////////////////////
// Public Method
///////////////////////////////////////////////////////////////////////////////

bool CRecoveryMagic::Bind()
{
	Resist(LIFE_UP, &CRecoveryMagic::Healing);
	Resist(DECIPHER, &CRecoveryMagic::Decipher);
	Resist(HEAL_DISEASE, &CRecoveryMagic::HealDisease);
	Resist(GREAT_HEAL, &CRecoveryMagic::GreatHeal);
	Resist(REMOVE_CURSE, &CRecoveryMagic::RemoveCurse);
	Resist(RESTORE_AUTHORITY, &CRecoveryMagic::RestoreAuthority);
	Resist(MIRACLE_RECOVER, &CRecoveryMagic::MiracleRecover);
	Resist(RELIEF_AUTHORITY, &CRecoveryMagic::ReliefAuthority);
	Resist(RECOVER_POISON, &CRecoveryMagic::RecoverPoison);
	Resist(AUTHORITY_RECOVER_SIGHT, &CRecoveryMagic::AuthorityRecoverSight);
	Resist(CURE_DISEASE, &CRecoveryMagic::CureDisease);
	Resist(AUTHORITY_SIMUNIAN, &CRecoveryMagic::AuthoritySimunian);
	Resist(HOLY_CURE, &CRecoveryMagic::HolyCure); // 030415 kyo 
	return true;
}

bool CRecoveryMagic::Healing()
{ // [1]ü��ȸ�� : HP ����
	if (m_pTarget->IsFullLife())
	{ // MP�� ���� ���ִٸ�
		return false;
	}
	const int nInt = m_pCaster->GetAbility(INT_);
	const int nWsPs = m_pCaster->GetAbility(WSPS);
	const int nPlus = ((nInt + nWsPs)>>1)*(m_pCaster->Skill[TACTICS_Magery]>>1) + 100;
	const int nReal = m_pTarget->IncLife(nPlus);
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex, nReal);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_H);
	m_packet.u.magic.server_magic_result_h.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_h.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_h.nLife = nReal;
	m_packet.u.magic.server_magic_result_h.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_h.nResult = HIT_AND_NOTDEAD;
	SendMagicResult();
	return true;
}

bool CRecoveryMagic::Decipher()
{ // [4]�ص� ���� : ���ְ迭 ������ �ߵ�, ������ ���¸� ����
	m_pTarget->ClearCurse(3);
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT);
	m_packet.u.magic.server_magic_result.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result.nResult = HIT_AND_NOTDEAD;
	SendMagicResult();
	return true;
}

bool CRecoveryMagic::HealDisease()
{ // [5]����ġ�� : Health(����� ����) ����
	if (m_pTarget->IsFullHungry() == true)
	{ // ����� ��ġ�� ���� ���ִٸ�
		return false;
	}
	
	const int nPlus = m_pTarget->HungryMax/5;
	m_pTarget->IncHungry(nPlus);
	m_pTarget->SendCharInfoBasic(SP, m_pTarget->Hungry);//020704 lsw
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT);
	m_packet.u.magic.server_magic_result.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result.nResult = HIT_AND_NOTDEAD;
	SendMagicResult();
	return true;
}

bool CRecoveryMagic::GreatHeal()
{ // [6]��ü��ȸ�� : HP�� �ִ���� ����, ���� 1, 2�迭�� ���� ���� ȸ��
	if (m_pTarget->IsFullLife())
	{ // MP�� ���� ���ִٸ�
		return false;
	}
	
	const int nInt = m_pCaster->GetAbility(INT_);
	const int nWsPs = m_pCaster->GetAbility(WSPS);
	const int nPlus = ((nInt + nWsPs)>>1)*((m_pCaster->Skill[TACTICS_Magery]*3)>>1) + 600;
	const int nReal = m_pTarget->IncLife(nPlus);
	// ���� 1, 2�迭 ���� ���� ȸ��
	m_pTarget->ClearCurse(1);
	m_pTarget->ClearCurse(2);
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex, nReal);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_H);
	m_packet.u.magic.server_magic_result_h.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_h.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_h.nLife = nReal;
	m_packet.u.magic.server_magic_result_h.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_h.nResult = HIT_AND_NOTDEAD;
	SendMagicResult();
	return true;
}

bool CRecoveryMagic::RemoveCurse()
{ // [78]�������� : ���� 1, 2, 3, 4�迭 ���� ����
	m_pTarget->ClearCurse(1);
	m_pTarget->ClearCurse(2);
	m_pTarget->ClearCurse(3);
	m_pTarget->ClearCurse(4);
	::SendMagicCommand(m_pTarget, SET_CUREBLIND, 0, 0);	//�÷»�� ȸ��
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT);
	m_packet.u.magic.server_magic_result.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result.nResult = HIT_AND_NOTDEAD;
	SendMagicResult();
	return true;
}

bool CRecoveryMagic::RestoreAuthority()
{ // [151]ȸ���ǱǴ� : �ִ��� HP�� ä����
	if (m_pTarget->IsFullLife())
	{ // MP�� ���� ���ִٸ�
		return false;
	}
	
	const int nWis = m_pCaster->GetAbility(WIS);
	const int nWsPs = m_pCaster->GetAbility(WSPS);
	const int nPlus = ((nWis + nWsPs)>>1)*(m_pCaster->Skill[TACTICS_Orison]) + 400;
	const int nReal = m_pTarget->IncLife(nPlus);
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex, nReal);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_H);
	m_packet.u.magic.server_magic_result_h.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_h.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_h.nLife = nReal;
	m_packet.u.magic.server_magic_result_h.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_h.nResult = HIT_AND_NOTDEAD;
	SendMagicResult();
	return true;
}

bool CRecoveryMagic::MiracleRecover()
{ // [156]��ġ�� ���� : �����ڿ� �ֺ��� ���� �Ÿ� ���� �ִ� ĳ���͵��� HP�� 50000���� �÷���
	if (m_pTarget->IsFullLife())
	{ // HP�� ���� ���ִٸ�
		return false;
	}
	// Life ����
	const int nReal = m_pTarget->IncLife(50000);
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex, nReal);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_H);
	m_packet.u.magic.server_magic_result_h.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_h.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_h.nLife = nReal;
	m_packet.u.magic.server_magic_result_h.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_h.nResult = HIT_AND_NOTDEAD;
	SendMagicResult();
	return true;
}

bool CRecoveryMagic::ReliefAuthority()
{ // [164]������ �Ǵ� : ����ڸ� ���� ���¿��� ���� ���·� ����� HP�� ������ �ִ���� ����� ��ġ�� ���� �÷���
	//020501 lsw �츮���� ��ħ
	if(!m_pCaster->bCanViewGhost)//������ �� �� ���� ���¶��
	{
		return false;
	}
	if(m_pTarget->viewtype != VIEWTYPE_GHOST_) 
	{ // ���� ���°� �ƴ϶��
		return false;
	}
	if(m_pTarget->IsReporter()) return false; //Finito added to that reporter cant be res.

	SkillMgr.CharacterToAlive(m_pTarget, 1); //����� �����ε� Ǯ�� ä��ϴ�.
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_M);
	m_packet.u.magic.server_magic_result_m.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_m.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_m.nLife = m_pTarget->HpMax;
	m_packet.u.magic.server_magic_result_m.nMana = m_pTarget->ManaMax;
	m_packet.u.magic.server_magic_result_m.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_m.nResult = HIT_AND_ALIVE;
	SendMagicResult();
	return true;
}

bool CRecoveryMagic::RecoverPoison()
{ // [154]�ص��� �Ǵ� : ���ְ迭 ������ �ߵ�, ������ ���¸� ����
	m_pTarget->ClearCurse(3);
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT);
	m_packet.u.magic.server_magic_result.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result.nResult = HIT_AND_NOTDEAD;
	SendMagicResult();
	return true;
}

bool CRecoveryMagic::AuthorityRecoverSight()
{ // [173]�÷�ȸ���� �Ǵ� : ���ְ迭 ������ �÷»���� ����
	m_pTarget->ClearCurse(4);
	::SendMagicCommand(m_pTarget, SET_CUREBLIND, 0, 0);	//�÷»�� ȸ��
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT);
	m_packet.u.magic.server_magic_result.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result.nResult = HIT_AND_NOTDEAD;
	SendMagicResult();
	return true;
}

bool CRecoveryMagic::CureDisease()
{ // [155]����ġ���� �Ǵ� : Health(����� ����) ����
	if (m_pTarget->IsFullHungry()) 
	{ // ����� ��ġ�� ���� ���ִٸ�
		return false;
	}
	
	const int nPlus = m_pTarget->HungryMax/4;
	m_pTarget->IncHungry(nPlus);
	m_pTarget->SendCharInfoBasic( SP, m_pTarget->Hungry);//020704 lsw
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_T);
	m_packet.u.magic.server_magic_result_t.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_t.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_t.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_t.nResult = HIT_AND_NOTDEAD;
	SendMagicResult();
	return true;
}

bool CRecoveryMagic::AuthoritySimunian()
{ // [181]�ù��Ͼ��� �Ǵ�
	if (m_pTarget->IsFullHungry()) 
	{ // ����� ��ġ�� ���� ���ִٸ�
		return false;
	}
	
	const int nPlus = m_pTarget->HungryMax/4;
	m_pTarget->IncHungry(nPlus);
	m_pTarget->SendCharInfoBasic(SP, m_pTarget->Hungry);//020704 lsw
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_T);
	m_packet.u.magic.server_magic_result_t.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_t.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_t.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_t.nResult = HIT_AND_NOTDEAD;
	SendMagicResult();
	return true;
}

bool CRecoveryMagic::HolyCure()
{ // [179]�ż��� ġ�� = ��������+��ġ�Ǳ���+������ ���� // 030415 kyo
	
	m_pTarget->ClearCurse(1);
	m_pTarget->ClearCurse(2);
	m_pTarget->ClearCurse(3);
	m_pTarget->ClearCurse(4);
	m_pTarget->ClearCurse(6);//Freezn ����
	
	const int nPlus = m_pTarget->HungryMax; // 030516 kyo
	m_pTarget->IncHungry(nPlus);
	m_pTarget->SendCharInfoBasic(SP, m_pTarget->Hungry);//020704 lsw
	
	::SendMagicCommand(m_pTarget, SET_CUREBLIND, 0, 0);	//�÷»�� ȸ��
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������	
	if (m_pTarget->IsFullLife())
	{ // HP�� ���� ���ִٸ� ������ ����. 
		m_pTarget->DecLife(1);
		//return false;
	}
	const int nReal = m_pTarget->IncLife(50000);
	
	InitMagicResult(CMD_MAGIC_RESULT_H);
	m_packet.u.magic.server_magic_result_h.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_h.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_h.nLife = nReal;
	m_packet.u.magic.server_magic_result_h.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_h.nResult = HIT_AND_NOTDEAD;
	SendMagicResult();
	return true;
}