#include "..\stdafx.h"
#include "DefaultHeader.h"
#include "CItem.h"
#include "Op_Magic.h"
#include "WeatherControl.h"


extern CItem_List Item_Ref ;
extern t_connection	connections[DRAGON_MAX_CONNECTIONS_+1];
void getItemIndex(int, int &, int &) ;

const char equip_able[9]={2, 3, 4, 5, 6, 7, 8, 8, 9 } ;
//////////////////////////////////////////////////////////////////////////
//
// �Լ�����: �ش���ġ�� item�� ������ �ִ��� �Ǻ��ϴ� �Լ�(ġ���̳� ����
//				�� ����� ó��)
// �Ķ����:	item_no; ������ ��ȣ
//				char_id; ������ �� ĳ������ id(index)			
//				source; �������� ��ġ�� ��� ����
//
// ���ϰ�: ������ ���� ����
//
//////////////////////////////////////////////////////////////////////////

//Functions added by Eleval for new items

bool SummonMonsterItem(CHARLIST *pCaster, int X, int Y) //Function made by Eleval for Summoning Potion 22/05/09
{
	int smID = 7;
	int randID = rand()%3;
	if(pCaster->fame < 1000)
		return false;
	else if(pCaster->fame >= 1000 && pCaster->fame < 1050)
		switch(randID)
		{
			case 0:
				smID = 7; //Skelleton
				break;
			case 1:
				smID = 8; //Goblin
				break;
			case 2:
				smID = 5; //Zombie
				break;
		}
	else if(pCaster->fame >= 1050 && pCaster->fame < 1100)
		switch(randID)
		{
			case 0:
				smID = 62; //Orc
				break;
			case 1:
				smID = 33; //Wolf
				break;
			case 2:
				smID = 11; //Bear
				break;
		}
	else if(pCaster->fame >= 1100 && pCaster->fame < 1150)
		switch(randID)
		{
			case 0:
				smID = 14; //Lycanthrope
				break;
			case 1:
				smID = 43; //Harpy
				break;
			case 2:
				smID = 49; //Skellton King
				break;
		}
	else if(pCaster->fame >= 1150 && pCaster->fame < 1200)
		switch(randID)
		{
			case 0:
				smID = 42; //Mujina
				break;
			case 1:
				smID = 40; //Man Scorp
				break;
			case 2:
				smID = 47; //Lizard Man
				break;
		}
	else if(pCaster->fame >= 1200 && pCaster->fame < 1250)
		switch(randID)
		{
			case 0:
				smID = 13; //Troll
				break;
			case 1:
				smID = 38; //Stone Golem
				break;
			case 2:
				smID = 38; //Stone Golem
				break;
		}
	else if(pCaster->fame >= 1250 && pCaster->fame < 1300)
		switch(randID)
		{
			case 0:
				smID = 44; //Crystal Golem
				break;
			case 1:
				smID = 4; //Baku
				break;
			case 2:
				smID = 12; //Ogre
				break;
		}
	else if(pCaster->fame >= 1300 && pCaster->fame < 1400)
		switch(randID)
		{
			case 0:
				smID = 171; //White Bear
				break;
			case 1:
				smID = 45; //Specter
				break;
			case 2:
				smID = 10; //Gargoyle
				break;
		}
	else if(pCaster->fame >= 1400 && pCaster->fame < 1500)
		switch(randID)
		{
			case 0:
				smID = 10; //Gargoyle
				break;
			case 1:
				smID = 34; //Brue
				break;
			case 2:
				smID = 45; //Specter
				break;
		}
	else if(pCaster->fame >= 1500 && pCaster->fame < 1600)
		switch(randID)
		{
			case 0:
				smID = 34; //Brue
				break;
			case 1:
				smID = 15; //Minotaurus
				break;
			case 2:
				smID = 15; //Minotaurus
				break;
		}
	else if(pCaster->fame >= 1600 && pCaster->fame < 1700)
		switch(randID)
		{
			case 0:
				smID = 15; //Minotaurus
				break;
			case 1:
				smID = 48; //Ettin
				break;
			case 2:
				smID = 48; //Ettin
				break;
		}
	else if(pCaster->fame >= 1700 && pCaster->fame < 1800)
		switch(randID)
		{
			case 0:
				smID = 48; //Ettin
				break;
			case 1:
				smID = 120; //Mushroom King
				break;
			case 2:
				smID = 120; //Mushroom King
				break;
		}
	else if(pCaster->fame >= 1800 && pCaster->fame < 1900)
		switch(randID)
		{
			case 0:
				smID = 120; //Mushroom King
				break;
			case 1:
				smID = 121; //Argos
				break;
			case 2:
				smID = 121; //Argos
				break;
		}
	else if(pCaster->fame >= 1900 && pCaster->fame < 2000)
		switch(randID)
		{
			case 0:
				smID = 121; //Argos
				break;
			case 1:
				smID = 120; //Mushroom King
				break;
			case 2:
				smID = 55; //Dark Bear
				break;
		}
	else if(pCaster->fame >= 2000 && pCaster->fame < 2100)
		switch(randID)
		{
			case 0:
				smID = 55; //Dark Bear
				break;
			case 1:
				smID = 55; //Dark Bear
				break;
			case 2:
				smID = 55; //Dark Bear
				break;
		}
	else if(pCaster->fame >= 2100 && pCaster->fame < 2300)
		switch(randID)
		{
			case 0:
				smID = 55; //Dark Bear
				break;
			case 1:
				smID = 37; //Cyclop
				break;
			case 2:
				smID = 55; //Dark Bear
				break;
		}
	else if(pCaster->fame >= 2300 && pCaster->fame < 2500)
		switch(randID)
		{
			case 0:
				smID = 37; //Cyclop
				break;
			case 1:
				smID = 37; //Cyclop
				break;
			case 2:
				smID = 123; //Sandworm
				break;
		}
	else if(pCaster->fame >= 2500 && pCaster->fame < 2600)
		switch(randID)
		{
			case 0:
				smID = 123; //Sandworm
				break;
			case 1:
				smID = 163; //Gazer
				break;
			case 2:
				smID = 122; //SandTrap
				break;
		}
	else if(pCaster->fame >= 2600 && pCaster->fame < 2700)
		switch(randID)
		{
			case 0:
				smID = 163; //Gazer
				break;
			case 1:
				smID = 54; //Succubus
				break;
			case 2:
				smID = 163; //Gazer
				break;
		}
	else if(pCaster->fame >= 2700 && pCaster->fame < 2800)
		switch(randID)
		{
			case 0:
				smID = 54; //Succubus
				break;
			case 1:
				smID = 54; //Succubus
				break;
			case 2:
				smID = 87; //Ifrit
				break;
		}
	else if(pCaster->fame >= 2800 && pCaster->fame < 2900)
		switch(randID)
		{
			case 0:
				smID = 54; //Succubus
				break;
			case 1:
				smID = 47; //Ifrit
				break;
			case 2:
				smID = 88; //Blitz
				break;
		}
	else if(pCaster->fame >= 2900 && pCaster->fame < 3000)
		switch(randID)
		{
			case 0:
				smID = 88; //Blitz
				break;
			case 1:
				smID = 83; //Vampire
				break;
			case 2:
				smID = 16; //Balrog
				break;
		}
	else if(pCaster->fame >= 3000)
		smID = 16; //Balrog
	/*else if(pCaster->fame >= 2050 && pCaster->fame < 2100)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2100 && pCaster->fame < 2150)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2150 && pCaster->fame < 2200)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2200 && pCaster->fame < 2250)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2250 && pCaster->fame < 2300)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2300 && pCaster->fame < 2350)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2350 && pCaster->fame < 2400)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2400 && pCaster->fame < 2450)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2450 && pCaster->fame < 2500)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2500 && pCaster->fame < 2550)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2550 && pCaster->fame < 2600)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2600 && pCaster->fame < 2650)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2650 && pCaster->fame < 2700)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2700 && pCaster->fame < 2750)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2750 && pCaster->fame < 2800)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2800 && pCaster->fame < 2850)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2850 && pCaster->fame < 2900)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2900 && pCaster->fame < 2950)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 2950 && pCaster->fame < 3000)
		smID = 7; //Skelleton
	else if(pCaster->fame >= 3000)
		smID = 7; //Skelleton*/
	


	if (::SummonMonster(pCaster, smID, X, Y) == false)  
		{
			return false;
		}
	return true;
}
//End of them
bool exist(int item_no, int char_id, POS &source)
{
	if( item_no == IN_COINS || item_no == IN_COIN )			// 0222 YGI
	{
		ItemAttr *temp = GetItemByPOS( char_id, source );
		if( !temp ) return NOT;
		
		if( temp->item_no == IN_COINS && temp->attr[IATTR_MUCH] <= 5 ) temp->item_no = IN_COIN;
		else if( temp->item_no == IN_COIN && temp->attr[IATTR_MUCH] > 5 ) temp->item_no = IN_COINS;
	}
	// 010210 YGI
	if( item_no == IN_NEW_COINS || item_no == IN_NEW_COIN )			// 0222 YGI
	{
		ItemAttr *temp = GetItemByPOS( char_id, source );
		if( !temp ) return NOT;
		
		if( temp->item_no == IN_NEW_COINS && temp->attr[IATTR_MUCH] <= 5 ) temp->item_no = IN_NEW_COIN;
		else if( temp->item_no == IN_NEW_COIN && temp->attr[IATTR_MUCH] > 5 ) temp->item_no = IN_NEW_COINS;
	}

	switch(source.type) {
		case INV: // inventory
			//connections[char_id].chrlst.
			if(connections[char_id].chrlst.inv[source.p1][source.p2][source.p3].item_no == item_no) return OK ;
			return NOT ;
		case HAND:
			if(connections[char_id].chrlst.handheld.item_no == item_no) return OK ;
			else return NOT ;

		case EQUIP:
			if(connections[char_id].chrlst.equip[source.p3].item_no == item_no) return OK ;
			else return NOT ;

		case QUICK:
			if(connections[char_id].chrlst.quick[source.p3].item_no == item_no) return OK ;
			else return NOT ;
		
		case BANK :		//1225
			if(connections[char_id].chrlst.bank[source.p1][source.p2][source.p3].item_no == item_no) return OK ;
			else return NOT ;
		
		case BOX://�ڽ��� ������ ����//021030 lsw
			return NOT ;

		case GROUND:
			// check the existence by item_index
			if(ItemList[source.p3].bAlive) {
				if(ItemList[source.p3].x == source.p1 && ItemList[source.p3].y == source.p2 && 
					ItemList[source.p3].item_no == item_no) return OK ;
				else return NOT ; 
			}
			else return NOT ;
		case OTHER_CH : {					//0105
//<soto-tai
							CHARLIST	*ch;
							if( source.p3 < 10000 )	ch = &connections[source.p3].chrlst;
							else	ch = &NPCList[ source.p3-10000 ];
							if (!ch) return NOT;

							int a, b, c;
							for( a=0; a<3; a++ )
								for( b=0; b<3; b++ )
									for( c=0; c<8; c++ )
										if( ch->inv[a][b][c].item_no == item_no )
										{
											source.p1 = INV;
											source.p2 =	a*100+b*10+c;
											return OK;
										}

/*							for( c=0; c<8; c++)
								if( ch->equip[c].item_no == item_no )
								{
									source.p1 = EQUIP;
									source.p2 = c;
									return OK;
								}
							for( c=0; c<6; c++)//020530 lsw
								if( ch->quick[c].item_no == item_no )
								{
									source.p1 = QUICK;
									source.p2 = c;
									return OK;
								}
*/
							return NOT;
						}
//>soto-tai
		default:
			return NOT ;
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// �Լ�����: �κ��丮������ ���ڸ��� ã�� �� ����� �˷��ִ� �Լ�
//
// �Ķ����:	chr; �ش� ĳ������ *
//				p1, p2, p3; �κ��丮 �迭�� ù��°, �ι�° ������ index
//			
// ���ϰ�: ���ڸ��� ���� ����(����ÿ��� p1,p2,p3�� ����)
//
//////////////////////////////////////////////////////////////////////////////
void SendRareDisplayEffect(CHARLIST *ch, const int iDyRareType)
{
	if(0 > iDyRareType || MAX_ITEM_FUNCTION <=iDyRareType )
	{
		return;
	}

	const int iSendDisplayNo	= ItemFunction[iDyRareType].iEffectNo;
	const int iSendDisplayTime	= 5;
	if(iSendDisplayTime && iSendDisplayNo)//����Ʈ ������//�ӽ÷� ���Ƴ��� �׽�Ʈ�� ���ؼ�
	{//����Ʈ ���̺� ���� �ؼ� ��� ����
		t_packet p;
		const short cn = ch->GetServerID();
		p.h.header.type		= CMD_ADD_EFFECT;
		p.h.header.size		= sizeof( t_AddEffect );
		p.u.AddEffect.wEffectNo	=iSendDisplayNo;

		p.u.AddEffect.idTarget	=cn;	
		p.u.AddEffect.wDuration	=iSendDisplayTime;
		QueuePacket( connections, cn, &p, 1);
		CastMe2Other( ch->GetServerID(), &p );
	}
	return;
}

void SendRareDisplayEffect(CHARLIST *ch)
{
	const int iSendDisplayNo	= RareEM.GetRareDisplayEffectNo(DYNAMICRARE,ch->DynamicRare);	// ���� ������ ��ȣ
	const int iSendDisplayTime	= RareEM.GetRareDisplayEffectTime(ch->DynamicRare);
	if(iSendDisplayTime && iSendDisplayNo)//����Ʈ ������//�ӽ÷� ���Ƴ��� �׽�Ʈ�� ���ؼ�
	{//����Ʈ ���̺� ���� �ؼ� ��� ����
		t_packet p;
		const short cn = ch->GetServerID();
		p.h.header.type		= CMD_ADD_EFFECT;
		p.h.header.size		= sizeof( t_AddEffect );
		p.u.AddEffect.wEffectNo	=iSendDisplayNo;
//		p.u.AddEffect.wEffectNo	=474;//TEST

		p.u.AddEffect.idTarget	=cn;	

		p.u.AddEffect.wDuration	=iSendDisplayTime;
//		p.u.AddEffect.wDuration	=10;//TEST

		QueuePacket( connections, cn, &p, 1);
		CastMe2Other( ch->GetServerID(), &p );
	}
	return;
}

//////////////////////////////////////////////////////////////////////////
//
// �Լ�����: �������� ��ġ�� �ٲ۴�. NULL������ ������ �߰��Ͽ� ��������
//				��ġ�̵� �� �ڸ��ٲ�, ���, ������ ���� ������ �̵��� 
//				����� ��� ���꿡 ���.(�� ����, �κ��丮��������)
//
// �Ķ����:	char_id ; ������ �� ĳ���� id(index)
//				cstauts ; ĳ������ ���º�ȭ�� Ŭ���̾�Ʈ�� �˷��ֱ� ����	
//						  packet�� ���Ե� structure. �ܼ���, equip�̳� 
//						  use�Լ��� �Ķ���ͷ� �Ѿ��.
//				source, dest ; ��/��ǥ ��� ����(POS STRUCTURE���� ����)
//
// ���ϰ�: �ش� ����(�̵�/����/������)�� ���� ����
//											
//////////////////////////////////////////////////////////////////////////
// *************************************************************************************
//												
//				ĳ���Ͱ��� �̵� ���� ���� �ȵ�. �ʰ��� �̵� ���� �ȵ�.
//											
// ************************************************************************************
								
// ĳ���Ͱ��� ������ �̵��� �����ϱ� ���ؼ��� dest�� p1�� charlist������ index�� �Ѿ�;� �Ѵ�.
// �ʰ��� ������ �̵��� �����ϱ� ���ؼ��� dest�� p1, p2�� x,y�� ���;� �Ѵ�.
int exchangePOS_of_Item(const int char_id, t_chr_status_info *cstatus, const POS SourcePos, const POS DestPos)		// 0624 YGI
{
	CHARLIST *hero = CheckServerId( char_id );
	if( !hero ) 
	{
		return 0;
	}

	ItemAttr tu = {0,}, *pSourceItem=NULL;	
	int item_id ;
	POS other_pos;			
	bool iSendDyRareDisplayEffect =0;

	switch(SourcePos.type) 
	{
		case INV: 
			{
				pSourceItem= &hero->inv[SourcePos.p1][SourcePos.p2][SourcePos.p3]; 
			}break ;		
		case EQUIP: 
			{
				pSourceItem= &hero->equip[SourcePos.p3] ; 
			}break ;		
		case QUICK: 
			{
				pSourceItem= &hero->quick[SourcePos.p3] ;
			}break ;		
		case BANK :	
			{
				pSourceItem= &hero->bank[SourcePos.p1][SourcePos.p2][SourcePos.p3] ;
			}break ;		
		case HAND:	
			{
				pSourceItem= &hero->handheld;
			}break ;//021030 lsw �ڽ� �����ϴ�.
		case GROUND: 
			{
				tu.item_no = ItemList[SourcePos.p3].item_no; 
				::memcpy( &tu, &ItemList[SourcePos.p3], sizeof( DWORD )*6 );
				pSourceItem = NULL;
			}break;
//<soto-tai
		case OTHER_CH :			// 0105
			{
				CHARLIST *ch = NULL;
				if( SourcePos.p3 < 10000 ) 
				{
					ch = ::CheckServerId(SourcePos.p3);
				}
				else 
				{
					ch = ::NPC_ReturnCharListPoint(SourcePos.p3);
				}
				if(!ch)//����� ����
				{
					return 0;
				}

				switch( SourcePos.p1 )
				{
				case INV :
					{
						const int a= SourcePos.p2 /100;
						const int b = (SourcePos.p2 - a*100)/10;
						const int c = SourcePos.p2 % 10;
						pSourceItem= &ch->inv[a][b][c] ;
						::SetItemPos( INV, a, b, c, &other_pos );
						break;
					}
/*
				case EQUIP : 
					{
						pSourceItem= &ch->equip[SourcePos.p2] ;
						::SetItemPos( EQUIP, SourcePos.p2, &other_pos );
					}break;

				case QUICK :
					{
						pSourceItem= &ch->quick[SourcePos.p2] ;
						SetItemPos( QUICK, SourcePos.p2, &other_pos );
					}break;
*/
				default : 
					{
						return 0 ; 
					}break;
				}
				break;
			}
//>soto-tai

		default:
			return 0 ;
	}

	if( pSourceItem )
	{
		tu = *pSourceItem;
	}

	CItem *ii = ItemUnit( tu.item_no );
	if( NULL == ii ) return 0;
	switch(DestPos.type) 
	{
		case INV:
			{	
				ItemAttr &DestItem = hero->inv[DestPos.p1][DestPos.p2][DestPos.p3];
				if( SourcePos.type == HAND && ii->GetRbutton() == DIVIDE_ITEM )
				{
					int sum_able = 0 ;
					if( tu.item_no == DestItem.item_no	//������ �ѹ��� ��ġ�ϰ�
					 &&	tu.attr[IATTR_RARE_MAIN] == DestItem.attr[IATTR_RARE_MAIN] ) //���� �Ӽ��� ������
					{
						sum_able = 1;		// 010522 YGI
					}

					CItem *t = ItemUnit( DestItem );
					if(	( t && t->GetItemKind() == IK_MONEY		&& ii->GetItemKind() == IK_MONEY )		//���� ����
					 ||	( t && t->GetItemKind() == IK_NEW_MONEY && ii->GetItemKind() == IK_NEW_MONEY ) ) 
					{
						sum_able = 1;				// 010210 YGI
					}

					if( DestItem.item_no == 0 )
					{
						DestItem = tu;
						DestItem.attr[IATTR_MUCH] = 0;
						sum_able = 1;
					}

					if( sum_able )
					{
						DestItem.attr[IATTR_MUCH]+=tu.attr[IATTR_MUCH];	// ������ ���� ��ġ��
						::CheckAutoDivideMoney( &DestItem, char_id );				// 0415_2 YGI
						::SendServerItemAttr( char_id, IATTR_DURATION, DestPos, &DestItem );
						::DeleteItem( pSourceItem );
						goto OK_;
					}
				}
				// ���� �ָӴ� ����
				else if( SourcePos.type == HAND && ii->GetRbutton() == USE_ITEM )	// ��� �ִ� �������� �����̰�
				{
					CItem *t = ItemUnit( DestItem );
					if(t && ii->GetItemKind() != IK_POTION_BOX && t->GetItemKind() == IK_POTION_BOX)  // ����� �ָӴ��̸�
					{
						// ���� ����
						CPotionBox potion_box( hero );
						if(potion_box.PutItem( pSourceItem ))
						{
							goto OK_;
						}
					}
				}
				else if(SourcePos.type == EQUIP)			// 010604 YGI
				{
					if( DestItem.item_no )
					{
						::MoveEmptyInv( &DestItem, hero );
					}
					ii->ReleaseItem( hero );
				}
				
				*pSourceItem= DestItem  ;		// 001030 YGI
				DestItem  = tu ;

				goto OK_;
			}break;
				
		case EQUIP: // case EQUIP		
			{
				ItemAttr &DestItem = hero->equip[DestPos.p3];
				int dest_type, dest_index;
				::getItemIndex( DestItem.item_no, dest_type, dest_index );
				CItem *t = ItemUnit( dest_type, dest_index );		// �ƹ��͵� ���� �� �ִ�. 
				if( t )		// 010604 YGI
				{
					t->ReleaseItem( hero );
					::MoveEmptyInv( &DestItem, hero );
					// acer4
					// Ȱ�� �Ű��� ��� ȭ�쵵 �ű��.
					if( DestPos.p3 == WT_WEAPON && t->GetSkill_Ability() == TACTICS_Archery )
					{
						ItemAttr *arrow_item = &hero->equip[WT_SHIELD];
						if( arrow_item->item_no )
						{
							CItem *tt = ::ItemUnit( arrow_item->item_no );
							if( tt ) tt->ReleaseItem( hero );
							::MoveEmptyInv( arrow_item, hero );
							POS pos;
							::SetItemPos( EQUIP, WT_SHIELD , &pos );
							::SendServerEachItem( &pos, arrow_item, char_id );
						}
					}

				}

				if( ii->is_equipable(char_id, cstatus, SourcePos, DestPos) ) 
				{
					*pSourceItem= hero->equip[DestPos.p3] ;
					hero->equip[DestPos.p3]= tu ;
				
					ii->EquipItem( hero );		//

					goto OK_;
				}
				else return 0 ;
			}break;
		case QUICK :								//1214
			{
				if( ii->GetWearAble() == WEAR_BELT ) 
				{
					*pSourceItem= hero->quick[DestPos.p3] ;
					hero->quick[DestPos.p3]= tu ;
					goto OK_;
				}
				else return 0;
			}break;

		case BANK :						//1225
			{
				ItemAttr &DestItem = hero->bank[DestPos.p1][DestPos.p2][DestPos.p3];
				if( DestItem.item_no )		
				{
					// ���࿡�� �����Դ�.
					::SendItemEventLog( &DestItem, char_id, SN_NOT_USER, SILT_GET_BANK, 2 ); //YGI acer
					::MoveEmptyInv( &DestItem, hero );
				}

				if( SourcePos.type == HAND && tu.item_no == DestItem.item_no && ii->GetRbutton() == DIVIDE_ITEM 
					&& tu.attr[IATTR_RARE_MAIN] == DestItem.attr[IATTR_RARE_MAIN])//010604//�����Ӽ��� ��ġ��
				{
					DestItem.attr[IATTR_MUCH]+=tu.attr[IATTR_MUCH];	// ������ ���� ��ġ��
					::DeleteItem( pSourceItem );
					goto OK_;
				}
				*pSourceItem= DestItem;
				DestItem = tu;
				if(SourcePos.type == EQUIP) 
				{
					ii->ReleaseItem( hero );
				}
				::SendItemEventLog( &DestItem, char_id, SN_NOT_USER, SILT_PUT_BANK, 2 ); //YGI acer
				goto OK_;
			}break;
//soto-tai
		case HAND:			
			{
				ItemAttr &DestItem = hero->handheld;
				if( DestItem.item_no )		// �տ� ������ ��� ������ ����ִ� �κ����� ����������. 
					::MoveEmptyInv( &DestItem, hero );

				int release = false;
				switch( SourcePos.type )
				{
					case EQUIP : {
									release = true;									
									break;
								 }
					case OTHER_CH : {
										// finito 040707 check for noexchange item kind
										if (IsNoExchange(&tu))
										{
											return 0;
										}
										// end of check

										if( SourcePos.p3 >= 10000 ) break;
										CHARLIST *target_ch = ::CheckServerId( SourcePos.p3 );
										if( !target_ch ) return NOT;
										::SendItemEventLog( pSourceItem, char_id, SourcePos.p3, SILT_GET_OTHER_CH_INVEN, 1 ); //YGI acer
										// 020428 YGI acer
										if( !::SendDeleteItem( pSourceItem, &other_pos, target_ch ) ) return NOT;
										//soto-tai
										target_ch->inv[other_pos.p1][other_pos.p2][other_pos.p3] = ::GenerateItem(IN_STEAL_RESULT);
										::SendServerEachItem(&other_pos,&target_ch->inv[other_pos.p1][other_pos.p2][other_pos.p3],target_ch->GetServerID());
										break;
									}
					case BANK :
						{
							::SendItemEventLog( pSourceItem, char_id, SN_NOT_USER, SILT_GET_BANK, 2 ); //YGI acer
							break;
						}
				}
				*pSourceItem= DestItem;
				DestItem= tu ;
			
				if( release )
				{
					ii->ReleaseItem( hero );
				}
				goto OK_;
			}break;
//>soto-tai

		case USE:
			{		
				if( hero->IsDead() ){return 0;}
				
				switch( ii->GetRbutton() )
				{
				case USE_ITEM:
				case REMAIN_ITEM:
					switch (tu.item_no)
					{
						case 10291:
						{
							RecvReqResetAbility(hero->GetServerID());
						}
						break;	
						case 31:
							{	
								hero->Cp=hero->CpMax;
								hero->SendCharInfoBasic(CP,hero->CpMax);								
							}
							break;
						case 32:
							{	
								hero->Cp=hero->CpMax;
								hero->SendCharInfoBasic(CP,hero->CpMax);								
							}	
							break;
						case 33:
							{	
								hero->Cp=hero->CpMax;
								hero->SendCharInfoBasic(CP,hero->CpMax);								
							}
							break;
						case 4033: //Eleval 22/05/09 - For summoning pot
							{
								SummonMonsterItem(hero, hero->X / 32, hero->Y / 32);
							}break;
					}
					
				

					break;
				default: 
					{
						return 0;
					}
					break;
				}

				switch(tu.item_no)
				{
				case 3052:
					{
						if(hero->Gender == MALE)
						{
							::SendEatChcolate( hero->Name, pSourceItem->attr[IATTR_LIMIT], char_id );
						}
					}break;
				case 3053:
					{
						if(hero->Gender == FEMALE )
						{
							::SendEatCandy( hero->Name, pSourceItem->attr[IATTR_LIMIT], hero->total_id );
						}
					}break;
				case 3105:
					{//< CSD-021003 : ������ų ����Ʈ ȹ��
						if (!hero->IsLimit(1))
						{
								  hero->IncCombatPoint(1);
						}
					}break;
				default:
					{
					}break;
				}

				int no_delete = 0;// ������ ���� ��쵵 �ִ�.//1 �̸� �������� ���� // 2 ������ ����
				if(SourcePos.type != GROUND && SourcePos.type != EQUIP)		
				{
					int add_hp = 0;
					const int iUseitemKind = ii->GetItemKind();
					switch(iUseitemKind)
					{
					//<! BBD 040213 ������ �ִ� ����
					case IK_POTION_BAG:
						{
							no_delete = 1;
							add_hp = ii->EatItem( hero );
						}break;
					//> BBD 040213 ������ �ִ� ����
					case IK_POTION_BOX:// �ָӴϸ� Ŭ���ߴ�.
						{
							no_delete = 1;
							CPotionBox potion_box( hero );

							if(SourcePos.type == INV)
							{
								potion_box.Empty();
							}
							else
							{
								add_hp = potion_box.UseItem();	
							}
						}break;
					case IK_SPECIALPOTION:
						{
							no_delete = 3;
						}break;
					case IK_CANDLE:
					case IK_GOOD_CANDLE:
						{
							no_delete = 2;
							add_hp = ii->EatItem( hero );
							if(ii->GetImunityCure3())//��Ƽ�� ���� �ʵ�
							{	// ����ڰ� ��Ƽ���� ���
								for (int i = 0; i < MAX_PARTY_MEMBER; ++i)
								{
									if (hero->party[i].On)
									{ 
										//CHARLIST *Target = CheckServerId( hero->party[i].Server_id );
										CHARLIST *Target = CheckServerName( hero->party[i].Name );
										if(!Target){continue;}
										::WeatherControl.SetChLight(Target,ii->GetImunityCure2(),5*60);
									}
								}
							}							
						}break;
					default:
						{
							add_hp = ii->EatItem( hero );
						}break;
					}//switch(iUseitemKind)
					t_packet p;
					p.h.header.type		= CMD_SERVER_CHARACTER_CONDITION2;		// 010618 YGI
					p.h.header.size		= sizeof( t_server_character_condition );
					p.u.angra.server_character_condition.idTarget = WORD(char_id);	
					p.u.angra.server_character_condition.nLife = hero->Hp;	// 010618 YGI
      				p.u.angra.server_character_condition.nState = hero->GetState();
					
      				QueuePacket( connections, char_id, &p, 1);
					p.h.header.type		= CMD_SERVER_CHARACTER_CONDITION;
					p.u.angra.server_character_condition.nLife = add_hp;		// 0224 YGI
					::CastMe2Other( char_id, &p );

					//020314 lsw
					if(pSourceItem->attr[IATTR_RARE_MAIN] && ((RareMain*)&(pSourceItem->attr[IATTR_RARE_MAIN]))->IsDynamicRare)
					{

						const int iGrade= ((RareMain*)&(pSourceItem->attr[IATTR_RARE_MAIN]))->grade;
						const int iPri	= ((RareMain*)&(pSourceItem->attr[IATTR_RARE_MAIN]))->soksung1;
						const int iSec	= ((RareMain*)&(pSourceItem->attr[IATTR_RARE_MAIN]))->soksung2;
						const int iThi	= ((RareMain*)&(pSourceItem->attr[IATTR_RARE_MAIN]))->soksung3;

						// ���� ���ش�. // YGI 020527
						if( !no_delete ) 
						{
							::SendItemEventLog( pSourceItem, char_id, SN_NOT_USER, SILT_USE, 3 ); //YGI acer
							::DeleteItem( pSourceItem );		// ����Ѱ� ��·�� ��������.
							::SendServerEachItem(&SourcePos,pSourceItem,char_id);
							no_delete = 1;
						}

						if(	RareEM.ApplyDynamicRareEffect(hero,iPri,iGrade,1)
						||	RareEM.ApplyDynamicRareEffect(hero,iSec,iGrade,2)
						||	RareEM.ApplyDynamicRareEffect(hero,iThi,iGrade,3) )
						{
							iSendDyRareDisplayEffect = true;
						}
						
						if( (iUseitemKind ==	IK_GOOD_CANDLE 	||	iUseitemKind ==	IK_CANDLE )// ���ʸ�
							&& ii->GetImunityCure3() )//��Ƽ�� ���� �ʵ�
						{
							// ����ڰ� ��Ƽ���� ���
							for (int i = 0; i < MAX_PARTY_MEMBER; ++i)
							{
								if (hero->party[i].On)
								{ 
									//CHARLIST *Target = ::CheckServerId( hero->party[i].Server_id );
									CHARLIST *Target = ::CheckServerName( hero->party[i].Name );									
									if(!Target){continue;}
									RareEM.ApplyDynamicRareEffect(Target,iPri,iGrade,1);
									RareEM.ApplyDynamicRareEffect(Target,iSec,iGrade,2);
									RareEM.ApplyDynamicRareEffect(Target,iThi,iGrade,3);
								}
							}
						}
					}
					switch(no_delete)
					{
					case 0:
						{
							::SendItemEventLog( pSourceItem, char_id, SN_NOT_USER, SILT_USE, 3 ); //YGI acer
							::DeleteItem( pSourceItem );		// ����Ѱ� ��·�� ��������.
							::SendServerEachItem(&SourcePos,pSourceItem,char_id);
						}break;
					case 1:
						{
						}break;
					case 2:
						{
							::SendItemEventLog( pSourceItem, char_id, SN_NOT_USER, SILT_USE, 3 ); //YGI acer
							const int iResult = ItemMgr.DecItemDur(*pSourceItem,MULTIPLE_USE_ONE_TIME_DEC_DUR);		// ����Ѱ� �������� ��´�
							::SendServerEachItem(&SourcePos,pSourceItem,char_id);
						}break;
					case 3:
						{
							const int iResult = ItemMgr.DecItemDur(*pSourceItem,MULTIPLE_USE_ONE_TIME_DEC_DUR);		// ����Ѱ� �������� ��´�
							::SendServerEachItem(&SourcePos,pSourceItem,char_id);

						}break;
					}
					if(iSendDyRareDisplayEffect)//���ñ�� �����ۿ� ���Ѱ�
					{
						::SendRareDisplayEffect(hero);
					}
					//�������� ����� ȿ���� ���� �Ѵ�//���� �Ʒ��� �ٸ��� �Ϲݱ�� �����ۿ� ���Ѱ� //�� �κ��� EatItemCommon�� ���� ����
					if	(RareEM.ApplyDynamicRareEffect(hero,ii->GetCureDisease1(),1,0))//���⼭ �ð��� ���� �Ǿ� �ִ�
					{
						::SendRareDisplayEffect(hero,ii->GetCureDisease1());
						return 0;
					}//OK �� ȣ�� ���� ���� ���� �ֽ��ϴ�.(���̵� �������� ���
					goto OK_;
				}
			 }break;

		case GROUND:
			{
				// finito 040707 check for noexchange item kind
				if (IsNoExchange(&tu))
				{
					return 0;
				}
				// end of check

				if(pSourceItem) 
				{
					pSourceItem->item_no= 0 ;
					pSourceItem->attr[0]= 0 ;
					pSourceItem->attr[1]= 0 ;
					pSourceItem->attr[2]= 0 ; 
					pSourceItem->attr[3]= 0 ;
					pSourceItem->attr[4]= 0 ;
					pSourceItem->attr[5]= 0 ;
				}
				item_id = ::AddItemList( tu.item_no, tu.attr, 0, DestPos.p1, DestPos.p2, 0, 0) ;
				if(item_id < 0)	return 0 ;
				else goto OK_;
			}break ;

		case CHARACTER:			//0116	YGI
		{
			// finito 040707 check for noexchange item kind
			if (IsNoExchange(&tu))
			{
				return 0;
			}
			// end of check

			bool ret = false;
			int p1=0, p2=0, p3=0 ;

			CHARLIST *target_ch = ::CheckServerId( DestPos.p3 );
			
			if( target_ch )
			{
				ret = ::SearchInv(target_ch->inv,p1,p2,p3);//021030 lsw
			}

			if(ret) 
			{ // ���� ĳ���� �κ��丮�� ����� ������
				
				target_ch->inv[p1][p2][p3]= tu ;
				POS pos;
				::SetItemPos( INV, p1,p2,p3, &pos );
				::SendServerEachItem( &pos, &tu, DestPos.p3 );			// 001028 YGI

				// SourcePos�� �����.
				::SendItemEventLog( pSourceItem, char_id, DestPos.p3, SILT_PUT_OTHER_CH, 1 );
				::SendItemEventLog( pSourceItem, DestPos.p3, char_id, SILT_GET_OTHER_CH, 1 );
				::DeleteItem( pSourceItem );
				goto OK_;
			}
			else // �ٽ� �ǵ����ش�.
			{
				::MoveEmptyInv( pSourceItem, &connections[char_id].chrlst );
			}
			break;
		}

		default:
			{
				return 0 ;
			}break;
	}
	return 0;
OK_:
	ResetAbility( hero );//020303 lsw
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////
//																				//
//																				//
//																				//
//	Item�� ����� ó�����ִ� �޼ҵ��											//
//																				//
//																				//
//																				//
//																				//
//////////////////////////////////////////////////////////////////////////////////
int CItem_Plant::use(int char_id, t_chr_status_info *cstatus, POS source, POS dest)
{
	return OK ;
}

int CItem_Mineral::use(int char_id, t_chr_status_info *cstatus, POS source, POS dest)
{
	return OK ;
}

int CItem_Herb::use(int char_id, t_chr_status_info *cstatus, POS source, POS dest)
{
	return OK ;
}

int CItem_Cook::use(int char_id, t_chr_status_info *cstatus, POS source, POS dest)
{
	return OK ;
}

int CItem_Potion::use(int char_id, t_chr_status_info *cstatus, POS source, POS dest)
{
	//connections[char_id].chrlst.Hp   += hp ;
	//connections[char_id].chrlst.MoveP+= ap ;
	//connections[char_id].chrlst.Mana += mp ;
	// another effects?
	return OK ;
}



/************************************************************************************/
//
//
//								���� �Լ���
//
//
/************************************************************************************/
// ������ �ε��� �˾Ƴ��� �Լ�
void getItemIndex(int item_no, int &type, int &index)
{
	type= item_no / 1000 ;
	index= item_no % 1000 ;
}

void getItemIndex(int char_id, POS source, int &type, int &index)
{
	//int type, index ;

	switch(source.type) {
		case HAND:
			type= connections[char_id].chrlst.handheld.item_no / 1000 ;
			index= connections[char_id].chrlst.handheld.item_no % 1000 ;
			break ;
		
		case INV:
			type= connections[char_id].chrlst.inv[source.p1][source.p2][source.p3].item_no / 1000 ;
			index= connections[char_id].chrlst.inv[source.p1][source.p2][source.p3].item_no % 1000 ;
			break ;

		case QUICK:
			type= connections[char_id].chrlst.quick[source.p3].item_no / 1000 ;
			index= connections[char_id].chrlst.quick[source.p3].item_no % 1000 ;
			break ;

		case EQUIP:
			type= connections[char_id].chrlst.equip[source.p3].item_no / 1000 ;
			index= connections[char_id].chrlst.equip[source.p3].item_no % 1000 ;
			break ;

		default:
			type= 0 ;
			index= 0 ;
			break ;
			
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// �Լ�����: ������ �и�(������ �ִ� �������� ���; ��, ���ѵ���)
//				���� �ش� ĳ������ �κ��丮�������� ����
//
// �Ķ����:	char_id; �ش� ĳ������ id(index)
//				source, dest; �������� ��ġ����
//
// ���ϰ�: ������ �и��� ��������
//
//////////////////////////////////////////////////////////////////////////////

int departItem(int char_id, POS source, POS dest, int dec_val)
{
	ItemAttr tu, *source_ptr ;
	int type, index ;

	
	//getItemIndex(char_id, source, type, index) ;
	getItemIndex(char_id, source, type, index) ;
	// save source item info & position
	printf("\n DEPART ITEM==> char_id:%d  %d(%d %d %d) --> %d(%d %d %d) %d %d", char_id, source.type, source.p1, source.p2, source.p3,
		dest.type, dest.p1, dest.p2, dest.p3, type, index) ;
	switch(source.type) {
		/*
		case INV:	
			tu= connections[char_id].chrlst.inv[source.p1][source.p2][source.p3] ;
			source_ptr= &connections[char_id].chrlst.inv[source.p1][source.p2][source.p3] ;
			break ;
		*/

		case HAND:
			tu= connections[char_id].chrlst.handheld ;
			source_ptr= &connections[char_id].chrlst.handheld ;
			break ;

		default:
			return NOT ;
	}

	// exchage the two items
	switch(dest.type) {
		case INV:
			// set duration
			source_ptr->attr[0]+= dec_val ;
			connections[char_id].chrlst.inv[dest.p1][dest.p2][dest.p3]= tu ;
			connections[char_id].chrlst.inv[dest.p1][dest.p2][dest.p3].attr[0]= -dec_val ;
			return OK ;
			break ;

		/*
		case HAND:
			// ���� ����ִ°��� üũ�ؾ� �ϴ°�????
			// ������ ����~
			if(source.type == EQUIP) { // Unequip
				//getItemIndex(char_id, source, type, index) ;
				Item_Ref.Item_Info[type][index]->unequip(char_id, cstatus, source, dest) ;
			}
			*source_ptr= connections[char_id].chrlst.handheld ;
			connections[char_id].chrlst.handheld= tu ;
			return OK ;
			// pickup the item 
			break ;
		*/

		default:
			return NOT ;
	}

	return OK ;
}


//////////////////////////////////////////////////////////////////////////////////
//																				//
//	����:   item  ��뿡 ���� ĳ���� ��ġ ��ȭ  								//
//																				//
//			virtual �Լ���														//
//																				//
//////////////////////////////////////////////////////////////////////////////////
int CItem_Potion::UseItem( CHARLIST *ch)
{
	ch->Hp += hp;
	if( ch->Hp > ch->HpMax ) ch->Hp = ch->HpMax;

	ch->Mana += mp;
	if( ch->Mana > ch->ManaMax ) ch->Mana = ch->ManaMax;
//	ch->TempMana = ch->Mana;//020214 lsw 

	ch->Hungry	+= ap; //hungry;
	if( ch->Hungry > ch->HungryMax ) ch->Hungry = ch->HungryMax;
	return 1;
}

int CItem_Herb::UseItem( CHARLIST *ch)
{

	return 1;
}

int CItem_Cook::UseItem( CHARLIST *ch)
{

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////
// 
//		�������� ���� ���� ĳ���� �ɷ�ġ ��ȭ��Ű�� ������ ��ö �Լ� 
//
/////////////////////////////////////////////////////////////////////////////////
//011218 lsw
bool	IsEquipAbleDualStep(const int iDualStep, const CHARLIST *ch)
{
	return ((iDualStep <= ch->GetClassStep())?true:false);
}

bool	IsEquipAbleClass(const int iWarrior,const int iThief,
						 const int iArcher,const int iWizard,
						 const int iPriest,const CHARLIST *ch)
{
	switch(ch->Class)
	{
	case WARRIOR:
		{
			if(!iWarrior){return false;}
		}break;
	case THIEF	:
		{
			if(!iThief){return false;}
		}break;
	case ARCHER	:
		{
			if(!iArcher){return false;}
		}break;
	case WIZARD	:
		{
			if(!iWizard){return false;}
		}break;
	case PRIEST	:
		{
			if(!iPriest){return false;}
		}break;
	default:
		{
			return false;
		}break;
	}
	return true;
}

bool	IsEquipAbleItemKind(const int iItemKind, const CHARLIST *ch)
{
	switch(iItemKind)
	{
	case IK_FALG://����϶� �� ������ ���� �־�� �Ѵ�
		{
			CItem * t = ItemUnit( ch->equip[WT_SHOES].item_no);
			if(!t)
			{
				return false;
			}
			const int iCmpItemKind= t->GetItemKind();
			if(IK_SADDLE != iCmpItemKind)
			{
				return false;
			}
		}break;
	default:
		{
		}break;
	}
	return true;
}

bool	IsEquipAbleAbilityCheck	(const int iNeedAbility, const int iMyAbility)
{
	if( (!iNeedAbility) || (iNeedAbility<=iMyAbility) )
	{
		return true;
	}
	return false;
}
bool	IsEquipAbleCheckWisInt	(const int iNeedWis, const int iNeedInt, const int iMyWis, const int iMyInt)
{
	if( iNeedWis && (!iNeedInt))//Wis�� �䱸 �ϸ�
	{
		return IsEquipAbleAbilityCheck(iNeedWis,iMyWis);
	}
	if( (!iNeedWis) && iNeedInt)//Int�� �䱸 �ϸ�
	{
		return IsEquipAbleAbilityCheck(iNeedInt,iMyInt);
	}
	if( (!iNeedWis) && (!iNeedInt))//�Ѵ� �ʿ� ���� �ʴ�
	{
		return true;
	}

	if( iNeedWis && iNeedInt )//�Ѵ� �䱸 �ϸ�
	{
		if(IsEquipAbleAbilityCheck(iNeedWis,iMyWis) || IsEquipAbleAbilityCheck(iNeedInt,iMyInt))//�Ѵ� ���� �ؾ� ��
		{
			return true;
		}
	}
	return false;
}

bool	IsEquipAbleCheckWsPs	(const int iNeedWs, const int iNeedPs, const int iMyWsPs, const int iSpellType)
{
	switch (iSpellType)
	{
		case WIZARD_SPELL:
			{
				if(IsEquipAbleAbilityCheck(iNeedWs,iMyWsPs))
				{
					return true;
				}
			}break;
		case PRIEST_SPELL:
			{
				if(IsEquipAbleAbilityCheck(iNeedPs,iMyWsPs))
				{
					return true;
				}
			}break;
		default:
			{
			}break;
	}
	return false;
}
bool	IsEquipAbleCheckGender	(const int iNeedGender, const int iMyGender)
{
	switch(iNeedGender)
	{
	case 0:
		{
			return true;
		}break;
	case 1:
		{
			if(iMyGender == MALE)
			{
				return true;
			}
		}break;
	case 2:
		{
			if(iMyGender == FEMALE)
			{
				return true;
			}
		}break;
	default :
		{
			return false;
		}break;
	}
	return false;
}
bool	IsEquipAbleCheckMouseMRD	(const int iNeedMouseMRD, const int iMyMouseMRD)// ��ƽüũ
{
	if( (iNeedMouseMRD <= 1) || (iNeedMouseMRD <= iMyMouseMRD) )
	{
		return true;
	}
	return false;
}

bool IsEquipAbleCheckAbleDay(const int start, const int end)
{	//< CSD-030812
	if(!start)	{return true;}//���� ���� 
	if(!end)	{return true;}//���� ���� 

	int mon = g_mon+1;
	int day = g_day+1;

	const int FullToday = (mon*100)+day;
	
	if (start <= end)
	{
		if( start <= FullToday && end >= FullToday)
		{
			return true;//����Ⱓ�̴�.
		}
	}
	//< 040102 kyo
	else
	{
		if( start <= FullToday && 1231 >= FullToday)
		{
			return true;
		}
		else if( 101 <= FullToday&& end >= FullToday)
		{
			return true;
		}		
	}
	//> 040102 kyo

	return false;
}	//> CSD-030812

inline bool IsEquipAbleCheckNation(const int iAbleNation, const CHARLIST *ch)//000  100 ���� 10 ���� 1 �Ͻ�
{
	switch(ch->name_status.nation)
	{
	case NW_BY:
		{
			if((iAbleNation%1000)/100)
			{
				return true;
			}
		}break;
	case NW_ZY:
		{
			if((iAbleNation%100)/10)
			{
				return true;
			}
		}break;
	case NW_YL:
		{
			if((iAbleNation%10)/1)
			{
				return true;
			}
		}break;
	default :
		{
			return false;
		}break;
	}
	return false;
}

inline bool IsEquipAbleCheckLv(const int iAbleLv, const CHARLIST *ch)
{	//< CSD-030806
	if (!iAbleLv)
	{
		return true;
	}
	
	if (iAbleLv <= ch->GetLevel())	
	{
		return true;
	}

	return false;
}	//> CSD-030806

inline bool IsEquipAbleCheckFame(const int iAbleFame, const CHARLIST *ch)
{
	if(!iAbleFame){return true;}//���� 
	if( iAbleFame <= ch->fame)
	{
		return true;
	}
	return false;
}

__inline int EatItemCommon(CHARLIST *ch,const int iHp, const int iMp, const int iHungry,const int iLight)
{
//	if	(RareEM.ApplyDynamicRareEffect(ch,DyRare,1,0))//���⼭ �ð��� ���� �Ǿ� �ִ�
//	{
//		SendRareDisplayEffect(ch);
//	}
	
	int iReturnValue = 0;
	if(iHp)
	{
		iReturnValue = ch->IncLife(iHp);
	}
	if(iMp && ch->Spell == WIZARD_SPELL)
	{
		ch->IncMana(iMp);
		ch->SendCharInfoBasic(MP, ch->Mana);//���� �Ծ����� ������ ������ ���� �þ�� ���� ����
	}
	if(iHungry)
	{
		ch->IncHungry(iHungry);
	}
	if(iLight)
	{
		WeatherControl.SetChLight(ch,iLight,5*60);
	}//5��
	return iReturnValue;
}

/*
cure_disease1;//���� ��� �ѹ�
cure_disease2;//���� ���� 
cure_disease3;//��Ƽ�� ����
*/

int CItem_Etc::EatItem( CHARLIST *ch )
{
	return EatItemCommon(ch,0,0,0,GetImunityCure2());
}

int CItem_Plant::EatItem( CHARLIST *ch )
{
	return EatItemCommon(ch,hp,mp,ap,GetImunityCure2());
}
///////////////////////////////
int CItem_Herb::EatItem(CHARLIST *ch)
{
	return EatItemCommon(ch,hp,mp,ap,GetImunityCure2());
}

int CItem_Cook::EatItem(CHARLIST *ch)
{
	return EatItemCommon(ch,hp,mp,ap,GetImunityCure2());
}

int CItem_Potion::EatItem(CHARLIST *ch)
{
	return EatItemCommon(ch,hp,mp,ap,GetImunityCure2());
}	

/////////////////////////////////////////////////////////////////////////////////
//	
// ������ ������ ���� ĳ���� �ɷ�ġ ��ȭ�� ����ϴ� ��� �Լ�
//	
/////////////////////////////////////////////////////////////////////////////////

__inline int	IsEquipAbleCommon(const CHARLIST *ch)//020314 lsw
{	//���������� ȣ��
	return 1;
}

__inline int	EquipItemCommon(const CHARLIST *ch)//020314 lsw
{	//���������� ȣ��
	return 1;
}

__inline int	ReleaseItemCommon(const CHARLIST *ch)//020314 lsw
{	//���������� ȣ��
	return 1;
}

__inline int EquipItemSetAbility(CHARLIST *ch,const int iStr	, const int iCon	, const int iDex	, 
								   const int iWis	, const int iInt	, const int iMovp	, 
								   const int iChar	, const int iEndu	, const int iMoral	,const int iLuck)
{

	ch->Strw	+= iStr	;	ch->Conw	+= iCon	;
	ch->Dexw	+= iDex	;	ch->Wisw	+= iWis	;
	ch->Intw	+= iInt	;	ch->MovePw	+= iMovp;
	ch->Charw	+= iChar;	ch->Enduw	+= iEndu;
	ch->Moralw	+= iMoral;	ch->Luckw	+= iLuck;
	return 1;
}

__inline int ReleaseItemSetAbility(CHARLIST *ch,const int iStr	, const int iCon	, const int iDex	, 
								   const int iWis	, const int iInt	, const int iMovp	, 
								   const int iChar	, const int iEndu	, const int iMoral	,const int iLuck)
{
	ch->Strw	-= iStr	;	ch->Conw	-= iCon	;
	ch->Dexw	-= iDex	;	ch->Wisw	-= iWis	;
	ch->Intw	-= iInt	;	ch->MovePw	-= iMovp;
	ch->Charw	-= iChar;	ch->Enduw	-= iEndu;
	ch->Moralw	-= iMoral;	ch->Luckw	-= iLuck;
	return 1;
}

__inline int EquipItemCalcAttackPower(CHARLIST *ch,const int iItem_table_damage)
{
	int iTempDmg =iItem_table_damage;
	if( 100000000 < iTempDmg  ) // ���̳ʽ� �������� ���
	{
		iTempDmg %= 100000000;
		ch->iPhysicalTotalDamage	-= iTempDmg / 10000 ;
		ch->iPhysicalRandomDamage	-= iTempDmg % 10000 ;
	}
	else if ( 100000000 > iTempDmg ) //�÷��� ������ �� ���
	{
		ch->iPhysicalTotalDamage	+= iTempDmg / 10000 ;
		ch->iPhysicalRandomDamage	+= iTempDmg % 10000 ;
	}
	return 0;
}

__inline int ReleaseItemCalcAttackPower(CHARLIST *ch,const int iItem_table_damage)
{
	int iTempDmg =iItem_table_damage;
	if( 100000000 < iTempDmg  ) // ���̳ʽ� �������� ���
	{
		iTempDmg %= 100000000;
		ch->iPhysicalTotalDamage	+= iTempDmg / 10000 ;
		ch->iPhysicalRandomDamage	+= iTempDmg % 10000 ;
	}
	else if ( 100000000 > iTempDmg ) //�÷��� ������ �� ���
	{
		ch->iPhysicalTotalDamage	-= iTempDmg / 10000 ;
		ch->iPhysicalRandomDamage	-= iTempDmg % 10000 ;
	}
	return 0;
}

__inline void EquipItemResist(CHARLIST *ch, const int iRP, const int iRC, const int iRH, 
											const int iRF, const int iRI, const int iRE)
{
	ch->IncExtResist(RT_POISON,	iRP);
	ch->IncExtResist(RT_CURSE,	iRC);
	ch->IncExtResist(RT_HOLY,	iRH);
	ch->IncExtResist(RT_FIRE,	iRF);
	ch->IncExtResist(RT_ICE	,	iRI);
	ch->IncExtResist(RT_ELECT,	iRE);
}

__inline void ReleaseItemResist(CHARLIST *ch, const int iRP, const int iRC, const int iRH, 
											  const int iRF, const int iRI, const int iRE)
{
	ch->DecExtResist(RT_POISON,	iRP);
	ch->DecExtResist(RT_CURSE,	iRC);
	ch->DecExtResist(RT_HOLY,	iRH);
	ch->DecExtResist(RT_FIRE,	iRF);
	ch->DecExtResist(RT_ICE	,	iRI);
	ch->DecExtResist(RT_ELECT,	iRE);
}

__inline void EquipItemHitAndDefenceRate(CHARLIST *ch, const int iHitRate, const int iDefenceRate)
{
	ch->item_Hit_Rate		+= iHitRate;			//	0805 YGI
	ch->item_Deffence_Rate	+= iDefenceRate;
}

__inline void ReleaseItemHitAndDefenceRate(CHARLIST *ch, const int iHitRate, const int iDefenceRate)
{
	ch->item_Hit_Rate		-= iHitRate;			//	0805 YGI
	ch->item_Deffence_Rate	-= iDefenceRate;
}

//010604 lsw	
int CItem_Weapon::EquipItem(CHARLIST *ch )
{	
	EquipItemSetAbility(ch,	Change_str,	Change_con,	Change_dex,	Change_wis,
	Change_int,	Change_Movp, Change_cha, Change_end,	Change_mor,	Change_luc);

	if( ch->Spell )	ch->wspsw += Change_ps;
	else			ch->wspsw += Change_ws;

	EquipItemHitAndDefenceRate(ch, Hit_rate, Defense_rate);//020314 lsw
	EquipItemResist(ch, Increase_Poisoning, Increase_Stone, Increase_Magic, Increase_Fire, Increase_Ice, Increase_lightning);//020314 lsw
	EquipItemCalcAttackPower(ch,GetDamage());//020303 lsw
	
	return EquipItemCommon( ch );			// 001219_2 YGI
}

//010604 lsw	
int CItem_Disposable::EquipItem(CHARLIST *ch )	// 010605_2 YGI
{	
	EquipItemHitAndDefenceRate(ch, Hit_rate, 0);//020314 lsw//���潺 ����Ʈ ���� ����������
	EquipItemCalcAttackPower(ch,GetDamage());//020303 lsw
	return EquipItemCommon( ch );			// 001219_2 YGI
}

//#####################################################
// �Ƹ� ����
////010604 lsw
int CItem_Armor::EquipItem(CHARLIST *ch)//020303 lsw
{	//ch ���ο� CalcNew �ø��� �Լ����� hp�� Mp hungry ���� ����ش�
	EquipItemSetAbility(ch,	Change_str,	Change_con,	Change_dex,	Change_wis,
	Change_int,	Change_Movp, Change_cha, Change_end,	Change_mor,	Change_luc);

	if( ch->Spell )	ch->wspsw += Change_ps;		// 001212 YGI
	else			ch->wspsw += Change_ws;		// 001212 YGI

	EquipItemHitAndDefenceRate(ch, Hit_rate, Defense_rate);//020314 lsw
	EquipItemResist(ch, Increase_Poisoning, Increase_Stone, Increase_Magic, Increase_Fire, Increase_Ice, Increase_lightning);//020314 lsw
	EquipItemCalcAttackPower(ch,GetDamage());
	return EquipItemCommon( ch );			// 001219_2 YGI
}

//#####################################################
// �Ǽ��縮 ����
//010604 lsw
int CItem_Accessory::EquipItem(CHARLIST *ch)
{
	EquipItemSetAbility(ch,	Change_str,	Change_con,	Change_dex,	Change_wis,
	Change_int,	Change_Movp, Change_cha, Change_end,	Change_mor,	Change_luc);

	EquipItemHitAndDefenceRate(ch,Hit_rate,Defense_rate);//020314 lsw

	if( ch->Spell )	ch->wspsw += Change_ps;		// 001217 YGI
	else			ch->wspsw += Change_ws;		// 001217 YGI

	EquipItemResist(ch, Increase_Poisoning, Increase_Stone, Increase_Magic, Increase_Fire, Increase_Ice, Increase_lightning);//020314 lsw
	EquipItemCalcAttackPower(ch,GetDamage());//020303 lsw
	return EquipItemCommon( ch );			// 001219_2 YGI
}

//#####################################################
// ETC ����
//010604 lsw
int CItem_Etc::EquipItem(CHARLIST *ch)
{
	EquipItemSetAbility(ch,	Change_str,	Change_con,	Change_dex,	Change_wis,
	Change_int,	0, Change_cha, Change_end,	Change_mor,	Change_luc);//Movp�� ����

	EquipItemHitAndDefenceRate(ch,Hit_rate,Defense_rate);//020314 lsw

	if( ch->Spell )	ch->wspsw += Change_ps;
	else			ch->wspsw += Change_ws;

	EquipItemResist(ch, Increase_Poisoning, Increase_Stone, Increase_Magic, Increase_Fire, Increase_Ice, Increase_lightning);//020314 lsw
	EquipItemCalcAttackPower(ch,GetDamage());//020303 lsw
	return EquipItemCommon( ch );			// 001219_2 YGI
}

/////////////////////////////////////////////////////////////////////////////////
// ������ ������ ĳ���� �ɷ�ġ ���� üũ 
//
/////////////////////////////////////////////////////////////////////////////////
// ���� ����		// 0206

//010604 lsw
int CItem_Weapon::ReleaseItem( CHARLIST *ch )
{
	ReleaseItemSetAbility(ch,	Change_str,	Change_con,	Change_dex,	Change_wis,
	Change_int,	Change_Movp, Change_cha, Change_end,	Change_mor,	Change_luc);

	ReleaseItemHitAndDefenceRate(ch,Hit_rate,Defense_rate);//020314 lsw
	ReleaseItemResist(ch, Increase_Poisoning, Increase_Stone, Increase_Magic, Increase_Fire, Increase_Ice, Increase_lightning);//020314 lsw
	ReleaseItemCalcAttackPower(ch,GetDamage());//020303 lsw
	ReleaseItemCommon(ch);//020314 lsw
	return 1;
}

int CItem_Disposable::ReleaseItem( CHARLIST *ch )		// 010605_2 YGI
{
	ReleaseItemHitAndDefenceRate(ch,Hit_rate,0);//020314 lsw
	ReleaseItemCalcAttackPower(ch,GetDamage());//020303 lsw
	ReleaseItemCommon(ch);//020314 lsw
	return 1;
}

//#####################################################
// ���� ���� ����
////010604 lsw
int CItem_Armor::ReleaseItem( CHARLIST *ch )
{
	ReleaseItemSetAbility(ch,	Change_str,	Change_con,	Change_dex,	Change_wis,
	Change_int,	Change_Movp, Change_cha, Change_end,	Change_mor,	Change_luc);

	ReleaseItemHitAndDefenceRate(ch,Hit_rate,Defense_rate);//020314 lsw

	ReleaseItemResist(ch, Increase_Poisoning, Increase_Stone, Increase_Magic, Increase_Fire, Increase_Ice, Increase_lightning);//020314 lsw
	ReleaseItemCalcAttackPower(ch,GetDamage());//020303 lsw
	ReleaseItemCommon(ch);//020314 lsw
	return 1;	
}

//#####################################################
// �Ǽ��縮 ����
////010604 lsw
int CItem_Accessory::ReleaseItem(CHARLIST *ch )
{
	ReleaseItemSetAbility(ch,	Change_str,	Change_con,	Change_dex,	Change_wis,
	Change_int,	Change_Movp, Change_cha, Change_end,	Change_mor,	Change_luc);
	ReleaseItemHitAndDefenceRate(ch,Hit_rate,Defense_rate);//020314 lsw

	if( ch->Spell )	ch->wspsw -= Change_ps;		// 001217 YGI
	else	ch->wspsw -= Change_ws;				// 001217 YGI

	ReleaseItemResist(ch, Increase_Poisoning, Increase_Stone, Increase_Magic, Increase_Fire, Increase_Ice, Increase_lightning);//020314 lsw
	ReleaseItemCalcAttackPower(ch,GetDamage());//020303 lsw
	ReleaseItemCommon(ch);//020314 lsw
	return 1;	
}

//#####################################################
// ETC ����
////010604 lsw
int CItem_Etc::ReleaseItem( CHARLIST *ch )
{
	ReleaseItemSetAbility(ch,	Change_str,	Change_con,	Change_dex,	Change_wis,
	Change_int,	0, Change_cha, Change_end,	Change_mor,	Change_luc);

	ReleaseItemHitAndDefenceRate(ch,Hit_rate,Defense_rate);//020314 lsw

	if( ch->Spell )	ch->wspsw -= Change_ps;		// 001217 YGI
	else	ch->wspsw -= Change_ws;				// 001217 YGI

	ReleaseItemResist(ch, Increase_Poisoning, Increase_Stone, Increase_Magic, Increase_Fire, Increase_Ice, Increase_lightning);//020314 lsw
	ReleaseItemCalcAttackPower(ch,GetDamage());//020303 lsw
	ReleaseItemCommon(ch);//020314 lsw
	return 1;	
}

//////////////////////////////////////////////////////////////////////////////////
//																				//
//	����: Item�� Equip�������� check�ϴ� �޼ҵ��								//
//			������ �޼ҵ�鵵 �ڵ���� ��� ������.								//
//			virtual �Լ���														//
//																				//
//	�Ķ����:	char_id; ���� ������ �ϴ� �ش� ĳ������ id(index)				//
//				cstatus; ĳ������ ���º�ȭ�� Ŭ���̾�Ʈ�� �˷��� STRUCTURE *	//
//				source, dest; POS���� ����										//
//																				//
//////////////////////////////////////////////////////////////////////////////////
int CItem_Weapon::is_equipable(int char_id, t_chr_status_info *cstatus, POS source, POS dest)
{
	const CHARLIST *ch =CheckServerId(char_id);
	if( !ch ) {	return 0;}

	if( wear_able != equip_able[dest.p3] )			// 0613 YGI
	{
		if( (wear_able != WEAR_TWO_HAND) ) return NOT;
		if( ch->equip[WT_SHIELD].item_no ) 
		{
			switch(Item_kind)
			{
			case IK_DUAL_BOW://030102 lsw Dual BOW
			case IK_SHORT_BOW:
			case IK_LONG_BOW:
				{
				}break;
			default:
				{
					return NOT;		// Ȱ�� �ƴѰ��
				}
			}
				
			CItem *t = ::ItemUnit( ch->equip[WT_SHIELD] );
			if( t )
			{
				switch(t->GetItemKind())
				{
				case IK_TWO_ARROW:
				case IK_DUAL_ARROW://030102 lsw ARROW
					{
					}break;
				default:
					{
						return NOT;// Ȱ�̱� �ѵ� Ȱ�̿��� ���� ��� �ִ� ��� 
					}
				}
			}
		}
		if( dest.p3 != WT_WEAPON ) return NOT;
	}
	else
	{
		switch(wear_able)
		{
		case WEAR_RIGHT_HAND://WT_WEAPON Position
			{
				CItem *t = ItemUnit( ch->equip[WT_SHIELD] );
				if( t )
				{
					switch(t->GetItemKind())
					{
					case IK_TWO_ARROW:
					case IK_DUAL_ARROW://030102 lsw ARROW
						{
							return NOT;//SHIELD Position in Arrow
						}break;
					}
				}
			}break;
		case WEAR_LEFT_HAND:
			{
				switch(GetItemKind())//My Weapon is Arrow // Case Dual Arrow
				{
				case IK_TWO_ARROW:
				case IK_DUAL_ARROW:
					{
						CItem *t = ItemUnit( ch->equip[WT_WEAPON] );
						if( t )
						{
							switch(t->GetItemKind())
							{
							case IK_DUAL_BOW://030102 lsw Dual BOW
							case IK_SHORT_BOW:
							case IK_LONG_BOW:
								{	
								}break;
							default:
								{
									return NOT;
								}break;
							}
						}
					}
				}
			}break;
		}
	}

	if(!IsEquipAbleAbilityCheck	(Need3_str	, ch->GetAbility(STR)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_con	, ch->GetAbility(CON)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_dex	, ch->GetAbility(DEX)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_end	, ch->GetAbility(ENDU)))	{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_cha	, ch->GetAbility(CHA)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_mor	, ch->GetAbility(MOR)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_Movp	, ch->GetAbility(MOVP)))	{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_luc	, ch->GetAbility(LUCK)))	{return 0;}
	if(!IsEquipAbleCheckMouseMRD(Mouse_MRD	, ch->Skill[Skill_Ability])){return 0;}
	if(!IsEquipAbleCheckWisInt	(Need3_wis	, Need3_int, ch->GetAbility(WIS),ch->GetAbility(INT_)) ){return 0;}
	if(!IsEquipAbleCheckWsPs	(Need3_ws	, Need3_ps, ch->GetAbility(WSPS), ch->Spell) ){return 0;}
	if(!IsEquipAbleCheckGender	(Need3_gender, ch->Gender) )			{return 0;}
	if(!IsEquipAbleCheckAbleDay	(Repair_Skill2_min,Repair_Res1) )		{return 0;}
	if(!IsEquipAbleCheckNation(Imunity_Cure_4, ch))		{return 0;}
	if(!IsEquipAbleCheckLv(Imunity_Cure_5, ch))		{return 0;}
	if(!IsEquipAbleCheckFame(Imunity_Cure_6, ch))		{return 0;}
	if(!IsEquipAbleItemKind(GetItemKind(),ch))	{return 0;}
	if(!IsEquipAbleDualStep(GetNeedDualStep(),ch)){return 0;}
	if(!IsEquipAbleClass(
		GetClassWarriorAble(),GetClassThiefAble(),
		GetClassArcherAble(),GetClassWizardAble(),
		GetClassClericAble(),ch)){return 0;}//021113 lsw
	return IsEquipAbleCommon(ch);
}

int CItem_Tool::is_equipable(int char_id, t_chr_status_info *cstatus, POS source, POS dest)
{
	const CHARLIST *ch =CheckServerId(char_id);
	if( !ch ) {	return 0;}
	if(!IsEquipAbleCheckAbleDay	(Repair_Skill2_min,Repair_Res1) ){return 0;}
	if(!IsEquipAbleItemKind(GetItemKind(),ch))	{return 0;}
	
	return IsEquipAbleCommon(ch);
}

int CItem_Potion::is_equipable(int char_id, t_chr_status_info *cstatus, POS source, POS dest)
{
	const CHARLIST *ch =CheckServerId(char_id);
	if( !ch ) {	return 0;}
	return 0;//������ ���� ����
}

int CItem_Armor::is_equipable(int char_id, t_chr_status_info *cstatus, POS source, POS dest)
{
	const CHARLIST *ch =CheckServerId(char_id);
	if( !ch ) {	return 0;}

	if( wear_able != equip_able[dest.p3] )			// ��ġ�� �� ���� ��� // 0621 YGI
	{
		if( (wear_able != WEAR_TWO_HAND) ) return NOT;
		if( ch->equip[WT_SHIELD].item_no ) return NOT;
		if( dest.p3 != WT_WEAPON ) return NOT;
	}
	
	if( wear_able == WEAR_LEFT_HAND )						// ��հ��� ����Ҷ� ���и� �����ϸ�...
	{
		CItem *t = ItemUnit( ch->equip[0] );
		if( t && t->GetWearAble() == WEAR_TWO_HAND ) return NOT;
	}
	if(!IsEquipAbleAbilityCheck	(Need3_str	, ch->GetAbility(STR)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_con	, ch->GetAbility(CON)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_dex	, ch->GetAbility(DEX)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_end	, ch->GetAbility(ENDU)))	{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_cha	, ch->GetAbility(CHA)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_mor	, ch->GetAbility(MOR)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_Movp	, ch->GetAbility(MOVP)))	{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_luc	, ch->GetAbility(LUCK)))	{return 0;}
	if(!IsEquipAbleCheckMouseMRD(Mouse_MRD	, ch->Skill[Skill_Ability])){return 0;}
	if(!IsEquipAbleCheckWisInt	(Need3_wis	, Need3_int, ch->GetAbility(WIS),ch->GetAbility(INT_)) ){return 0;}
	if(!IsEquipAbleCheckWsPs	(Need3_ws	, Need3_ps, ch->GetAbility(WSPS), ch->Spell) ){return 0;}
	if(!IsEquipAbleCheckGender	(Need3_gender, ch->Gender) )		{return 0;}
	if(!IsEquipAbleCheckAbleDay	(Repair_Skill2_min,Repair_Res1) ){return 0;}
	if(!IsEquipAbleCheckNation(Imunity_Cure_4, ch))		{return 0;}
	if(!IsEquipAbleCheckLv(Imunity_Cure_5, ch))		{return 0;}
	if(!IsEquipAbleCheckFame(Imunity_Cure_6, ch))		{return 0;}
	if(!IsEquipAbleItemKind(GetItemKind(),ch))	{return 0;}
	if(!IsEquipAbleDualStep(GetNeedDualStep(),ch)){return 0;}
	if(!IsEquipAbleClass(
		GetClassWarriorAble(),GetClassThiefAble(),
		GetClassArcherAble(),GetClassWizardAble(),
		GetClassClericAble(),ch)){return 0;}//021113 lsw
	return IsEquipAbleCommon(ch);
}

int CItem_Disposable::is_equipable(int char_id, t_chr_status_info *cstatus, POS source, POS dest)
{
	const CHARLIST *ch =CheckServerId(char_id);
	if( !ch ) {	return 0;}

	if( wear_able != equip_able[dest.p3] )// ��ġ�� �� ���� ��� // 0621 YGI
	{
		if( (wear_able != WEAR_TWO_HAND) ) return NOT;		// ��չ��Ⱑ �ƴҶ�
		if( ch->equip[WT_SHIELD].item_no ) return NOT;		// �����ڸ��� ���� �ִٸ�
		if( dest.p3 != WT_WEAPON ) return NOT;				// ��ġ�� ���� �ڸ��� �ƴϸ� NOT�� ����
	}
	else 
	{
		if(	Item_kind == IK_TWO_ARROW
		||	Item_kind == IK_DUAL_ARROW)
		{
			CItem *t = ItemUnit( ch->equip[WT_WEAPON] );
			if(t)
			{
				switch(t->GetItemKind())
				{
				case IK_DUAL_BOW://030102 lsw Dual BOW
				case IK_SHORT_BOW:
				case IK_LONG_BOW:
					{
					}break;
				default:
					{
						return NOT;		// Ȱ�� �ƴѰ��
					}
				}
			}
			else
			{
				return NOT;		// Ȱ�� �ƴѰ��
			}
		}
	}
	if(!IsEquipAbleAbilityCheck	(Need3_str	, ch->GetAbility(STR)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_con	, ch->GetAbility(CON)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_dex	, ch->GetAbility(DEX)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_end	, ch->GetAbility(ENDU)))	{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_cha	, ch->GetAbility(CHA)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_mor	, ch->GetAbility(MOR)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_Movp	, ch->GetAbility(MOVP)))	{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_luc	, ch->GetAbility(LUCK)))	{return 0;}
	if(!IsEquipAbleCheckMouseMRD(Mouse_MRD	, ch->Skill[Skill_Ability])){return 0;}
	if(!IsEquipAbleCheckWisInt	(Need3_wis	, Need3_int, ch->GetAbility(WIS),ch->GetAbility(INT_)) ){return 0;}
	if(!IsEquipAbleCheckWsPs	(Need3_ws	, Need3_ps, ch->GetAbility(WSPS), ch->Spell) ){return 0;}
	if(!IsEquipAbleCheckGender	(Need3_gender, ch->Gender) )		{return 0;}
//	if(!IsEquipAbleCheckAbleDay	(Repair_Skill2_min,Repair_Res1) ){return 0;}//DisPosable�� Repair_Skill2_min����
//	if(!IsEquipAbleCheckNation(Imunity_Cure_4, ch))		{return 0;}
//	if(!IsEquipAbleCheckLv(Imunity_Cure_5, ch))			{return 0;}
//	if(!IsEquipAbleCheckFame(Imunity_Cure_6, ch))		{return 0;}
	if(!IsEquipAbleItemKind(GetItemKind(),ch))	{return 0;}

	return IsEquipAbleCommon(ch);
}

