#ifndef __SNAKE_H__
#define __SNAKE_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>


#define		ROW 	30
#define		COL 	60
enum map_elem 
{
		space, wall, snake, food
};
enum DIREC
{
		left, right, up, down
};
struct myPoint
{
		int row;
		int col;
};
typedef struct myPoint Point;
typedef struct SnakeNode
{
	Point pos;
	struct SnakeNode *next;
}sNode;
Point sFood[5];
Point *P_buff;
sNode *listHead;
enum DIREC g_dir;
int *P_map;
int s_index;
unsigned int nFood;
unsigned int score;


extern void initMap();
extern void initSnake();
extern void initFood();
extern void initBuff();
extern void initGame(unsigned int*);
extern void showGame(unsigned int*);
extern void ctlGame(unsigned int*);
extern enum map_elem isWhat(int, int);
extern void insertBody(int , int);
extern void snakeMove(enum DIREC, unsigned int*);
extern void quit();
extern void quit_f();
extern void changemode(int);
extern int kbhit();


















#endif


