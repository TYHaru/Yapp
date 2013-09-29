#include "stdafx.h"
#include "YAPP!.h"
#include "gamedef.h"

void menu(int *menu_arrow, Player *player, int reset, int *stage){
	int menu_select=0;
	if(GetKeyState(VK_LEFT) && 0x8000){
		if(menu_arrow[0] > 1){
			menu_arrow[0]--;
		}
	}
	if(GetKeyState(VK_RIGHT) && 0x8000){
		if(menu_arrow[0] < 3){
			menu_arrow[0]++;
		}
	}
	if(GetKeyState(VK_RETURN) && 0x8000){
		menu_select = menu_arrow[0];
	}
	switch(menu_select){
		case BEGIN:
			for(int i=0; i<2; i++){
				player[i].left = 130;
				player[i].right = 130+PLAYERSIZE;
				player[i].top = 130;
				player[i].bottom = 130+PLAYERSIZE;
				player[i].life = 1;
			}
			stage[0] = TUTORIAL1;
			break;
		case SAVE:
			reset = RESET;
			savePoint(0, 0, 0, 0, player, stage, reset);
			break;
		case EXIT:
			exit(0);
	}
}
void DrawMenu(HINSTANCE hInst, HDC hdc, HDC backDC, int *menu_arrow){
	HDC BackgroundDC, BeginDC, SaveDC, ExitDC, PlayerDC;
	HBITMAP Backgroundbit, Beginbit, Savebit, Exitbit, Playerbit;
	BackgroundDC = CreateCompatibleDC(hdc);
	BeginDC = CreateCompatibleDC(hdc);
	SaveDC = CreateCompatibleDC(hdc);
	ExitDC = CreateCompatibleDC(hdc);
	PlayerDC = CreateCompatibleDC(hdc);
	Backgroundbit = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP14)); //배경
	Beginbit = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP16)); //시작
	Savebit = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP17));  //이어
	Exitbit = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP20));  //끝
	Playerbit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));//캐릭터
	SelectObject(BackgroundDC, Backgroundbit);
	SelectObject(BeginDC, Beginbit);
	SelectObject(SaveDC, Savebit);
	SelectObject(ExitDC, Exitbit);
	SelectObject(PlayerDC, Playerbit);
	BitBlt(backDC, 0, 0, 900, 600, BackgroundDC, 0, 0, SRCCOPY);
	BitBlt(backDC, 80, 230, 200, 200, BeginDC, 0, 0, SRCCOPY);
	BitBlt(backDC, 340, 230, 200, 200, SaveDC, 0, 0, SRCCOPY);
	BitBlt(backDC, 600, 230, 200, 200, ExitDC, 0, 0, SRCCOPY);
	switch(menu_arrow[0]){
		case BEGIN:
			BitBlt(backDC, 170, 470, PLAYERSIZE, PLAYERSIZE, PlayerDC, 0, 0, SRCCOPY);
			break;
		case SAVE:
			BitBlt(backDC, 430, 470, PLAYERSIZE, PLAYERSIZE, PlayerDC, 0, 0, SRCCOPY);
			break;
		case EXIT:
			BitBlt(backDC, 690, 470, PLAYERSIZE, PLAYERSIZE, PlayerDC, 0, 0, SRCCOPY);
			break;
	}	
	DeleteDC(BackgroundDC);
	DeleteDC(BeginDC);
	DeleteDC(SaveDC);
	DeleteDC(ExitDC);
	DeleteDC(PlayerDC);
	DeleteObject(Backgroundbit);
	DeleteObject(Beginbit);
	DeleteObject(Savebit);
	DeleteObject(Exitbit);
	DeleteObject(Playerbit);
}