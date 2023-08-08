// ThunderCombat.cpp: implementation of the CThunderCombat class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "ThunderCombat.h"

#include "..\HigherLayers\OP_Magic.h"
///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////////////////////////////////////

CThunderCombat::CThunderCombat()
{

}

CThunderCombat::~CThunderCombat()
{

}

///////////////////////////////////////////////////////////////////////////////
// Public Method
///////////////////////////////////////////////////////////////////////////////

bool CThunderCombat::Bind() 
{ 
	Resist(LIGHTNING_BOOM, &CThunderCombat::LightningBoom);
	Resist(THUNDER_BLOW, &CThunderCombat::ThunderBlow);
	Resist(LIGHTNING_SHOCK, &CThunderCombat::LightningShock);
	Resist(THUNDER_STRIKE, &CThunderCombat::ThunderStrike);
	Resist(LIGHTNING_SHIELD, &CThunderCombat::LightningShield);
	Resist(LIGHTNING_EXTREME, &CThunderCombat::LightningExtreme);
	return true; 
}

bool CThunderCombat::Elapse(CHARLIST* pTarget)
{	//< CSD-TW-030623
	switch (pTarget->GetPassiveCombat())
	{
    case LIGHTNING_SHIELD:
		{
			if (!pTarget->IsPassiveCombatState())
			{
				pTarget->InitPassiveCombat();
				SendInit(PASSIVE_COMBAT, pTarget->GetServerID());
			}

			break;
		}
	}
	
	return true;
}	//> CSD-TW-030623

bool CThunderCombat::LightningBoom()
{	// [215]����Ʈ�� ��
	switch (GetKind(m_pCaster))
	{	//< CSD-030723
    case WR_SHORT:  return AttackShort();
    case WR_MIDDLE: return AttackMiddle();
    case WR_LONG1:  return AttackLong(WR_LONG1);
    case WR_LONG2:  return AttackLong(WR_LONG2);
	}	//> CSD-030723
	
	return false;
}

bool CThunderCombat::ThunderBlow()
{ // [216]��� ��ο�
	// ������� ����ڿ��� Packet���� ������
	t_server_combat_result packet;
	packet.nSkill = m_nIndex;
	packet.nResult = HIT_AND_NOTDEAD;
	packet.idTarget = m_idTarget;
	SendResult(CMD_COMBAT_RESULT, &packet);
	return true;
}

bool CThunderCombat::LightningShock()
{ // [217]����Ʈ�� ��ũ
	// ������� ����ڿ��� Packet���� ������
	t_server_combat_result packet;
	packet.nSkill = m_nIndex;
	packet.nResult = HIT_AND_NOTDEAD;
	packet.idTarget = m_idTarget;
	SendResult(CMD_COMBAT_RESULT, &packet);
	return true;
}

bool CThunderCombat::ThunderStrike()
{ // [218]����Ʈ�� ��
	// ������� ����ڿ��� Packet���� ������
	t_server_combat_result packet;
	packet.nSkill = m_nIndex;
	packet.nResult = HIT_AND_NOTDEAD;
	packet.idTarget = m_idTarget;
	SendResult(CMD_COMBAT_RESULT, &packet);
	return true;
}

bool CThunderCombat::LightningShield()
{ // [219]����Ʈ�� ����
	m_pCaster->dwCombatState = m_dwNow + CalcMaintain();
	// �Ϲ� ��ȣ�迭 ���� �������� ����
	m_pCaster->dwNormalProtect = m_dwNow + CalcMaintain();
	// ������� ����ڿ��� Packet���� ������
	t_server_combat_result packet;
	packet.nSkill = m_nIndex;
	packet.idTarget = m_idTarget;
	packet.nResult = HIT_AND_NOTDEAD;
	SendResult(CMD_COMBAT_RESULT, &packet);
	return true;
}

bool CThunderCombat::LightningExtreme()
{	//< CSD-030723
	switch (GetKind(m_pCaster))
	{
    case WR_SHORT:  return AttackShort();
    case WR_MIDDLE: return AttackMiddle();
    case WR_LONG1:  return AttackLong(WR_LONG1);
    case WR_LONG2:  return AttackLong(WR_LONG2);
	}
	
	return false;
}	//> CSD-030723