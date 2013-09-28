
#include "stdafx.h"
#include "YAPP!.h"
#include "gamedef.h"


void tuto(Player *player, int *save, char (*map)[WIDTH], TRAP trap[],int * stage, MapBox (*mapbox)[WIDTH], Bullet *player_bullet, int *player_bullet_count, int *enemy_count)
{
	static int first=0;
	static char c_map[HEIGHT][WIDTH]={
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//0
	{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' '},//1
	{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' '},//2
	{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' '},//3
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//4
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//5
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//6
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//7
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//8
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#'},//9
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' '},//10
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ','#','#',' '},//11
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//12
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//13
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//14
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//15
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//16
	{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//17	
	{' ','#','#','#','#','#','#','#','#',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' '},//18
	{' ','#','#','#','#','#','#','#','#',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' '},//19
	{' ','#','#','#','#','#','#','#','#',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' '},//20
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}//21
	// 0  1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31
	};
	clear(930,210,960,270,player,stage,TUTORIAL2, player_bullet, player_bullet_count, enemy_count);
	if(first==0)
	{	
		Box a[2]={{13*BOXSIZE,16*BOXSIZE,16*BOXSIZE,17*BOXSIZE},
			{13*BOXSIZE,15*BOXSIZE,16*BOXSIZE,16*BOXSIZE}};
		TRAP inst[2]={{a[0],1,1,0,16,16,2,0,3,LRTYPE,DIE},
		{a[1],1,1,0,15,16,2,0,1,LRTYPE,MOVE_LIMIT}}; //{인식범위, 사라지는 상자 가로,세로, 카운트(기본 0),x좌표, 시작하는좌표,끝나는좌표,가속도,속도}
		
		trap[0]=inst[0];
		trap[1]=inst[1];
		insert_map(map, c_map, mapbox);
		first++;
	}

  // TODO: 여기에 그리기 코드를 추가합니다.
	trapf(&trap[0],player,map,mapbox,save);
	trapf(&trap[1],player,map,mapbox,save);
	FC_Crash(player, map, save, mapbox);
	//mapCheck2(player, map, save);
}
void DrawBlockTuto(HDC hdc,HDC backDC,HDC mapDC, TRAP trap[], int stage, HINSTANCE hInst)
{
	switch(stage)
			{
				case TUTORIAL1:
					for(int k=0;k<2;k++)
					{
						if(trap[k].count==1)
						{
							for(int i=0;i<trap[k].val;i++)
								for(int j=0;j<trap[k].hor;j++)
								{
									BitBlt(backDC, trap[k].present.left+(i-1)*BOXSIZE, trap[k].present.top+(j-1)*BOXSIZE, BOXSIZE, BOXSIZE, mapDC, 0, 0, SRCCOPY);
								};
						}
					}
					break;
				case TUTORIAL2:
					HDC ButtonDC = CreateCompatibleDC(hdc);
					HDC kupaDC = CreateCompatibleDC(hdc);
					HDC fireDC = CreateCompatibleDC(hdc);
					HBITMAP buttonbit = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP4));
					HBITMAP kupabit = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP5));
					HBITMAP firebit = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP6));
					SelectObject(ButtonDC,buttonbit);
					SelectObject(kupaDC,kupabit);
					SelectObject(fireDC,firebit);
					for(int k=0;k<4;k++)
					{
						if(trap[k].count==1)
						{
							for(int i=0;i<trap[k].val;i++)
								for(int j=0;j<trap[k].hor;j++)
								{
									BitBlt(backDC, trap[k].present.left+(i-1)*BOXSIZE, trap[k].present.top+(j-1)*BOXSIZE, BOXSIZE, BOXSIZE, mapDC, 0, 0, SRCCOPY);
								};
						}
					}
					if(trap[5].count==BOSSUP||trap[5].count==BOSSRAID || trap[5].count== BOSSFIRE || trap[5].count==BEATBOSS)
					{
						
						if(trap[5].count!=BEATBOSS)
							BitBlt(backDC,4*BOXSIZE,18*BOXSIZE,BOXSIZE,BOXSIZE,ButtonDC,0,0,SRCCOPY);
						if(trap[5].count== BOSSFIRE)
							BitBlt(backDC,17*BOXSIZE,17*BOXSIZE-170,120,170,fireDC,0,0,SRCCOPY);
						BitBlt(backDC,trap[5].present.left,trap[5].present.top,210,290,kupaDC,0,0,SRCCOPY);
					}

					break;
			}
}
void Draw_Bullet(HDC hdc, HDC backDC, Bullet *bullet, int *bullet_count, HINSTANCE hInst){
	int i;
	HDC BulletDC = CreateCompatibleDC(hdc);
	HBITMAP Bulletbit = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP7));
	SelectObject(BulletDC,Bulletbit);
	for(i=0; i<bullet_count[0]; i++){
		BitBlt(backDC, bullet[i].left, bullet[i].top, P_BULLETSIZE, P_BULLETSIZE, BulletDC, 0, 0, SRCCOPY);
	}
}
void tuto2(Player *player, int *save, char (*map)[WIDTH], TRAP trap[],int * stage, MapBox (*mapbox)[WIDTH], Bullet *player_bullet, int *player_bullet_count, int *enemy_count)
{
	static int first=0;
	static char c_map[HEIGHT][WIDTH]={
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//0
		{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' '},//1
		{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' '},//2
		{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' '},//3
		{' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//4
		{' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//5
		{' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//6
		{' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//7
		{' ',' ',' ',' ',' ','#','#',' ','#','#',' ',' ','#','#',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//8
		{'#','#','#','#','#','#','#',' ','#','#',' ',' ','#','#',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//9
		{' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//10
		{' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//11
		{' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//12
		{' ','#','#',' ',' ','#','#','#','#','#',' ',' ','#','#',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//13
		{' ','#','#',' ',' ','#','#','#','#','#',' ',' ','#','#',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//14
		{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' '},//15
		{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//16
		{' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//17
		{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' '},//18
		{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' '},//19
		{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' '},//20
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}//21
		//0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30 31  32
	};
	clear(0,210,30,270,player,stage,TUTORIAL1, player_bullet,player_bullet_count, enemy_count);
	if(first==0)
	{
		Box a[4]={{5*BOXSIZE,6*BOXSIZE,7*BOXSIZE,8*BOXSIZE},
		{3*BOXSIZE,15*BOXSIZE,6*BOXSIZE,16*BOXSIZE},
		{11*BOXSIZE,17*BOXSIZE,12*BOXSIZE,18*BOXSIZE},
		{14*BOXSIZE,17*BOXSIZE,15*BOXSIZE,18*BOXSIZE}
		};
		
		TRAP inst[4]={{a[0],2,1,0,5,8,3,0,4,DUTYPE,MOVE_LIMIT},
		{a[1],4,3,0,3,18,21,0,6,UDTYPE,MOVE_LIMIT},
		{a[2],1,1,0,11,18,3,2,3,DUTYPE,MOVE_LIMIT,RE},
		{a[3],1,1,0,14,18,3,2,3,DUTYPE,MOVE_LIMIT,RE}
		}; //{인식범위, 사라지는 상자 가로,세로, 카운트(기본 0),x좌표, 시작하는좌표,끝나는좌표,가속도,속도}
		for(int i=0;i<4;i++)
			trap[i]=inst[i];
		first++;
		insert_map(map, c_map, mapbox);
	}
	for(int i=0;i<4;i++)
		trapf(&trap[i],player,map,mapbox,save);
	tuto2Set(player,trap,map,mapbox);
	FC_Crash(player, map, save, mapbox); 
}
void tuto2Set(Player player[], TRAP trap[], char (*map)[WIDTH], MapBox (*mapbox)[WIDTH])
{
	Box reco={18*BOXSIZE,14*BOXSIZE,20*BOXSIZE,18*BOXSIZE};
	static int count=0;
	if(trap[0].present.top<=3*BOXSIZE +PLAYERSIZE &&player[1].top<3*BOXSIZE )
	{
		player[0].life=0;
		player[1].life=0;
	}
	if(trap[2].present.top<=3*BOXSIZE +PLAYERSIZE &&player[1].top<3*BOXSIZE )
	{
		player[0].life=0;
		player[1].life=0;
	}
	if(trap[3].present.top<=3*BOXSIZE +PLAYERSIZE &&player[1].top<3*BOXSIZE )
	{
		player[0].life=0;
		player[1].life=0;
	}
	if(trap[2].count==0  && player[0].top>18*BOXSIZE && (11*BOXSIZE<=player[0].left && player[0].left<=12*BOXSIZE))
	{
		player[0].life=0;
		player[1].life=0;
	}
	if(trap[3].count==0 && player[0].top>18*BOXSIZE && (14*BOXSIZE<=player[0].left && player[0].left<=15*BOXSIZE))
	{
		player[0].life=0;
		player[1].life=0;
	}
	if(trap[5].count>=BOSSUP || recognizer(reco,player[0]))
	{
		if(count==0){
			trap[5].count=BOSSUP;
		}
		
		
		count++;
		if(count%50==0&& count<200)
		{
			Box boxReco={17*BOXSIZE-PLAYERSIZE,(14+count/50)*BOXSIZE,18*BOXSIZE+PLAYERSIZE,(15+count/50)*BOXSIZE};
			map[14+count/50][17]='#';
			mapbox[14+count/50][17].value='#';
			if(recognizer(boxReco,player[0]))
			{
				player[0].life=0;
				player[1].life=0;
			}
		}
		bossRaid(player,map,mapbox,trap);
	}

}
void bossRaid(Player player[], char (*map)[WIDTH], MapBox (*mapbox)[WIDTH],TRAP trap[])
{

	if(trap[5].count==BOSSUP)  // 일정범위에오면 쿠파가 날라옴
	{
		for(int a=21;a<29;a++)
			for(int b=1;b<4;b++)
			{
				map[b][a]=' ';
				mapbox[b][a].value=' ';
			}
		trap[5].present.left=630;
		trap[5].present.right=630+210;
		trap[5].present.top=-270;
		trap[5].present.bottom=20;
		map[20][5]='#';
		mapbox[20][5].value='#';
		FC_insert(mapbox);
		trap[5].count=BOSSRAID;


	}
	
	if(trap[5].count==BOSSRAID|| trap[5].count== BOSSFIRE)
	{
		Box button={5*BOXSIZE,18*BOXSIZE,6*BOXSIZE,19*BOXSIZE};

		if(trap[5].present.bottom<17*BOXSIZE){
			trap[5].present.top+=5;
			trap[5].present.bottom+=5;
		}
		else if (trap[5].present.bottom>=17*BOXSIZE-5)
		{
			trap[5].count=BOSSFIRE;
		}
		if(recognizer(button,*player))          //버튼을 밟을 경우 쿠파 터지면서 클리어
		{
			trap[5].count=BEATBOSS;
			map[17][17]=map[16][17]=map[15][17]=' ';
			mapbox[17][17].value=mapbox[16][17].value=mapbox[15][17].value=' ';
		}
	}
	else if(trap[5].count==BEATBOSS)
	{
		for(int a=21;a<29;a++)
			for(int b=18;b<21;b++)
			{
				map[b][a]=' ';
				mapbox[b][a].value=' ';
			}
		FC_insert(mapbox);
		trap[5].present.top+=30;
		trap[5].present.bottom+=30;
	}

}
