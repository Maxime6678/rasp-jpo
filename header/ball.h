#ifndef BALL_H_
#define BALL_H_
typedef struct Ball
{
	int* coords;
	int* vecd;
} Ball;
#endif
Ball* initBall(int x, int y);

int isBorder(int mx, int my, int max, int may);

void move(Ball* ball);
