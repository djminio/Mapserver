// MagicState.cpp: implementation of the CMagicState class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "MagicState.h"

#include "..\LowerLayers\MyLog.h"

///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////////////////////////////////////
/* Declared inline in the header
CMagicState::CMagicState()
{
  Clear();
}
*/
///////////////////////////////////////////////////////////////////////////////
// Public Method
///////////////////////////////////////////////////////////////////////////////

void CMagicState::Clear()
{	//< CSD-TW-030623
	ClearTransMap();          // ��� ��� ���� �ʱ�ȭ
	ClearMagic();             // ���� ��ȣ �ʱ�ȭ

	ClearActiveState();
	ClearPassiveState();
	ClearRecoveryState();
	
	m_nAttack = 0;            // ������ ���� ȸ�� 
	m_nNature = NAT_NORMAL;   // ���� ���� �ʱ�ȭ
	m_nState = CON_NORMAL;    // ���� ���� �ʱ�ȭ
	m_bTamed = false;         // ���̹� ���� �ʱ�ȭ  
	m_bSummon = false;        // ��ȯ ���� ���� �ʱ�ȭ
	m_wPoisonedPoint = 0;     // �ߵ��Ǿ��� �� HP�� ���ҵǴ� �� �ʱ�ȭ
	m_wPoisonedCount = 0;     // �ߵ��Ǿ��� �� HP�� ���ҵǴ� �� �ʱ�ȭ
	m_nLifeUp = 0;            // Life ������
	
	m_dwAttack = 0;           // ������ ���� �ð� �ʱ�ȭ
	m_dwCasting = 0;          // ���� ���� ���� �ð� �ʱ�ȭ
	m_dwContinue = 0;         // ���� ���� ���� �ð� �ʱ�ȭ
	m_bLock = true;           // ���� ���� ���� �ʱ�ȭ
	
	apShort.Clear();          // �ܰŸ� ������ ���ݷ�
	apMiddle.Clear();         // �߰Ÿ� ������ ���ݷ�
	apLong.Clear();           // ��Ÿ� ������ ���ݷ�
	
	dpShort.Clear();          // �ܰŸ� ������ ����
	dpMiddle.Clear();         // �߰Ÿ� ������ ����
	dpLong.Clear();           // ��Ÿ� ������ ����
	
	dpFire.Clear();           // �Ұ迭 ���ݸ���  ����
	dpIce.Clear();            // �����迭 ���ݸ��� ����
	dpElect.Clear();          // ���ݰ迭 ���ݸ��� ����
	dpHoly.Clear();           // �ŷ°迭 ���ݸ��� ����
	
	dpCurse1.Clear();         // ���� 1�迭 ���� ����
	dpCurse2.Clear();         // ���� 2�迭 ���� ����
	dpCurse3.Clear();         // ���� 3�迭 ���� ����
	dpCurse4.Clear();         // ���� 4�迭 ���� ����
	dpCurse5.Clear();         // ���� 5�迭 ���� ����
	dpFreeze.Clear();         // CSD-021216 : �� ���� ���� ����
    
	amplify.Clear();          // ���� ���� ������
	speedUp.Clear();          // �̵��ӵ� ����   
	speedDown.Clear();        // �̵��ӵ� ����  
	
	avoid.Clear();            // ȸ����
	agility.Clear();          // ��ø��
	
	dwCurse1 = 0;             // ���� 1�迭 ���� ���� 
	dwCurse2 = 0;             // ���� 2�迭 ���� ���� 
	dwCurse3 = 0;             // ���� 3�迭 ���� ���� 
	dwCurse4 = 0;             // ���� 4�迭 ���� ���� 
	dwFreeze = 0;             // CSD-021024 : �� ���� ���� ����
	
	dwNormalProtect = 0;      // �Ϲ� ��ȣ�迭 ���� ����
	dwSpecialProtect = 0;     // Ư�� ��ȣ�迭 ���� ���� 
	dwExceptProtect = 0;      // ���� ��ȣ�迭 ���� ���� (��� ������ ����)
	
	dwAttackDelay = 0;	      // ���� �ӵ� ����(ĳ���Ͱ� ���� �Ҽ� �ִ� ����)
	dwDontMove = 0;           // �̵��� ���� ����
	dwDontAttack = 0;		      // �Ϲ����� ������ ���� ����
	dwDontCasting = 0;		    // ���� ĳ������ ���� ����
	dwDontMiss = 0;           // ��� ������ ���ݰ� ������ ����
	dwBlocking = 0;           // �ܺο� ���ܵ� ����
	dwLight = 0;              // ������ ���� ������ ����  
	dwMagicDamageToMana = 0;  // ����� ���� ������ ������ �Ҹ��Ͽ� ���Ƴ�
	dwReturnMagic = 0;		    // ������ ȿ���� �����ڿ��� �ǵ���
	dwTransparency = 0;		    // ĳ���Ͱ� �����ϰ� �� 
	dwLifeUp = 0;             // ���� �ð����� Life�� �ö�
	dwStrikeReflect = 0;      // CSD-021015 : �������� ������ �ݻ�
	dwMagicReflect = 0;       // CSD-021015 : �������� ������ �ݻ�
	dwUpDivineMana = 0;		// 030415 kyo

	for (int i = 0; i < NAT_NORMAL; ++i)
	{
		dwNature[i] = 0;
	}
}	//> CSD-TW-030623

