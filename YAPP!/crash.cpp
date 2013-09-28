
#include "stdafx.h"
#include "YAPP!.h"
#include "gamedef.h"


BOOL recognizer(Box a,Player player)								//인식범위를 결정하는 함수 인식범위 내에 들어오면 TRUE를 반환한다.
{
	if( 
		( a.left<=player.left && player.right<= a.right  ) && 
		( a.top <=player.top && player.bottom<= a.bottom )
		)
	{
		return TRUE;
	}
	else 
		return FALSE;
}

void mapCheck2(Player *player, char (*map)[WIDTH], int *save) //		맵체크 전체 복사
{

	int xLeft[2], xRight[2], yTop[2], yBottom[2];
	Player save_player[2];
	int i;
	for(i=0; i<2; i++){
		xLeft[i] = player[i].left/BOXSIZE; //각각 30으로 나눠서 좌표화시킴
			if(player[i].left%BOXSIZE == 0){
			xLeft[i]++;
		}
		xRight[i] = player[i].right/BOXSIZE;
		if(player[i].right%BOXSIZE == 0){
			xRight[i]--;
		}
		yTop[i] = player[i].top/BOXSIZE;
		if(player[i].top%BOXSIZE == 0){
			yTop[i]++;
		}
		yBottom[i] = player[i].bottom/BOXSIZE;
		if(player[i].bottom%BOXSIZE == 0){
			yBottom[i]--;
		}
		save_player[i]=player[i];
	
	}

	if(((map[yTop[1]][xLeft[1]]==' ' && map[yTop[0]][xLeft[0]]=='#')|| 
		((map[yTop[1]][xRight[1]]==' ')&& map[yTop[0]][xRight[0]]=='#'))
		) //위 충돌
	{
		for(i=0;i<2;i++)
		{
			player[i].top=yTop[1]*30;
			player[i].bottom=yTop[1]*30+PLAYERSIZE;
		}
	}
/*
	else if(((map[yBottom[1]][xLeft[1]]==' ' && map[yBottom[0]][xLeft[0]]=='#')|| 
		((map[yBottom[1]][xRight[1]]==' ')&& map[yBottom[0]][xRight[0]]=='#'))
		) //아래 충돌
	{
		for(i=0;i<2;i++)
		{
			player[i].bottom=(yBottom[1]+1)*30-1;
			player[i].top=(yBottom[1]+1)*30-PLAYERSIZE-1;
		}
		for(i=0; i<3; i++){
				save[i] = 0;
		}
	}
	*/
}
BOOL LR_Crash(char (*map)[WIDTH], Player *player, MapBox (*mapbox)[WIDTH], int key){
	int i, j;
	int save_player[2]; //save_player[0] 는 player[0].left, save_player[1] 는 player[0].right
	if(key == LEFT){
		save_player[0] = player[0].left-3;
		save_player[1] = player[0].right-3;
	}
	else if(key == RIGHT){
		save_player[0] = player[0].left+3;
		save_player[1] = player[0].right+3;
	}
	for(i=0; i<HEIGHT; i++){
		for(j=0; j<WIDTH; j++){
			if(mapbox[i][j].value == '#'){
				if(save_player[0] - mapbox[i][j].right < 0){
					if(save_player[1] - mapbox[i][j].left > 0){
						if(player[0].top - mapbox[i][j].bottom < 0){
							if(player[0].bottom - mapbox[i][j].top > 0){
								return FALSE;
							}
						}
					}
				}
			}
		}
	}
	return TRUE;
}
void FC_Crash(Player *player, char (*map)[WIDTH], int *save, MapBox (*mapbox)[WIDTH]){
	int i, j, k;
	for(i=0; i<HEIGHT; i++){
		for(j=0; j<WIDTH; j++){
			if(mapbox[i][j].floor_check == 1){ //바닥일 때 검사
				if(((mapbox[i][j].left < player[0].left) && (player[0].left < mapbox[i][j].right)) ||
					((mapbox[i][j].left < player[0].right) && (player[0].right < mapbox[i][j].right))){ //플레이어의 좌우 위치 둘중 하나가 박스의 좌우좌표 안에 있을 때
						if((0 < player[0].bottom - mapbox[i][j].top) && (player[0].bottom - mapbox[i][j].top < 30)){
							if(player[0].top >=player[1].top){
								player[0].bottom = mapbox[i][j].top;
								player[0].top = player[0].bottom - PLAYERSIZE;
								for(k=0; k<3; k++){
									save[k] = 0;
								}
							}
						}
				}
			}
			if(mapbox[i][j].ceiling_check == 1){
				if(((mapbox[i][j].left < player[0].left) && (player[0].left < mapbox[i][j].right)) ||
					((mapbox[i][j].left < player[0].right) && (player[0].right < mapbox[i][j].right))){ //플레이어의 좌우 위치 둘중 하나가 박스의 좌우좌표 안에 있을 때
						if((-30 < player[0].top - mapbox[i][j].bottom) && (player[0].top - mapbox[i][j].bottom < 0)){
							if(player[0].top < player[1].top){
								player[0].top = mapbox[i][j].bottom;
								player[0].bottom = player[0].top + PLAYERSIZE;
							}
						}
				}
			}
		}
	}
}

