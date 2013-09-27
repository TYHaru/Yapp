

#define		PLAYERSIZE			20
#define		BOXSIZE				30
#define		AC_TIMER_ID			1
#define		JUMP_TIMER_ID		2
#define		MOVE_TIMER_ID		3
#define		LEFT				1
#define		RIGHT				2
#define		DIE					1
#define		MOVE_LIMIT			2
#define		TUTORIAL1			01
#define		TUTORIAL2			02
#define		STAGE1_1			11
#define		STAGE1_2			12
#define		STAGE2_1			21
#define		STAGE2_2			22
#define		WIDTH				32
#define		HEIGHT				22

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
	int present;			//�����ȼ�								�ȼ��� ���
	int ac;					//���ӵ� ������� 0						�ȼ��� ���
	int v;					//�׳ɼӵ�(���� ���ӵ��� ���ϰ�� 0		�ȼ��� ���
	char trapID;
}TRAP;


//�Լ� ����
void trapf(TRAP *trap, Player *player, char (*map)[WIDTH]);			//Ʈ�� ��� ������ �ս��� ������ �� �ִ� �Լ���.
																	//�����ϰ� ���� �����¿�� �����϶� ����ϸ� ����.	
void tuto(Player *player, int *save, char (*map)[WIDTH], TRAP trap[],int * stage, MapBox (*mapbox)[WIDTH]);	//Ʃ�丮���Լ���
void tuto2(Player *player, int *save, char (*map)[WIDTH], TRAP trap[], int * stage, MapBox (*mapbox)[WIDTH]);


BOOL recognizer(Box a,Player player);								//�νĹ����� �����ϴ� �Լ� �νĹ��� ���� ������ TRUE�� ��ȯ�Ѵ�
void insert_map(char (*map)[WIDTH], char (*c_map)[WIDTH], MapBox (*mapbox)[WIDTH]); //�ʿ� �־���
void mapCheck2(Player *player, char (*map)[WIDTH], int *save);
BOOL LR_Crash(char (*map)[WIDTH], Player *player, MapBox (*mapbox)[WIDTH], int key); //�¿� �浹 �Լ�
void FC_Crash(Player *player, char (*map)[WIDTH], int *save, MapBox (*mapbox)[WIDTH]); //���� �浹 �Լ�
BOOL limit(char (*map)[WIDTH],Player player[], int key);
void trapf(TRAP *trap, Player *player, char (*map)[WIDTH], MapBox (*mapbox)[WIDTH]);
void clear(int a,int b, int c, int d, Player * player,int * stage, int stagename);	//������Ʒ� ������ �ʱ�ȭ
void FC_insert(MapBox (*mapbox)[WIDTH]);