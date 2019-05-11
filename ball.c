#include "header/ball.h"
#include <stdlib.h>
#include <malloc.h>

Ball* initBall(int x, int y){
	Ball* b = malloc(sizeof(Ball));
	b->coords = (int*) calloc(2, sizeof(int));
	b->coords[0] = x;
	b->coords[1] = y;
	b->vecd = (int*) calloc(2, sizeof(int));
	b->vecd[0] = 0;
	b->vecd[1] = 1;
	return b;
}

void move(Ball* ball){
	ball->coords[0] += ball->vecd[0];
	ball->coords[1] += ball->vecd[1];
	printf("x: %i, y: %i\n", ball->coords[0], ball->coords[1]);
	printf("dx: %i, dy: %i\n", ball->coords[0] + ball->vecd[0], ball->coords[1] + ball->vecd[1]);
	printf("vecx: %i, vecy: %i\n", ball->vecd[0], ball->vecd[1]);
}