/*BOOL limit(char (*map)[WIDTH],Player player[], int key)  //좌우 움직임 봉쇄
{
	int xLeft, xRight, yTop, yBottom;
	xLeft = (*player).left/BOXSIZE;
	xRight = (*player).right/BOXSIZE;
	yTop = (*player).top/BOXSIZE;
	yBottom = (*player).bottom/BOXSIZE;
	if((*player).bottom%30==0)
	{
	//	yBottom-=1;
	}
	switch(key)
	{
	case LEFT:
		if(yTop==yBottom)
		{
			if(map[yTop][xLeft-1]=='#')
			{
				if(map[yTop][xLeft]==' '&&(((*player).left-3)/30)==xLeft)
				{
					return TRUE;
				}
				return FALSE;
			}
		}
		else if(yTop!=yBottom)
		{
			if(map[yTop][xLeft-1]=='#'||map[yTop-1][xLeft-1]=='#')
			{
				if(map[yTop][xLeft]==' '&&(((*player).left-3)/30)==xLeft)
				{
					return TRUE;
				}
				return FALSE;
			}
		}
		break;
	case RIGHT:
		if(yTop==yBottom)
		{
			if(map[yTop][xRight+1]=='#')
			{
				if(map[yTop][xRight]==' '&&(((*player).right+3)/30)==xRight)
				{
					return TRUE;
				}
				return FALSE;
			}
		}
		else if(yTop!=yBottom)
		{
			if(map[yTop][xRight+1]=='#'||map[yTop-1][xRight+1]=='#')
			{
				if(map[yTop][xRight]==' '&&(((*player).right+3)/30)==xRight)
				{
					return TRUE;
				}
				return FALSE;
			}
		}
		break;
	default:
		return TRUE;
	}
	return TRUE;
}*/

void player_bullet_crash(Bullet *player_bullet, MapBox (*mapbox)[WIDTH], Enemy *enemy, int *enemy_count, int *player_bullet_count){
	int i, j, k;
	int enemy_check[ENEMY_MAX]= {0}, bullet_check[P_BULLET_MAX] = {0};
	int bullet_delete = 0;
	for(i=0; i<player_bullet_count[0]; i++){
		for(j=0; j<enemy_count[0]; j++){
			if(player_bullet[i].left - enemy[j].right < 0){
				if(player_bullet[i].right - enemy[j].left > 0){
					if(player_bullet[i].top - enemy[j].bottom < 0){
						if(player_bullet[i].bottom - enemy[j].top > 0){
							enemy_check[j]	= 1;
							bullet_check[i] = 1;
							enemy[j].HP--;
						}
					}
				}
			}
		}
		for(j=0; j<HEIGHT; j++){
			for(k=0; k<WIDTH; k++){
				if(player_bullet[i].left - mapbox[i][j].right < 0){
					if(player_bullet[i].right - mapbox[i][j].left > 0){
						if(player_bullet[i].top - mapbox[i][j].bottom < 0){
							if(player_bullet[i].bottom - mapbox[i][j].top > 0){
								bullet_check[i] = 1;
							}
						}
					}
				}
			}
		}
		if(bullet_check[i] == 1){
			bullet_delete++;
		}
	}
	for(i=0; i<enemy_count[0]; i++){
		if(enemy_check[i] == 1){
			if(enemy[i].HP == 0){
				for(j=i; j<enemy_count[0]; j++){
					enemy[j].left = enemy[j+1].left;
					enemy[j].right = enemy[j+1].right;
					enemy[j].top = enemy[j+1].top;
					enemy[j].bottom = enemy[j+1].bottom;
					enemy[j].HP = enemy[j+1].HP;
					enemy_count[0]--;
				}
			}
		}
	}
	for(i=0; i<player_bullet_count[0]; i++){
		if(bullet_check[i] == 1){
			for(j=i; j<player_bullet_count[0]; j++){
				player_bullet[j].PE = player_bullet[j+1].PE;
				player_bullet[j].direction = player_bullet[j+1].direction;
				player_bullet[j].left = player_bullet[j+1].left;
				player_bullet[j].right = player_bullet[j+1].right;
				player_bullet[j].top = player_bullet[j+1].top;
				player_bullet[j].bottom = player_bullet[j+1].bottom;
				player_bullet_count[0]--;
			}
		}
	}
}