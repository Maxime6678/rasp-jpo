#include "header/brickmanager.h"
#include "header/brick.h"
#include "header/util.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <wiringPi.h>
#include <unistd.h>

// COULEUR
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[40m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define LEDVERTE 26
#define LEDROUGE 22
const int baro[] = {7, 0, 1, 2, 3, 4, 5, 6};


// CONST
#define NBR_BRIQUE 8
#define WIDTH 90
#define HEIGHT 40
#define BRICK_WIDTH 10
#define BRICK_HEIGHT 4
#define BALL_CHAR 'o'

void init(BrickManager* brickManager, int* lose){
	Brick* brique;
	brique = (Brick*) malloc (NBR_BRIQUE * sizeof(Brick));
	brique[0] = createBrick(WIDTH/2-BRICK_WIDTH, HEIGHT/2, BRICK_WIDTH, BRICK_HEIGHT);
	brique[1] = createBrick(WIDTH/2, HEIGHT/2, BRICK_WIDTH, BRICK_HEIGHT);
	brique[2] = createBrick(WIDTH/2+BRICK_WIDTH, HEIGHT/2, BRICK_WIDTH, BRICK_HEIGHT);
	brique[3] = createBrick(WIDTH/2+(BRICK_WIDTH*2), HEIGHT/2, BRICK_WIDTH, BRICK_HEIGHT);
	brique[4] = createBrick(WIDTH/2+(BRICK_WIDTH*2), HEIGHT/2-BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT);
	brique[5] = createBrick(WIDTH/2-BRICK_WIDTH, HEIGHT/2-BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT);
	brique[6] = createBrick(WIDTH/2, HEIGHT/2-BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT);
	brique[7] = createBrick(WIDTH/2+BRICK_WIDTH, HEIGHT/2-BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT);
	for(int i = 0; i < 8; ++i){
		brique[i].hp = random_int(1, 4);
	}
	for (int i = 0; i < 8; ++i)
	{
		digitalWrite(baro[i],HIGH);
	}
	brickManager->brique = brique;
	brickManager->lose = lose;
	Ball* ball = initBall(WIDTH/2, 4);
	brickManager->ball = ball;
	Cursor* cursor;
	cursor = (Cursor*) malloc(sizeof(Cursor));
	initCursor(cursor, WIDTH);
	brickManager->cursor = cursor;
}

Brick* getBriqueArray(BrickManager* brickManager){
	return brickManager->brique;
}

int random_int(int min, int max) 
{
   return min + rand() % (max - min);
}

void tick(BrickManager* brickManager){
	Ball* ball = brickManager->ball;
	Brick* brick = getTouchingBrick(ball->coords[0], ball->coords[1], brickManager);
	Cursor* cursor = brickManager->cursor;
	if(brick != NULL){
		int* normalVec = normal(brick, ball->coords[0], ball->coords[1]);
		int* vecD = ball->vecd;
		int* vecN = calloc(2, sizeof(int));
		double dProduct = dot(vecD, normalVec);
		// Reflection (utilisé dans les calculs de lumières)
		//printf("%L\n", dProduct);
		vecN[0] = vecD[0] - 2 * dProduct * normalVec[0];
		vecN[1] = vecD[1] - 2 * dProduct * normalVec[1];
		//printf("VECX(x:%i,y:%i), VECX2(x:%i,y:%i)\n",vecD[0], vecD[1], vecN[0], vecN[1]);
		ball->vecd = vecN;
		brick->hp = brick->hp - 1;
		move(ball);
	}else if(isBorder(ball, 0, 0, WIDTH, HEIGHT)){
		//printf("Touching borders\n");
		int* normalVec = (int*) calloc(2, sizeof(int));
		//Game over
		if(ball->coords[1] <= 1){
			for (int b = 0; b < NBR_BRIQUE; ++b){
				brickManager->brique[b].hp = 0;
			}
			//printf("%i", *(brickManager->lose));
			*(brickManager->lose) = 1;
			//printf("%i", *(brickManager->lose));
			return;
		}
		if(ball->coords[0] <= 1){
			normalVec[0] = 1;normalVec[1] = 0;
		}else if(ball->coords[0] >= (WIDTH-1)){
			normalVec[0] = -1;normalVec[1] = 0;
		}else if(ball->coords[1] >= (HEIGHT-1)){
			normalVec[0] = 0;normalVec[1] = 1;
		}else{
			normalVec[0] = 0;normalVec[1] = -1;
		}
		int* vecD = ball->vecd;
		int* vecN = calloc(2, sizeof(int));
		double dProduct = dot(vecD, normalVec);
		vecN[0] = vecD[0] - 2 * dProduct * normalVec[0];
		vecN[1] = vecD[1] - 2 * dProduct * normalVec[1];
		ball->vecd = vecN;
		move(ball);
	}else if(isBorderCursor(cursor, brickManager)){
		int* normalVec = (int*) calloc(2, sizeof(int));
		normalVec[0] = 0; normalVec[1] = 1;
		int* vecD = ball->vecd;
		int* vecN = calloc(2, sizeof(int));
		double dProduct = dot(vecD, normalVec);
		vecN[0] = vecD[0] - 2 * dProduct * normalVec[0];
		vecN[1] = vecD[1] - 2 * dProduct * normalVec[1];
		ball->vecd = vecN;
		move(ball);
	}else{
		move(ball);
	}
}

int isBorderCursor(Cursor* cursor, BrickManager* brickManager){
	// x-taille/2
	// x+taille/2
	// y 0
	// y hauteur
	if(brickManager->ball->coords[0] > (cursor->x - cursor->width/2)
		&& brickManager->ball->coords[0] < (cursor->x + cursor->width/2)
		&& brickManager->ball->coords[1] > 0
		&& brickManager->ball->coords[1] < (cursor->height+1)) {
		return 1;
	}
	return 0;
}

Brick* getTouchingBrick(int x, int y, BrickManager* brickManager){
	//printf("x:%i y:%i\n",x,y);
	for (int i = 0; i < NBR_BRIQUE; ++i)
	{
		Brick* brick = malloc(sizeof(Brick));
		brick = &(brickManager->brique[i]);
		if(isTouching(brick, x, y) && brick->hp != 0){
			//printf("TOUCHING at x: %i, y: %i\n", x, y);
			return brick;
		}
	}
	Brick* brick = NULL;
	return brick;
}

void display(BrickManager* brickManager){
	char affichage[WIDTH][HEIGHT];
	system("clear");
	for (int i = 0; i < WIDTH; ++i){
		for (int j = 0; j < HEIGHT; ++j){
			if(j == 0 || j == (HEIGHT-1)){
				affichage[i][j] = '=';
			}else{
				affichage[i][j] = ' ';
			}
		}
	}
	// =================================================================== Affichage des briques
	for (int ii = 0; ii < NBR_BRIQUE; ++ii){
		Brick brick = brickManager->brique[ii];
		if(brick.hp == 0)continue;
		int w = brick.width/2;
		int h = brick.height/2;
		for (int i = -w; i < w; ++i){
			for (int j = -h; j < h; ++j){
				if(brick.setup != 1)return;
				if(i == 0 && j == 0){
					affichage[brick.x+i][brick.y+j] = brick.hp+'0';
				}else if(i == -w || i == w-1){
					affichage[brick.x+i][brick.y+j]='|';
				}else if(j == -h || j == h-1){
					affichage[brick.x+i][brick.y+j]='=';
				}else{
					affichage[brick.x+i][brick.y+j]=' ';
				}

				//affichage[brick.x+i][brick.y+j] = '=';

			}
		}
	}
	// =================================================================== Affichage de la balle
	Ball* ball = brickManager->ball;
	affichage[ball->coords[0]][ball->coords[1]] = BALL_CHAR;
	// =================================================================== Affichage de la cursor
	Cursor* cursor = brickManager->cursor;
	int w = cursor->width/2;
	int h = cursor->height;
	for(int i = -w; i < w; ++i){
		for(int j = 0; j < h; ++j){
			affichage[cursor->x+i][j+1] = '-';
		}
	}
	for (int i = HEIGHT-1; i >= 0; --i){
		printf("|");
		for (int j = 0; j < WIDTH; ++j){
			printf("%c", affichage[j][i]);
		}
		printf("|");
		printf("\n");
	}
		for (int b = 0; b < NBR_BRIQUE; ++b){
		Brick brick = brickManager->brique[b];
		if(brick.hp == 0){
			if(digitalRead(baro[b])==HIGH){
				digitalWrite(baro[b],LOW);
			}
		}
	}
}
int isNotEmpty(BrickManager* brickManager){
		for (int b = 0; b < NBR_BRIQUE; ++b)
		{
			Brick brick = brickManager->brique[b];
			if(brick.hp >= 1){
				return 1;
		}
	}
	return 0;
}
