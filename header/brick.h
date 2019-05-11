#ifndef BRICK_H_
#define BRICK_H_
typedef struct Brick
{
	int x;
	int y;
	int width;
	int height;
	int maxHP;
	int hp;
	int setup;
} Brick;
#endif

Brick createBrick(int x, int y, int width, int height);

int* normal(Brick* brick, int x, int y);

int isTouching(Brick *brick, int x, int y);

int exist(Brick* brick);

void afficheBrick(Brick* brick);
