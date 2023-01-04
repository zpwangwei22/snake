#include"snake.h"

void initGame(unsigned int *snakeLife)
{
		//initializing snake
		nFood = 0;
		*snakeLife = 1;
		g_dir = 1;
		P_map = (int*)malloc(sizeof(int)*ROW*COL);
		initSnake();
		//initializeing food
		P_buff = (Point *)malloc(sizeof(Point)*ROW*COL - 2*(COL-2) - 2*ROW - 3);
		initBuff();
		initFood();
		//initializing map
		initMap();
}
void initMap()
{
//		P_map = (int*)malloc(sizeof(int)*ROW*COL);
		for(int i=0;i<ROW;i++)
		{
				for(int j=0;j<COL;j++)
				{
						*(P_map + i*COL + j) = isWhat(i,j);
				}
		}
}
void initSnake()
{
		for(int i=0;i<3;i++)
		{
				insertBody(2, (2+i));
		}
}
void initBuff()
{
//		P_buff = (Point *)malloc(sizeof(Point)*ROW*COL - 2*(COL-2) - 2*ROW - 3);
		s_index = 0;
		for(int i=0; i<ROW; i++)
				for(int j=0; j<COL; j++)
				{
						if(isWhat(i,j) == space)
						{
								P_buff[s_index].row = i;
								P_buff[s_index].col = j;
								s_index ++;
						}
				}
}
void initFood()
{
		int rNum = 0;
		for(int i=0; i<5; i++)
		{
				rNum = rand() % s_index;
				sFood[i].row = P_buff[rNum].row;
				sFood[i].col = P_buff[rNum].col;
		}
}
void insertBody(int row, int col)
{
		sNode *P_new = NULL;
		P_new = (sNode *)malloc(sizeof(sNode));
		P_new->pos.row = row;
		P_new->pos.col = col;
		P_new->next = NULL;
		
		P_new->next = listHead;
		listHead = P_new;
}

void showGame(unsigned int* snakeLife)
{
		system("clear");
		printf("up:'i'		down:'k'		left:'j'		right:'l'		quit:'ESC'  \n");
//		printf("nFood = %d\n", nFood);
		printf("score = %u\n", score);
//		printf("life = %u\n",  *snakeLife);
		for(int i=0; i<ROW; i++)
		{
				for(int j=0; j<COL; j++)
				{
						switch(*(P_map+i*COL+j))
						{
							case wall : 	printf("#");break;
							case space :	printf(" ");break;
							case snake :	printf("@");break;
							case food :		printf("$");break;
						}
				}
				printf("\n");
		}
}

enum map_elem isWhat(int row, int col)
{
		if(row == 0 || row == ROW - 1 || col == 0 || col == COL - 1)
		{
				return wall;
		}
		sNode *tmp = listHead;
		while(tmp != NULL)
		{
				if(tmp->pos.row == row && tmp->pos.col == col)
						return snake;
				tmp = tmp->next;
		}

		for(int i=0; i<5; i++)
		{
				if(sFood[i].row == row && sFood[i].col == col )
						return food;
		}
		
		return space;
		
}

void ctlGame(unsigned int *snakeLife)
{
		char ch;
		changemode(1);
		if(kbhit())
		{
		ch = getchar();
		switch(ch)
		{
				case 'i': g_dir = up;    break;
				case 'k': g_dir = down;  break;
				case 'j': g_dir = left;  break;
				case 'l': g_dir = right; break;
				case 27: *snakeLife = 0;
						  quit();       break;
		}
		}
		changemode(0);
		usleep(180000);
		snakeMove(g_dir,snakeLife);
		if(nFood != 0 && ((nFood % 5) == 0))
		{
				nFood = 0;
				initBuff();
				initFood();
		}
		
		initMap();
		
		sNode *check = NULL;
		check = listHead->next->next->next;
		while(check != NULL)
		{
				if(listHead->pos.row == check->pos.row && listHead->pos.col == check->pos.col)
				{
						*snakeLife = 0;
						quit_f();
						return;
				}
				check = check->next;
		}



}

void snakeMove(enum DIREC dir, unsigned int *snakeLife)
{
//		sNode *m_tmp = NULL;
//		m_tmp = listHead;
//		while(m_tmp->next->next != NULL)
//		{
//				m_tmp = m_tmp->next;
//		}
//		free(m_tmp->next);
//		m_tmp->next = NULL;
//
		int x,y;
		switch(dir)
		{
				case up:
							x = listHead->pos.row - 1;
					    	y = listHead->pos.col;
				   			break;
				case down:
							x = listHead->pos.row + 1;
							y = listHead->pos.col;
							break;
				case left:
							x = listHead->pos.row;
							y = listHead->pos.col - 1;
							break;
				case right:
							x = listHead->pos.row;
							y = listHead->pos.col + 1;
				   
		}

		for(int i=0;i<5;i++)
		{
				if(x == sFood[i].row && y == sFood[i].col)
				{
						insertBody(x,y);
						sFood[i].row += ROW*COL;
						sFood[i].col += ROW*COL;
						nFood++;
						score++;
				}
		}

		if((isWhat(x,y) == space) || (isWhat(x,y) == snake))
		{
				sNode *m_tmp = NULL;
				m_tmp = listHead;
				while(m_tmp->next->next != NULL)
				{
						m_tmp = m_tmp->next;
				}
				free(m_tmp->next);
				m_tmp->next = NULL;
				insertBody(x,y);
		}
		if(isWhat(x,y) == wall)
		{
				*snakeLife = 0;
				quit_f();
				
		}
//		if(isWhat(listHead->pos.row,listHead->pos.col) == snake)
//		{
//				*snakeLife = 0;
//		}

}

void changemode(int n_dir)
{
  static struct termios oldt, newt;

  if (n_dir == 1 )
  {
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  }
  else
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

int kbhit (void)
{
  struct timeval tv;
  fd_set rdfs;

  tv.tv_sec = 0;
  tv.tv_usec = 0;

  FD_ZERO(&rdfs);
  FD_SET (STDIN_FILENO, &rdfs);

  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &rdfs);

}
void quit()
{
		printf("The game is terminated!\n");
        printf("Good Game,you got %d points!\n", score);
}
void quit_f()
{
        printf("-------  OOOOOPS!!!  -----------\n");
        printf("Good Game,you got %d points!\n", score);
}



