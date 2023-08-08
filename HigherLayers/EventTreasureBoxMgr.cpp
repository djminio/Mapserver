// EventTreasureBoxMgr.cpp: implementation of the CEventTreasureBoxMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "EventTreasureBoxMgr.h"
#include "CItem.h"
#include "ItemMgr.h"

extern ItemAttr GenerateItem(const int iItemFullNo);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CEventTreasureBoxMgr* CEventTreasureBoxMgr::m_pClass = NULL;
bool CEventTreasureBoxMgr::m_bEvent = true; // m_bEvent�� true������.������ų���ִ�.

CEventTreasureBoxMgr::CEventTreasureBoxMgr()
{
	
}

CEventTreasureBoxMgr::~CEventTreasureBoxMgr()
{
	this->m_vtMake_DropItem_Info_List.clear();
}

bool CEventTreasureBoxMgr::LoadTable(HDBC hDragonDB)
{
	if(NULL == hDragonDB)
	{
		MyLog(0,"CEventTreasureBoxMgr::LoadTable Error : HBDC is NULL!!");
		return false;
	}

	HSTMT		hStmt = NULL;
	RETCODE		retCode;
	SDWORD		cbValue;
	char		szQuerry[512];

	sprintf_s(szQuerry, sizeof(szQuerry), "SELECT * FROM Event_Treasure_Item");
	SQLAllocStmt(hDragonDB, &hStmt);
	retCode = SQLExecDirect(hStmt, (UCHAR *)szQuerry, SQL_NTS);

	if (!SQLOK(retCode))
	{
		MyLog(0,"CEventTreasureBoxMgr::LoadTable Error : Query Error!!");
		SQLFreeStmt(hStmt, SQL_DROP);
		return false;
	}
	
	retCode = SQLFetch(hStmt);
	if (!SQLOK(retCode))
	{
		MyLog(0,"CEventTreasureBoxMgr::LoadTable Error : No Data!!!!");
		SQLFreeStmt(hStmt, SQL_DROP);
		return false;
	}

	m_vtMake_DropItem_Info_List.clear();

	while(SQLOK(retCode))
	{
		int nCt = 2;
		DROPITEM_INFO	DropItemInfo;
		memset(&DropItemInfo,0,sizeof(DROPITEM_INFO));
		SQLGetData(hStmt,nCt++,SQL_C_LONG,&DropItemInfo.nSadOnyx,0,&cbValue);
		SQLGetData(hStmt,nCt++,SQL_C_LONG,&DropItemInfo.nLeafOfBessed,0,&cbValue);
		SQLGetData(hStmt,nCt++,SQL_C_LONG,&DropItemInfo.nCoins,0,&cbValue);
		SQLGetData(hStmt,nCt++,SQL_C_LONG,&DropItemInfo.nGoldCoin,0,&cbValue);

		SQLGetData(hStmt,nCt++,SQL_C_LONG,&DropItemInfo.nGrade_Min,0,&cbValue);
		SQLGetData(hStmt,nCt++,SQL_C_LONG,&DropItemInfo.nGrade_Max,0,&cbValue);

		int i;
		for(i = 0; i < 6;i++)
		{
			SQLGetData(hStmt,nCt++,SQL_C_LONG,&DropItemInfo.stItem[i].nItem,0,&cbValue);
			SQLGetData(hStmt,nCt++,SQL_C_LONG,&DropItemInfo.stItem[i].nItem_Rate,0,&cbValue);
		}

		for(i = 0;i < 4;i++)
		{
			SQLGetData(hStmt,nCt++,SQL_C_LONG,&DropItemInfo.stRareItem[i].nItem,0,&cbValue);
			SQLGetData(hStmt,nCt++,SQL_C_LONG,&DropItemInfo.stRareItem[i].nItem_Rate,0,&cbValue);			
		}

		m_vtMake_DropItem_Info_List.push_back(DropItemInfo);
		retCode = SQLFetch(hStmt);
	}

	SQLFreeStmt(hStmt, SQL_DROP);

	return true;
}

