//###########################################################
//#define CIA_DURATION		101		// ������ �Ӽ� �ٲٱ� 
//#define CIA_VIEW_CHANGE		102
//#define CIA_MUCH			103


// 020428 YGI acer
extern void CheckChracterTimeElapsed_Kein( CHARLIST *ch, int cn );
extern void killCharacter(CHARLIST *a, CHARLIST *d );
extern int GetItemView( int item_no, int is_man );
extern void HungryMuchAdd( CHARLIST *ch, const int iType);//020214 lsw
extern void SetItemPos(int type, POS* IP_set);
extern void SetItemPos(int type, int p, POS* IP_set);
extern void SetItemPos(int type, int p1, int p2, int p3, POS* IP_set);
extern DWORD GetMoneyByItem( CHARLIST *ch );
extern DWORD GetMoneyByOldItem( CHARLIST *ch );		// 010210 YGI
extern int DropItem( int x, int y, ItemAttr *item );
extern DWORD GetNewMoneyByItem( CHARLIST *ch );		// 010210 YGI

extern int SearchItemPosByNumber(ItemAttr *item, int &a, int &b, int &c, CHARLIST *ch);		// 010614 YGI
extern int SearchCoinItem( int &a, int &b, int &c, CHARLIST *ch );
extern ItemAttr *SearchItemOfInvByKind( int kind, CHARLIST *ch );
extern ItemAttr *SearchItemOfInvByKind( int kind, CHARLIST *ch, int &i, int &j, int &k );
extern int SubtractMoney( DWORD money, CHARLIST *ch );
extern int SubtractOldMoney( DWORD money, CHARLIST *ch );		// 010210 YGI
extern ItemAttr *SearchInv( CHARLIST *ch );
extern int IsEqualPosByPos( POS first, POS second );
extern void SendServerKillMon( short int cn );		// op_battle ���� ���
extern int GetTotalItemWeight( CHARLIST *ch );

extern void CheckItem( short int cn ); // �߸��� �������� ������ �ִ��� 
extern int CheckAutoDivideMoney( ItemAttr *item, const short int cn );		// 100000�� ���� ������ ó��
extern bool ExistItem( short int cn, ItemAttr item, POS pos );		// ���� �����ϴ� ��?
extern int CalcMovpByItem( CHARLIST *ch, int movp );
extern void CheckEquipItem( CHARLIST *ch );
extern void KillWho( CHARLIST *death_ch, CHARLIST *attack_ch );
extern int CheckInventory( CHARLIST *ch, int item, int count );
extern int SendDeleteItemQuantity( CHARLIST *ch, int item, int count );
extern int SendDeleteMuchItemQuantity( CHARLIST *ch, int item, int count );

extern int EquipItem( CHARLIST *ch );
extern int ReleaseItem( CHARLIST *ch );

extern int	DeleteINVItem(CHARLIST*	pChar,int nItemNumber,int nDelCount);


extern void CheckMallItemTime(short int cn);
extern bool IsNoExchange(ItemAttr* item);