int CItem_Accessory::is_equipable(int char_id, t_chr_status_info *cstatus, POS source, POS dest)
{
	const CHARLIST *ch =CheckServerId(char_id);
	if( !ch ) {	return 0;}

	if( wear_able != equip_able[dest.p3] ) return NOT;		// ��ġ�� �� ���� ���
    if(!IsEquipAbleAbilityCheck	(Need3_str	, ch->GetAbility(STR)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_con	, ch->GetAbility(CON)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_dex	, ch->GetAbility(DEX)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_end	, ch->GetAbility(ENDU)))	{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_cha	, ch->GetAbility(CHA)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_mor	, ch->GetAbility(MOR)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_Movp	, ch->GetAbility(MOVP)))	{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_luc	, ch->GetAbility(LUCK)))	{return 0;}
	if(!IsEquipAbleCheckMouseMRD(Mouse_MRD	, ch->Skill[Skill_Ability])){return 0;}
	if(!IsEquipAbleCheckWisInt	(Need3_wis	, Need3_int, ch->GetAbility(WIS),ch->GetAbility(INT_)) ){return 0;}
	if(!IsEquipAbleCheckWsPs	(Need3_ws	, Need3_ps, ch->GetAbility(WSPS), ch->Spell) ){return 0;}
	if(!IsEquipAbleCheckGender	(Need3_gender, ch->Gender) )		{return 0;}
	if(!IsEquipAbleCheckAbleDay	(Repair_Skill2_min,Repair_Res1) ){return 0;}//DisPosable�� Repair_Skill2_min����
	if(!IsEquipAbleCheckNation(Imunity_Cure_4, ch))		{return 0;}
	if(!IsEquipAbleCheckLv(Imunity_Cure_5, ch))		{return 0;}
	if(!IsEquipAbleCheckFame(Imunity_Cure_6, ch))		{return 0;}
	if(!IsEquipAbleItemKind(GetItemKind(),ch))	{return 0;}
	if(!IsEquipAbleDualStep(GetNeedDualStep(),ch)){return 0;}
	if(!IsEquipAbleClass(
		GetClassWarriorAble(),GetClassThiefAble(),
		GetClassArcherAble(),GetClassWizardAble(),
		GetClassClericAble(),ch)){return 0;}//021113 lsw
	return IsEquipAbleCommon(ch);
}

