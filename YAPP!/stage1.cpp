
#include "stdafx.h"
#include "YAPP!.h"
#include "gamedef.h"

void DrawBlockStage1(HDC hdc,HDC backDC,HDC mapDC, TRAP trap[], int stage, HINSTANCE hInst, char (*map)[WIDTH])
{
	HDC backgroundDC=CreateCompatibleDC(hdc);
	HDC lavaDC=CreateCompatibleDC(hdc);
	HDC fireDC=CreateCompatibleDC(hdc);
	HDC sandDC=CreateCompatibleDC(hdc);
	HDC saveDC=CreateCompatibleDC(hdc);
	HDC waterDC=CreateCompatibleDC(hdc);
	HBITMAP backbit= LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP8));
	SelectObject(backgroundDC,backbit);
	BitBlt(backDC, 0, 0, 900, 600, backgroundDC, 0, 0, SRCCOPY);
	switch(stage)
	{
		case STAGE1_1:
			HBITMAP lavabit= LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP12));
			HBITMAP firebit= LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP10));
			HBITMAP sandbit= LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP9));
			HBITMAP savebit= LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP11));
			HBITMAP waterbit= LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP13));
			SelectObject(lavaDC,lavabit);
			SelectObject(fireDC,firebit);
			SelectObject(sandDC,sandbit);
			SelectObject(saveDC,savebit);
			SelectObject(waterDC,waterbit);
			for(int i=0;i<HEIGHT-1;i++){
				for(int j=0;j<WIDTH-1;j++)
				{
					if(map[i][j]=='#'){
						BitBlt(backDC, (j-1)*BOXSIZE, (i-1)*BOXSIZE, BOXSIZE, BOXSIZE, mapDC,0,0,SRCCOPY);
					}
					else if(map[i][j]=='s'){
						BitBlt(backDC, (j-1)*BOXSIZE, (i-1)*BOXSIZE, BOXSIZE, BOXSIZE, saveDC,0,0,SRCCOPY);
					}
					else if(map[i][j]=='S'){
						BitBlt(backDC, (j-1)*BOXSIZE, (i-1)*BOXSIZE, BOXSIZE, BOXSIZE, sandDC,0,0,SRCCOPY);
					}
					else if(map[i][j]=='f'){
						TransparentBlt(backDC, (j-1)*BOXSIZE, (i-1)*BOXSIZE, BOXSIZE, BOXSIZE, fireDC,0,0,BOXSIZE, BOXSIZE, RGB(255,255,255));
					}
					else if(map[i][j]=='F'){
						BitBlt(backDC, (j-1)*BOXSIZE, (i-1)*BOXSIZE, BOXSIZE, BOXSIZE, lavaDC,0,0,SRCCOPY);
					}
					else if(map[i][j]=='W'){
						BitBlt(backDC, (j-1)*BOXSIZE, (i-1)*BOXSIZE, BOXSIZE, BOXSIZE, waterDC,0,0,SRCCOPY);
					}
				}
			}
	
	}
}
void stage1(Player *player, int *save, char (*map)[WIDTH], TRAP trap[], int * stage, MapBox (*mapbox)[WIDTH] , int * reset)
{
	static int first=0;
	static char c_map[HEIGHT][WIDTH]={
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//0
		{' ','#','#',' ','f','f','f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f','f','f','f',' ','s','f',' ','#','#',' '},//1
		{' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ','#',' ','#','#',' '},//2
		{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ','#',' ','#','#',' '},//3
		{' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ','#','#',' '},//4
		{' ','#','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#','#','#','#','#','#',' ','#','#',' '},//5
		{' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ','#','#',' '},//6
		{' ','#','#',' ',' ',' ',' ',' ','#',' ',' ',' ','S','S',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ','#','#',' '},//7
		{' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ','S','S',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ','#',' ','#','#',' '},//8
		{'#','#','#',' ',' ',' ',' ',' ','#',' ',' ',' ','S','S','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#','#',' '},//9
		{' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ','S','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#','#',' '},//10
		{' ','#','#',' ',' ',' ',' ',' ','#',' ',' ',' ','S','S',' ',' ','S',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ','#','#',' '},//11
		{' ','#','#',' ',' ',' ',' ','D','#','#',' ',' ','S','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#','#',' '},//12
		{' ','#','#',' ',' ','#','#','#','#',' ',' ',' ','S','S',' ',' ',' ',' ',' ','S',' ',' ','S','#','#',' ',' ','#',' ','#','#',' '},//13
		{' ','#','#',' ',' ','#','#','#','#','#',' ',' ','S','S','W','W','W','W','W','W','W','W','S',' ',' ',' ',' ','#',' ','#','#',' '},//14
		{' ','#','#','f','f','f','f','f','f','f','f','f','S','S','W','W','W','W','W','W','W','W','S',' ',' ',' ',' ','#',' ','#','#',' '},//15
		{' ','#','#','F','F','F','F','F','F','F','F','F','S','S','W','W','W','W','W','W','W','W','S',' ',' ',' ','B','#',' ','#','#',' '},//16
		{' ','#','#','F','F','F','F','F','F','F','F','F','#','#','W','W','W','W','W','W','W','W','#',' ',' ',' ',' ','#',' ','#','#',' '},//17
		{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#',' '},//18
		{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#',' '},//19
		{' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#',' '},//20
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}//21
		//0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30 31  32
	};
	static char save_map[HEIGHT][WIDTH];
		savePoint(2,7,3,8,player,stage,reset[0]);
	if(first==0)
		insert_map2(save_map,c_map);
	if(first==0 || reset[0]==RESET)
	{
		insert_map2(c_map, save_map);
		reset[0]=0;
	}
	insert_map2(map, c_map);
	insert_map1(map, mapbox);
	insert_map2(c_map, map);
	FC_Crash(player, map, save, mapbox);
}