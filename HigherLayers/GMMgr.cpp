// GMMgr.cpp: implementation of the CGMMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "CItem.h"
#include "Auction.h"
#include "DefaultHeader.h"
#include "DR_NETWORK.h"
#include "GMMgr.h"
CGMMgr GMMgr;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGMMgr::CGMMgr()
{

}

CGMMgr::~CGMMgr()
{

}

int CGMMgr::IsAllGM(CHARLIST *ch)const//1�� 2�� �� ����?
{
	for(int i = 0; MAX_GM_MAIN > i ; i++)
	{
		if(	g_GmMain[i].job_level == 1
		||	g_GmMain[i].job_level == 2)//1�����̳� 2���� ��ų�� ��� 1000000 �̾�� �Ѵ�
		{
			if(1000000 !=ch->skillexp[g_GmMain[i].skill].skillexp)
			{
				return 0;
			}
		}
	}//�⺻���� All Gm�̾�� �Ѵ�
	return 1;
}

bool CGMMgr::IsMerchant(CHARLIST *ch)const
{ 
	if(IsAllGM(ch))
	{
		if(ch->skillexp[MERCHANT].skillexp == 1000000)	
		{
			return true;
		}
	}
	return false;
}

int CGMMgr::IsSkillMaster(CHARLIST *ch)const
{	
	if(IsMerchant(ch))
	{
		t_SkillExp3* pExp3 =  (t_SkillExp3*)&ch->skillexp[SKILL_MASTER];
		const int iSkillType = pExp3->skillType;
		switch(pExp3->skillType)
		{
		case GM_QUEST_BLACKSMITH_MASTER:
		case GM_QUEST_CARPENTER_MASTER:
		case GM_QUEST_BOWCRAFT_MASTER:
		case GM_QUEST_TAILOR_MASTER	:
			{
				return iSkillType;
			}break;
		default:
			{
				return 0;
			}break;
		}
	}
	return 0;
}


int CGMMgr::CanGmRegist( const int iGmIndex, CHARLIST *ch )
{
	if(	(MAX_GM_MAIN) <= iGmIndex//iGmIndex �� 0 ���� ���� ����
	||	0 > iGmIndex) 
	{
		return -1;
	}	// ������ ���
	
	if (ENABLE_GM_LEVEL >= ch->GetLevel())
	{	//< CSD-030806
		return -1;
	}	//> CSD-030806

	if(!ch->IsPayedUser()) //20 ���ϸ�//021126 lsw
	{
		return -1;
	}
		
	const GM_QUEST *pGmMain = &g_GmMain[iGmIndex];
//	if( pGmMain->need_money > ch->Money ) {return 0;}	// ���� �����ϴ�.

	for( int i=0; i<MAX_GM_NEED_ITEM_COUNT; i++ )
	{
		const int iItemNo = pGmMain->need_item[i];
		if( iItemNo )
		{	// ���� �� �������� ������ �ִ��� üũ( �κ��丮�� ������ �־�� �Ѵ�. );
			const int ct = ::CheckInventory( ch, iItemNo, pGmMain->need_quantity[i] );
			if( ct < 0 ) 
			{
				return -4;								// Ư�� �������� ������ �����ϴ�.
			}
		}
	}

	switch(pGmMain->job_level)
	{
	case 1:
	case 2:
		{
			const int iSkillExpIndex = g_GmMain[iGmIndex].skill;
			if( ch->skillexp[iSkillExpIndex].skillexp != 999999 )
			{
				return -2;			// ����ġ�� �ȵ�
			}
			if(2 == pGmMain->job_level)//case 1�� �����ϱ�
			{
				int ok =0;
				switch(iSkillExpIndex)
				{
				case CARPENTRY		:	{if(ch->skillexp[CUTDOWN].skillexp == 1000000) ok = 1;}break;
				case BLACKSMITHY	:	{if(ch->skillexp[MINING].skillexp == 1000000) ok = 1;}break;
				case COOKING		:	{if(ch->skillexp[FARMING].skillexp == 1000000 
										||	ch->skillexp[FISHING].skillexp == 1000000)ok = 1;}break;
				case TAILORING		:	{if(ch->skillexp[BUTCHERING].skillexp == 1000000) ok = 1;}break;
				case BOWCRAFTING	:	{if(ch->skillexp[CUTDOWN].skillexp == 1000000) ok = 1;}break;
				case ALCHEMING		:	{if(ch->skillexp[HERBDIGGING].skillexp == 1000000) ok = 1;}break;
				case CANDLEMAKING	:	{if(ch->skillexp[FISHING].skillexp == 1000000) ok = 1;}break;
				default:
					ok = 0;
					break;
				}
				if(1==ok){return 2;}
			}
		}break;//case 2:
	case 3:
		{
			return ((IsAllGM(ch))?3:-3);
		}break;
	case 4:
		{
			return ((IsMerchant(ch))?4:-4);
		}break;
	default:
		{
			return -3;
		}break;
	}//switch(pGmMain->job_level)
	return 1;
}