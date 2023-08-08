#include "..\stdafx.h"
#include "DefaultHeader.h"
#include "CItem.h"
#include "OP_Magic.h"

extern int GetBoxItemId_SQL( );
extern struct CItem_List Item_Ref ;
extern void getItemIndex(int, int &, int &) ;

////////////////////////////////////////////////////////////////////////////////
//
//	������ ��ȣ�� Ÿ���� ���� ���� �Ѿ������� �Ǵ��ϴ� �Լ�
//
//		�Ķ���ʹ� Ÿ�԰� ��ȣ�� �Է� �ް�
//		�����ͷ� �����Ѵ�.	�� �� ���� ��� NULL����
//
////////////////////////////////////////////////////////////////////////////////
CItem *ItemUnit( ItemAttr item )
{
	int type, num;
	getItemIndex( item.item_no, type, num );
	return ItemUnit( type, num );
}
//011030 lsw >
CItem *ItemUnit( int item_no )
{
	return ItemUnit( item_no/1000, item_no%1000);
}
//011030 lsw <

CItem *ItemUnit( int type, int item_no )
{
	if( (type<0) || (type>10) ) return NULL;
	if( (item_no<=0) || (item_no > Item_Ref.nItem[type]) ) return NULL;

	switch( type )
	{
		case 	PLANT		:	return &CPlant		[item_no];	break;
		case 	MINERAL		:	return &CMineral	[item_no];	break;
		case 	HERB		:	return &CHerb		[item_no];	break;
		case 	COOK		:	return &CCook		[item_no];	break;
		case 	POTION		:	return &CPotion		[item_no];	break;
		case 	TOOL		:	return &CTool		[item_no];	break;
		case 	WEAPON		:	return &CWeapon		[item_no];	break;
		case 	DISPOSABLE	:	return &CDisposable	[item_no];	break;
		case 	ARMOR		:	return &CArmor		[item_no];	break;
		case 	ACCESSORY	:	return &CAccessory	[item_no];	break;
		case 	ETC			:	return &CEtc		[item_no];	break;
	}
	return NULL;
//	return Item_Ref.Item_Info[type][item_no];
}

DWORD CreateItemDuration( int type, int itemno )			// 0620 YGI
{
	static int bonus = 0;
	
	CItem *t;

	t = ItemUnit( type, itemno );
	if( t == NULL ) return 0;

	DWORD basic_dur;
	
	 if( type == DISPOSABLE )
		basic_dur = t->GetItemQuantity();
	else if( t->GetRbutton() == DIVIDE_ITEM ) 
	{
		basic_dur = t->GetDuration();
		if( basic_dur == -1 ) basic_dur = 1;
	}
	else basic_dur = MAKELONG( t->GetDuration(), t->GetDuration() );

	return basic_dur;
}

ItemAttr GenerateItem( const int iItemFullNo, const int iCustomType, const DWORD dwValue )
{
	return ItemMgr.GenerateItem(iItemFullNo,iCustomType,dwValue);
}

ItemAttr GenerateItem( const int iItemFullNo )
{
	return ItemMgr.GenerateItem(iItemFullNo);
}

// 010109 YGI
int DeleteItem( ItemAttr *item )
{
	int type, num;
	if( !item ) return 0;		// NULL�� ��� 
	getItemIndex( item->item_no, type, num );

	CItem *t = ItemUnit( type, num );
	if( !t ) 
	{
		memset( item, 0, sizeof( ItemAttr ) );
		return 0;
	}

	if( t->GetItemKind() == IK_BOX ) 
		SendDeleteBox( item->attr[IATTR_ID] );
	t->ThisMapValue--;

	memset( item, 0, sizeof( ItemAttr ) );
	return 1;
}

int GetWeight( ItemAttr item )
{
	int type, num;
	getItemIndex( item.item_no, type, num );

	CItem *t = ItemUnit( type, num );
	if( !t ) return 1;

	int weight = t->GetWeight();

	if( type == DISPOSABLE)
	{
		int dur = t->GetItemQuantity();
	}
	if( t->GetRbutton() == DIVIDE_ITEM )
	{
		int dur = t->GetItemDuration();
		if( dur > 0 ) 
			weight *= item.attr[IATTR_MUCH] / dur;
		else weight *= item.attr[IATTR_MUCH];
	}

	return weight;
}

