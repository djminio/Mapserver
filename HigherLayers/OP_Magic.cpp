#include "..\stdafx.h"
#include "..\LowerLayers\mylog.h"
#include "..\LowerLayers\protocol.h"
#include "..\LowerLayers\servertable.h"
#include "DefaultHeader.h"
#include "CItem.h"
#include "Scrp_exe.h"
#include "map.h"

#include "op_Magic.h"
#include "WeatherControl.h"
#include "SealStoneGameServer.h"
#include "NationSys.h"
#include "ArenaManager.h"

#define PLAYER	0
#define NPC		1

#define MAGIC_TRAP		1
#define MAGIC_OBJECT	2

#define WG_DEBUG //Added by Eleval 25/05/09

// MAGIC Operation
MAGICTRAP   g_MagicTrap;
LPMAGICTRAP g_lpMagicTrap[8][8];
int			g_Condition_Table[8][8] ;	

extern		MAGICTABLE Magic_Ref[] ;
extern		t_connection connections[] ;

extern NPCName_by_Gender	NPC_Name_Ref[Num_Of_NPC_Name];
extern NPCLev_to_Exp		NPC_Lev_Ref[Num_Of_NPC_Lev] ;
extern NPC_Generation		NPC_Gen_Ref[Num_Of_NPC_Generation] ;

extern void SendItemAttrDurationChange( t_connection c[], int cn, int pos );
extern void rollDice(int, int &) ;
extern bool isLevelUp(CHARLIST*);
extern void CheckNK( int, int, int );
extern int  BreakItemByDuration( CHARLIST *ch, POS pos );

extern NPC_Generation		NPC_Gen_Ref[Num_Of_NPC_Generation] ;

///////////////////////// 0726 lkh �߰� ///////////////////////////
extern void TameNpcAI( LPCHARLIST master );			//���ο��� ���� �ִ� �׹�NPC�� �ൿ�� ����

///////////////////////// 0803 lkh �߰� ///////////////////////////
extern void SendSkillResult( int cn, int skillno, int target_id, int x, int y, int result );
extern void SendNK( int id, int nk );
extern void SendNK( int id, int nk3, int nk4, int nk6 );

//////////////////////// 0809 lkh �߰� /////////////////////////////
extern bool CanBattleArea( LPCHARLIST a, LPCHARLIST  d);
extern void CheckNK( int a_id, int d_id, int type  );
extern void InNK( LPCHARLIST ch, int nation, short int add_nk );
extern inline int IsNKNation( LPCHARLIST ch );
extern inline int IsHeNK( LPCHARLIST ch, int nation );
BOOL	  Doing_MagicEX(CHARLIST*	Char);
void	  CheckTimeTrap(void);

extern bool ExtraExp(void);
extern int addEXP(CHARLIST *a, CHARLIST *d, int criteria, int damage );
extern int GetEnemyEnemy( CHARLIST *attacker, CHARLIST *defender );

void SendCMD_MAGIC_POSITION( t_server_magic_position *);
BOOL InsertTrap(short int, short int, short int, DWORD);
void AddTrap( LPMAGICTRAP *Header, LPMAGICTRAP lpMagicTrap_add );
extern LPMAGICTRAP	FindTrap( LPMAGICTRAP *Header, short int tile_X, short int tile_Y );
extern BOOL			ReturnSuccessResult(int small_Dice, int big_Dice, CHARLIST *caster);
void Recv_fight_stone(int cn, t_packet packet);
void Fight_Stone_End(int cn, int flag);

static BOOL	 result;  
static int	 dice1, dice2 ;

// ���������� ����� �� Ŭ������ �󼺰��� ���̺�
int		classCorrection[5][5]={0,-1,0,0,-1, 1,0,0,-1,0, 0,0,0,1,1, 0,1,-1,0,0, -1,0,1,0,0 };


POINT	tab44[44]={6,0, 6,-1, 5,-1, 5,-2, 5,-3, 4,-3, 3,-3, 3,-4, 2,-4, 1,-4, 1,-5, 0,-5, -1,-5, -1,-4, -2,-4, -3,-4, -3,-3,
-4,-3, -5,-3, -5,-2, -5,-1, -6,-1, -6,0, -6,1, -5,1, -5,2, -5,3, -4,3, -3,3, -3,4, -2,4, -1,4, -1,5, 0,5, 1,5,
1,4, 2,4, 3,4, 3,3, 4,3, 5,3, 5,2, 5,1, 6,1};

POINT	tab36[36]={5,0, 5,-1, 4,-1, 4,-2, 3,-2, 3,-3, 2,-3, 1,-3, 1,-4, 0,-4, -1,-4, -1,-3, -2,-3, -3,-3, -3,-2, -4,-2, -4,-1,
-5,-1, -5,0, -5,1, -4,1, -4,2, -3,2, -3,3, -2,3, -1,3, -1,4, 0,4, 1,4, 1,3, 2,3, 3,3, 3,2, 4,2, 4,1, 5,1 };

