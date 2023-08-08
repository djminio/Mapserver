#include "defaultheader.h"
#include "Citem.h"
#ifndef __teambattle_h__
#define __teambattle_h__

extern void Script( int num );
extern void CalcWinLoseScore( WINLOSEPOINT &win_lose, int wintype );
extern void SendFightMapChat( short int cn, t_packet *packet );		// ��ü���� ������.
extern void SendFightMapChatMyTeam( short int cn, t_packet *packet );
extern void SendGamblingResult(CHARLIST* pGambler, int nPayment, DWORD dwMoney);

//////////////////////////////////////////////////////////////////
// �׺� ������
struct k_game_item
{
	int count;
	int *lpItem;

	k_game_item()
	{
		count = 0;
		lpItem = 0;
	}
	~k_game_item() { SAFE_DELETE_ARRAY(lpItem); }
};

class CGambleItem
{
private:
	k_game_item m_GambleItem[MAX_GAMBLE_ITEM_KIND][MAX_GAMBLE_ITEM_TYPE]; // CSD-030520

public :
	CGambleItem()
	{
	}

	~CGambleItem()
	{	//< CSD-030517
		for (int i = 0; i < MAX_GAMBLE_ITEM_KIND; ++i)
		{	
			for (int j = 0; j < MAX_GAMBLE_ITEM_TYPE; ++j)
			{
				Release(i, j);
			}
		}		
	}	//> CSD-030517

public:
	int SetSize( int house, int type, int count );
	int Release( int houes, int type );

public:
	void SetItem( int house, int type, int pos, int item_no )
	{
		m_GambleItem[house][type].lpItem[pos] = item_no;
	}

	int GetItem(int house, int type, int pos)
	{	//< CSD-040223
		return m_GambleItem[house][type].lpItem[pos];
	}	//> CSD-040223
	
	int Rand(int house, int type)
	{	//< CSD-040223
		if (m_GambleItem[house][type].count)
		{
			return rand()%m_GambleItem[house][type].count;
		}

		return -1;
	}	//> CSD-040223

	int GetRandItem(int house, int type)
	{	//< CSD-040223
		const int nRandom = Rand(house, type);
		return (nRandom == -1) ? -1:GetItem(house, type, nRandom);
	}	//> CSD-040223
};
extern CGambleItem g_GambleItem;
//////////////////////////////////////////////////////////////////
// >> 011019 ygi
class CTodayGambleItem
{
public :
	ItemAttr m_TodayItem;
public :
	CTodayGambleItem()
	{
		DeleteTodyaItem();
	}
	int DeleteTodyaItem()
	{
		memset( &m_TodayItem, 0, sizeof( ItemAttr ) );
		return 1;
	}
	ItemAttr GetTodayItem()
	{
		return m_TodayItem;
	}
	int SetTodayItem( ItemAttr *item )
	{
		m_TodayItem = *item;
		return 1;
	}
	int CreateTodayItem();
};

extern CTodayGambleItem g_TodayGambleItem;
extern int RefreshTodayItem();
extern k_nation_item_data g_nation_item;	// ���� ��� ������

// �� ������ ������� ���� �ߴ°�?

const int  STONE_SCORE_FIRST=	IA2_NOTMOVE;		// 1: �ʱ� �϶� 
const int  STONE_SCORE_2	=	IA2_OPENED;		//	2 �ڸ�
const int  STONE_SCORE_1	=	IA2_BROKEN;		// ù°�ڸ�

class CColossusStone
{
public :
	ITEMLIST * stone;
	CColossusStone *next;
public : 
	CColossusStone() { next = 0; }
	~CColossusStone() { SAFE_DELETE(next); }
};

class CColossusStoneMgr
{
public :
	CColossusStone	m_StoneList;
	DWORD m_GotStoneTime;		// ���� ���� ������ �ð�
	int m_GotStoneTeam;			// ���� ���� ������ ��
	int m_MaxStone;


public:
	CColossusStoneMgr()
	{
		m_MaxStone = 0;
		SetWinCondition();
	}
	int SetWinCondition( DWORD time = 0, int team = 0 )
	{
		if( !time || !m_GotStoneTime || team != m_GotStoneTime )
		{
			m_GotStoneTime = time;
			m_GotStoneTeam = team;
		}
		return 1;
	}
	bool IsEnd()
	{
		if( !m_GotStoneTime ) return false;
		if( g_curr_time - m_GotStoneTime > 30 ) return true;
		else return false;
	}
	~CColossusStoneMgr()
	{
	}

	int AddStone( int id );
	ITEMLIST *GetList( int count );
	void GetTeamCount( int team[4] );
	void SetStoneByTeam( int id, int team );		// ������ ������ �ǵ������;
	void SetStoneFirst();		// �ʱ� ����	
	int GetMaxStone();
};

extern void SetStoneByTeam( ITEMLIST *item, int team );
extern int GetTeamByStone( DWORD attr );
extern CColossusStoneMgr g_ColossusStone;
extern int GetFightTeamNumber( CHARLIST *ch );		// 0, 1, 2, 3