int GetTotalItemWeight( CHARLIST *ch )
{
	int weight = 0;
	int a, b, c;
	for(a=0;a<3;a++)
		for(b=0;b<3;b++)
			for(c=0;c<8;c++)
				if(ch->inv[a][b][c].item_no) 
					weight += GetWeight( ch->inv[a][b][c] );
	for(a=0;a<6;a++)
		if(ch->quick[a].item_no)	weight += GetWeight(ch->quick[a]);
	for(a=0;a<8;a++)
		if(ch->equip[a].item_no)	weight += GetWeight(ch->equip[a]);
	if( ch->handheld.item_no ) weight += GetWeight( ch->handheld );

	return weight;
}



/////////////////////////////////////////////////
// ���� �̹����� �����´�
/////////////////////////////////////////////////
int GetItemView( int item_no, int is_man )
{
	CItem *t;
	int type, num;
	getItemIndex( item_no, type, num );
	
	t = ItemUnit( type, num );
	if( !t ) return 0;
	else return t->GetItemShow( is_man );
}
/////////////////////////////////// //0101 //////////////////////////////////////



//////////////////////////// Item POS Set /////////////////////////////////
void SetItemPos(int type, POS* IP_set)
{
	IP_set->type = (char)type;
	IP_set->p1 = 0;
	IP_set->p2 = 0;
	IP_set->p3 = 0;
}

void SetItemPos(int type, int p, POS* IP_set)
{
	IP_set->type = (char)type;
	IP_set->p1 = 0;
	IP_set->p2 = 0;
	IP_set->p3 = (short int)p;
}

void SetItemPos(int type, int p1, int p2, int p3, POS* IP_set)
{
	IP_set->type = ( char )type;
	IP_set->p1 = (short int)p1;
	IP_set->p2 = (short int)p2;
	IP_set->p3 = (short int)p3;
}

DWORD GetMoneyByItem( CHARLIST *ch )
{
	return (LocalMgr.IsChangeMoney())?GetNewMoneyByItem(ch):GetMoneyByOldItem(ch);
}

DWORD GetNewMoneyByItem( CHARLIST *ch )		// �κ��� �ִ� ����
{
	DWORD money=0;

	int type, num;
	CItem *t;

	int weight = 0;
	for( int i=0; i<3; i++ )
		for( int j=0; j<3; j++ )
			for( int k=0; k<8; k++ )
			{
				ItemAttr &item = ch->inv[i][j][k];
				if( item.item_no )
				{
					weight += GetWeight( item );
					getItemIndex( item.item_no, type, num );
					t = ItemUnit( type, num );
					if(t && t->GetItemKind() == IK_NEW_MONEY )
					{
						if( item.item_no == IN_NEW_COIN && item.attr[IATTR_MUCH] > 5)	// ����
						{
							item.item_no = IN_NEW_COINS;		// �� ���̷� �ٲ�
						}
						else if( item.item_no == IN_NEW_COINS && item.attr[IATTR_MUCH] <= 5 ) // ���� ����
						{
							item.item_no = IN_NEW_COIN;
						}
						money += item.attr[IATTR_MUCH];
					}
				}
			}
	ch->itemweight = weight;
	return money;
}

DWORD GetMoneyByOldItem( CHARLIST *ch )
{
	DWORD money=0;

	int type, num;
	CItem *t;

	int weight = 0;
	for( int i=0; i<3; i++ )
		for( int j=0; j<3; j++ )
			for( int k=0; k<8; k++ )
			{
				ItemAttr &item = ch->inv[i][j][k];
				if( item.item_no )
				{
					weight += GetWeight( item );
					getItemIndex( item.item_no, type, num );
					t = ItemUnit( type, num );
					if(t && t->GetItemKind() == IK_MONEY )
					{
						if( item.item_no == IN_COIN && item.attr[IATTR_MUCH] > 5)	// ����
						{
							item.item_no = IN_COINS;		// �� ���̷� �ٲ�
						}
						else if( item.item_no == IN_COINS && item.attr[IATTR_MUCH] <= 5 ) // ���� ����
						{
							item.item_no = IN_COIN;
						}
						money += item.attr[IATTR_MUCH];
					}
				}
			}
	ch->itemweight = weight;
	return money;
}