void SendViewType(CHARLIST *target, int view_Type, int continue_Time)
{	
	short int target_id=0;
	
	if (target->SprType == SPRITETYPE_NPC)
	{
		target_id = target->GetServerID() + 10000;
	}
	else
	{
		target_id = target->GetServerID();
	}
	
	t_packet	packet;
	
	packet.h.header.type							= CMD_SERVER_MAGICVIEWTYPE;
	packet.h.header.size							= sizeof(t_server_magicviewtype);
	
	packet.u.angra.server_magicviewtype.target_id	= target_id;
	packet.u.angra.server_magicviewtype.view_Type	= view_Type;
	packet.u.angra.server_magicviewtype.second_Time	= continue_Time;
	
	if( target_id < 10000 )		//PC�� ��츸 ����
	{
		QueuePacket(connections, target_id, &packet, 1);	//���ü���� ����
		CastMe2Other( target_id, &packet );					//���ü�� �ٶ󺸰� �ִ� ��� PC
	}
	else
		CastMe2Other( target_id-10000, &packet );			//���ü�� �ٶ󺸰� �ִ� ��� PC
}	

// PC/NPC�� ����/ü��ġ��ȭ�� �˸��� �Լ�
void SendCharacterCondition(CHARLIST* lpChar, int change_HP)
{
	t_packet p;
	
	p.h.header.type		= CMD_SERVER_CHARACTER_CONDITION;
	p.h.header.size		= sizeof(t_server_character_condition);
	p.u.angra.server_character_condition.nLife = change_HP;
	p.u.angra.server_character_condition.nState = lpChar->GetState();
	
	if( lpChar->SprType == SPRITETYPE_NPC )
	{
		p.u.angra.server_character_condition.idTarget = lpChar->GetServerID() + 10000;
		CastNPC2Other( lpChar->GetServerID(), &p );
	}
	else 
	{
		p.u.angra.server_character_condition.idTarget = lpChar->GetServerID();
		QueuePacket( connections, lpChar->GetServerID(), &p, 1);
		CastMe2Other( lpChar->GetServerID(), &p );
	}
}

bool SummonMonster(CHARLIST* pMaster, int nCreate, int nX, int nY)
{ // ���� ��ȯ
	// ����ִ� NPC�� ������ ������ ID ���ϱ�
	const int nNumber = GetAliveNPCList();	
	if (nNumber == -1)  return false;
	//MyLog(LOG_NORMAL, "SummonMonster : %d", nCreate); // CSD-LOG
	// NPC ����
	if (pMaster->IsPlayer())
	{
		if (::NPC_Create(nNumber, nCreate, nX, nY, -1, 0, GT_SKILL_SUMMON) == 0)
		{
			return false;
		}
	}
	else
	{	//< CSD-040407
		if (::NPC_Create(nNumber, nCreate, nX, nY, -1, 0, GT_SKILL_SUMMON) == 0)
		{
			return false;
		}  
	}	//> CSD-040407
	// ��ȯ�� ����  
	const WORD idMaster = pMaster->GetServerID();
	pMaster->m_xSummon.Increase(nNumber);
	// ��ȯ������ ����
	CHARLIST*	pFollowing = &NPCList[nNumber];
	if (!pFollowing) return false;
	pFollowing->SetMaster(idMaster);
	pFollowing->viewtype = VIEWTYPE_STAND_UP_;
	
	if (pMaster->IsPlayer())
	{
		const int nSprNo = pFollowing->SprNo;
		pFollowing->SetSummonMonster(true);
		pFollowing->ctrlpc = idMaster;
		pFollowing->tame = NPC_Gen_Ref[nSprNo].Taming_max;
		pFollowing->SetTamed(true);
		pFollowing->MoveP = pMaster->MoveP;
		pFollowing->tamingcountdown = 60;
		pFollowing->tame_cmd	= LC_TAME_FOLLOWME;
		pFollowing->oldpatterntype = pFollowing->patterntype;
		pFollowing->patterntype = NPC_PATTERN_TAME_;
		strcpy_s(pFollowing->HostName, sizeof(pFollowing->HostName), connections[idMaster].chrlst.Name);
	}
	
	RunArea(connections);	// ��ȯ�� ȣ��	 
	
	if (pMaster->IsPlayer())
	{
		const WORD idFollowing = pFollowing->GetServerID();
		SendNPC_Parameter(idFollowing, NPC_PARAMETER_TAME_CMD, pFollowing->tame_cmd);
		SendNPC_Parameter(idFollowing, NPC_PARAMETER_OLDPATTERNTYPE, pFollowing->oldpatterntype);
		SendNPC_Parameter(idFollowing, NPC_PARAMETER_PATTERNTYPE, pFollowing->patterntype);
		SendToAllHostName(idFollowing, pFollowing);
		// ��ȯ�� �ൿ ó��
		t_tame_command packet;
		packet.cmd = LC_TAME_FOLLOWME;
		strcpy_s(packet.mybaby, sizeof(packet.mybaby), pFollowing->Name);
		RecvTameCommand(idMaster, &packet);
	}
	
	return true;
}

