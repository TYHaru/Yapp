

#define		PLAYERSIZE			20
#define		BOXSIZE				30
#define		P_BULLETSIZE		2
#define		O_BULLETSIZE		4
#define		ENEMY_MAX			10
#define		P_BULLETSIZE		2
#define		O_BULLETSIZE		4
#define		P_BULLET_MAX		20		//플레이어 총알 수 제한
#define		O_BULLET_MAX		100		//맵 총알 수 제한
#define		AC_TIMER_ID			1
#define		JUMP_TIMER_ID		2
#define		MOVE_TIMER_ID		3
#define		BULLET_TIMER_ID		4
#define		BULLETMOVE_TIMER_ID	5
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
#define		NN					1		//북
#define		NE					2		//북동
#define		EE					3		//동
#define		SE					4		//남동
#define		SS					5		//남
#define		SW					6		//남서
#define		WW					7		//서
#define		NW					8		//북서

//trap관련 메크로
#define		UDTYPE				1		//위에서 아래: 1 /아래에서 위 : 2 /좌에서 우 : 3 / 우에서 좌 : 4
#define		DUTYPE				2
#define		LRTYPE				3
#define		RLTYPE				4



//구조체

typedef struct {                  //맵체크 구조체
	int value;
	int left;
	int right;
	int top;
	int bottom;
	int floor_check; 
	int ceiling_check;
}MapBox;
typedef struct {					//플레이어 구조체
	int left;
	int top;
	int right;
	int bottom;
	int life;
}Player;
typedef struct {						//박스 구조체
	int left;
	int top;
	int right;
	int bottom;
}Box;
typedef struct 
{
	Box reco;				//인식범위
	int val;				//없어지는 상자갯수(가로)
	int hor;				//없어지는 상자갯수(새로)
	int count;
	int hold;					//x좌표
	int start;				//시작하는 y좌표
	int end;				//끝나는 y좌표
	int ac;					//가속도 없을경우 0						픽셀로 계산
	int v;					//그냥속도(없이 가속도만 붙일경우 0		픽셀로 계산
	char type;				//위에서 아래: UDTYPE /아래에서 위 : DUTYPE /좌에서 우 : LRTYPE / 우에서 좌 : RLTYPE
	char key;
	char trapID;

	Box present;			//현재픽셀								픽셀로 계산
}TRAP;
typedef struct{
	int PE; //player이면 0, Enemy 이면 1 
	int direction;
	int left;
	int right;
	int top;
	int bottom;
}Bullet;
typedef struct{
	int HP; //체력
	int left;
	int right;
	int top;
	int bottom;
}Enemy;

//함수 원형
void trapf(TRAP *trap, Player *player, char (*map)[WIDTH]);			//트랩 펑션 함정을 손쉽게 정의할 수 있는 함수다.
																	//간단하게 블럭을 상하좌우로 움직일때 사용하면 좋다.	
void tuto(Player *player, int *save, char (*map)[WIDTH], TRAP trap[],int * stage, MapBox (*mapbox)[WIDTH]);	//튜토리얼함수다
void tuto2(Player *player, int *save, char (*map)[WIDTH], TRAP trap[], int * stage, MapBox (*mapbox)[WIDTH]);

void player_bullet_crash(Bullet *player_bullet, MapBox (*mapbox)[WIDTH], Enemy *enemy, int *enemy_count, int *player_bullet_count); //총알 충돌함수
BOOL recognizer(Box a,Player player);								//인식범위를 결정하는 함수 인식범위 내에 들어오면 TRUE를 반환한다
void insert_map(char (*map)[WIDTH], char (*c_map)[WIDTH], MapBox (*mapbox)[WIDTH]); //맵에 넣어줌
void mapCheck2(Player *player, char (*map)[WIDTH], int *save);
BOOL LR_Crash(char (*map)[WIDTH], Player *player, MapBox (*mapbox)[WIDTH], int key); //좌우 충돌 함수
void FC_Crash(Player *player, char (*map)[WIDTH], int *save, MapBox (*mapbox)[WIDTH]); //상하 충돌 함수
BOOL limit(char (*map)[WIDTH],Player player[], int key);
void trapf(TRAP *trap, Player *player, char (*map)[WIDTH], MapBox (*mapbox)[WIDTH], int save[]);
void clear(int a,int b, int c, int d, Player * player,int * stage, int stagename);	//좌위우아래 순으로 초기화
void FC_insert(MapBox (*mapbox)[WIDTH]);
BOOL trap_reco(TRAP trap,Player player[], int save[]);
void moveLimit(TRAP trap,Player player[], int save[]);