bool CEventTreasureBoxMgr::IsTreasureBox(const int nItemKind)
{
	if(ITEM_TREASURE_BOX_KIND == nItemKind)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CEventTreasureBoxMgr::CreatTreasure(const int nBoxItemId , int cn)
{
	const int nItemLevel = ItemList[nBoxItemId].attr[4]; //�ڽ���  ������ ��Ÿ����// 1~4
	if(nItemLevel > m_vtMake_DropItem_Info_List.size() || nItemLevel <= 0)
	{
		return 0;
	}
	const int nSardonyxNum	= m_vtMake_DropItem_Info_List[nItemLevel-1].nSadOnyx;
	const int nLeafOfBessed	= m_vtMake_DropItem_Info_List[nItemLevel-1].nLeafOfBessed;
	const int nCoins		= m_vtMake_DropItem_Info_List[nItemLevel-1].nCoins;
	const int nGoldCoin		= m_vtMake_DropItem_Info_List[nItemLevel-1].nGoldCoin;
	const int nRareGradeMin	= m_vtMake_DropItem_Info_List[nItemLevel-1].nGrade_Min;
	const int nRareGradeMax	= m_vtMake_DropItem_Info_List[nItemLevel-1].nGrade_Max;

	int nItemCreateCount = 0;

	CreateItemRandomPosition(SADONIX_NO,0,nSardonyxNum,ItemList[nBoxItemId].x,ItemList[nBoxItemId].y,300);
	nItemCreateCount += nSardonyxNum;
	CreateItemRandomPosition(BLESSLEAF_NO,0,nLeafOfBessed,ItemList[nBoxItemId].x,ItemList[nBoxItemId].y,300);
	nItemCreateCount += nLeafOfBessed;
	CreateItemRandomPosition(10254,0,nGoldCoin,ItemList[nBoxItemId].x,ItemList[nBoxItemId].y,300);
	nItemCreateCount += nGoldCoin;

//Coin�� ���� ��� �Ͽ��� �Ѵ�. 100���� �Ѱ��̴�.
	{
		if(nCoins > 1000000)
		{
			if(LocalMgr.IsChangeMoney())
			{
				CreateItemRandomPosition(IN_NEW_COINS,nCoins,1,ItemList[nBoxItemId].x,ItemList[nBoxItemId].y,300);
			}
			else
			{
				CreateItemRandomPosition(IN_COINS,nCoins,1,ItemList[nBoxItemId].x,ItemList[nBoxItemId].y,300);
			}
			nItemCreateCount++ ;
		}
		else
		{
			const int nLimitCoins = 1000000;
			const int count = (int)(nCoins/nLimitCoins);
			const int	mod	  = nCoins%nLimitCoins;			
			
			if(LocalMgr.IsChangeMoney())
			{			
				CreateItemRandomPosition(IN_NEW_COINS,nLimitCoins,count,ItemList[nBoxItemId].x,ItemList[nBoxItemId].y,300);
				nItemCreateCount += count;
				if(mod)
				{
					CreateItemRandomPosition(IN_NEW_COINS,mod,1,ItemList[nBoxItemId].x,ItemList[nBoxItemId].y,300);
					nItemCreateCount++;
				}
					
			}
			else
			{
				CreateItemRandomPosition(IN_COINS,nLimitCoins,count,ItemList[nBoxItemId].x,ItemList[nBoxItemId].y,300);
				nItemCreateCount += count;
				if(mod)
				{
					CreateItemRandomPosition(IN_COINS,mod,1,ItemList[nBoxItemId].x,ItemList[nBoxItemId].y,300);
					nItemCreateCount++;
				}
			}
		}
	}

//Coins ��.
	int i;
	for(i = 0;i < 6;i++) //�ʵ��� ��� ������.
	{
		const int nNumber = m_vtMake_DropItem_Info_List[nItemLevel-1].stItem[i].nItem;
		const int nRate = m_vtMake_DropItem_Info_List[nItemLevel-1].stItem[i].nItem_Rate;

		if(nNumber)
		{
			if(nRate > 0)
			{
				if(nRate > rand()%100)
				{
					CreateItemRandomPosition(nNumber,0,1,ItemList[nBoxItemId].x,ItemList[nBoxItemId].y,300);
					nItemCreateCount++;
				}
			}
			else continue;
		}
		else break;//������ �ѹ��� ������..�� ���� �ʵ��� ��־����۵� ����.
	}

	
	for( i = 0; i < 4;i++)//�ʵ��� ���� ������.
	{
		const int nNumber = m_vtMake_DropItem_Info_List[nItemLevel-1].stRareItem[i].nItem;
		const int nRate = m_vtMake_DropItem_Info_List[nItemLevel-1].stRareItem[i].nItem_Rate;

		if(nNumber)
		{
			if(nRate > 0)
			{
				if(nRate > rand()%100)
				{
					CreateRareItemRandomPosition(nNumber,1,nRareGradeMin,nRareGradeMax,ItemList[nBoxItemId].x,ItemList[nBoxItemId].y,300);
					nItemCreateCount++;
				}
			}
			else continue;
		}
		else break;//������ �ѹ��� ������..�� ���� �ʵ��� ��������۵� ����.		
	}

	t_packet packet;
	packet.h.header.type = CMD_SEND_EFFECT;
	packet.u.kein.send_effect.effect_num = 585;
	packet.u.kein.send_effect.target_id = cn;
	packet.u.kein.send_effect.x = ItemList[nBoxItemId].x;
	packet.u.kein.send_effect.y = ItemList[nBoxItemId].y;
	packet.h.header.size = sizeof( k_send_effect );
	
	QueuePacket(connections, cn, &packet, 1);
	CastMe2Other( cn, &packet );


	ItemList[nBoxItemId].bAlive = REMOVE_;
	SetArea(REMOVE_ITEM_AREA, nBoxItemId);


	return	nItemCreateCount;
}

//����������� ���� ��ġ�� �����.
void CEventTreasureBoxMgr::CreateItemRandomPosition(const int nItemNumber, const int nDuration, const int nCreateCount,const int Xpos,const int Ypos, const int nRange)
{
	for(int i = 0; i < nCreateCount;i++)
	{
		int nRandRange = (rand()%nRange) - (nRange/2);
		int nRandX = Xpos + nRandRange;
		nRandRange = (rand()%nRange)  - (nRange/2);
		int nRandY = Ypos + nRandRange;
		ItemAttr	stItem;		

		//Item�� �����.
		if(nDuration > 0)
		{
			stItem = GenerateItem(nItemNumber,IATTR_MUCH,nDuration);
		}
		else
		{
			stItem = GenerateItem(nItemNumber);
		}

		//������ ���� �߸���.
		::DropItem(nRandX,nRandY,&stItem);
	}
}

void CEventTreasureBoxMgr::CreateRareItemRandomPosition(const int nItemNumber, const int nCreateCount,const int nGradeMin,const int nGradeMax,const int Xpos,const int Ypos, const int nRange)
{
	RareMain r;

	for(int i = 0;i < nCreateCount; i++)
	{
		int nRandRange = (rand()%nRange)  - (nRange/2);
		int nRandX = Xpos + nRandRange;
		nRandRange = (rand()%nRange)  - (nRange/2);
		int nRandY = Ypos + nRandRange;
		
		ItemAttr stRareItem = ItemMgr.GiveRareItem(nItemNumber,0,RARE_ABLE,1,nGradeMin,nGradeMax,r,0);

		::DropItem(nRandX,nRandY,&stRareItem);
	}
}