bool FollowSummon(WORD idFollowing, WORD idMaster)
{
	CHARLIST* pFollowing = GetCharListPtr(idFollowing + 10000);
	if (pFollowing == NULL)  return false;
	
	t_tame_command packet;
	packet.cmd = LC_TAME_FOLLOWME;
	
	const string strName = pFollowing->Name;                                              
	
	if (strName.length() < NM_LENGTH)
	{
		strcpy_s(packet.mybaby, sizeof(packet.mybaby), strName.c_str());
		::RecvTameCommand(idMaster, &packet);
		return true;
	} 
	
	return false;
}

void KillMonster(WORD wNumber)
{
	if (wNumber >= NPC_LIST_START && wNumber < MAX_NPC_LIST)
	{ // ������ ID�� ��ȿ���� ���� �˻�
		CHARLIST* pTarget = &NPCList[wNumber];

#ifdef WG_DEBUG
		if(pTarget != NULL && !pTarget->IsTamedNpc())
		{
			if (pTarget != NULL && !(pTarget->SprNo == 55 || pTarget->SprNo == 37 || pTarget->SprNo == 31 || pTarget->SprNo == 54 || pTarget->SprNo == 16)) //Eleval 25/05/09 - To fix Monster Bug with DB, Cyc, etc...
			{
				killCharacter(NULL, pTarget);
				SendCharacterCondition(pTarget, 0);
			}
		}
		else if(pTarget != NULL && pTarget->IsTamedNpc())
		{
			killCharacter(NULL, pTarget);
			SendCharacterCondition(pTarget, 0);
		}
#else
		if (pTarget != NULL)
		{
			killCharacter(NULL, pTarget);
			SendCharacterCondition(pTarget, 0);
		}
#endif
	}
}

void CheckCharacterCondition(CHARLIST* pTarget)
{
	if (pTarget->attackedblock > 0)  --pTarget->attackedblock;
	if (pTarget->IsPlayer())
	{
		if (pTarget->GetState() == CON_DEATH)
		{ // ��ȯ�� ���Ͱ� �ִٸ� ���� ����
			pTarget->m_xSummon.Remove(KillMonster); 
		}
	}
	// �����ð��� ���� ������ ���Ͽ� ���¸� ȸ��
	pTarget->Recovery(g_curr_time);
}

void CheckTransparency(CHARLIST* pTarget, bool bAuto)
{
	if (bAuto)  
	{ // �ڵ����� ����ǵ��� ����
		pTarget->dwTransparency = 0;
	}
	
	if (pTarget->dwTransparency <= 0 && pTarget->viewtype == VIEWTYPE_TRANSPARENCY_)
	{
		pTarget->viewtype = VIEWTYPE_NORMAL_;
		SendViewType(pTarget, VIEWTYPE_NORMAL_, 0);
	}
}

////////////////////////// 0811 lkh ���� - Ư�� Ŭ���̾�Ʈ���Ը� ���� //////////////////////////
void SendMagicCommand(CHARLIST* lpChar, short int slot1, short int slot2, short int slot3)
{
	////////////////////// 0308 lkh �߰� ///////////////////////
	if(lpChar->GetServerID() == 0)	return;
	
	t_packet p;
	
	p.h.header.type		= CMD_SERVER_MAGICCOMMAND;
	p.h.header.size		= sizeof( t_server_magic_command );
	p.u.angra.server_magic_command.command			= (short) slot1;
	p.u.angra.server_magic_command.sub_command		= (short) slot2;
	p.u.angra.server_magic_command.sub_term			= (short) slot3;
	
	QueuePacket( connections, lpChar->GetServerID(), &p, 1);
}

int	 CorrectionMagicState(CHARLIST *target, int total_MagicDamage, int magic_No)	//�� �迭�� �� �� ��濡 ���� ����
{					
	int correction_Rate =0;
	
	//�� �迭�� ��/���� ��ġ ����
	switch(Magic_Ref[magic_No].order_Type)
	{				
	case 1://��		
	case 2://��		
	case 3://�Ϲ�	
	case 4://ȭ��	
	case 5://��		
	case 6://����	
	case 7://��ȯ	
	case 8://�ð�	
	case 9://�ż�	
	case 10://����	
	case 11://����	
	case 12://Ư��	
		break;		
	}				
	return correction_Rate;
}					

/*******************************************************************************************/
//	
//	
// Wizard Spell ���� �Լ���....
//	
//	
//	
/*******************************************************************************************/

