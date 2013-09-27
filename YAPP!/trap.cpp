
#include "stdafx.h"
#include "YAPP!.h"
#include "gamedef.h"
	
void trapf(TRAP *trap, Player *player, char (*map)[WIDTH])
{
	if( (*trap).count != 1&& (*trap).count != 2 && recognizer((*trap).reco,*player))						//인식범위 좌측 우측모두 0부터시작
	{
		for(int i=0;i<(*trap).hor;i++)
			for(int j=0;j<(*trap).val;j++)				//지우는 것
			{
				map[(*trap).start+i][(*trap).hold+j]=' ';
			}
		(*trap).count=1;
	}
	if((*trap).count==1)
	{
		if((*trap).end>(*trap).start)					//만약 위에서 아래, 좌에서 우로 이동시	
		{
			if((*trap).present<(*trap).end*BOXSIZE)		
			{
				(*trap).present+=(*trap).v;
				(*trap).v+=(*trap).ac;
				if((*trap).present>=(*trap).end*BOXSIZE)
				{
					(*trap).count=2;
				}
			}
		}
		else if((*trap).end<(*trap).start)			//만약 아래에서 위, 우에서 좌로 이동시
		{
			if((*trap).present>(*trap).end*BOXSIZE)		
			{
				(*trap).present-=(*trap).v;
				(*trap).v+=(*trap).ac;
				if((*trap).present<=(*trap).end*BOXSIZE)
				{
					(*trap).count=2;
				}
			}
		}
	}		
}
void clear(int a,int b, int c, int d, Player * player,int * stage, int stagename)
{
	Box reco={a,b,c,d};
			
	if(recognizer(reco,*player))
	{
		(*stage)=stagename;
		if(a==930)
		{
			(*player).left=30;
			(*player).right=30+PLAYERSIZE;
		}
		else if(c==30)
		{
			(*player).left=929-PLAYERSIZE;
			(*player).right=929;
		}
		if(b==630)
		{
			(*player).top=30;
			(*player).bottom=30+PLAYERSIZE;
		}
		else if(d==30)
		{
			(*player).top=630-PLAYERSIZE;
			(*player).bottom=630;
		}
	}
	return;
}