/////////////////////////////////////////////////////////////////////////
//	ĳ���Ͱ� ������ �ִ� ������ �㿡 ������
///////////////////////////////////////////////////////////////////////
int DropItem( int x, int y, ItemAttr *item )
{
	return AddItemList( item->item_no, item->attr, 0, x, y, 0, 0 );
}


/////////////////////////////////////////////////////////////////////
//
// �� �����ۿ� ������ �޼ҵ�� ( �� ���� ���ϱ� �Լ� )
//
////////////////////////////////////////////////////////////////////

// 010210 YGI
int SubtractOldMoney( DWORD money, CHARLIST *ch )
{
	CHARLIST *check_ch = CheckServerId( ch->GetServerID());
	if( check_ch != ch ) return -1;
	if( !money ) return 1;

	int a, b, c;
	ItemAttr *item = SearchItemOfInvByKind( IK_MONEY, ch, a, b, c );
	if( !item ) return -1;		// �� �������� �ϳ��� ����. -->SCharacterData.nMoney = 0;		==> ���� ����...

	POS pos;
	SetItemPos( INV, a, b, c, &pos);
	if( item->attr[IATTR_MUCH] <= money )
	{
		money -= item->attr[IATTR_MUCH];
		// 020428 YGI acer
		SendDeleteItem( item, &pos, ch );
		SubtractOldMoney( money, ch );
	}
	else 
	{
		item->attr[IATTR_MUCH] -= money;
		SendChangeDurationByKein( &pos, item->attr[IATTR_MUCH], ch->GetServerID());
		return 1;
	}
	return 1;
}


// 010109 YGI
int SubtractMoney( DWORD money, CHARLIST *ch, int type )
{
	CHARLIST *check_ch = CheckServerId( ch->GetServerID());
	if( check_ch != ch ) return -1;

	if(ch->Money < money ) return -1;	// ���� ������
	if( !money ) return 1;

	int a = 0, b = 0, c = 0;
	ItemAttr *item  = NULL;
	if(LocalMgr.IsChangeMoney())//030102 lsw
	{
		item = SearchItemOfInvByKind( IK_NEW_MONEY, ch, a, b, c );
	}
	else
	{
		item = SearchItemOfInvByKind( IK_MONEY, ch, a, b, c );
	}
	if( !item ) return -1;		// �� �������� �ϳ��� ����. -->SCharacterData.nMoney = 0;		==> ���� ����...

	POS pos;
	SetItemPos( INV, a, b, c, &pos);
	if( item->attr[IATTR_MUCH] <= money )
	{
		money -= item->attr[IATTR_MUCH];
		// 020428 YGI acer
		SendDeleteItem( item, &pos, ch );
		return SubtractMoney( money, ch );
	}
	else 
	{
		item->attr[IATTR_MUCH] -= money;
		SendChangeDurationByKein( &pos, item->attr[IATTR_MUCH], ch->GetServerID());
		return 1;
	}
	return 1;
}
int SubtractMoney( DWORD money, CHARLIST *ch )
{
	int ret = SubtractMoney( money, ch, 1 );	// ��� ȣ���� ��� ������
	ch->Money = GetMoneyByItem( ch );			// �� ����� �ѹ��� �Ѵ�.
	return ret;
}

int SearchItemPosByNumber(ItemAttr *item, int &a, int &b, int &c, CHARLIST *ch)
{
	for(a=0;a<3;a++)
		for(b=0;b<3;b++)
			for(c=0;c<8;c++)
				if(ch->inv[a][b][c].item_no == item->item_no && 
					ch->inv[a][b][c].attr[IATTR_RARE_MAIN] == item->attr[IATTR_RARE_MAIN] )
					return 1;
	return 0;
}