///////////////////// �������� ����ġ�� ���� / �������ġ�� ���ÿ� ó����
///////////////////// 0726 lkh ���� //////////////////////
void AddCasterEXP(CHARLIST *attacker, CHARLIST *defender, int result, int magicType, int magic_Num, int damage)
{	//< CSD-030509
#ifdef LMS_MAPSERVER
	return;
#endif
	if (g_pArenaManager->IsColossusArena())
	{
		return;
	}
	
	if (attacker->IsNpc())
	{
		return;
	}
	//> CSD-030509  
	DWORD exp;
	int base_point;
	extern NPCLev_to_Exp		NPC_Lev_Ref[Num_Of_NPC_Lev];
	
	if( defender->SprType == SPRITETYPE_NPC )
	{
		if( defender->Race == HUMAN ) return;
	}
	
	if (defender->IsTamedNpc() == true) return;	// �¹ֵ� �����׼��� ��ġ�� ������ ����. 
	//	result->0:������ ��� / 1:�������� ���� �׿��� ��� / 2:������ ������ ���
	//	magicType->0:�Ϲ� ���� 1,2,3->���� ���� 
	
	//	1 : �Ϲ� ����					
	//	2 : 							
	//	3 : ���ְ迭����.				
	
	switch( magicType )				
	{			
	case 0 : //�Ϲݸ���(���� ����/ ���� �����ְų� ������ ���ظ� ���� �ʴ¸��� )
		{			
			if(result)	//���� ���� ���
			{		
				switch(magic_Num)
				{	
					// Healing
				case 1 :
					// GreatHealing
				case 6 :
					// ȸ���ǱǴ�
				case 151 :
					//��ġ�� ����
				case 156 :		
					exp = (DWORD)(damage*2/100) + 15;	// �÷��� hp���� 2%�� ����ġ�� �ش�. 
					break;
					
				default:		base_point = (int)Magic_Ref[magic_Num].Exp;			//�Ϲ� ������ ������ ��� ����ġ��
					exp = (DWORD)(base_point);
					break;
				}	
				
				switch( defender->SprNo )
				{	
				case 92 :	// ���..
				case 93 :	// ���..
				case 94 :	// ����..
				case 95 :	// ����ƺ�.
					{
						if (attacker->GetLevel() <= ENABLE_DUMMY_LEVEL)
						{	//< CSD-030806  
							attacker->ChangeUpAddExp(exp);
							attacker->ChangeUpTacExp(2, exp*3);
							isLevelUp(attacker);
						}	//> CSD-030806
						
						break;
					}
				case 96  : //  ��ƽ���ÿ�.			
					{
						attacker->ChangeUpTacExp(3, exp/3);
						
						if (attacker->Mana < attacker->ManaMax)
						{								
							attacker->Mana = attacker->ManaMax;
							attacker->SendCharInfoBasic( MP, attacker->Mana );//020704 lsw
							//							attacker->TempMana = attacker->Mana;//020214 lsw
						}								
						break;							
					}									
				default :							
					{ //< CSD-020821  
						attacker->ChangeUpAddExp(exp);
						attacker->ChangeUpTacExp(2, exp*3);
						isLevelUp(attacker);
						break;
					} //> CSD-020821
				}
			}		
			break;
		}			
	case 1 :
	case 2 :
	case 3 :
		{			
			switch( defender->SprNo )
			{	
			case 92 :	// ���..
			case 93 :	// ���..
			case 94 :	// ����..
			case 95 :	// ����ƺ�.
				{
					if (attacker->GetLevel() > ENABLE_DUMMY_LEVEL)
					{	//< CSD-030806
						break;
					}	//> CSD-030806

					exp = addEXP( attacker, defender, result, damage );
					attacker->ChangeUpTacExp(2, damage);
					isLevelUp(attacker);
					break;
				}
			case 96 : //  ��ƽ���ÿ�. 
				{
					int d = (attacker->GetLevel()/10); //< CSD-030806
					if( d == 0 ) d = 1;
					attacker->ChangeUpTacExp(3, damage/2/d);
					attacker->Mana = attacker->ManaMax;
					attacker->SendCharInfoBasic(MP, attacker->Mana );//020704 lsw
					//					attacker->TempMana = attacker->Mana; //020214 lsw
					break;
				}
			default :
				exp = addEXP( attacker, defender, result, damage );
				attacker->ChangeUpTacExp(2, exp*3);
				isLevelUp(attacker);
				break;
			}	
			break;
		}		
	}			
}				

bool IsMovable(int& rX, int& rY)
{
	if (g_lpMapFile->wWidth <= rX)   rX = g_lpMapFile->wWidth - 1;
	if (g_lpMapFile->wHeight <= rY)  rY = g_lpMapFile->wHeight - 1;
	// Don't �Ӽ�, ����, �ٸ� ĳ���Ϳ� ���� ������ ���¶�� �̵� �Ұ�
	//< CSD-030210
	if (TileMap[rX][rY].attr_dont)    return false;
	if (TileMap[rX][rY].attr_inside)  return false;
	if (TileMap[rX][rY].attr_light)   return false;
	//< CSD-030210
	return true;
}

void TransArea(BYTE nType, CHARLIST* pTarget, int nX, int nY)
{ // ��ġ �̵�
	//< CSD-020909 : ������ ������ ��ġ ����
	pTarget->MoveGox = pTarget->X = nX<<5;
	pTarget->MoveGoy = pTarget->Y = nY<<5;
	pTarget->MoveSx	= nX;
	pTarget->MoveSy	= nY;
	pTarget->OldMoveSx = nX;
	pTarget->OldMoveSy = nY;
	pTarget->MovePathCount	= 0;
	pTarget->MoveLength		= 0;	
	//> CSD-020909
	if (pTarget->IsNpc())
	{
		SetArea(MOVE_NPC_AREA, pTarget->GetServerID());
	}
	else
	{
		SetArea(MOVE_PC_AREA, pTarget->GetServerID());
	}
    
	t_server_magic_position	smp;
	smp.nType =	nType;
	smp.idTarget = (pTarget->IsNpc()) ? (pTarget->GetServerID() + 10000):(pTarget->GetServerID());
	smp.nX = nX;
	smp.nY = nY;  
	SendCMD_MAGIC_POSITION(&smp);
}

