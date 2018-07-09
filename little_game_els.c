#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include "./keyboard/keyboard.h"

#define FC 5 //qian jing yan se 
#define BC 7 //bei jing yan se
#define H 20 //bei jing de gao
#define W 10 //bei jing de kuang

struct data
{
	int x;
	int y;
};

struct data t = {5,0};//xia luo qi shi wei zhi
int background[H][W] = {};

struct shape
{
	int s[5][5];
};


struct shape shape_arr[7] = { //zhuang tu an
{
	0,0,0,0,0,
	0,0,1,0,0,
	0,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0,
},
{
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,1,1,0,0,
	0,0,0,0,0,
},
{
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,1,0,
	0,0,0,0,0,
},
{
	0,0,0,0,0,
	0,0,1,1,0,
	0,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
},
{
	0,0,0,0,0,
	0,1,1,0,0,
	0,0,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0,
},
{
	0,0,0,0,0,
	0,1,1,0,0,
	0,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
},
{
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
}
};

void drow_element(int x,int y,int c)
{
	x *= 2;
	x++;
	y++;
	
	printf("\033[?25l");
	printf("\033[%d;%dH",y,x);
	printf("\033[3%dm\033[4%dm",c,c);
	printf("[]");
	fflush(stdout);
	printf("\033[0m");
}

void drow_back(void)
{
	int i = 0;
	int j =0;
	for(;i<H;i++)
	{
		for(j = 0; j<W; j++)
            if(background[i][j] == 0)
			    drow_element(j,i,BC);
            else
                drow_element(j,i,FC);
	}
}

void set_back(struct data* t,struct shape p)
{
    int i = 0;
    int j = 0;
    for(; i<5; i++)
        for(j = 0; j<5; j++)
        {
            if(p.s[i][j] != 0)
                background[t->y+i][t->x+j] = 1;
        }
}

void drow_shape(int x, int y, struct shape p,int c)
{
	int i = 0;
	int j = 0;
	for(;i<5; i++)
	{
		for(j = 0;j<5;j++)
		{
			if(p.s[i][j] != 0)
				drow_element(x+j,y+i,c);
		}
	}
}

int can_move(int x,int y, struct shape p)
{
    int i = 0;
    int j = 0;
    for(; i<5; i++)
    {
        for(j = 0; j<5; j++)
        {
            if(p.s[i][j] == 0)
                continue;
            if(x+j >= W)
                return 0;
            if(y+i >= H)
                return 0;
            if(x+j < 0)
                return 0;
            if(background[y+i][x+j]!=0)
                return 0;
        }
    }
    return 1;
}

void mclean_line(void)
{
    for(int i = 0; i<H; i++)
    {
        int total = 0;
        for(int j = 0; j<W; j++)
        {
            if(background[i][j] != 0)
                total++;
        }
        if(total == W)
        {
            for(int k = i; k>0; k--)
            {
                memcpy(background[k],background[k-1],sizeof(background[k]));
            }
            memset(background[0],0X00,sizeof(background[0]));
        }
    }
}

void tetris_timer(struct data* t)
{
	drow_shape(t->x,t->y,shape_arr[0],BC);
	if(can_move(t->x,t->y+1,shape_arr[0]))
         t->y++;
    else
    {
        set_back(t,shape_arr[0]);
        mclean_line();
        drow_back();
        t->y = 0;
    }
	drow_shape(t->x,t->y,shape_arr[0],FC);
}

struct shape turn_90(struct shape p)
{
    struct shape t;
    int i = 0;
    int j = 0;
    for(; i<5; i++)
    {
        for(j = 0; j<5; j++)
        {
            t.s[i][j] = p.s[4-j][i];
        }
    }
    return t;
}

int tetris(struct data* t)
{
	int ret = 0;
	int c = get_key();
    if(is_up(c))
    {
		drow_shape(t->x,t->y,shape_arr[0],BC);
        shape_arr[0] = turn_90(shape_arr[0]);
	    if(can_move(t->x,t->y,shape_arr[0]) == 0)
        {
            shape_arr[0] = turn_90(shape_arr[0]);
            shape_arr[0] = turn_90(shape_arr[0]);
            shape_arr[0] = turn_90(shape_arr[0]);

        }
        drow_shape(t->x,t->y,shape_arr[0],FC);
    }
    else if(is_left(c))
	{
		drow_shape(t->x,t->y,shape_arr[0],BC);
	    if(can_move(t->x-1,t->y,shape_arr[0]))
            t->x--;
        drow_shape(t->x,t->y,shape_arr[0],FC);
	}
    else if(is_right(c))
    {
        drow_shape(t->x,t->y,shape_arr[0],BC);
	    if(can_move(t->x+1,t->y,shape_arr[0]))
             t->x++;
        drow_shape(t->x,t->y,shape_arr[0],FC);
    }
    else if(is_down(c))
    {
		drow_shape(t->x,t->y,shape_arr[0],BC);
	    if(can_move(t->x,t->y+1,shape_arr[0]))
            t->y++;
        drow_shape(t->x,t->y,shape_arr[0],FC);
    }
    else if(is_esc(c))
        ret = 1;
    return ret;
}

void handler(int s)
{
    if(s == SIGALRM)
         tetris_timer(&t);
    else if(s == SIGINT)
    {
        printf("\033[?25h");
        recover_keyboard();
        exit(0);
    }
}

int main()
{
    init_keyboard();
	drow_back();
	
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM,&act,NULL);
    sigaction(SIGINT,&act,NULL);

    struct itimerval it;
    it.it_value.tv_sec = 0;
    it.it_value.tv_usec = 1;
    it.it_interval.tv_sec = 1;
    it.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL,&it,NULL);

    while(1)
	{
        if(tetris(&t)==1)
            break;
	}

	printf("\033[?25h");
    recover_keyboard();
	return 0;
}