int SearchCoinItem( int &a, int &b, int &c, CHARLIST *ch )		// 010210 YGI
{
	for(a=0;a<3;a++)
		for(b=0;b<3;b++)
			for(c=0;c<8;c++)
			{
				int iItemNo1 = IN_NEW_COIN, iItemNo2 = IN_NEW_COINS;
				if(LocalMgr.IsChangeMoney())//030102 lsw
				{
					iItemNo1 = IN_NEW_COIN;
					iItemNo2  =IN_NEW_COINS;
				}
				else
				{
					iItemNo1 = IN_COIN;
					iItemNo2  =IN_COINS;
				}
				
				if( ch->inv[a][b][c].item_no == iItemNo1 || ch->inv[a][b][c].item_no == iItemNo2 )
				{
					if( ch->inv[a][b][c].attr[IATTR_MUCH] == MAX_MONEY ) continue;
					return 1;
				}
			}
	return 0;
}

ItemAttr *SearchItemOfInvByKind( int kind, CHARLIST *ch, int &i, int &j, int &k )
{
	int type, num;
	CItem * t;
	for( i=0; i<3; i++ )
		for( j=0; j<3; j++ )
			for( k=0; k<8; k++ )
			{
				ItemAttr &item = ch->inv[i][j][k];
				if( item.item_no )
				{
					getItemIndex( item.item_no, type, num );
					t = ItemUnit( type, num );
					if( t && t->GetItemKind() == kind ) 
					{
						return &item;
					}
				}
			}
	return NULL;
}

ItemAttr *SearchItemOfInvByKind( int kind, CHARLIST *ch )
{
	int a, b, c;
	return SearchItemOfInvByKind( kind, ch, a, b, c );
}

ItemAttr *SearchInv( CHARLIST *ch )
{
	for( int a=0; a<3; a++ )
		for( int b=0; b<3; b++ )
			for( int c=0; c<8; c++ )
			{
				if( !ch->inv[a][b][c].item_no ) return &ch->inv[a][b][c];
			}
	return NULL;
}


int IsEqualPosByPos( POS first, POS second )
{
	if( first.type	!= second.type	|| 
		first.p1	!= second.p1	||
		first.p2	!= second.p2	||
		first.p3	!= second.p3 )		return 0;

	return 1;
}

void CheckItem( short int cn ) // �߸��� �������� ������ �ִ���
{	//021126 lsw
	CHARLIST *ch = CheckServerId(cn);
	if( !ch ) {return;}

	POS pos = {0,};

	int a=0, b=0, c=0;
	for( a=0; a<3; a++ )
	for( b=0; b<3; b++ )
	for( c=0; c<8; c++ )
	{
		ItemAttr *pItem = &ch->inv[a][b][c];
		if(pItem->item_no)
		{
			if(!ItemMgr.CheckFaultItem(*pItem,true))//020116 LSW// 10 ��� �̻��� ���� �� �̻��� ������ ���� 
			{	
				::SetItemPos( INV, a, b, c, &pos );
				::SendServerEachItem( &pos, pItem, cn );
				::SendItemEventLog( pItem, cn, 0, SILT_DELETE_BY_ATTR, 1 ); //YGI acer
			}
		}
	}
	
	for( a=0; a<ITEM_EQUIP_MAX; a++ )
	{
		ItemAttr *pItem = &ch->equip[a];
		if(pItem->item_no)
		{
			if(!ItemMgr.CheckFaultItem(*pItem,true))//020116 LSW// 10 ��� �̻��� ���� �� �̻��� ������ ���� 
			{
				::SetItemPos( EQUIP, a, &pos );
				::SendServerEachItem( &pos, pItem, cn );
				::SendItemEventLog( pItem, cn, 0, SILT_DELETE_BY_ATTR, 1 ); //YGI acer
			}
		}
	}
	
	for( a=0; a<ITEM_QUICK_MAX ; a++ )
	{
		ItemAttr *pItem = &ch->quick[a];
		if(pItem->item_no)
		{
			//soto-030513 �� 5���� �ɺ� �������̴�.
			if( a >= 5)
			{
				::SetItemPos( QUICK, a, &pos );
				::SendServerEachItem( &pos, pItem, cn );
				::SendItemEventLog( pItem, cn, 0, SILT_DELETE_BY_ATTR, 1 ); //YGI acer
			}
			else
			if(!ItemMgr.CheckFaultItem(*pItem,true))//020116 LSW// 10 ��� �̻��� ���� �� �̻��� ������ ���� 
			{
				::SetItemPos( QUICK, a, &pos );
				::SendServerEachItem( &pos, pItem, cn );
				::SendItemEventLog( pItem, cn, 0, SILT_DELETE_BY_ATTR, 1 ); //YGI acer
			}
		}
	}

	for( a=0; a<5; a++ )
	for( b=0; b<3; b++ )
	for( c=0; c<6; c++ )
	{
		ItemAttr *pItem = &ch->bank[a][b][c];
		if(pItem->item_no)
		{
			if(!ItemMgr.CheckFaultItem(*pItem,true))//020116 LSW// 10 ��� �̻��� ���� �� �̻��� ������ ���� 
			{
				::SetItemPos( BANK, a, b, c, &pos );
				::SendServerEachItem( &pos, pItem, cn );
				::SendItemEventLog( pItem, cn, 0, SILT_DELETE_BY_ATTR, 1 ); //YGI acer
			}
		}
	}

	return;
}

