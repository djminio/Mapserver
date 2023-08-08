// AssistanceMagic.cpp: implementation of the CAssistanceMagic class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "AssistanceMagic.h"

#include "..\HigherLayers\OP_Magic.h"
#include "..\HigherLayers\WeatherControl.h"

extern CHARLIST* CheckServerName( const char* szName );// kyo 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAssistanceMagic::CAssistanceMagic()
{
	
}

CAssistanceMagic::~CAssistanceMagic()
{
	
}

///////////////////////////////////////////////////////////////////////////////
// Public Method
///////////////////////////////////////////////////////////////////////////////

bool CAssistanceMagic::Bind()
{
	Resist(SPEED_UP, &CAssistanceMagic::SpeedUp);
	Resist(ENCHANT_WEAPON, &CAssistanceMagic::EnchantWeapon);
	Resist(PRAY_POWER, &CAssistanceMagic::PrayPower);
	Resist(GREAT_PRAY, &CAssistanceMagic::GreatPray);
	Resist(MINOR_AMPLIFY, &CAssistanceMagic::MinorAmplify);
	Resist(MAGIC_AMPLIFY, &CAssistanceMagic::MagicAmplify);
	Resist(TRANSPARENCY, &CAssistanceMagic::Transparency);
	Resist(LIGHT, &CAssistanceMagic::Light);
	Resist(AUTHORITY_LUCK, &CAssistanceMagic::AuthorityLuck);
	return true;
}

bool CAssistanceMagic::SpeedUp()
{	// [83]�ӵ����� : �̵��ӵ��� 20 ~ 50% ����
	const WORD wPeriod = CalcPeriod(); // �����ð� ���
	// ������ ���
	const int nInt = m_pCaster->GetAbility(INT_);
	const int nTactics = m_pCaster->Skill[TACTICS_Magery];
	int nBasic = (nInt + nTactics)/20;
	if (nBasic < 0)   nBasic = 0;
	if (nBasic > 30)  nBasic = 30;
	// �̵��ӵ� 20 ~ 50% ����
	m_pTarget->speedUp.SetState(m_dwNow + wPeriod, nBasic + 20);
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_T);
	m_packet.u.magic.server_magic_result_t.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_t.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_t.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_t.nResult = HIT_AND_NOTDEAD;
	m_packet.u.magic.server_magic_result_t.wDuration = wPeriod;
	SendMagicResult();
	return true;
}

bool CAssistanceMagic::EnchantWeapon()
{	// [21]��þƮ���� : ������ ���� �������� 50% ����
	const WORD wPeriod = CalcPeriod(); // �����ð� ���
	// ������ ���ݷ� 50% ����
	m_pTarget->SetPhysicalAttack(m_dwNow + wPeriod, 50, 50, 50);
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_T);
	m_packet.u.magic.server_magic_result_t.nMagic = m_nIndex; 
	m_packet.u.magic.server_magic_result_t.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_t.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_t.nResult = HIT_AND_NOTDEAD;
	m_packet.u.magic.server_magic_result_t.wDuration= wPeriod;
	SendMagicResult();
	return true;
}

bool CAssistanceMagic::PrayPower()
{	// [161]�⵵�� ���� : ������ ���� �������� 50% ����
	const WORD wPeriod = CalcPeriod(); // �����ð� ���
	// ������ ���ݷ� 50% ����
	m_pTarget->SetPhysicalAttack(m_dwNow + wPeriod, 50, 50, 50);
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_T);
	m_packet.u.magic.server_magic_result_t.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_t.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_t.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_t.nResult = HIT_AND_NOTDEAD;
	m_packet.u.magic.server_magic_result_t.wDuration = wPeriod;
	SendMagicResult();
	return true;
}

bool CAssistanceMagic::GreatPray()
{	// [166]������ �⵵
	const WORD wPeriod = CalcPeriod(); // �����ð� ���
	// ������ ���ݷ� 50% ����
	m_pTarget->SetPhysicalAttack(m_dwNow + wPeriod, 50, 50, 50);
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_T);
	m_packet.u.magic.server_magic_result_t.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_t.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_t.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_t.nResult = HIT_AND_NOTDEAD;
	m_packet.u.magic.server_magic_result_t.wDuration = wPeriod;
	SendMagicResult();
	return true;
}