void CMagicState::Recovery(DWORD dwNow)
{	//< CSD-TW-030623 : �����ð��� ���� ������ ���Ͽ� ���¸� ȸ��
	// ���� ���� �˻�
	if (apShort.IsContinue(dwNow) == false)  apShort.Clear();
	if (apMiddle.IsContinue(dwNow) == false)  apMiddle.Clear();
	if (apLong.IsContinue(dwNow) == false)  apLong.Clear();
	if (dpShort.IsContinue(dwNow) == false)  dpShort.Clear();
	if (dpMiddle.IsContinue(dwNow) == false)  dpMiddle.Clear();
	if (dpLong.IsContinue(dwNow) == false)  dpLong.Clear();
	
	if (dpFire.IsContinue(dwNow) == false)  dpFire.Clear();
	if (dpIce.IsContinue(dwNow) == false)  dpIce.Clear();
	if (dpElect.IsContinue(dwNow) == false)  dpElect.Clear();
	if (dpHoly.IsContinue(dwNow) == false)  dpHoly.Clear();
	
	if (dpCurse1.IsContinue(dwNow) == false)  dpCurse1.Clear();
	if (dpCurse2.IsContinue(dwNow) == false)  dpCurse2.Clear();
	if (dpCurse3.IsContinue(dwNow) == false)  dpCurse3.Clear();
	if (dpCurse4.IsContinue(dwNow) == false)  dpCurse4.Clear();
	if (dpCurse5.IsContinue(dwNow) == false)  dpCurse5.Clear();
	if (dpFreeze.IsContinue(dwNow) == false)  dpFreeze.Clear();
	
	if (amplify.IsContinue(dwNow) == false)  amplify.Clear();  
	if (speedUp.IsContinue(dwNow) == false)  speedUp.Clear();
	if (speedDown.IsContinue(dwNow) == false)  speedDown.Clear();  
	if (avoid.IsContinue(dwNow) == false)  avoid.Clear();
	if (agility.IsContinue(dwNow) == false)  agility.Clear();
	
	if (dwNormalProtect < dwNow)  dwNormalProtect = 0;
	if (dwSpecialProtect < dwNow)  dwSpecialProtect = 0;
	if (dwExceptProtect < dwNow)  dwExceptProtect = 0;
	
	if (dwAttackDelay < dwNow)  dwAttackDelay = 0;
	if (dwDontMove < dwNow)  dwDontMove = 0;
	if (dwDontAttack < dwNow)  dwDontAttack = 0;
	if (dwDontCasting < dwNow)  dwDontCasting = 0;
	if (dwDontMiss < dwNow)  dwDontMiss = 0;
	if (dwBlocking < dwNow)  dwBlocking = 0;
	if (dwLight < dwNow) dwLight = 0;
	if (dwTransparency < dwNow)  dwTransparency = 0;
	
	if (dwMagicDamageToMana < dwNow)  dwMagicDamageToMana = 0;
	if (dwReturnMagic < dwNow)  dwReturnMagic = 0;
	if (dwLifeUp < dwNow)  dwLifeUp = 0;
	if (dwStrikeReflect < dwNow)  dwStrikeReflect = 0;
	if (dwMagicReflect < dwNow)  dwMagicReflect = 0;
	if (dwUpDivineMana < dwNow) dwUpDivineMana = 0;
	
	for (int i = 0; i < NAT_NORMAL; ++i)
	{
		if (dwNature[i] < dwNow)
		{
			dwNature[i] = 0;
			m_nNature = NAT_NORMAL;
		}
	}
	
	if (dwCombatState < dwNow)  dwCombatState = 0;
	if (dwCombatRecovery < dwNow)  dwCombatRecovery = 0; 
}	//> CSD-TW-030623

