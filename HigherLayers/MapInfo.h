// MapInfo.h: interface for the CMapInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPINFO_H__6A59C12B_1C45_495B_958A_D5A51EFE0646__INCLUDED_)
#define AFX_MAPINFO_H__6A59C12B_1C45_495B_958A_D5A51EFE0646__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_MAP_		200		// �����ϰ� �Ȱ��ƾ� �Ѵ�. // 031013 kyo 100 -> 200���� 

// map_move_type

#define MMT_FAIL		-1		// ���� ���̴�.
#define MMT_NORMAL		0		// �̵��ϴµ� �ƹ��� ������ ����.
#define MMT_NOT_MOVE	1		// �̵� ���ϰ� ���Ƶ� ���̴�.

#pragma pack(push,1)
typedef struct MAPINFO
{
	char mapfile[30];
	char mapname[30];
	char cPosType; // CSD-030509
	int  nSaveX;   // CSD-030509
	int  nSaveY;   // CSD-030509
	char daylightcontrol;	// ������ ������ 0     // ������  ( �Ʒ��Ͱ� ���� ���� ) 
	char rain;		//  1 :�̸� �� ���°��̴�.	0 : �� ���� �ʴ� �������� ���̴�. 
	char nation;	//  �����ڵ�. 
	char forrookie;//0 -> PK �ǰ� HPȸ�� ���� 1-> PK�ȵ� 2->PK �ȵǰ� HP ���� ȸ�� 3->PK �ǰ� HP ���� ȸ��
	int  ghostguide3x, ghostguide3y;	// nation code 3
	int  ghostguide4x, ghostguide4y;	// nation code 4..

	int	 port;
	int  group;//020420 lsw
	int  Class;//021113 lsw
	int  LvMin;//020420 lsw
	int  LvMax;//021113 lsw
	int  nDisableMagicType; // CSD-030516

	int	 m_MoveType;//GM�� ���� �ϴ� ����Ÿ, ���̺��� �̷� �ʵ尡 ����

	MAPINFO()
	{
		cPosType = 0; // CSD-030509
		nSaveX= 0;    // CSD-030509
		nSaveY= 0;    // CSD-030509
		daylightcontrol= 0;	// ������ ������ 0     // ������  ( �Ʒ��Ͱ� ���� ���� ) 
		rain= 0;		//  1 :�̸� �� ���°��̴�.	0 : �� ���� �ʴ� �������� ���̴�. 
		nation= 0;	//  �����ڵ�. 
		forrookie= 0;
		ghostguide3x= 0, ghostguide3y= 0;	// nation code 3
		ghostguide4x= 0, ghostguide4y= 0;	// nation code 4..

		port = 0;
		group= 0;//020420 lsw
		Class= 0;//021113 lsw
		LvMin= 0;//020420 lsw
		LvMax= 0;//021113 lsw
		nDisableMagicType = 0; // CSD-030516

		m_MoveType = 0;
	}
}t_MapInfo,*LPMAPINFO;
#pragma pack(pop,1)

extern t_MapInfo MapInfo[MAX_MAP_];
t_MapInfo* GetMapInfoByMapName(const char *szMapName); // CSD-030506
t_MapInfo* GetMapInfoByMapPort(int nPort);             // CSD-030506

#endif // !defined(AFX_MAPINFO_H__6A59C12B_1C45_495B_958A_D5A51EFE0646__INCLUDED_)
