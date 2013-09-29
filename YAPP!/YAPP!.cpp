#include "stdafx.h"
#include "YAPP!.h"
#include "gamedef.h"

#define MAX_LOADSTRING 100
// ���� ����:
HINSTANCE hInst;	 // ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];	 // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];	 // �⺻ â Ŭ���� �̸��Դϴ�.
// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM	 MyRegisterClass(HINSTANCE hInstance);
BOOL	 InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_YAPP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	
	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_YAPP));

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	}
	
	return (int) msg.wParam;
}



//
// �Լ�: MyRegisterClass()
//
// ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style	 = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra	 = 0;
	wcex.cbWndExtra	 = 0;
	wcex.hInstance	 = hInstance;
	wcex.hIcon	 = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_YAPP));
	wcex.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_YAPP);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm	 = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
	return RegisterClassEx(&wcex);
}

//
// �Լ�: InitInstance(HINSTANCE, int)
//
// ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
// ����:
//
// �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
// �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.
	
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	CW_USEDEFAULT, 0, 920	, 700, NULL, NULL, hInstance, NULL);
	
	if (!hWnd)
	{
		return FALSE;
	}
	
	ShowWindow(hWnd, nCmdShow);
	
	UpdateWindow(hWnd);

	return TRUE;
}

//
// �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
// ����: �� â�� �޽����� ó���մϴ�.
//
// WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
// WM_PAINT	- �� â�� �׸��ϴ�.
// WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int ac=0,j_flag=0,j_not=0;
	static float j_count1=0;
	static Player player[2] = {{130,130,130+PLAYERSIZE,130+PLAYERSIZE,1} , {130,130,130+PLAYERSIZE,130+PLAYERSIZE,1}}; //player[0]�� ������ġ player[1]�� ����ġ
	PAINTSTRUCT ps;
	static HANDLE hTimer;
	static char map[HEIGHT][WIDTH]={};
	static int stage=TUTORIAL2, trapKey[10];
	static TRAP trap[10];
	static MapBox mapbox[HEIGHT][WIDTH] = {0};
	int save[3] = {0};	 //save[0] = ac, save[1] = j_count1, save[2] = j_not
	HDC hdc, hBitDC, mapDC, backDC, charDC, BulletDC;
	HBITMAP hBit, mapbit, Bulletbit;
	HBITMAP backbitmap;	 //������ dc�� ����� BitMap�� �ٸ����� ���� ���ָ鼭 �� BitMap�� dc�� �����Ѵ�.
	RECT rt={0,0,900,700};
	static int player_bullet_direction;
	static Bullet player_bullet[P_BULLET_MAX];
	static int player_bullet_count[1] = {0};
	static int enemy_count[1] = {0};
	static int reset=0;
	char B[7] = "bullet";
	SetTimer(hWnd, MOVE_TIMER_ID, 10, NULL);
	SetTimer(hWnd, BULLET_TIMER_ID, 200, NULL); //�Ѿ� Ÿ�̸�

	save[0] = ac;
	save[1] = j_count1;
	save[2] = j_not;
	
	switch(stage)
	{
		case TUTORIAL1:
			tuto(player, save, map,trap,&stage, mapbox,&reset);
			break;
		case TUTORIAL2:
			tuto2(player,save,map,trap, &stage, mapbox, &reset);
			break;
		case STAGE1_1:
			stage1(player,save,map,trap, &stage, mapbox, &reset);
			break;
	}


	ac = save[0];
	j_count1 = save[1];
	j_not = save[2];
	
	
	switch (message)
	{
	
		case WM_CREATE :
			hTimer=(HANDLE)SetTimer(hWnd,AC_TIMER_ID,50,NULL);
			return 0;


		case WM_KEYDOWN:
			switch(wParam)
			{
				case 'R':
				case 'r':
					reset=RESET;
					return false;
				case 'z': //�������� ���� 2�ܱ��� ���
				case 'Z':
					if(player[0].life==1 && j_count1<2 && j_not<1.1)
					{
						SetTimer(hWnd,JUMP_TIMER_ID,50,NULL);
						j_not++;
						ac=0;
						j_flag=0;
						j_count1+=1;
					//	InvalidateRect(hWnd,NULL,false);
						return false;
					}
			}


		case WM_TIMER:
			switch(wParam)
			{
				case AC_TIMER_ID: //�߷�ó��
					if(ac<17)
						ac+=2;
					player[1].top = player[0].top;
					player[0].top+=ac;
					player[1].bottom = player[0].bottom;
					player[0].bottom+=ac;
					InvalidateRect(hWnd,NULL,FALSE);
					return false;

				case JUMP_TIMER_ID:
					player[1].top = player[0].top;
					player[0].top-=(20-j_flag*3); //���� �ö󰥼��� ������
					player[1].bottom = player[0].bottom;
					player[0].bottom-=(20-j_flag*3);
					j_flag++;
					if(j_flag==4)
						KillTimer(hWnd,2); 
					return false;
				case MOVE_TIMER_ID:
					if(player[0].life!=0)
					{
						if(GetAsyncKeyState(VK_LEFT) < 0) //���ʤ���
						{
							if(LR_Crash(map, player, mapbox, LEFT)) // if �� �߰��� �Է�
							{
								player_bullet_direction == WW;
								player[1].left = player[0].left;
								player[0].left -= 3;
								player[1].right = player[0].right;
								player[0].right -= 3;
							}
						}
						if(GetAsyncKeyState(VK_RIGHT) < 0) //������ ����
						{
							if(LR_Crash(map, player, mapbox, RIGHT))//if �� �߰��� �Է� (�̵� �Ұ��ϰ� ����)
							{
								player_bullet_direction == EE;
								player[1].left = player[0].left;
								player[0].left += 3;
								player[1].right = player[0].right;
								player[0].right += 3;
							}
						}
					}
					return false;
				case BULLET_TIMER_ID:
					if(GetAsyncKeyState(0x58) < 0) // X = Bullet
					{
						player_bullet[player_bullet_count[0]].direction = player_bullet_direction;
						if(player_bullet[player_bullet_count[0]].direction == WW){
							player_bullet[player_bullet_count[0]].right = player[0].left;
							player_bullet[player_bullet_count[0]].left = player_bullet[player_bullet_count[0]].right - P_BULLETSIZE;
						}
						else if(player_bullet[player_bullet_count[0]].direction == EE){
							player_bullet[player_bullet_count[0]].left = player[0].right;
							player_bullet[player_bullet_count[0]].right = player_bullet[player_bullet_count[0]].left + P_BULLETSIZE;
						}
						player_bullet[player_bullet_count[0]].top = player[0].top + 11;
						player_bullet[player_bullet_count[0]].bottom = player_bullet[player_bullet_count[0]].top + P_BULLETSIZE;
						player_bullet_count[0]++;
					}
					for(int i=0; i<player_bullet_count[0]; i++){
						if(player_bullet[i].direction == WW){
							player_bullet[i].right -= 10;
							player_bullet[i].left = player_bullet[i].right - P_BULLETSIZE;
						}
						else if(player_bullet[i].direction == EE){
							player_bullet[i].left += 10;
							player_bullet[i].right = player_bullet[i].left + P_BULLETSIZE;
						}
					}
					return false;
			}


		case WM_PAINT:

			hdc = BeginPaint(hWnd, &ps);
			backDC=CreateCompatibleDC(hdc);
			backbitmap = CreateCompatibleBitmap(hdc,rt.right,rt.bottom);
			hBitDC = CreateCompatibleDC(hdc);
			mapDC = CreateCompatibleDC(hdc);
			charDC = CreateCompatibleDC(hdc);
			BulletDC = CreateCompatibleDC(hdc);
			if(player[0].life==1)
				mapbit=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP1));
			else
				mapbit=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP3));
			if(stage/10==TUTO)
				hBit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
			else if(stage/10==STAGE1)
				hBit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
			Bulletbit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP15));
			SelectObject(backDC, backbitmap);
			SelectObject(mapDC,hBit);
			SelectObject(charDC,mapbit);
			SelectObject(BulletDC, Bulletbit);
			SelectObject(backDC,hBit);
			FillRect(backDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
			switch(stage/10)
			{
				case TUTO:
					DrawBlockTuto(hdc,backDC,mapDC,trap,stage,hInst,map);
					break;
				case STAGE1:
					DrawBlockStage1(hdc,backDC,mapDC,trap,stage,hInst,map);
					break;
			}
			for(int i=0; i<player_bullet_count[0]; i++){
				//BitBlt(backDC, player_bullet[i].left, player_bullet[i].top, P_BULLETSIZE, P_BULLETSIZE, BulletDC , 0, 0, SRCCOPY);
				TextOut(hdc, player_bullet[i].left, player_bullet[i].top, B, strlen(B)); 
			}
		TransparentBlt(backDC, player[0].left-BOXSIZE, player[0].top-BOXSIZE, PLAYERSIZE, PLAYERSIZE, charDC, 0, 0,PLAYERSIZE,PLAYERSIZE, RGB(255,255,255));
		BitBlt(hdc,0,0,rt.right,rt.bottom,backDC,0,0,SRCCOPY);

// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
// SelectObject(hBitDC, hOldBit); 
// SelectObject(mapDC, holdmap); 
		DeleteObject(backbitmap);
		DeleteObject(hBit);
		DeleteObject(Bulletbit);
		DeleteObject(mapbit);
		DeleteDC(hBitDC);
		DeleteDC(backDC);
		DeleteDC(BulletDC);
		DeleteDC(hdc);
		DeleteDC(mapDC);
		DeleteDC(charDC);
		
		EndPaint(hWnd, &ps);
		return FALSE;
	case WM_DESTROY:
		KillTimer(hWnd, AC_TIMER_ID);
		KillTimer(hWnd, MOVE_TIMER_ID);
		KillTimer(hWnd, BULLET_TIMER_ID);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