bool CMagicState::CheckAttack(BYTE nCount, DWORD dwNow)
{
	if (m_dwAttack < dwNow)
	{
		m_dwAttack = dwNow;
		m_nAttack = 0;
	}
	else
	{
		if (m_nAttack >= nCount)
		{
			return false;
		}
		
		++m_nAttack;
	}
	
	return true;
}

bool CMagicState::CheckStart(BYTE nMagic, DWORD dwNow)
{	//< CSD-TW-030606
	switch (Magic_Ref[nMagic].magic_Type)
	{
	case 0:
	case 9: return false;
	}
	
	if (m_dwCasting > dwNow)
	{
		return false;
	}
	// ȭ������ ��� ���� �ð� ����
	if (nMagic == FIRE_WALL)  
	{
		m_dwFireWall = dwNow + Magic_Ref[nMagic].continue_Time;
	}
	// �������� ��� ���� �ð� ����
	if (nMagic == ICE_WALL)  
	{
		m_dwIceWall = dwNow + Magic_Ref[nMagic].continue_Time;
	}
	
	m_nMagic = nMagic;                              // ������ ���� ��ȣ ����
	m_dwCasting = dwNow + DELAY;                    // ���� ���� ���� �ð�
	m_dwContinue = dwNow + GetCastContinue(nMagic); // ĳ���� ���� �ð� ����
	m_bLock = true;                                 // ���� ���� ����
	return true;
}	//> CSD-TW-030606

bool CMagicState::CheckDoing(BYTE nMagic, DWORD dwNow)
{ //
	switch (Magic_Ref[nMagic].Excute_Type)
	{
    case 0: // �ѹ� ������ ĳ���� ���� �ð����� ���� ���
		{
			if (m_dwContinue < dwNow)  
			{ // ��ȿ�� ���� ���� ���� �ð����� �˻�
				return false;
			}
			
			break;
		}
    case 1: // �ѹ� ������ �ѹ� ���� ���
		{
			if (m_bLock == false)  
			{ // ������ �ߴ��� �˻�
				return false;
			}
			
			break;
		}
    default: return false;
	}
	
	m_nMagic = nMagic; // ����� ���� ��ȣ ����
	return true;
}

bool CMagicState::CheckEnd(BYTE nMagic, DWORD dwNow)
{ //
	// ȭ���� ���� �ð� �˻�
	if (nMagic == FIRE_WALL && m_dwFireWall < dwNow)  
	{ 
		return false;
	}
	// ������ ���� �ð� �˻�
	if (nMagic == ICE_WALL && m_dwIceWall < dwNow)  
	{ 
		return false;
	}
	
	m_nMagic = nMagic; // ����� ���� ��ȣ ����
	return true;
}

bool CMagicState::CheckDelay(BYTE nMagic, DWORD dwNow)
{ // ��ȿ�� ���� ���� ���� �ð����� �˻�
	if (m_dwCasting > dwNow)  
	{ // ��ȿ�� ���� ���� ���� �ð����� �˻�
		return false;
	}
	
	m_nMagic = nMagic;                             // ����� ���� ��ȣ ����
	m_dwCasting = dwNow + GetCastContinue(nMagic); // ĳ���� ���� �ð� ���� 
	return true;
}

bool CMagicState::CheckCombat(BYTE nCombat, DWORD dwNow)
{
	if (dwCombatState > dwNow)  
	{ // ��ȿ�� ���� ���� ���� �ð����� �˻�
		return false;
	}
	
	return true;
}