// 020428 YGI acer
int BreakItemByDuration( ItemAttr *pItem, CHARLIST *ch, POS pos )		// �������� ���� �϶� �������� �νŴ�.
{
	SendItemEventLog( pItem, ch->GetServerID(), SN_NOT_USER, SILT_DELETE_BY_DURATION, 2 ); //YGI acer
	SendDeleteItem( pItem, &pos, ch, true );
	CheckAndSendChangeEquip( ch );

	return 1;
}

int CheckAutoDivideMoney( ItemAttr *item, const short int cn )		// 100000�� ���� ������ ó��
{//021126 lsw
	CItem *t = ItemUnit( *item );
	if( !t ) {return 0 ;}

	if( t->GetItemKind() != IK_MONEY 
	&&	t->GetItemKind() != IK_NEW_MONEY ) {return 0;}		// ���� ��츸
	CHARLIST *ch = ::CheckServerId( cn );
	if( !ch ) {return 0;}

	if( item->attr[IATTR_DURATION] > MAX_MONEY ) //100���� �Ѿ��
	{//���� �������� 100������ �Ѵ´�
		int a=0, b=0, c=0;
		if( !::SearchMoneyItem( ch->inv, a, b, c ) )//������̳� ���� ����
		{//������̳� ���� ����
			if (!::SearchInv(ch->inv, a, b, c))
			{
				ItemAttr temp_item = *item;//���������� temp�� ���� 
				item->attr[IATTR_MUCH]		= MAX_MONEY;//100�������� ����� �ְ�
				temp_item.attr[IATTR_MUCH] -= MAX_MONEY;//100���� ���� ũ�ϱ� 100������ ������ -���� �ȵȴ�
				::DropItem( ch->X, ch->Y, &temp_item );//����� �Ϳ��� 100���� �� ���� �ٴڿ� �기��
				::SendItemEventLog( &temp_item , cn, cn, SILT_PUT_GROUND_MAX_INVEN, 1 );
				return 0;
			}
		}//if( !::SearchMoneyItem( ch->inv, a, b, c ) )//������̳� ���� ����

		//������̳� ���� �ֳ�
		ItemAttr *new_item = &ch->inv[a][b][c];
		if( new_item->item_no )
		{//�װ� ���̶�� SearchMoneyItem�� ���� ����ȣ�� ���� �ȴ�
			new_item->attr[IATTR_MUCH] += (item->attr[IATTR_MUCH] - MAX_MONEY);//100���� �ѱ� ������ 100������ ���� ������ ���� ���Ѵ�
		}
		else
		{//��ĭ �̶��
			*new_item = *item;
			new_item->attr[IATTR_MUCH] = (item->attr[IATTR_MUCH] - MAX_MONEY);//100���� ������ �κ��� �ִ´�
		}

		item->attr[IATTR_MUCH] = MAX_MONEY;
		::SendServerEachItem( item, ch );//������� ��ȭ�� Ŭ���̾�Ʈ�� �����ش�
		if( new_item->attr[IATTR_MUCH] > MAX_MONEY ) 
		{//�ְ� �������� 100�� ������ �������� ���� ��� ������
			::CheckAutoDivideMoney( new_item, cn );
		}
		POS pos = {0,};
		::SetItemPos( INV, a, b, c, &pos );
		::SendServerEachItem( &pos, new_item, cn );
		return 1;
	}//if( item->attr[IATTR_DURATION] > MAX_MONEY ) //100���� �Ѿ��
	else//100���� �ȳѳ�.. ���� �ʿ䰡 ����
	{
		return 2;
	}
	return 0;
}