void TransMap(CHARLIST* pTarget)
{ // �� �̵�
	// ���� �̵� ��� ���� ���ϱ�
	int nPort = 0, nX = 0, nY = 0;
	pTarget->GetTransMap(nPort, nX, nY);
	// ���̸� ���ϱ�
	const string strMapName = GetMapName(nPort);
	
	if (strMapName == pTarget->MapName)
	{ // ���� �ʿ��� ��� �̵�
		TransArea(PT_TELEPORT, pTarget, nX, nY);
	}
	else
	{ // �ٸ� ������ ��� �̵�
		MapMove(pTarget->GetServerID(), (char*)strMapName.c_str(), nX, nY);
	}
	// ���� �̵� ��� ���� �ʱ�ȭ
	pTarget->ClearTransMap();
}

/////////////////////////// 0111 �̱��� /////////////////////////////////
void SendCMD_MAGICTRAP_EXPOSE( t_server_magictrap_expose *p)
{
	t_packet	packet;
	
	packet.h.header.type							= CMD_SERVER_MAGICTRAP_EXPOSE;
	packet.h.header.size							= sizeof(t_server_magictrap_expose);
	
	packet.u.angra.server_magictrap_expose.target_id		= (short int)p->target_id;
	packet.u.angra.server_magictrap_expose.x				= (short int)p->x;
	packet.u.angra.server_magictrap_expose.y				= (short int)p->y;
	packet.u.angra.server_magictrap_expose.trap_Type		= (short int)p->trap_Type;
	
	if(p->target_id<10000)
	{
		QueuePacket(connections, p->target_id, &packet, 1);		//���ü���� ����
		CastMe2Other( p->target_id, &packet );								//���ü�� �ٶ󺸰� �ִ� ��� PC
	}
	else
		CastNPC2Other( p->target_id-10000, &packet );
}

void SendCMD_MAGIC_POSITION( t_server_magic_position *p)
{
	t_packet	packet;
	packet.h.header.type = CMD_SERVER_MAGIC_POSITION;
	packet.h.header.size = sizeof(t_server_magic_position);
	packet.u.angra.server_magic_position.nType= p->nType;
	packet.u.angra.server_magic_position.idTarget	= p->idTarget;
	packet.u.angra.server_magic_position.nX	= p->nX;
	packet.u.angra.server_magic_position.nY	= p->nY;
	
	if (p->idTarget >= 10000)
	{
		CastNPC2Other(p->idTarget - 10000, &packet);
	}
	else 
	{
		QueuePacket(connections, p->idTarget, &packet, 1); //���ü���� ����
		CastMe2Other(p->idTarget, &packet); //���ü�� �ٶ󺸰� �ִ� ��� PC
	}
}