bool CMagicState::CheckMultiEffect(BYTE nMagic)
{
	switch(nMagic)
	{
	//Can have effect more than once per execute
	case TOXIC_CLOUD:
	case FIRE_ARROW:
	case SCORCHER:
	case CIRCLE_FLAME:
	case FIRE_WALL:
	case FLAME_WAVE:
	case APOCALYPSE:
	case ICE_ARROW:
	case FREEZE_5TILE_RADIUS:
	case ICE_WALL:
	case CIRCLE_ICE:
	case ICE_STORM:
	case FREEZE_9TILE_RADIUS:
	case LIGHTNING_BOLT:
	case CHAIN_LIGHTNING:
	case CIRCLE_LIGHTNING:
	case LIGHTNING_5TILE_RADIUS:
	case SNOWSTORM:
	case ICE_BREATH2:
	case BLOOD_LIGHTNING:
	case PHEONIX:
	case METEOR_STRIKE:
	case GREAT_THUNDER_BOLT:
	case GREAT_METEOR:
	case MIRACLE_RECOVER:
	case HOLY_LIGHT:
	case GREAT_PRAY:
	case DIVINE_POWER:
	case HOLY_CURE:
	case AUTHORITY_SIMUNIAN:
	case AUTHORITY_CHARISNUMEN:
	case AUTHORITY_OF_WHOARENCHA:
	case GREAT_SHIELD:
		return true;
		break;
	//Cannot have an effect multiple times
	case PROTECTION:
	case LIFE_UP:
	case SHIELD:
	case HEAL_DISEASE:
	case GREAT_HEAL:
	case SLOW:
	case CONFUSION:
	case INTOXICATION:
	case STONELY:
	case ABSOLUTE_PARALYSIS:
	case VAMPIRE_TOUCH:
	case SPIDER_WEB:
	case TRANSPARENCY:
	case ENCHANT_WEAPON:
	case MINOR_AMPLIFY:
	case MAGIC_AMPLIFY:
	case FIRE_RESIST:
	case ICE_RESIST:
	case LIGHT:
	case ELECT_RESIST:
	case LIGHTNING:
	case ICE_BALL:
	case FIRE_BALL:
	case TWINKLE_STAR:
	case LOW_MONSTER_RECALL:
	case MIDDLE_MONSTER_RECALL:
	case PHASING:
	case MEMORIZING_LOCATION:
	case TOWN_PORTAL:
	case TELEPORT:
	case MAGIC_DETECT:
	case REMOVE_CURSE:
	case PROTECT_RANGE_WEAPON:
	case SPEED_UP:
	case LOST_SIGHT:
	case DRAGON_SCALE:
	case SUMMONING_SKELETON:
	case SUMMONING_UNDEAD:
	case RESTORE_AUTHORITY:
	case PROTECT_DANGER:
	case BLESS:
	case RECOVER_POISON:
	case CURE_DISEASE:
	case PERFECT_PROTECT:
	case CANCEL_DIVINE:
	case RECURRENCE_DIVINE:
	case PRAY_POWER:
	case ANTHEM:
	case HOLY_FIRE:
	case APPRECIATE:
	case VOICE_SOUL:
	case TURN_UNDEAD:
	case CURSE:
	case AUTHORITY_RECOVER_SIGHT:
	case AUTHORITY_LUCK:
	case AUTHORITY_LOST_SIGHT:
	case PRAY:
	case AUTHORITY_LETHY:
	case AUTHORITY_OF_ATHYAS:
	case RAGE_STONE:
	case LIFE_DRAIN:
	case RAGE_BLAST:
	case RAGE_LIGHT_BALL:
		return false;
		break;
	default:
		/*
		PHYSICAL
		DECIPHER
		MAGICAL_TRAP
		NULLITY_MAGIC
		DISEASE_INDUCE
		MULTI_PORT
		DEATH_FIRE
		FLYING_SPARK
		VAMPIRE_POISON
		VAMPIRE_DODGE
		FEATHER_OF_CURSE
		CURSE_OF_HELL
		RECALL_FOLLOW
		FIRE_EXPLOSION
		FIRE_STORM
		SHADOW_OF_EVIL = 98,           // ���� �׸���
		FREEZING = 99,                 // ���� ��
		BLITZ_SPEAR = 100,             // ����â
		LIGHTNING_CLOUD = 101,         // ���� ����
		FIRE_BREATH = 102,             // ȭ�� �극��
		ICE_BREATH = 103,              // ���� �극��
		LIGHTNING_BREATH = 104,        // ���� �극��
		FLAME_PILLAR = 105,            // ȭ�� ���
		FLAME_POUR = 106,              // ȭ�� ��ǳ 
		OCTA_LIGHTNING = 107,          // ��� ����
		BLOOD_SPRINKLE = 108,          // �ǻѸ���
		GAZER	= 109,				   // ������
		FLAME_ARROW = 110,             // ȭ��ȭ�� 
		AREA_BAT_ATTACK = 111,         // ���� �������
		AREA_PARALYSIS = 112,          // ���� ����
		AREA_POISON = 113,             // ���� �ߵ�
		AREA_CONFUSION = 114,          // ���� ȥ��
		AREA_SLOW = 115,               // ���� �ӵ�����
		RELIEF_AUTHORITY = 164,        // ������ �� 
		INFLUENCE_DIVINE = 168,        // �ſ��� ��ȭ
		HOLY_RAGE = 170,               // ������ �г�

  		THROW_ARROW = 194,             // ȭ��
		THROW_KNIFE = 195,             // ��

  		// ���� �Ӽ� ������ų
		LIGHTNING_BOOM = 215,          
		THUNDER_BLOW = 216,
		LIGHTNING_SHOCK = 217,
		THUNDER_STRIKE = 218,
		LIGHTNING_SHIELD = 219,
		LIGHTNING_EXTREME = 220,
		// ���� �Ӽ� ������ų
		BLOOD_EARTH = 221,             
		GROUND_ATTACK = 222, 
		BLOOD_WILL = 223,
		STONE_ARMOR = 224,
		SIMUNIAN_BOSOM = 225,
		EARTH_EXTREME = 226,
		// ȭ�� �Ӽ� ������ų 
		SWORD_N_ROSES = 227,
		MULTIPLE_FIRE = 228, 
		FLEET_MISSILE = 229,
		CONVERTING_ARMOR = 230, 
		BURNING_BLOODY= 231,
		FIRE_EXTREME = 232,
		// ��� �Ӽ� ������ų
		POISONING_NOVA = 233,
		CHERROY_SHADE = 234, 
		DARK_BLADE = 235, 
		TYBERN_GIFT = 236,
		ACUQUIRE_DARK = 237,
		DARK_EXTREME = 238,
		// ���� �Ӽ� ������ų
		ICING_BLAST = 239,
		CRITICAL_HIDING = 240, 
		SHARK_MISSILE = 241, 
		HORN_OF_ICEBERG = 242, 
		ICE_SHIELD = 243,
		ICE_EXTREME = 244,
		// �ٶ� �Ӽ� ������ų
		CHARGING = 245,
		DOUBLE_ATTACK = 246, 
		WHILWIND = 247,
		TWISTER = 248, 
		GUST = 249, 
		WIND_EXTREME = 250,
		// ����Ʈ ������
		ITEM_FIRE_EFFECT = 610, // CSD-030916
		ITEM_ICE_EFFECT = 611, // CSD-030916
		ITEM_LIGHTNING_EFFECT = 612, // CSD-030916	
		// �̺�Ʈ
		THROW_SNOW = 193,
		THROW_WATER_BALL = 661,
		THROW_BIG_GULP = 663,
		// ������ ȿ��
		ITEM_EFFECT_FIRE = 605,
		ITEM_EFFECT_ICE = 606,
		ITEM_EFFECT_LIGHTNING = 607

		*/
		return true;
		break;
	};
};