class CGuildHouseUnit
{
public :
	int id;
	int level;				// ���
	int nation;				// �����ϴ� ��ġ ����
	int blue;				// ���ſ� �ʿ��� �Ķ� �ñ׳� ��
	int red;				// ���ſ� �ʿ��� ���� �ñ׳� ��
	char map_name[20];		// ��ġ ��
	int x;					// ��ġ ��ǥ ( �Ա� ��ǥ )
	int y;
	int guild_code;			// ���� ���
	int year;
	int month;
	int day;
	int	event_no;		// �ش� �ʿ� ��� ���� ���� ��ȣ

public : 
	CGuildHouseUnit() { clear(); }
	int GoToHouse( short int cn );		// �ٸ� ���̸� ���̵��� �����ϰ� ���� ���� ��쿣 ���̵� ��ƾ�� �����Ų��.
	void clear() { id = 0; }
	
};

//#define MAX_GUILD_HOUSE	100
class CGuildHouse
{
public :
	int m_Max;
	CGuildHouseUnit	m_aGuildHouse[MAX_GUILD_HOUSE];
public :
	CGuildHouse() { m_Max = 0; }
	CGuildHouseUnit *GetPointByEventNo( char *map_name, int event_no );	// �ش� �ʰ� �̺�Ʈ ��ȣ�� �������� Ŭ������ ����
	int GoToHouse( CHARLIST *ch );	// �ش� �������Ʒ� �̵�
	CGuildHouseUnit *GetPointByGuildCode( int guild_code );		// ��� �ڵ�� �������� Ŭ������ ����
	int IsMyGuildHouse( CHARLIST *ch, int event_no );
	int SetMax( int max ) { if( max >= m_Max ) m_Max = max+1; return 1; }
	int clear();
	CGuildHouseUnit	*GetHouseByGuildCode( int guild_code );
	CGuildHouseUnit	*GetHouseByIndex( int index )
	{ 
		return &m_aGuildHouse[index]; 
	}
};

extern CGuildHouse	g_GuildHouse;



//< soto-030324
#define		MAX_GUARDIAN_GUILD	3

// ��Ű�� ���. // ������ �ٲ�� ���� 1����常 �ٲ��.
class CGuardianGuild
{
private:
	int m_nGuildCount; // ���� ��Ű�� ����� ���� ��Ÿ����.
	int	m_n1stGuildCode; // 1���� ��� �ڵ带 �˾Ƴ���.
	vector<int>m_vtGuildList;
	
	// �����ڵ带 �˻����� �ʰ� ��� �ڵ带 ����Ѵ�.(�ߺ��� ������ �ִ�)
	int	ForcingAddGuild(int nGuildCode)
	{		
		m_vtGuildList.push_back(nGuildCode);
		return ++m_nGuildCount;
	}
public:
	CGuardianGuild() //������
	{ 
		m_vtGuildList.reserve(MAX_GUARDIAN_GUILD);
		m_nGuildCount = 0;
		m_n1stGuildCode = -1; 

	} // ������.
	
	bool IsGuardianGuild(int nGuildCode)// �� ����ڵ尡 ��Ű�� ����� �ڵ��̳�?
	{
		for(int i = 0;i < m_nGuildCount;i++)
		{
			if(m_vtGuildList[i] == nGuildCode) return true;
		}
		return false;
	}	
	
	int AddGuild(int nGuildCode)//�ߺ����� �ʰ� �߰� ��Ų��.
	{
		if(!IsGuardianGuild(nGuildCode))
		{
			m_nGuildCount = ForcingAddGuild(nGuildCode);
		}

		return m_nGuildCount;
	}
	
	int FirstGuild()//1�� ����ڵ带 �˾Ƴ���.// �������� -1�� ����.
	{
		if(!m_nGuildCount)return -1;

		return m_n1stGuildCode;
	}

	int GetCount()
	{
		if(m_vtGuildList.empty()){return 0;}
		const int nCount = m_vtGuildList.size();
		return __min(nCount,MAX_GUARDIAN);
	}

	int	GetGuildCode(int nIndex)
	{
		if(nIndex < m_nGuildCount)
			return m_vtGuildList[nIndex];
		return -1;
	}

	// �ϵ��� ���� �ϳ��� �ƴ϶�.. ���������� �ϳ��� �ٲ����. ��� 3����.
	bool	Is1StGuild(int nGuildCode){ return IsGuardianGuild(nGuildCode); }// soto-030324

	void Set1stGuild(int nGuildCode)//1���� ��带 ����Ѵ�.
	{
		if(!m_nGuildCount)//���� ��尡 �ƹ��� ��� �Ǿ� ���� ������.
		{
			ForcingAddGuild(nGuildCode);
			m_n1stGuildCode = nGuildCode;
		}
		else // �ϳ� �̻��� ��尡 ��ϵǾ� ������.
		{
			if(IsGuardianGuild(nGuildCode)) // ����Ʈ�� ��ϵ� �ڵ��ΰ�?
			{
				m_n1stGuildCode = nGuildCode;
			}
			else
			{
				ForcingAddGuild(nGuildCode);
				m_n1stGuildCode = nGuildCode;
			}
		}
	}

	void ClearGuild()
	{ 
		m_vtGuildList.clear();
		m_n1stGuildCode = -1;
		m_nGuildCount = 0;
	}
};

extern CGuardianGuild	g_CGuardianGuild; // ��Ű�� ��� ���� ���� Ŭ����. // soto
//> soto-030324
#endif
