//////////////////////////////////////////////////////////////
// �׺�
//////////////////////////////////////////////////////////////////////////////////////////////////
int g_rune_band[8] = { 2, -1, 1, -1, 2, -1, 1, -1 };		// �� ���ÿ� ���� ��� ����
int g_lv2band[10] = { 0,0,1,1,2,3,3,4,4,4 };	// ������ ���� ��尪 ����
int g_choice_house[10][5] =				// ���� ������ Ȯ��
{
	{ 800, 159, 10, 31, 0 },
	{ 540, 400, 20, 38, 3 },
	{ 700, 259, 10, 31, 0 },
	{ 460, 480, 20, 38, 3 },
	{ 200, 645, 50, 100, 5 },
	{ 100, 745, 60, 120, 8 },
	{ 150, 695, 50, 100, 5 },
	{ 100, 745, 60, 120, 8 },
	{ 150, 690, 55, 100, 5 },
	{ 80, 755, 65, 125, 9 },
};
int g_house_band_class[5][11][6] =		// ���� �����ϰ� �� �濡 ���� ��� �������� ���� Ȯ��
{
	{	{ 35, 40, 20, 5, 0, 0 } ,
		{ 25, 30, 20, 20, 5, 0 } , 
		{ 15, 25, 34, 20, 5, 0 },
		{ 5, 25, 25, 29, 15, 1 },
		{ 0, 20, 30, 34, 25, 1 },
		{ 0, 10, 30, 29, 25, 6 },
		{ 0, 0, 25, 30, 35, 10 },
		{ 0, 0, 15, 29, 40, 16 }, 
		{ 0, 0, 10, 35, 30, 25 },
		{ 0, 0, 0, 30, 40, 30 },
		{ 0, 0, 0, 20, 30, 50 }, },
	{	{ 100,  },
		{ 99, 1,  },
		{ 98, 2, },
		{ 97, 2, 1, },
		{ 96, 2, 1, 1, },
		{ 94, 3, 2, 1, },
		{ 90, 6, 3, 1, },
		{ 85, 8, 5, 2, },
		{ 80, 10, 7, 3, },
		{ 75, 12, 10, 3, },
		{ 70, 15, 11, 4, }, },
	{	{ 100, },
		{ 100, }, 
		{ 99, 1, }, 
		{ 99, 1, },
		{ 98, 2, }, 
		{ 97, 3, },
		{ 96, 3, 1, }, 
		{ 95, 4, 1, }, 
		{ 94, 4, 2, }, 
		{ 93, 5, 2, },
		{ 91, 6, 3, }, },
	{	{ 100, },
		{ 100, }, 
		{ 99, 1, }, 
		{ 98, 2, },
		{ 95, 3, 2, },
		{ 94, 3, 2, 1, },
		{ 93, 3, 2, 1, 1, },
		{ 92, 4, 2, 1, 1, },
		{ 91, 5, 2, 1, 1, },
		{ 90, 5, 3, 1, 1, },
		{ 88, 6, 3, 2, 1, }, },
	{	{ 100, },
		{ 100, }, 
		{ 99, 1, }, 
		{ 98, 2, },
		{ 97, 2, 1, },
		{ 96, 2, 1, 1, },
		{ 95, 2, 1, 1, 1, },
		{ 94, 2, 2, 1, 1, },
		{ 93, 3, 2, 1, 1, },
		{ 92, 4, 2, 1, 1, },
		{ 91, 4, 3, 1, 1, }, },
};
int g_item2house_type[10][6] =		// ������ ������ ������ ���� ���õǾ����� ���
{
	{ 1,0,0,0,0,0 },
	{ 2,0,0,0,0,0 },
	{ 1,0,0,0,1,0 },
	{ 2,0,0,0,1,0 },
	{ 0,0,1,0,0,0 },
	{ 0,0,2,0,0,0 },
	{ 0,0,1,0,1,0 },
	{ 0,0,2,0,1,0 },
	{ 0,0,1,0,0,1 },
	{ 0,0,2,0,0,1 },
};

int g_give_gamble_item_rate[16][2] =			// �ݷμ��� ����� �׺� ������ �־��ֱ�
{
	{ 0, 0 },
	{ 0, 0, },
	{100, 0, },
	{99, 1, },
	{99, 1, },
	{98, 2, },
	{98, 2, },
	{97, 3, },
	{96, 4, },
	{96, 4, },
	{95, 5, },
	{95, 5, },
	{94, 6, },
	{94, 6, },
	{93, 7, },
	{92, 8, },
};

int g_map2band[][2] =			// �ʴ� ��尪 ��ȭ ��
{
	{ 10, -2 },
	{ 20, -1 },
	{ 40, 0 },
	{ 60, 1 },
	{ 100, 2 },
	{ 150, 3 },
};

int g_create_today_item[8] = { 50, 30, 10, 5, 2, 1, 1, 1 };
int g_get_today_item = 100;

////////////////////////////////////////////////////////////////////////////////////////////////