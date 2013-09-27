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
	static Player player[2] = {{130,130,130+PLAYERSIZE,130+PLAYERSIZE} , {130,130,130+PLAYERSIZE,130+PLAYERSIZE}}; //player[0]�� ������ġ player[1]�� ����ġ
	PAINTSTRUCT ps;
	static HANDLE hTimer;
	static char map[HEIGHT][WIDTH]={};
	static int stage=TUTORIAL1, trapKey[10];
	static TRAP trap[10];
	static MapBox mapbox[HEIGHT][WIDTH] = {0};
	int save[3] = {0};	 //save[0] = ac, save[1] = j_count1, save[2] = j_not
	HDC hdc, hBitDC, mapDC, backDC, charDC;
	HBITMAP hBit, mapbit;
	HBITMAP backbitmap;	 //������ dc�� ����� BitMap�� �ٸ����� ���� ���ָ鼭 �� BitMap�� dc�� �����Ѵ�.
	HBITMAP hOldBit,holdmap,holdchar; 
	RECT rt={0,0,900,700};
	static int player_bullet_direction;
	Bullet player_bullet[P_BULLET_MAX];
	
	SetTimer(hWnd, MOVE_TIMER_ID, 10, NULL);

	save[0] = ac;
	save[1] = j_count1;
	save[2] = j_not;
	
	switch(stage)
	{
		case TUTORIAL1:
			tuto(player, save, map,trap,&stage, mapbox);
			break;
		case TUTORIAL2:
			tuto2(player,save,map,trap, &stage, mapbox);
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
				case 'z'://�������� ���� 2�ܱ��� ���
				case 'Z':
					if(j_count1<2 && j_not<1.1)
					{
						SetTimer(hWnd,JUMP_TIMER_ID,20,NULL);
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
					if(GetAsyncKeyState(VK_LEFT) & 0x8000) //���ʤ���
					{
						if(LR_Crash(map, player, mapbox, LEFT)) // if �� �߰��� �Է�
						{
							player[1].left = player[0].left;
							player[0].left -= 3;
							player[1].right = player[0].right;
							player[0].right -= 3;
						}
					}
					if(GetAsyncKeyState(VK_RIGHT) & 0x8000) //������ ����
					{
						if(LR_Crash(map, player, mapbox, RIGHT))//if �� �߰��� �Է� (�̵� �Ұ��ϰ� ����)
						{
							player[1].left = player[0].left;
							player[0].left += 3;
							player[1].right = player[0].right;
							player[0].right += 3;
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
			mapbit=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP1));
			hBit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
			hOldBit = (HBITMAP)SelectObject(backDC, backbitmap);
			holdmap = (HBITMAP)SelectObject(mapDC,hBit);
			holdchar = (HBITMAP)SelectObject(charDC,mapbit);
			SelectObject(backDC,hBit);
			FillRect(backDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
			switch(stage)
			{
				case TUTORIAL1:
					if(trap[0].count==1)
					{
						BitBlt(backDC, trap[0].present-BOXSIZE, (trap[0].hold-1)*BOXSIZE, BOXSIZE, BOXSIZE, mapDC, 0, 0, SRCCOPY);
					}
					break;
				case TUTORIAL2:
					break;
			}
			for(int i=0;i<HEIGHT-1;i++){
				for(int j=0;j<WIDTH-1;j++)
				{
					if(map[i][j]=='#'){
					BitBlt(backDC, (j-1)*BOXSIZE, (i-1)*BOXSIZE, BOXSIZE, BOXSIZE, mapDC, 0, 0, SRCCOPY);
				}
			}
		}
		BitBlt(backDC, player[0].left-BOXSIZE, player[0].top-BOXSIZE, PLAYERSIZE, PLAYERSIZE, charDC, 0, 0, SRCCOPY);
		BitBlt(hdc,0,0,rt.right,rt.bottom,backDC,0,0,SRCCOPY);

// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
// SelectObject(hBitDC, hOldBit); 
// SelectObject(mapDC, holdmap); 
		DeleteObject(hBit);
		DeleteObject(mapbit);
		DeleteDC(backDC);
		DeleteDC(mapDC);
		
		EndPaint(hWnd, &ps);
		return FALSE;
	case WM_DESTROY:
		KillTimer(hWnd,1);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


BOOL trap_reco(TRAP trap,Player player[],int key) //���� �� ������
{

	switch(key)
	{
	case DIE:
		
		break;

	case MOVE_LIMIT:

		break;
	default:
		return -1;
	}

}

