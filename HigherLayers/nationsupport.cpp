#include "..\stdafx.h"
#include "DefaultHeader.h"
#include "CItem.h"
#include "Op_Magic.h"
#include "Op_Battle.h"
#include "Map.h"
#include "ChrLog.h"
#include "nationsys.h"

extern cWarfield*	g_pWarfield;

extern bool isNationWarfieldServer();
extern bool isNationManageServer();

#define MAX_SQUAD_1_RARE_CALSS	5
#define MAX_SQUAD_2_RARE_CALSS	4
#define MAX_SQUAD_3_RARE_CALSS	3
#define MAX_SQUAD_4_RARE_CALSS	2

#define MAX_SQUAD_NUMBER		4
#define MAX_SQUAD_RARE			3

int		iSquadRareType[MAX_SQUAD_NUMBER][MAX_SQUAD_RARE];
bool	bSquadRared[MAX_SQUAD_NUMBER];

//��ȹ�ڰ� ������ �������� �ƽ���.
const int	iSquadMaxRareClass[MAX_SQUAD_NUMBER]	=	{MAX_SQUAD_1_RARE_CALSS,MAX_SQUAD_2_RARE_CALSS,MAX_SQUAD_3_RARE_CALSS,MAX_SQUAD_4_RARE_CALSS};
//��Ȳ�� ���� ���ϴ� �ƽ���.
int		iSquadNowMaxRareClass[MAX_SQUAD_NUMBER]	=	{MAX_SQUAD_1_RARE_CALSS,MAX_SQUAD_2_RARE_CALSS,MAX_SQUAD_3_RARE_CALSS,MAX_SQUAD_4_RARE_CALSS}; 
int		iSquadNowRareClass[MAX_SQUAD_NUMBER]	=	{0,0,0,0}; 

void SquadRarePlus(CHARLIST *ch, int iRareType, int iClass)
{
	if(!isNationWarfieldServer()) return;//���Ⱑ ������ �� �ƴϸ� ����� ����ġ�� ���� �ʴ´�.	
	
	int iPlusValue = ItemRare[iRareType].GRADE[iClass];
}


//������ �� ������ �� �̰Ŵ�... Ŭ������ ���� ���� Ÿ���� ��� ����
int CheckSquadRareGrade( int  iBattleType,int iSquadNo, int iManCount, bool bCommanderLogin, bool bSquadLeaderLogin, int iSquadItemStatus)
{
	int iRareSquadGradeNow = 0;
	//���� �� ������ üũ ����
	//�δ����� ��� �ʰ� ���ÿ� ���� Ÿ���� ������ �ȴ�
	if(!isNationWarfieldServer()) return 0;//����� üũ �ؼ� �⺻���ΰ� ��� üŷ �� �д�	
	
	int MemberCount = g_pWarfield->GetSquadCurrentMemberCount(iBattleType,iSquadNo);
	
	if( MemberCount )//����
	{	
		if(MemberCount < 19 )
			iRareSquadGradeNow = 1;
		if(MemberCount < 29 && MemberCount > 19 )
			iRareSquadGradeNow = 2;
		if(MemberCount < 39 && MemberCount > 29 )
			iRareSquadGradeNow = 3;
		if(MemberCount < 49 && MemberCount > 39)
			iRareSquadGradeNow = 4;
		if(MemberCount > 49 )
			iRareSquadGradeNow = 5;

		iSquadNowRareClass[iSquadNo] = iRareSquadGradeNow ;//�̳��� ���� �ٲ� �ָ� �ȴ�
	}

	//��ɰ��� ������ �ƽ� ���� true �� �����ش� ( +1 �Ǵ°� )
	iSquadNowMaxRareClass[iSquadNo] = iSquadNowMaxRareClass[iSquadNo]+bCommanderLogin;

	if( bSquadLeaderLogin )//�δ����� ������ ����� �ش�
	{
		if(iSquadItemStatus)//��� ��� �������� ���� �� ���� +1 �� �ǰ� ��� ���� �������� ���� -1�� �ȴ�.
		{
			iSquadNowRareClass[iSquadNo] += iSquadItemStatus;//���� ��Ÿ���̹Ƿ� �������� �Ѵ�.
			if( iSquadNowRareClass[iSquadNo] > iSquadNowMaxRareClass[iSquadNo])
			{
				iSquadNowRareClass[iSquadNo]=iSquadNowMaxRareClass[iSquadNo];
			}
			else if( iSquadNowRareClass[iSquadNo] < 0)
			{
				iSquadNowRareClass[iSquadNo] =0;
			}

		}
	}
	else
	{
		iSquadNowRareClass[iSquadNo] = 0;//�δ����� ������ ���δ�.
	}
	return iRareSquadGradeNow = iSquadNowRareClass[iSquadNo];
}