void CMagicState::InitCurse()
{ //< CSD-021024 : ���ְ迭 ���� ���¿� ���� �ʱ�ȭ
	dwCurse1 = 0;
	dwCurse2 = 0;
	dwCurse3 = 0;
	dwCurse4 = 0;
	dwFreeze = 0;
} //> CSD-021024

void CMagicState::ClearCurse(BYTE nType)
{
	switch (nType)
	{
    case 1: 
		{ 
			dwCurse1 = 0;
			dwDontCasting = 0;
			dwDontAttack = 0;
			dwBlocking = 0;
			DelState(CON_CURSE|CON_DAZE|CON_STONE);
			break;
		} 
    case 2: 
		{ //< CSD-021024
			dwCurse2 = 0;
			speedDown.Clear();
			DelState(CON_SLOW);
			break;
		} //> CSD-021024
    case 3: 
		{
			dwCurse3 = 0; 
			dwCurse3 = 0;
			m_wPoisonedPoint = 0;
			DelState(CON_POISON);
			break;
		}
    case 4: 
		{
			dwCurse4 = 0;
			DelState(CON_DARKNESS);
			break;
		}
    case 6:
		{ //< CSD-021024
			dwFreeze = 0;
			dwAttackDelay = 0;
			DelState(CON_FROZEN);
			break;
		} //> CSD-021024
	}
}

