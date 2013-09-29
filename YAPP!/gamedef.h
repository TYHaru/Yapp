
#pragma comment(lib, "msimg32.lib")

#define		PLAYERSIZE			20
#define		BOXSIZE				30
#define		P_BULLETSIZE		2
#define		O_BULLETSIZE		4
#define		ENEMY_MAX			10
#define		P_BULLETSIZE		2
#define		O_BULLETSIZE		4
#define		P_BULLET_MAX		20		//�÷��̾� �Ѿ� �� ����
#define		O_BULLET_MAX		100		//�� �Ѿ� �� ����
#define		AC_TIMER_ID			1
#define		JUMP_TIMER_ID		2
#define		MOVE_TIMER_ID		3
#define		BULLET_TIMER_ID		4
#define		BULLETMOVE_TIMER_ID	5
#define		LEFT				1
#define		RIGHT				2
#define		DIE					1
#define		MOVE_LIMIT			2
#define		MENU				0
#define		TUTO				1
#define		TUTORIAL1			11
#define		TUTORIAL2			12
#define		STAGE1				2
#define		STAGE1_1			21
#define		STAGE1_2			22
#define		STAGE2				3
#define		STAGE2_1			31
#define		STAGE2_2			32
#define		WIDTH				32
#define		HEIGHT				22
#define		NN					1		//��
#define		NE					2		//�ϵ�
#define		EE					3		//��
#define		SE					4		//����
#define		SS					5		//��
#define		SW					6		//����
#define		WW					7		//��
#define		NW					8		//�ϼ�
#define		RESET				100
#define		BEGIN				1
#define		SAVE				2
#define		EXIT				3

//trap���� ��ũ��
#define		UDTYPE				1		//������ �Ʒ�: 1 /�Ʒ����� �� : 2 /�¿��� �� : 3 / �쿡�� �� : 4
#define		DUTYPE				2
#define		LRTYPE				3
#define		RLTYPE				4
#define		RE					1		//���밡��
#define		NOT					0		//���� �Ұ� �̰� ��������

//BOSS���� ��ũ��
#define		BOSSUP				100
#define		BOSSRAID			101
#define		BOSSFIRE			102
#define		BEATBOSS			103
//����ü

typedef struct {                  //��üũ ����ü
	int value;
	int left;
	int right;
	int top;
	int bottom;
	int floor_check; 
	int ceiling_check;
}MapBox;
typedef struct {					//�÷��̾� ����ü
	int left;
	int top;
	int right;
	int bottom;
	int life;
}Player;
typedef struct {						//�ڽ� ����ü
	int left;
	int top;
	int right;
	int bottom;
}Box;
typedef struct 
{
	Box reco;				//�νĹ���
	int val;				//�������� ���ڰ���(����)
	int hor;				//�������� ���ڰ���(����)
	int count;
	int hold;					//x��ǥ
	int start;				//�����ϴ� y��ǥ
	int end;				//������ y��ǥ
	int ac;					//���ӵ� ������� 0						�ȼ��� ���
	int v;					//�׳ɼӵ�(���� ���ӵ��� ���ϰ�� 0		�ȼ��� ���
	char type;				//������ �Ʒ�: UDTYPE /�Ʒ����� �� : DUTYPE /�¿��� �� : LRTYPE / �쿡�� �� : RLTYPE
	char key;
	char recur;				//���밡��?
	Box present;			//�����ȼ�								�ȼ��� ���
}TRAP;
typedef struct{
	int PE; //player�̸� 0, Enemy �̸� 1 
	int direction;
	int left;
	int right;
	int top;
	int bottom;
}Bullet;
typedef struct{
	int HP; //ü��
	int left;
	int right;
	int top;
	int bottom;
}Enemy;

//�Լ� ����
void trapf(TRAP *trap, Player *player, char (*map)[WIDTH]);			//Ʈ�� ��� ������ �ս��� ������ �� �ִ� �Լ���.
																	//�����ϰ� ���� �����¿�� �����϶� ����ϸ� ����.	
void tuto(Player *player, int *save, char (*map)[WIDTH], TRAP trap[],int * stage, MapBox (*mapbox)[WIDTH], int * reset);	//Ʃ�丮���Լ���
void tuto2(Player *player, int *save, char (*map)[WIDTH], TRAP trap[], int * stage, MapBox (*mapbox)[WIDTH],int *reset);

void player_bullet_crash(Bullet *player_bullet, MapBox (*mapbox)[WIDTH], Enemy *enemy, int *enemy_count, int *player_bullet_count); //�Ѿ� �浹�Լ�
BOOL recognizer(Box a,Player player);								//�νĹ����� �����ϴ� �Լ� �νĹ��� ���� ������ TRUE�� ��ȯ�Ѵ�
void insert_map1(char (*map)[WIDTH], MapBox (*mapbox)[WIDTH]); //�ʿ� �־���
void insert_map2(char (*map)[WIDTH], char (*c_map)[WIDTH]);
void mapCheck2(Player *player, char (*map)[WIDTH], int *save);
BOOL LR_Crash(char (*map)[WIDTH], Player *player, MapBox (*mapbox)[WIDTH], int key); //�¿� �浹 �Լ�
void FC_Crash(Player *player, char (*map)[WIDTH], int *save, MapBox (*mapbox)[WIDTH]); //���� �浹 �Լ�
BOOL limit(char (*map)[WIDTH],Player player[], int key);
void trapf(TRAP *trap, Player *player, char (*map)[WIDTH], MapBox (*mapbox)[WIDTH], int save[]);
void clear(int a,int b, int c, int d, Player * player,int * stage, int stagename);	//������Ʒ� ������ �ʱ�ȭ
void FC_insert(MapBox (*mapbox)[WIDTH]);
BOOL trap_reco(TRAP trap,Player player[], int save[]);
void moveLimit(TRAP trap,Player player[], int save[]);
void DrawBlockTuto(HDC hdc,HDC backDC,HDC mapDC, TRAP trap[], int *stage, HINSTANCE hInst, char (*map)[WIDTH]);
void tuto2Set(Player player[], TRAP trap[], char (*map)[WIDTH], MapBox (*mapbox)[WIDTH]);
void bossRaid(Player player[], char (*map)[WIDTH], MapBox (*mapbox)[WIDTH],TRAP trap[]);
void stage1(Player *player, int *save, char (*map)[WIDTH], TRAP trap[], int * stage, MapBox (*mapbox)[WIDTH], int * reset);
void DrawBlockStage1(HDC hdc,HDC backDC,HDC mapDC, TRAP trap[], int *stage, HINSTANCE hInst, char (*map)[WIDTH]);
void savePoint(int a,int b, int c, int d,Player player[],int* stage,int reset);
void menu(int *menu_arrow, Player *player, int reset, int *stage);
void DrawMenu(HINSTANCE hInst, HDC hdc, HDC backDC, int *menu_arrow);