bool CAssistanceMagic::MinorAmplify()
{	// [25]������ : ���� ������ �������� 20% ����
	const WORD wPeriod = CalcPeriod(); // �����ð� ���
	// ���� ������ �������� 20% ����
	m_pTarget->amplify.SetState(m_dwNow + wPeriod, 20);
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_T);
	m_packet.u.magic.server_magic_result_t.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_t.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_t.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_t.nResult = HIT_AND_NOTDEAD;
	m_packet.u.magic.server_magic_result_t.wDuration = wPeriod;
	SendMagicResult();
	return true;
}

bool CAssistanceMagic::MagicAmplify()
{	// [26]�������� : ���� ������ �������� 50% ����
	const WORD wPeriod = CalcPeriod(); // �����ð� ���
	// ���� ������ �������� 50% ����
	m_pTarget->amplify.SetState(m_dwNow + wPeriod, 50);
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_T);
	m_packet.u.magic.server_magic_result_t.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_t.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_t.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_t.nResult = HIT_AND_NOTDEAD;
	m_packet.u.magic.server_magic_result_t.wDuration = wPeriod;
	SendMagicResult();
	return true;
}

bool CAssistanceMagic::Transparency()
{	// [22]�����ֹ� : �ڽ��� ���� �����ϰ� ����� ��
	const WORD wPeriod = CalcPeriod(); // �����ð� ���
	m_pTarget->dwTransparency = m_dwNow + wPeriod; 
	// ����ü ����� ���� VIEWTYPE ����(transparency)
	m_pTarget->viewtype = VIEWTYPE_TRANSPARENCY_;
	::SendViewType(m_pTarget, VIEWTYPE_TRANSPARENCY_, m_pTarget->dwTransparency);
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_T);
	m_packet.u.magic.server_magic_result_t.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_t.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_t.nState = m_pTarget->GetState();
	// �Ϲ� �������� ������ ��� Ŭ���̾�Ʈ���� �ٽ� ������·� �����ϹǷ� ���з� ����
	m_packet.u.magic.server_magic_result_t.nResult = HIT_FAILED;
	m_packet.u.magic.server_magic_result_t.wDuration = wPeriod;
	SendMagicResult();
	return true;
}

bool CAssistanceMagic::Light()
{	// [46]�� : ������ ȯ�ϰ� ����(�㿡 �þ߰� ��ο����� ���� ����)
	const WORD wPeriod = CalcPeriod(); // �����ð� ���
	m_pTarget->dwLight = m_dwNow + wPeriod;
	// ������ ȯ�ϰ� ��
	WeatherControl.SetChLight(m_pCaster, nMaximumLight, wPeriod);
	
	for (int i = 0; i < MAX_PARTY_MEMBER; ++i)
	{
		if (m_pCaster->party[i].On)
		{ 
			//CHARLIST *Target = CheckServerId( m_pCaster->party[i].Server_id );
			CHARLIST *Target = CheckServerName( &(m_pCaster->party[i].Name[0]) );
			if(!Target){continue;}
			WeatherControl.SetChLight(Target,nMaximumLight/2,5*60);
		}
	}
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_T);
	m_packet.u.magic.server_magic_result_t.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_t.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_t.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_t.nResult = HIT_AND_NOTDEAD;
	m_packet.u.magic.server_magic_result_t.wDuration = wPeriod;
	SendMagicResult();
	return true;
}

bool CAssistanceMagic::AuthorityLuck()
{	// [175]���� ����� �Ǵ� : ��� ������ ���ݰ� ������ ����
	const WORD wPeriod = CalcPeriod(); // �����ð� ���
	m_pTarget->dwDontMiss = m_dwNow + wPeriod;
	// �������� ����ġ ���
	::AddCasterEXP(m_pCaster, m_pTarget, 2, 0, m_nIndex);
	// ������� ����ڿ��� Packet���� ������
	InitMagicResult(CMD_MAGIC_RESULT_T);
	m_packet.u.magic.server_magic_result_t.nMagic = m_nIndex;
	m_packet.u.magic.server_magic_result_t.idTarget = m_idTarget;
	m_packet.u.magic.server_magic_result_t.nState = m_pTarget->GetState();
	m_packet.u.magic.server_magic_result_t.nResult = HIT_AND_NOTDEAD;
	m_packet.u.magic.server_magic_result_t.wDuration = wPeriod;
	SendMagicResult();
	return true;
}