void CMagicState::ApplyCurse(BYTE nType, BYTE nState, DWORD dwTime)
{ //< CSD-021024 : ���ְ迭 ���� ���·� ����
	switch (nType)
	{
    case 1: dwCurse1 = dwTime; AddState(nState); break;
    case 2: dwCurse2 = dwTime; AddState(nState); break;
    case 3: dwCurse3 = dwTime; AddState(nState); break;
    case 4: dwCurse4 = dwTime; AddState(nState); break;
    case 6: dwFreeze = dwTime; AddState(nState); break;
    default: return;
	}
} //> CSD-021024

int CMagicState::GetAvailRange(BYTE nMagic) const
{
	return Magic_Ref[nMagic].avail_Range;
}

int CMagicState::GetCastReady(BYTE nMagic) const 
{ 
	return Magic_Ref[nMagic].cast_Time*70; 
}

int CMagicState::GetCastContinue(BYTE nMagic) const
{ 
	return Magic_Ref[nMagic].cast_Continue/6;
}

int CMagicState::GetDualStep(BYTE nMagic) const // 030415 kyo
{
	return Magic_Ref[nMagic].nDualStep;
}

void CMagicState::ClearTransMap()
{ // ���� �̵� ��� ���� �ʱ�ȭ
	m_nTransPort = m_nTransX = m_nTransY = 0;
}

void CMagicState::GetTransMap(int& rPort, int& rX, int& rY) const
{ // ���� �̵� ��� ���� ���ϱ�
	rPort = m_nTransPort;
	rX = m_nTransX;
	rY = m_nTransY;
}

void CMagicState::SetTransMap(int nPort, int nX, int nY)
{ // ���� �̵� ��� ���� ����
	m_nTransPort = nPort;
	m_nTransX = nX;
	m_nTransY = nY;
}

void CMagicState::ClearCombat(BYTE nSelect)
{	//< CSD-TW-030623
	switch (Magic_Ref[nSelect].Spell_Type)
	{
    case ACTIVE_COMBAT:
		{
			InitActiveCombat();
			ClearActiveState();
			break;
		}
    case PASSIVE_COMBAT:
		{
			InitPassiveCombat();
			ClearPassiveState();
			break;
		}
	case RECOVERY_COMBAT:
		{
			InitRecoveryCombat();
			ClearRecoveryState();
			break;
		}
	}
}	//> CSD-TW-030623

void CMagicState::SetActiveCombat(BYTE nCombat, int nCount)
{ 
	m_nActive = nCombat; 
	m_nCount = nCount;
}

void CMagicState::SetPassiveCombat(BYTE nCombat, DWORD dwPeriod) 
{ 
	m_nPassive = nCombat; 
	dwCombatState = dwPeriod;
}

void CMagicState::SetRecoveryCombat(BYTE nCombat, DWORD dwPeriod) // 030415 kyo
{
	m_nRecovery = nCombat;
	dwCombatRecovery = dwPeriod;
}

void CMagicState::SetPhysicalAttack(DWORD dwTime, BYTE nShort, BYTE nMiddle, BYTE nLong)
{ // ������ ���ݷ� ���� ����
	if (nShort > 0)   apShort.SetState(dwTime, nShort);   // �ܰŸ� ������ ���ݷ�
	if (nMiddle > 0)  apMiddle.SetState(dwTime, nMiddle); // �߰Ÿ� ������ ���ݷ�
	if (nLong > 0)    apLong.SetState(dwTime, nLong);     // ��Ÿ� ������ ���ݷ�
}