void RecvCMD_CLIENT_CHARACTER_DEMAND(int cn, t_client_character_demand *p)
{	//< CSD-030515
	CHARLIST* target = GetCharListPtr(p->target_id);
	if (!target) return;

	switch (p->command_type)
	{	
	case CCD_PLAYSOUND_EVENT1:	
		{	// ������� ��� ��û
			t_packet packet;
			packet.h.header.type = CMD_SERVER_MAGICCOMMAND;
			packet.h.header.size = sizeof(t_server_magic_command);
			packet.u.angra.server_magic_command.command	= 851;
			packet.u.angra.server_magic_command.sub_command	= 0;
			packet.u.angra.server_magic_command.sub_term = 0;
			QueuePacket(connections, cn, &packet, 1);
			break;
		}
	case CCD_PLAYSOUND_EVENT2:
		{	// �ڼ��Ҹ� ��û
			t_packet packet;
			packet.h.header.type = CMD_SERVER_MAGICCOMMAND;
			packet.h.header.size = sizeof(t_server_magic_command);
			packet.u.angra.server_magic_command.command	= 853;
			packet.u.angra.server_magic_command.sub_command	= 0;
			packet.u.angra.server_magic_command.sub_term = 0;
			QueuePacket(connections, cn, &packet, 1);
			break;
		}
	case CCD_START_QUEST:	
		{	// ����Ʈ �������� ��� ��û 
			t_packet packet;
			packet.h.header.type = CMD_SERVER_MAGICCOMMAND;
			packet.h.header.size = sizeof(t_server_magic_command);
			packet.u.angra.server_magic_command.command	= CCD_START_QUEST;
			packet.u.angra.server_magic_command.sub_command	= 0;
			packet.u.angra.server_magic_command.sub_term = 0;
			QueuePacket(connections, p->target_id, &packet, 1);
			break;
		}
	case CCD_END_QUEST:	
		{	// ����Ʈ ���� ��� ��û 
			t_packet packet;
			packet.h.header.type = CMD_SERVER_MAGICCOMMAND;
			packet.h.header.size = sizeof(t_server_magic_command);
			packet.u.angra.server_magic_command.command	= CCD_END_QUEST;
			packet.u.angra.server_magic_command.sub_command	= 0;
			packet.u.angra.server_magic_command.sub_term = 0;
			QueuePacket(connections, p->target_id, &packet, 1);
			break;
		}
	case CCD_QUEST_SALUTE:
		{
			t_packet packet;
			packet.h.header.type = CMD_SERVER_MAGICCOMMAND;
			packet.h.header.size = sizeof(t_server_magic_command);
			packet.u.angra.server_magic_command.command	= CCD_QUEST_SALUTE;
			packet.u.angra.server_magic_command.sub_command	= p->target_id;
			packet.u.angra.server_magic_command.sub_term = 0;
			QueuePacket(connections, p->target_id, &packet, 1);
			break;
		}
	case CCD_QUEST_GETSKILL: 
		{	// ����Ʈ ���ȹ�� ��� ��û
			t_packet packet;
			packet.h.header.type = CMD_SERVER_MAGICCOMMAND;
			packet.h.header.size = sizeof(t_server_magic_command);
			packet.u.angra.server_magic_command.command	= CCD_QUEST_GETSKILL;
			packet.u.angra.server_magic_command.sub_command = 0;
			packet.u.angra.server_magic_command.sub_term = 0;
			QueuePacket(connections, p->target_id, &packet, 1);
			break;
		}
	case CCD_QUEST_GETITEM:	
		{	// ����Ʈ ������ȹ�� ��� ��û 
			t_packet packet;
			packet.h.header.type = CMD_SERVER_MAGICCOMMAND;
			packet.h.header.size = sizeof(t_server_magic_command);
			packet.u.angra.server_magic_command.command	= CCD_QUEST_GETITEM;
			packet.u.angra.server_magic_command.sub_command = 0;
			packet.u.angra.server_magic_command.sub_term = 0;
			QueuePacket(connections, p->target_id, &packet, 1);
			break;
		}
	case CCD_QUEST_MONSTER:
		{	// ����Ʈ ������ ħ�� 
			t_packet packet;
			packet.h.header.type = CMD_SERVER_MAGICCOMMAND;
			packet.h.header.size = sizeof(t_server_magic_command);
			packet.u.angra.server_magic_command.command = CCD_QUEST_MONSTER;
			packet.u.angra.server_magic_command.sub_command	= 0;
			packet.u.angra.server_magic_command.sub_term = 0;
			QueuePacket(connections, cn, &packet, 1);
			break;
		}
	case CCD_START_QUEST_BBS:
		{	// ���ڻ���(����) 
			t_packet packet;
			packet.h.header.type = CMD_SERVER_MAGICCOMMAND;
			packet.h.header.size = sizeof(t_server_magic_command);
			packet.u.angra.server_magic_command.command = CCD_START_QUEST_BBS;
			packet.u.angra.server_magic_command.sub_command	= 0;
			packet.u.angra.server_magic_command.sub_term = 0;
			QueuePacket(connections, cn, &packet, 1);
			break;//��� �����ڿ��� ����
		}
	case CCD_END_QUEST_BBS:	//���ڻ���(����) ��Ȳ ����.
		{
			t_packet packet;
			packet.h.header.type = CMD_SERVER_MAGICCOMMAND;
			packet.h.header.size = sizeof(t_server_magic_command);
			packet.u.angra.server_magic_command.command	= CCD_END_QUEST_BBS;
			packet.u.angra.server_magic_command.sub_command	= 0;
			packet.u.angra.server_magic_command.sub_term = 0;
			QueuePacket(connections, cn, &packet, 1);
			break;
		}
	case CCD_COMPLETE_QUEST:
		{	// ����Ʈ�� ������ ������ ȿ��
			t_packet packet;
			packet.h.header.type = CMD_SERVER_MAGICCOMMAND;
			packet.h.header.size = sizeof(t_server_magic_command);
			packet.u.angra.server_magic_command.command	= CCD_COMPLETE_QUEST;
			packet.u.angra.server_magic_command.sub_command	= p->target_id;
			packet.u.angra.server_magic_command.sub_term = 0;
			QueuePacket(connections, cn, &packet, 1);
			break;
		}
	case CCD_FIGHT_LOSE: // 1:1 ������� ���..
		{	// �����
			Fight_Stone_End(cn, 1);
			break;
		}
	case CCD_FIGHT_DRAW:
		{	// �����
			Fight_Stone_End(cn, 3);
			break;
		}
	case CCD_FIGHT_LOGOUT:
		{	// �α׾ƿ��� ���
			Fight_Stone_End(cn, 4);
			break;
		}
	}
}	//> CSD-030515

