#ifndef __NATION_H__
#define __NATION_H__

#define NM_ADD			1		// ���� �����ش�.
#define NM_SUBTRACT		2		// ������ ����.

struct tagNationInfo
{
//	char	name[30];			// ���� �̸�
	int		main_map_port;		// ����Ÿ�� ������ �ʼ���
	char	king_name[20];		// ���̸�
	double	nation_money;		// ����
	int		king_support;		// �� ������
	int		visa_va;			// ���̼����� �� ���� ��ȣ
	int		visa_zy;
	int		visa_ill;

	int		visa_pri_va;		// ���̼����� �� ���� ����
	int		visa_pri_zy;
	int		visa_pri_ill;

	int		visa_mer_va;		// ���ο� ���� ��ȣ( ���̼��� �� )
	int		visa_mer_zy;
	int		visa_mer_ill;

	int		visa_mer_pri_va;	// ���ο��� �� ���� ����( ���̼��� �� )
	int		visa_mer_pri_zy;
	int		visa_mer_pri_ill;

	int		visit_limit_va;		// ���̼����� �湮�ڼ� �ִ�
	int		visit_limit_zy;
	int		visit_limit_ill;

	int		friend_va;
	int		friend_zy;
	int		friend_ill;

	int		cond_va;			// 1: ����,		5: �⺻,	9: ����
	int		cond_zy;
	int		cond_ill;

	int		dec_anti_va;		// ������ ���밨�� 1 ���̱� ���� ��
	int		dec_anti_zy;
	int		dec_anti_ill;

	int		dec_max_va;			// ������ ���ϼ� �ִ� �Ϸ� ���� �ִ뷮
	int		dec_max_zy;
	int		dec_max_ill;

	int		nation_item[20];		// ������ ������ �ִ� 20������ �������� �� -> �������� ������ ����
	
	int		prize_money_va;			// ħ���� ó�� ���� ��
	int		prize_money_zy;
	int		prize_money_ill;

	int		prize_item_va;			// ħ���� ó�ܽ� ���� ������
	int		prize_item_zy;
	int		prize_item_ill;
};

extern tagNationInfo NationInfo[MAX_NATION];
extern int	 g_MapPort;		// 010522 YGI
extern void CheckMainMap();
extern void SendNationMoney( int type, int nation, double moneny );
extern void SaveNationInfo( int nation );		// ��� ���� �����Ѵ�.
extern int LoadNationInfoOfMainMap( int nation );

#endif