//����Ÿ�� ( Attacker Defencer ReForce), Ŀ�ؼ� �ѹ�, ���� ���� ������(���)
void SquadRareReSet(int iBattleType, int cn,int iSquadItemStatus)//iSquadItemStatus->���� ��� �����ۿ� ���� Ŭ���� ���氪
{//020215 lsw

	//Ÿ�԰� �δ� �ѹ��� ��ɰ��� ������ �ֳ��� üũ �Ͽ�
	//�ο��� ���� �Ӽ��� ����� �̾Ƴ���
	CHARLIST *ch = &connections[cn].chrlst;
	if (!ch) return;
	
	int iSquadNo  = connections[cn].chrlst.NWCharacter.SquadNo;
	int iRareClass = 0;

	//�̰� ���ʵ� �ΰ�.
	if(!isNationWarfieldServer()) return;

	bool bCommanderLogin = g_pWarfield->CommanderExist(iBattleType);
	bool bSquadLeaderLogin = g_pWarfield->SquadLeaderExist(iBattleType,connections[cn].chrlst.NWCharacter.SquadNo);

	int iSquadRareClass = CheckSquadRareGrade(iBattleType ,iSquadNo , g_pWarfield->GetSquadCurrentMemberCount(iBattleType,iSquadNo),  bCommanderLogin, bSquadLeaderLogin, iSquadItemStatus);

	//Ÿ��( ������ , ����� , �뺴)
	//������ �ѹ� �� ��ġ �ϴ� ����� �˻� �� ����
	SquadList* g_SquadList;
	g_SquadList = g_pWarfield->GetSquadListPointer(iBattleType,iSquadNo);	
	
	char SquadRare[3] = {0,0,0};
	//011008 lsw �̰� �ּ� Ǫ����
	memcpy(SquadRare,g_pWarfield->GetSquadRareSok2(iBattleType,iSquadNo),3);
	
	for(SquadListItor itor=g_SquadList->begin();	itor!=g_SquadList->end()	;	itor++)
	{
		//������� 0,1,2,3 ���� �� �ּ���.. 
		ch = &connections[(*itor)->GetData()].chrlst;
		if(ch)
		{
				ch->SquadRare.grade		= iSquadRareClass;
				ch->SquadRare.soksung1	= SquadRare[0];
				ch->SquadRare.soksung2	= SquadRare[1];
				ch->SquadRare.soksung3	= SquadRare[2];
				ResetAbility(ch);
		}
	}
	
}

//���� ������ ������ ȣ�� // �Ӽ����ϱ⸸ �մϴ�.
void GetSquadRare(char *Squadrare,int squadNo/*char [3]*/)
{
	if( !isNationManageServer() )
		return;

	if (!Squadrare[0]) //�̹� �Ӽ��� ���� ���� �Ӽ� �ο� ���� �ʴ´�
	{
		int squadrarecount =0;
		int	squadrarecountMax =0;
		
		switch (squadNo)
		{
			case 1:
			case 2:
				{
					squadrarecountMax	= 3;
				}break;
			case 3:
			case 4:
				{
					squadrarecountMax	= 2;
				}break;
			default:
				squadrarecountMax	= 0;
				break;
		}
		for(squadrarecount = 0;squadrarecount<squadrarecountMax;squadrarecount++)
		{
			//���� �Ӽ��� �޾ƿԴ�//�Ӽ��� ��� ��������.
			//���⼭ �־��ֱ�
			Squadrare[squadrarecount] = ItemMgr.GetAbleRareKind(RARE_ABLE|RARE_ABLE_SQUAD,0);//��������//020725 lsw
		}
	}
}

extern bool isNewWarfieldServer();
extern CNewWarfield* g_pNewWarfield;


// 020418 YGI
int IsStartNationWar()		// �� ���� ���� ���̰� ���� ���� ���ΰ�?
{
	if (isNationWarfieldServer())
	{
		if (g_pWarfield->GetStatus()==NW_WAR)
			return true;
	}
	if (isNewWarfieldServer())
	{
		if (g_pNewWarfield->GetWarfieldStatus()==NW_WAR)
			return true;
	}
	return false;
//	return ( isNationWarfieldServer() && g_pWarfield->GetStatus()==NW_WAR );
}