void LoadConditionTable(void)
{
	FILE* file;
	int buff = 0;
	
	char DataPath[MAX_PATH];
	
	wsprintf( DataPath, "%s/data/condition_table.txt",  GameServerDataPath  );
	file = fopen( DataPath, "rt");
	if(file)
	{
		for(int i=0; i<8; i++)
			for(int j=0; j<8; j++)
				fscanf_s(file, "%d", &g_Condition_Table[i][j] );
			fclose(file);
			
			file=fopen("./OutPut/condition_table.bin", "wb" );
			if(file)
			{
				fwrite( g_Condition_Table, sizeof(int), 64, file);
				fclose(file);
			}
	}
	else
	{
		file = fopen( "./OutPut/condition_table.bin", "rb" );
		if(file)
		{
			fread( g_Condition_Table, sizeof(int), 64, file);
			fclose(file);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//									�� ��ġ ���� �Լ�(0111)                                       //
/////////////////////////////////////////////////////////////////////////////////////////////////// 

void InitTrap()
{
	memset(g_lpMagicTrap, 0, sizeof(g_lpMagicTrap));
}

BOOL InsertTrap(short int tile_X, short int tile_Y, short int trap_Type, DWORD	continue_Time)
{
	if (tile_X < 0)  return FALSE;
	if (tile_Y < 0)  return FALSE;
	if (tile_X >= g_Map.file.wWidth - 1)  return FALSE; 
	if (tile_Y >= g_Map.file.wHeight -1)	return FALSE;
	
	LPTILE tile = &TileMap[tile_X][tile_Y];
	if (tile == NULL)       return FALSE;
	if (tile->attr_dont)		return FALSE;
	if (tile->attr_magic)		return FALSE;
	if (tile->attr_inside)  return FALSE;
	if (tile->attr_map)		  return FALSE; 
	if (tile->occupied)		  return FALSE;
	if (tile->attr_light)   return FALSE;
	
	tile->attr_magic = 1;
	// ���� ��� Ÿ�� �Ӽ��� Ʈ�� ��ġ �Ӽ� �ο�
	g_MagicTrap.trap_X = tile_X;
	g_MagicTrap.trap_Y = tile_Y;
	g_MagicTrap.trap_Type	= trap_Type;
	g_MagicTrap.Time = continue_Time;
	AddTrap(&g_lpMagicTrap[tile_X/((g_Map.file.wWidth+7)/8)][tile_Y/((g_Map.file.wHeight+7)/8)], &g_MagicTrap);
	return TRUE;
}

void AddTrap( LPMAGICTRAP *Header, LPMAGICTRAP lpMagicTrap_add )		//��ũ�� ����Ʈ�� �Ӹ��� �ٿ� �ֱ�
{		
	LPMAGICTRAP t, temp;
	
	if( *Header == NULL )		//��ũ�� ����Ʈ ���� ����
	{	
		MemAlloc( *Header, sizeof( MAGICTRAP ));
		(*Header)->trap_X		= lpMagicTrap_add->trap_X;
		(*Header)->trap_Y		= lpMagicTrap_add->trap_Y; 
		(*Header)->trap_Type	= lpMagicTrap_add->trap_Type; 
		(*Header)->Time			= lpMagicTrap_add->Time;
		
		(*Header)->prev			= NULL;
		(*Header)->next			= NULL;
	}		
	else						//�̹� ������ ����Ʈ�� ÷�� ����/�ε��ؿ� �����Ͱ� ���� ���
	{	
		t = NULL;
		MemAlloc( t, sizeof( MAGICTRAP ));
		
		t->trap_X			= lpMagicTrap_add->trap_X;
		t->trap_Y			= lpMagicTrap_add->trap_Y; 
		t->trap_Type		= lpMagicTrap_add->trap_Type;
		t->Time				= lpMagicTrap_add->Time;
		
		temp = *Header ;
		temp->prev = t;
		t->next = temp;
		t->prev = NULL;
		*Header = t;
	}
}


void DeleteTrap( LPMAGICTRAP *Header, LPMAGICTRAP lpMagicTrap_Delete)
{		
	
	LPMAGICTRAP  t = *Header;//g_lpMapSkillTable;
	
	while( t != NULL )
	{		
		if( t == lpMagicTrap_Delete )
		{
			if( lpMagicTrap_Delete == *Header )		//header�� ���ŵǴ� ���
			{
				t = (*Header)->next;
				
				if(*Header!=NULL)
					MemFree( *Header );
				
				if(t!=NULL)
				{
					*Header = t;
					(*Header)->prev = NULL;
				}
				return;
			}
			else 
			{
				if ( t->prev != NULL )
				{
					t->prev->next = t->next;
				}
				if( t->next != NULL )
				{
					t->next->prev = t->prev;
				}
				
				MemFree( t );
				return;
			}
		}
		
		t= t->next;
	}
}		

//	���� ������ǥ...7
LPMAGICTRAP FindTrap( LPMAGICTRAP *Header, short int tile_X, short int tile_Y )
{	   	
	LPMAGICTRAP	t;
	t = *Header;
	while( t != NULL )
	{	
		if( t->trap_X == tile_X && t->trap_Y == tile_Y )
		{
			return t;
		}
		t = t->next;
	}		
	return NULL;
}

bool SearchTrap(CHARLIST* pCaster, int nX, int nY)
{ // Ŭ���� ������ ���� 5Ÿ�� ������ �������� ����/��/����ü Ž�� 
	for (int i = -2; i < 3; i++)
	{
		const int nFindX = nX + i;
		
		for (int j = -2; j < 3; j++)
		{			
			const int nFindY = nY + j;

			if (nFindX < 0)  return false;
			if (nFindY < 0)  return false; 
			if (nFindX >= g_lpMapFile->wWidth)   return false;
			if (nFindY >= g_lpMapFile->wHeight)  return false;

			if (TileMap[nFindX][nFindY].attr_magic == 1)	
			{ // ���� ȿ�� �ִ� ���
				LPMAGICTRAP lpHeader = g_lpMagicTrap[nFindX/((g_Map.file.wWidth+7)/8)][nFindY/((g_Map.file.wHeight+7)/8)];
				LPMAGICTRAP lpMagicTrap = FindTrap(&lpHeader, nFindX, nFindY);
				
				if (lpMagicTrap != NULL) 
				{ //ã�� Ʈ���� �ִ� ���
					t_packet	packet;
					packet.h.header.type = CMD_SERVER_MAGICAL_DETECT;
					packet.h.header.size = sizeof(t_server_magical_detect);
					packet.u.angra.server_magical_detect.tile_X	= nFindX;
					packet.u.angra.server_magical_detect.tile_Y	= nFindY;
					packet.u.angra.server_magical_detect.type	= MAGIC_TRAP;
					// ���ü���� ��� ����
					QueuePacket(connections, pCaster->GetServerID(), &packet, 1);	
					return true;
				}
			}
		}
	}
	
	return false;
}

void	SendExposeTrap(CHARLIST* lpChar, short int tile_X, short int tile_Y, short int trap_Type)				//������ ó�� �� ȿ��������� Ŭ���̾�Ʈ�� ���� ����	
{
	t_server_magictrap_expose		server_magictrap_expose;
	
	if (lpChar->SprType == SPRITETYPE_NPC)
	{
		server_magictrap_expose.target_id = lpChar->GetServerID() + 10000;
	}
	else
	{
		server_magictrap_expose.target_id = lpChar->GetServerID();
	}
	
	server_magictrap_expose.x					= (short int)tile_X;
	server_magictrap_expose.y					= (short int)tile_Y;
	server_magictrap_expose.trap_Type			= (short int)trap_Type;
	
	SendCMD_MAGICTRAP_EXPOSE( &server_magictrap_expose );
}

void	CheckTimeTrap(void)
{
	static DWORD	time;
	if( g_curr_time - time < 10 )  return;
	time = g_curr_time;
	
	LPMAGICTRAP	magictrap, t;
	
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			magictrap	=	g_lpMagicTrap[i][j];
			
			while(magictrap!=NULL)
			{
				if(magictrap->Time <= g_curr_time)
				{
					TileMap[magictrap->trap_X][magictrap->trap_Y].attr_magic = 0;		//��ȿ �ð� ����� ���
					t = magictrap->next;
					DeleteTrap(&g_lpMagicTrap[i][j], magictrap);
					magictrap=t;
					continue;
				}
				magictrap=magictrap->next;
			}
		}
	}
}

void NPCLostSight(CHARLIST *target, int Time)
{
	target->ApplyCurse(4, CON_SLOW, g_curr_time + Time);
}

BOOL ReturnSuccessResult(int small_Dice, int big_Dice, CHARLIST *caster)
{
	short int		wisdom		= caster->Wis;						//max:500
	short int		intelligence= caster->Int;						//max:500
	short int		WS_PS		= caster->wsps;						//max:500
	short int		total_Rate	= (wisdom+intelligence+WSPS)/100;	//����Ȯ���� ����(���ϴ°�) -> 0~50���� ��ġ
	
	big_Dice += total_Rate;
	
	rollDice(small_Dice, dice1) ;
	rollDice(big_Dice, dice2) ;
	
	if (dice1 <= dice2)
	{
		return TRUE;
	}
	
	return FALSE;
}

void Recv_fight_stone(int cn, t_packet packet)	//cn ��Ŷ�� ���� ��..
{	//< CSD-030515
	const int attack_id = cn;
	const int defend_id = packet.u.angra.server_fight_stone.fight_id; //�ο�� �𿡰Ե� flag�� ���..
	
	CHARLIST* attacker = CheckServerId(attack_id);

	if (attacker == NULL)
	{
		return;
	}

	if(attacker->fight_flag!=1)
	{
		attacker->fight_flag = packet.u.angra.server_fight_stone.fight_flag;
		attacker->fight_id   = defend_id;
	}
	
	CHARLIST* defender = CheckServerId(defend_id);

	if (defender == NULL)
	{
		return;
	}

	if(defender->fight_flag!=1)
	{
		defender->fight_flag = packet.u.angra.server_fight_stone.fight_flag;
		defender->fight_id = attack_id;
	}
}	//> CSD-030515