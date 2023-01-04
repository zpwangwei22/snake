#include"snake.h"


unsigned int* snakeLife;
int main()
{


		int * P_map = NULL;
		sNode * listHead = NULL;
		Point sFood[5] = {0};
		Point *P_buff = NULL;
		int s_index = 0;
		enum DIREC g_dir = 1;
		unsigned int nFood = 0;
		snakeLife = (unsigned int*)malloc(sizeof(unsigned int));
		score = 0;
		srand((unsigned int)time(NULL));
		initGame(snakeLife);
		while(*snakeLife != 0)
		{
				showGame(snakeLife);
				ctlGame(snakeLife);
		}

		free(snakeLife);
		snakeLife = NULL;




		return 0;
}
