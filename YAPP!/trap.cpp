
#include "stdafx.h"
#include "YAPP!.h"
#include "gamedef.h"
	
void trapf(TRAP *trap, Player *player, char (*map)[WIDTH], MapBox (*mapbox)[WIDTH], int save[])
{
	Box save_p[2]={{trap[0].start*BOXSIZE,trap[0].hold*BOXSIZE,trap[0].start*BOXSIZE+BOXSIZE*trap[0].val,trap[0].hold*BOXSIZE+BOXSIZE*trap[0].hor},
	{trap[0].hold*BOXSIZE,trap[0].start*BOXSIZE,trap[0].hold*BOXSIZE+BOXSIZE*trap[0].val,trap[0].start*BOXSIZE+BOXSIZE*trap[0].hor}};

	if( trap[0].count != 1&& trap[0].count != 2 && recognizer(trap[0].reco,*player))						//인식범위 좌측 우측모두 0부터시작
	{
		for(int i=0;i<trap[0].hor;i++)
			for(int j=0;j<trap[0].val;j++)				//지우는 것
			{
				map[trap[0].start+i][trap[0].hold+j]=' ';
				mapbox[trap[0].start+i][trap[0].hold+j].value=' ';
				FC_insert(mapbox);
			}
		if(trap[0].type==LRTYPE||trap[0].type==LRTYPE)
			trap[0].present=save_p[0]; 
		else
			trap[0].present=save_p[1];
		trap[0].count=1;
	}
	if(trap[0].count==1)
	{
		switch(trap[0].type)
		{
		case RLTYPE:
			if(trap[0].present.left<trap[0].end*BOXSIZE)		
			{
				trap[0].present.left+=trap[0].v;
				trap[0].present.right+=trap[0].v;
				trap[0].v+=trap[0].ac;
				if(trap[0].present.left>=trap[0].end*BOXSIZE)
				{
					trap[0].count=2;
				}
			}
			break;
		case UDTYPE:
			if(trap[0].present.top<trap[0].end*BOXSIZE)		
			{
				trap[0].present.top+=trap[0].v;
				trap[0].present.bottom+=trap[0].v;
				trap[0].v+=trap[0].ac;
				if(trap[0].present.top>=trap[0].end*BOXSIZE)
				{
					trap[0].count=2;
				}
			}
			break;
		case LRTYPE:

			if(trap[0].present.left>trap[0].end*BOXSIZE)		
			{
				trap[0].present.left-=trap[0].v;
				trap[0].present.right-=trap[0].v;
				trap[0].v+=trap[0].ac;
				if(trap[0].present.left<=trap[0].end*BOXSIZE)
				{
					trap[0].count=2;
				}
			}
			break;
		case DUTYPE:
			if(trap[0].present.top>trap[0].end*BOXSIZE)		
			{
				trap[0].present.top-=trap[0].v;
				trap[0].present.bottom-=trap[0].v;
				trap[0].v+=trap[0].ac;
				if(trap[0].present.top<=trap[0].end*BOXSIZE)
				{
					trap[0].count=2;
				}
			}
			break;
		}
		trap_reco(*trap,player,save);
/*			
		if(trap[0].end>trap[0].start)					//만약 위에서 아래, 좌에서 우로 이동시	
		{
			if(trap[0].present<trap[0].end*BOXSIZE)		
			{
				trap[0].present+=trap[0].v;
				trap[0].v+=trap[0].ac;
				if(trap[0].present>=trap[0].end*BOXSIZE)
				{
					trap[0].count=2;
				}
			}
		}
		else if(trap[0].end<trap[0].start)			//만약 아래에서 위, 우에서 좌로 이동시
		{
			if(trap[0].present>trap[0].end*BOXSIZE)		
			{
				trap[0].present-=trap[0].v;
				trap[0].v+=trap[0].ac;
				if(trap[0].present<=trap[0].end*BOXSIZE)
				{
					trap[0].count=2;
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

