#include "header/brickmanager.h"
#include "header/brick.h"
#include "header/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define NBR_BRIQUE 1
#define WIDTH 40
#define HEIGHT 40
#define BRICK_WIDTH 10
#define BRICK_HEIGHT 4
#define BALL_CHAR 'o'

void init(BrickManager* brickManager){
	Brick* brique;
	brique = (Brick*) malloc (NBR_BRIQUE * sizeof(Brick));
	brique[0] = createBrick(WIDTH/2-BRICK_WIDTH, HEIGHT/2, BRICK_WIDTH, BRICK_HEIGHT);
	brique[1] = createBrick(WIDTH/2, HEIGHT/2, BRICK_WIDTH, BRICK_HEIGHT);
	brique[2] = createBrick(WIDTH/2+BRICK_WIDTH, HEIGHT/2, BRICK_WIDTH, BRICK_HEIGHT);
	brickManager->brique = brique;
	Ball* ball = initBall(WIDTH/2, 1);
	brickManager->ball = ball;
}

Brick* getBriqueArray(BrickManager* brickManager){
	return brickManager->brique;
}

void tick(BrickManager* brickManager){
	Ball* ball = brickManager->ball;
	Brick* brick = getTouchingBrick(ball->coords[0], ball->coords[1], brickManager);
	printf("%p", brick);
	if(brick != NULL){
		int* normalVec = normal(brick, ball->coords[0], ball->coords[1]);
		int* vecD = ball->vecd;
		int* vecN = calloc(2, sizeof(int));
		double dProduct = dot(vecD, vecN);
		// Reflection (utilisé dans les calculs de lumières)
		vecN[0] = vecD[0] - 2 * dProduct * normalVec[0];
		vecN[1] = vecD[1] - 2 * dProduct * normalVec[1];
		ball->vecd = vecN;
		move(ball);
	}else if(isBorder(ball, 0, 0, WIDTH, HEIGHT)){
		int* vec = (int*) calloc(2, sizeof(int));
		if(ball->coords[0] <= 1){
			vec[0] = 1;vec[1] = 0;
		}else if(ball->coords[0] >= (WIDTH-1)){
			vec[0] = -1;vec[1] = 0;
		}else if(ball->coords[1] >= (HEIGHT-1)){
			vec[0] = 0;vec[1] = 1;
		}else{
			vec[0] = 0;vec[1] = -1;
		}
		int* vecD = ball->vecd;
		int* vecN = calloc(2, sizeof(int));
		double dProduct = dot(vecD, vecN);
		vecN[0] = vecD[0] - 2 * dProduct * normalVec[0];
		vecN[1] = vecD[1] - 2 * dProduct * normalVec[1];
		ball->vecd = vecN;
		move(ball);
	}else{
		move(ball);
	}
}

Brick* getTouchingBrick(int x, int y, BrickManager* brickManager){
	for (int i = 0; i < NBR_BRIQUE; ++i)
	{
		Brick* brick = malloc(sizeof(Brick));
		brick = &(brickManager->brique[i]);
		if(isTouching(brick, x, y)){
			printf("TOUCHING at x:%i, :%i", x, y);
			return brick;
		}
	}
	Brick* brick = NULL;
	return brick;
}

void display(BrickManager* brickManager){
	char affichage[WIDTH][HEIGHT];
	for (int i = 0; i < WIDTH; ++i){
		for (int j = 0; j < HEIGHT; ++j){
			affichage[i][j] = ' ';
		}
	}
	// =================================================================== Affichage des briques
	for (int ii = 0; ii < NBR_BRIQUE; ++ii){
		Brick brick = brickManager->brique[ii];
		for (int i = -(brick.width/2); i < (brick.width/2); ++i){
			for (int j = -(brick.height/2); j < (brick.height/2); ++j){
				if(brick.setup == 1){
					affichage[brick.x+i][brick.y+j] = '=';
				}else{
					break;
				}
			}
		}
	}
	// =================================================================== Affichage de la balle
	Ball* ball = brickManager->ball;
	affichage[ball->coords[0]][ball->coords[1]] = BALL_CHAR;

	for (int i = HEIGHT-1; i >= 0; --i){
		for (int j = 0; j < WIDTH; ++j){
			printf("%c", affichage[j][i]);
		}
		printf("\n");
	}
}