void CMagicState::SetPhysicalDefense(DWORD dwTime, BYTE nShort, BYTE nMiddle, BYTE nLong)
{ // ������ ���� ���� ����   
	if (nShort > 0)   dpShort.SetState(dwTime, nShort);   // �ܰŸ� ������ ����
	if (nMiddle > 0)  dpMiddle.SetState(dwTime, nMiddle); // �߰Ÿ� ������ ����
	if (nLong > 0)    dpLong.SetState(dwTime, nLong);     // ��Ÿ� ������ ����
}

void CMagicState::SetMagicalDefense(DWORD dwTime, BYTE nFire, BYTE nIce, BYTE nElect, BYTE nHoly)
{ // ���ݰ迭 ������ ���� ���� ���� ����
	if (nFire > 0)   dpFire.SetState(dwTime, nFire);   // �Ұ迭 ���ݸ��� ����
	if (nIce > 0)    dpIce.SetState(dwTime, nIce);     // �����迭 ���ݸ��� ����
	if (nElect > 0)  dpElect.SetState(dwTime, nElect); // ���ݰ迭 ���ݸ��� ����
	if (nHoly > 0)   dpHoly.SetState(dwTime, nHoly);   // Ȧ���迭 ���ݸ��� ����
}

void CMagicState::SetCurseDefense(DWORD dwTime, BYTE nSet)
{ // ���ְ迭 ������ ���� ��� ����
	if (nSet&CURSE_1)  dpCurse1.SetState(dwTime, 100);
	if (nSet&CURSE_2)  dpCurse2.SetState(dwTime, 100);
	if (nSet&CURSE_3)  dpCurse3.SetState(dwTime, 100);
	if (nSet&CURSE_4)  dpCurse4.SetState(dwTime, 100);
	if (nSet&CURSE_5)  dpCurse5.SetState(dwTime, 100);
	if (nSet&CURSE_FREEZE)  dpFreeze.SetState(dwTime, 100); // CSD-021216
}

void CMagicState::ClearNpcRun()
{ //
	m_nNature = NAT_NORMAL;
	dwNature[NAT_SPEED_UP] = 0;
	speedUp.Clear();
}

void CMagicState::ClearNpcStatusUp()
{ //
	m_nNature = NAT_NORMAL;
	dwNature[NAT_STATUS_UP] = 0;
	apShort.Clear();  // ������ ���� �ʱ�ȭ  
	apMiddle.Clear();
	apLong.Clear();
	dpShort.Clear();  // ������ ���� �ʱ�ȭ
	dpMiddle.Clear();
	dpLong.Clear();
	amplify.Clear();  // �������� �ʱ�ȭ
	dpFire.Clear();   // ���� ���� �ʱ�ȭ
	dpIce.Clear();
	dpElect.Clear();
	dpHoly.Clear();
	speedUp.Clear();  // �ӵ����� �ʱ�ȭ
}

void CMagicState::ClearNpcRecovery()
{ //
	m_nNature = NAT_NORMAL;
	dwNature[NAT_LIFE_UP] = 0; 
	dwLifeUp = 0;
	m_nLifeUp = 0;
}

void CMagicState::SetNpcRun(DWORD dwTime, int nSpeed)
{ //
	m_nNature = NAT_SPEED_UP;
	dwNature[NAT_SPEED_UP] = dwTime;
	speedUp.SetState(dwTime, nSpeed);
}

void CMagicState::SetNpcStatusUp(DWORD dwTime, int nAttack, int nDefense, int nSpeed)
{ //
	m_nNature = NAT_STATUS_UP;
	dwNature[NAT_STATUS_UP] = dwTime;
	// ������ ��� �� ����
	SetPhysicalAttack(dwTime, nAttack, nAttack, nAttack);
	SetPhysicalDefense(dwTime, nDefense, nDefense, nDefense);
	// ���� ��� �� ����
	amplify.SetState(dwTime, nAttack);
	SetMagicalDefense(dwTime, nDefense, nDefense, nDefense, nDefense);
	// �ӵ� ����
	speedUp.SetState(dwTime, nSpeed);
}

void CMagicState::SetNpcRecovery(DWORD dwTime, int nLife)
{ //
	m_nNature = NAT_LIFE_UP;
	dwNature[NAT_LIFE_UP] = dwTime; 
	dwLifeUp = dwTime;
	m_nLifeUp = nLife;
}

