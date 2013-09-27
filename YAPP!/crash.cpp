
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
						if((-15 < player[0].top - mapbox[i][j].bottom) && (player[0].top - mapbox[i][j].bottom < 0)){
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
//BOOL player_bullet_crash(Bullet (*player_bullet)[P_BULLET_MAX], Player *player, MapBox (*mapbox)[WIDTH]){