////////////////////// �� ������ �� ��ġ�� ������ �����ϴ� ��? ////////////////////
bool ExistItem( short int cn, ItemAttr item, POS pos )		// ���� �����ϴ� ��?
{
	CHARLIST *ch = &connections[cn].chrlst;
	if( !ch ) return false;

	ItemAttr *target = GetItemByPOS( cn, pos );
	if( !target ) return false;
	
	int ret = memcmp( &item, target, sizeof( ItemAttr )  );
	if( ret == 0 ) return true;
	return false;
}

////////////////////////// ������ ���Կ� ���� movp //////////////////////
int CalcMovpByItem( CHARLIST *ch, int movp )
{
	return movp;
	int result = 0;
	int max = ch->Str * 100;
	if( ch->itemweight <= max ) return movp;

	if( max )
	{
		float rate = ( ch->itemweight - max ) / ((float)max) * 100.0f;
		int move_down = (int) ((rate*2)/100.0f*movp );
		result = movp - move_down;
	}
	if( result < 0 ) result = 0;
	return result;
}

void CheckEquipItem( CHARLIST *ch )		// �������� �̵�������
{
	for( int c=0; c<8; c++ )
	{
		ItemAttr *item = &ch->equip[c];
		if( item->item_no )
		{
			CItem *t = ItemUnit(item->item_no);
			if( !t ) 
			{
				SendItemEventLog( item, ch->GetServerID(), 0, SILT_DELETE_BY_ATTR, 1 ); //YGI acer
				memset( item, 0, sizeof( ItemAttr ) );
				continue;
			}
			if( !t->GetItemImage() || !t->GetObjectNumber() ) 
			{
				SendItemEventLog( item, ch->GetServerID(), 0, SILT_DELETE_BY_ATTR, 1 ); //YGI acer
				memset( item, 0, sizeof( ItemAttr ) );
				continue;
			}
			t_chr_status_info cstatus;
			POS source = {0, };
			POS dest;
			SetItemPos( EQUIP, c, &dest );
			if( t->is_equipable( ch->GetServerID(), &cstatus, source, dest ) == NOT )
			{
				MoveEmptyInv( item, ch );
				SendServerEachItem( &dest, item, ch->GetServerID()); // ������ ����� Ŭ���̾�Ʈ�� �˸���.
				t->ReleaseItem( ch );
				continue;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
//		������ ������ ���� hp, mana ����
void ChangePlusHp( CHARLIST *ch, int hp_max_plus, int mp_max_plus )
{
	ch->HpMax	+=	hp_max_plus;
	ch->ManaMax	+=	mp_max_plus;
}

int CItem_Weapon::PlusHp(CHARLIST *ch )
{
	if( ch->Spell )	ChangePlusHp( ch, Change_Life_max, Change_Divine_Max );
	else			ChangePlusHp( ch, Change_Life_max, Change_mana_max);
	return 1;
}

int CItem_Armor::PlusHp(CHARLIST *ch)
{
	if( ch->Spell )	ChangePlusHp( ch, Change_Life_max, Change_Divine_Max );
	else			ChangePlusHp( ch, Change_Life_max, Change_mana_max);
	return 1;
}

int CItem_Accessory::PlusHp(CHARLIST *ch)
{
	if( ch->Spell )	ChangePlusHp( ch, Change_Life_max, Change_Divine_Max );
	else			ChangePlusHp( ch, Change_Life_max, Change_mana_max);
	return 1;
}

int CItem_Etc::PlusHp(CHARLIST *ch)
{
	if( ch->Spell )	ChangePlusHp( ch, Change_Life_max, Change_Divine_Max );
	else			ChangePlusHp( ch, Change_Life_max, Change_mana_max);
	return 1;
}
////////////////////////////////////////////////////////////////////////

// Ư�� �����۰� ���� ���� �������� ������ ���� ����
int CheckInventory( CHARLIST *ch, int item, int count )
{
	int ct = 0;
	for( int a=0; a<3; a++ )
	{	for( int b=0; b<3; b++ )
		{	for( int c=0; c<8; c++ )
			{
				if(ch->inv[a][b][c].item_no == item ) 
				{
					ct++;
				}
			}
		}	
	}

	return ct - count;
}

// Ư�� �������� ���ϴ� ������ŭ �����.
int SendDeleteMuchItemQuantity( CHARLIST *ch, int item, int count )
{
	if( !count ) return 1;
	int ct = 0;

	
	for( int a=0; a<3; a++ )
		for( int b=0; b<3; b++ )
			for( int c=0; c<8; c++ )
			{
				ItemAttr *lpItem = &ch->inv[a][b][c];
				if( lpItem->item_no == item ) 
				{
					if( lpItem->attr[IATTR_MUCH] > count ) 
					{
						lpItem->attr[IATTR_MUCH] -= count;
						POS pos;
						SetItemPos( INV, a, b, c, &pos );
						// ���� ���� ������ �����ش�.
						SendChangeDurationByKein( &pos, lpItem->attr[IATTR_MUCH], ch->GetServerID());
						return 1;
					}
					else if( lpItem->attr[IATTR_MUCH] == count )
					{
						POS pos;
						SetItemPos( INV, a, b, c, &pos );
						// 020428 YGI acer
						SendDeleteItem( lpItem, &pos, ch );
						return 1;
					}
					else
					{
						count -= lpItem->attr[IATTR_MUCH];
						POS pos;
						SetItemPos( INV, a, b, c, &pos );
						// 020428 YGI acer
						SendDeleteItem( lpItem, &pos, ch );
						continue;
					}
				}
			}

	return 0;
}

// Ư�� �������� ���ϴ� ������ŭ �����.
int SendDeleteItemQuantity( CHARLIST *ch, int item, int count )
{
	if( !count ) return 1;
	int ct = 0;
	for( int a=0; a<3; a++ )
		for( int b=0; b<3; b++ )
			for( int c=0; c<8; c++ )
			{
				if(ch->inv[a][b][c].item_no == item )
				{
					POS pos;
					SetItemPos( INV, a, b, c, &pos );
					// 020428 YGI acer
					SendItemEventLog( &ch->inv[a][b][c], ch->GetServerID(), -2, SILT_NEED_ITEM, 6 ); //YGI acer
					SendDeleteItem( &ch->inv[a][b][c], &pos, ch );
					ct++;
					if( ct >= count ) return 1;
				}
			}

	return 0;
}

int EquipItem( CHARLIST *ch )//020303 lsw 
{
	for( int i=0; i<8; i++ )
	{
		if( ch->equip[i].item_no )
		{
			CItem *t = ItemUnit( ch->equip[i] );
			if( !t ) continue;
			switch (t->GetWearAble())
			{
				case	WEAR_ANYTHING	:
				case	WEAR_RIGHT_HAND	:
				case	WEAR_LEFT_HAND	:
				case	WEAR_HEAD		:
				case	WEAR_BODY		:
				case	WEAR_NECK		:
				case	WEAR_SHOES		:
				case	WEAR_UNIQUE		:
				case	WEAR_TWO_HAND	:
				{
					t->EquipItem( ch );
				}
				break;

				case	WEAR_BELT		:
				case	WEAR_ONLY_INVEN	:
				default:
				{
				}
				break;
			}

		}
	}
	ResetAbility(ch);
	return 1;
}

int ReleaseItem( CHARLIST *ch )
{
	for( int i=0; i<8; i++ )
	{
		if( ch->equip[i].item_no )
		{
			CItem *t = ItemUnit( ch->equip[i] );
			if( !t ) continue;
			t->ReleaseItem( ch );
		}
	}
//	ch->ResetAbility();
	ResetAbility(ch);//020215 lsw
	return 1;
}

int	DeleteINVItem(CHARLIST*	pChar,int nItemNumber,int nDelCount)
{
	int nDeletedCount = 0;
	for(int i = 0;i < 3;++i)
		for(int j = 0;j < 3;++j)
			for(int k = 0;k < 8;++k)
			{
				if(pChar->inv[i][j][k].item_no == nItemNumber)
				{
					POS pos;
					if(nDelCount == 0)
					{
						SetItemPos( INV, i, j, k, &pos );
						SendItemEventLog( &pChar->inv[i][j][k], pChar->GetServerID(), -2, SILT_NEED_ITEM, 6 );
						SendDeleteItem( &pChar->inv[i][j][k], &pos, pChar );
						++nDeletedCount;
					}
					else
					{
						if(nDelCount > nDeletedCount)
						{
							SetItemPos( INV, i, j, k, &pos );
							SendItemEventLog( &pChar->inv[i][j][k], pChar->GetServerID(), -2, SILT_NEED_ITEM, 6 );
							SendDeleteItem( &pChar->inv[i][j][k], &pos, pChar );
							++nDeletedCount;
						}
						else
						{
							continue;
						}
					}
				}
			}

	return nDeletedCount;
}

void CheckMallItemTime( short int cn )
{
	CHARLIST *ch = CheckServerId(cn);
	if( !ch ) {return;}

	POS pos = {0,};

	int a=0, b=0, c=0;
	for( a=0; a<3; a++ )
	for( b=0; b<3; b++ )
	for( c=0; c<8; c++ )
	{
		ItemAttr *pItem = &ch->inv[a][b][c];
		CItem *t = ItemUnit(pItem->item_no);
		if(pItem->item_no && pItem->attr[IATTR_MALL_TIMED] > 0 && t->GetItemKind() != IK_TREASURE_MAP)
		{
			if (pItem->attr[IATTR_ATTR] > g_curr_time)
			{
				pItem->attr[IATTR_MALL_TIMED] = pItem->attr[IATTR_ATTR] - g_curr_time;
			}
			SetItemPos( INV, a, b, c, &pos );
			SendServerEachItem( &pos, pItem, cn );
		}
	}
	
	for( a=0; a<ITEM_EQUIP_MAX; a++ )
	{
		ItemAttr *pItem = &ch->equip[a];
		CItem *t = ItemUnit(pItem->item_no);
		if(pItem->item_no && pItem->attr[IATTR_MALL_TIMED] > 0 && t->GetItemKind() != IK_TREASURE_MAP)
		{
			if (pItem->attr[IATTR_ATTR] > g_curr_time)
			{
				pItem->attr[IATTR_MALL_TIMED] = pItem->attr[IATTR_ATTR] - g_curr_time;
			}
			SetItemPos( EQUIP, a, &pos );
			SendServerEachItem( &pos, pItem, cn );
		}
	}
	
	for( a=0; a<ITEM_QUICK_MAX ; a++ )
	{
		ItemAttr *pItem = &ch->quick[a];
		CItem *t = ItemUnit(pItem->item_no);
		if(pItem->item_no && pItem->attr[IATTR_MALL_TIMED] > 0 && t->GetItemKind() != IK_TREASURE_MAP)
		{
			if (pItem->attr[IATTR_ATTR] > g_curr_time)
			{
				pItem->attr[IATTR_MALL_TIMED] = pItem->attr[IATTR_ATTR] - g_curr_time;
			}
			SetItemPos( QUICK, a, &pos );
			SendServerEachItem( &pos, pItem, cn );
		}
	}

	for( a=0; a<5; a++ )
	for( b=0; b<3; b++ )
	for( c=0; c<6; c++ )
	{
		ItemAttr *pItem = &ch->bank[a][b][c];
		CItem *t = ItemUnit(pItem->item_no);
		if(pItem->item_no && pItem->attr[IATTR_MALL_TIMED] > 0 && t->GetItemKind() != IK_TREASURE_MAP)
		{
			if (pItem->attr[IATTR_ATTR] > g_curr_time)
			{
				pItem->attr[IATTR_MALL_TIMED] = pItem->attr[IATTR_ATTR] - g_curr_time;
			}
			SetItemPos( BANK, a, b, c, &pos );
			SendServerEachItem( &pos, pItem, cn );
		}
	}

	return;
}

bool IsNoExchange(ItemAttr* item)
{
	CItem* t = ItemUnit(item->item_no);
	if (t->GetItemKind() == IK_NOEXCHANGE || 
		t->GetItemKind() != IK_TREASURE_MAP &&
		//item->attr[IATTR_ATTR] != 0)
		item->attr[IATTR_MALL_TIMED] != 0)		
	{
		return true;
	}
	return false;
}