#include "brick.h"
#include "ball.h"
#include "cursor.h"

#ifndef BRICKMANAGER_H_
#define BRICKMANAGER_H_
typedef struct BrickManager
{
	Brick* brique;
	Ball* ball;
	Cursor* cursor;
	int* lose;

}BrickManager;
#endif

void init(BrickManager* brickManager, int* lose);

void tick(BrickManager* brickManager);

Brick* getBriqueArray(BrickManager* brickManager);

void display(BrickManager* brickManager);

Brick* getTouchingBrick(int x, int y, BrickManager* brickManager);

int isNotEmpty(BrickManager* brickManager);
