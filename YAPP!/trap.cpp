
#include "stdafx.h"
#include "YAPP!.h"
#include "gamedef.h"
	
void trapf(TRAP *trap, Player *player, char (*map)[WIDTH], MapBox (*mapbox)[WIDTH])
{
	Box save[2]={{(*trap).start*BOXSIZE,(*trap).hold*BOXSIZE,(*trap).start*BOXSIZE+BOXSIZE,(*trap).hold*BOXSIZE+BOXSIZE},
	{(*trap).hold*BOXSIZE,(*trap).start*BOXSIZE,(*trap).hold*BOXSIZE+BOXSIZE,(*trap).start*BOXSIZE+BOXSIZE}};
	static int first=0;
	if(first==0)
	{
		if((*trap).type==LRTYPE||(*trap).type==LRTYPE)
			(*trap).present=save[0]; 
		else
			(*trap).present=save[1];
		first++;
	}
	if( (*trap).count != 1&& (*trap).count != 2 && recognizer((*trap).reco,*player))						//인식범위 좌측 우측모두 0부터시작
	{
		for(int i=0;i<(*trap).hor;i++)
			for(int j=0;j<(*trap).val;j++)				//지우는 것
			{
				map[(*trap).start+i][(*trap).hold+j]=' ';
				mapbox[(*trap).start+i][(*trap).hold+j].value=' ';
				FC_insert(mapbox);
			}
		(*trap).count=1;
	}
	if((*trap).count==1)
	{
		switch((*trap).type)
		{
		case RLTYPE:
			if((*trap).present.left<(*trap).end*BOXSIZE)		
			{
				(*trap).present.left+=(*trap).v;
				(*trap).present.right+=(*trap).v;
				(*trap).v+=(*trap).ac;
				if((*trap).present.left>=(*trap).end*BOXSIZE)
				{
					(*trap).count=2;
				}
			}
			break;
		case DUTYPE:

			if((*trap).present.top<(*trap).end*BOXSIZE)		
			{
				(*trap).present.top+=(*trap).v;
				(*trap).present.bottom+=(*trap).v;
				(*trap).v+=(*trap).ac;
				if((*trap).present.top>=(*trap).end*BOXSIZE)
				{
					(*trap).count=2;
				}
			}
			break;
		case LRTYPE:

			if((*trap).present.left>(*trap).end*BOXSIZE)		
			{
				(*trap).present.left-=(*trap).v;
				(*trap).present.right-=(*trap).v;
				(*trap).v+=(*trap).ac;
				if((*trap).present.left<=(*trap).end*BOXSIZE)
				{
					(*trap).count=2;
				}
			}
			break;
		case UDTYPE:
			if((*trap).present.top>(*trap).end*BOXSIZE)		
			{
				(*trap).present.top-=(*trap).v;
				(*trap).present.bottom-=(*trap).v;
				(*trap).v+=(*trap).ac;
				if((*trap).present.top<=(*trap).end*BOXSIZE)
				{
					(*trap).count=2;
				}
			}
			break;
		}
/*			
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
		*/
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
BOOL trap_reco(TRAP trap,Player player[],int key) //아직 다 못만듬
{

	switch(key)
	{
	case DIE:
		if((player[0].left <=trap.present.right && trap.present.left<=player[0].right) &&
			(player[0].top<=trap.present.bottom && trap.present.top<= player[0].bottom))
		{
			player[0].life=0;
			player[1].life=0;
		}
		break;

	case MOVE_LIMIT:

		break;
	default:
		return -1;
	}

}

