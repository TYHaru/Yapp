
#include "stdafx.h"
#include "YAPP!.h"
#include "gamedef.h"
	
void trapf(TRAP *trap, Player *player, char (*map)[WIDTH], MapBox (*mapbox)[WIDTH], int save[])
{
	Box save_p[2]={{(*trap).start*BOXSIZE,(*trap).hold*BOXSIZE,(*trap).start*BOXSIZE+BOXSIZE*(*trap).val,(*trap).hold*BOXSIZE+BOXSIZE*(*trap).hor},
	{(*trap).hold*BOXSIZE,(*trap).start*BOXSIZE,(*trap).hold*BOXSIZE+BOXSIZE*(*trap).val,(*trap).start*BOXSIZE+BOXSIZE*(*trap).hor}};

	if( (*trap).count != 1&& (*trap).count != 2 && recognizer((*trap).reco,*player))						//인식범위 좌측 우측모두 0부터시작
	{
		for(int i=0;i<(*trap).hor;i++)
			for(int j=0;j<(*trap).val;j++)				//지우는 것
			{
				map[(*trap).start+i][(*trap).hold+j]=' ';
				mapbox[(*trap).start+i][(*trap).hold+j].value=' ';
				FC_insert(mapbox);
			}
		if((*trap).type==LRTYPE||(*trap).type==LRTYPE)
			(*trap).present=save_p[0]; 
		else
			(*trap).present=save_p[1];
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
		case UDTYPE:
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
		case DUTYPE:
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
		trap_reco(*trap,player,save);
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
BOOL trap_reco(TRAP trap,Player player[],  int save[]) //아직 다 못만듬
{

	switch(trap.key)
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
		if((player[0].left <=trap.present.right && trap.present.left<=player[0].right) &&
			(player[0].top<=trap.present.bottom && trap.present.top<= player[0].bottom))
		{
			moveLimit(trap,player,save);
		}
		break;
	default:
		return -1;
	}

}
void moveLimit(TRAP trap,Player player[], int save[])
{
	switch(trap.type)
	{
	case LRTYPE:
		if(player[1].left>=trap.present.right)
		{
			player[0].left=trap.present.right;
			player[0].right=player[0].left+PLAYERSIZE;
			player[1].left=player[0].left;
			player[1].right=player[0].right;
			
		}
		else if(player[1].bottom<=trap.present.top)
		{

			player[0].bottom=trap.present.top;
			player[0].top=player[0].bottom-PLAYERSIZE;
			player[1].bottom=player[0].bottom;
			player[1].top=player[0].top;
			for(int k=0; k<3; k++){
				save[k] = 0;
			}
			
		}
		else if(player[1].top>=trap.present.bottom)
		{
			player[0].top=trap.present.bottom;
			player[0].bottom=player[0].top+PLAYERSIZE;
			player[1].top=player[0].top;
			player[1].bottom=player[0].bottom;
			
		}
		else if(player[1].right>=trap.present.left)
		{
			player[0].left=player[1].left-3;
			player[0].right=player[1].right-3;
			player[1].left-=trap.v;
			player[1].right-=trap.v;
			
		}
		
		break;
	case RLTYPE:
		if(player[1].left>=trap.present.right)
		{
			player[0].left=player[1].left+3;
			player[0].right=player[1].right+3;
			player[1].left+=trap.v;
			player[1].right+=trap.v;
		}
		else if(player[1].bottom>=trap.present.top)
		{
			player[0].bottom=trap.present.top;
			player[0].top=player[0].bottom-PLAYERSIZE;
			player[1].bottom=player[0].bottom;
			player[1].top=player[0].top;
			for(int k=0; k<3; k++){
				save[k] = 0;
			}
		}
		else if(player[1].top<=trap.present.bottom)
		{
			player[0].top=trap.present.bottom;
			player[0].bottom=player[0].top+PLAYERSIZE;
			player[1].top=player[0].top;
			player[1].bottom=player[0].bottom;
		}
		else if(player[1].right>=trap.present.left)
		{
			player[0].right=trap.present.left;
			player[0].left=player[0].right-PLAYERSIZE;
			player[1].left=player[0].left;
			player[1].right=player[0].right;
		}
		break;
	case UDTYPE:
		if(player[1].left>=trap.present.right)
		{
			player[0].left=trap.present.right;
			player[0].right=player[0].left+PLAYERSIZE;
			player[1].left=player[0].left;
			player[1].right=player[0].right;
		}
		else if(player[1].bottom>=trap.present.top)
		{
			player[0].bottom=trap.present.top;
			player[0].top=player[0].bottom-PLAYERSIZE;
			player[1].bottom=player[0].bottom;
			player[1].top=player[0].top;
			for(int k=0; k<3; k++){
				save[k] = 0;
			}
		}
		else if(player[1].top<=trap.present.bottom)
		{
			player[0].top=player[1].top;
			player[0].bottom=player[1].bottom;
			player[1].top+=trap.v;
			player[1].bottom+=trap.v;
		}
		else if(player[1].right>=trap.present.left)
		{
			player[0].right=trap.present.left;
			player[0].left=player[0].right-PLAYERSIZE;
			player[1].left=player[0].left;
			player[1].right=player[0].right;
		}
		break;
	case DUTYPE:
		if(player[1].left>=trap.present.right)
		{
			player[0].left=trap.present.right;
			player[0].right=player[0].left+PLAYERSIZE;
			player[1].left=player[0].left;
			player[1].right=player[0].right;
		}
		else if(player[1].bottom>=trap.present.top)
		{
			player[0].bottom=trap.present.top;
			player[0].top=player[0].bottom-PLAYERSIZE;
			player[1].bottom=player[0].bottom;
			player[1].top=player[0].top;
			for(int k=0; k<3; k++){
				save[k] = 0;
			}
		}
		else if(player[1].top<=trap.present.bottom)
		{
			player[0].top=trap.present.bottom;
			player[0].bottom=player[0].top+PLAYERSIZE;
			player[1].top=player[0].top;
			player[1].bottom=player[0].bottom;
		}
		else if(player[1].right>=trap.present.left)
		{
			player[0].right=trap.present.left;
			player[0].left=player[0].right-PLAYERSIZE;
			player[1].left=player[0].left-3;
			player[1].right=player[0].right-3;
		}
		break;
	}
}