void CMagicState::CorrectShortDamage(int& rDamage, int nPlus, int nMinus) const
{ // �ܰŸ� ���⿡ ���� ���� ����
	int nRatio = dpShort.GetRatio();
	
	if (nPlus > 0)
	{
		nRatio += nPlus;
	}
	
	if (nMinus > 0)
	{
		nRatio -= nMinus;
		
	}
	
	rDamage -= rDamage*nRatio/100;
}

void CMagicState::CorrectMiddleDamage(int& rDamage, int nPlus, int nMinus) const
{ // �߰Ÿ� ���⿡ ���� ���� ����
	int nRatio = dpMiddle.GetRatio();
	
	if (nPlus > 0)
	{
		nRatio += nPlus;
	}
	
	if (nMinus > 0)
	{
		nRatio -= nMinus;
		
	}
	
	rDamage -= rDamage*nRatio/100;
}

void CMagicState::CorrectLongDamage(int& rDamage, int nPlus, int nMinus) const
{ // ��Ÿ� ���⿡ ���� ���� ����
	int nRatio = dpLong.GetRatio();
	
	if (nPlus > 0)
	{
		nRatio += nPlus;
	}
	
	if (nMinus > 0)
	{
		nRatio -= nMinus;
		
	}
	
	rDamage -= rDamage*nRatio/100;
}

void CMagicState::CorrectFireDamage(int& rDamage, int nPlus, int nMinus) const
{ // �Ұ迭 ������ ���� ���� ����
	int nRatio = dpFire.GetRatio();
	
	if (nPlus > 0)
	{
		nRatio += nPlus;
	}
	
	if (nMinus > 0)
	{
		nRatio -= nMinus;
		
	}
	
	rDamage -= rDamage*nRatio/100;
}

void CMagicState::CorrectIceDamage(int& rDamage, int nPlus, int nMinus) const
{ // �����迭 ������ ���� ���� ����
	int nRatio = dpIce.GetRatio();
	
	if (nPlus > 0)
	{
		nRatio += nPlus;
	}
	
	if (nMinus > 0)
	{
		nRatio -= nMinus;
		
	}
	
	rDamage -= rDamage*nRatio/100;
}

void CMagicState::CorrectElectDamage(int& rDamage, int nPlus, int nMinus) const
{ // ���ݰ迭 ������ ���� ���� ����
	int nRatio = dpElect.GetRatio();
	
	if (nPlus > 0)
	{
		nRatio += nPlus;
	}
	
	if (nMinus > 0)
	{
		nRatio -= nMinus;
		
	}
	
	rDamage -= rDamage*nRatio/100;
}

void CMagicState::CorrectHolyDamage(int& rDamage, int nPlus, int nMinus) const
{ // �ŷ°迭 ������ ���� ���� ����
	int nRatio = dpHoly.GetRatio();
	
	if (nPlus > 0)
	{
		nRatio += nPlus;
	}
	
	if (nMinus > 0)
	{
		nRatio -= nMinus;
		
	}
	
	rDamage -= rDamage*nRatio/100;
}

void CMagicState::CorrectMovePlus(int& rMove, int nPlus) const
{ //< CSD-020710
	const int nCorrent = rMove;
	
	if (speedUp.GetRatio() > nPlus)
	{
		rMove += speedUp.Convert(nCorrent);
	}
	else
	{
		rMove += (nCorrent*nPlus/100);
	}
} //> CSD-020710

void CMagicState::CorrectMoveMinus(int& rMove, int nMinus) const
{ //< CSD-021024
	const int nCorrent = rMove;
	
	if (speedDown.GetRatio() > nMinus)
	{ // �� ������ �����
		rMove -= speedDown.Convert(nCorrent);
	}
	else
	{
		rMove -= (nCorrent*nMinus/100);
	}
} //> CSD-021024

int CMagicState::GetRecoveryCombatDecHPRate(int nLevel) 
{// 030514 kyo // cpȸ�� ������ų�� ���� HP�������� %
	if( nLevel <= 0 )
	{
		return 0;
	}
	else if( nLevel == 1 )
	{
		return 5;
	}
	else if( nLevel == 2 )
	{
		return 10;
	}
	else
		return 15;
	return 0;
}