int CItem_Etc::is_equipable(int char_id, t_chr_status_info *cstatus, POS source, POS dest)
{
	const CHARLIST *ch =CheckServerId(char_id);
	if( !ch ) {	return 0;}

	if( wear_able != equip_able[dest.p3] ) return NOT;		// ��ġ�� �� ���� ���
    if(!IsEquipAbleAbilityCheck	(Need3_str	, ch->GetAbility(STR)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_con	, ch->GetAbility(CON)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_dex	, ch->GetAbility(DEX)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_end	, ch->GetAbility(ENDU)))	{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_cha	, ch->GetAbility(CHA)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_mor	, ch->GetAbility(MOR)))		{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_Movp	, ch->GetAbility(MOVP)))	{return 0;}
	if(!IsEquipAbleAbilityCheck	(Need3_luc	, ch->GetAbility(LUCK)))	{return 0;}
	if(!IsEquipAbleCheckMouseMRD(Mouse_MRD	, ch->Skill[Skill_Ability])){return 0;}
	if(!IsEquipAbleCheckWisInt	(Need3_wis	, Need3_int, ch->GetAbility(WIS),ch->GetAbility(INT_)) ){return 0;}
	if(!IsEquipAbleCheckWsPs	(Need3_ws	, Need3_ps, ch->GetAbility(WSPS), ch->Spell) ){return 0;}
	if(!IsEquipAbleCheckGender	(Need3_gender, ch->Gender) )		{return 0;}
	if(!IsEquipAbleCheckAbleDay	(Repair_Skill2_min,Repair_Res1) ){return 0;}//DisPosable�� Repair_Skill2_min����
	if(!IsEquipAbleCheckNation(Imunity_Cure_4, ch))		{return 0;}
	if(!IsEquipAbleCheckLv(Imunity_Cure_5, ch))		{return 0;}
	if(!IsEquipAbleCheckFame(Imunity_Cure_6, ch))		{return 0;}
	if(!IsEquipAbleItemKind(GetItemKind(),ch))	{return 0;}
	if(!IsEquipAbleDualStep(GetNeedDualStep(),ch)){return 0;}
	if(!IsEquipAbleClass(
		GetClassWarriorAble(),GetClassThiefAble(),
		GetClassArcherAble(),GetClassWizardAble(),
		GetClassClericAble(),ch)){return 0;}//021113 lsw
	return IsEquipAbleCommon(ch);
}
