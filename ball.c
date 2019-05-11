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

int isBorder(Ball* ball, int mx, int my, int max, int may){
	if(ball->coords[0] >= (mx+1) && ball->coords[0] <= (max-1)
			&& ball->coords[1] >= (my+1) && ball->coords[0] <= (may-1)){
				return 0;
			}
		return 1;
}

void move(Ball* ball){
	ball->coords[0] += ball->vecd[0];
	ball->coords[1] += ball->vecd[1];
	printf("x: %i, y: %i\n", ball->coords[0], ball->coords[1]);
	printf("dx: %i, dy: %i\n", ball->coords[0] + ball->vecd[0], ball->coords[1] + ball->vecd[1]);
	printf("vecx: %i, vecy: %i\n", ball->vecd[0], ball->vecd[1]);
}
