#include "header/brick.h"
#include <stdio.h>
#include <stdlib.h>

int exist(Brick* brick){
	return brick->hp == 0;
}

Brick createBrick(int x, int y, int width, int height){
	Brick b;
	b.x = x;
	b.y = y;
	b.width = width;
	b.height = height;
	b.maxHP = 1;
	b.hp = b.maxHP;
	b.setup = 1;
	return b;
}

int* normal(Brick* brick, int x, int y){
	int dm_x = x-(brick->width/2)-1;
	int dma_x = x+(brick->width/2)+1;
	int dm_y = y-(brick->height/2)-1;
	int dma_y = y+(brick->height/2)+1;
	int* vec = (int*) calloc(2, sizeof(int));

	if(dma_y < brick->y){
		// vector (array)
		//  x          y
		vec[0] = 0;vec[1] = 1;
		return vec;
	}
	if(dma_x < brick->x){
		// vector (array)
		//  x          y
		vec[0] = 1;vec[1] = 0;
		return vec;
	}
	if(dm_x > brick->x){
		// vector (array)
		//  x          y
		vec[0] = -1;vec[1] = 0;
		return vec;
	}
	// vector (array)
	//  x          y
	vec[0] = 0;vec[1] = -1;
	return vec;
}

int isTouching(Brick* brick, int x, int y){
	int dm_x = brick->x-(brick->width/2)-1;
	int dma_x = brick->x+(brick->width/2)+1;
	int dm_y = brick->y-(brick->height/2)-1;
	int dma_y = brick->y+(brick->height/2)+1;
	if((x > dm_x-1
		&& x < dma_x+1
		&& y > dm_y-1
		&& y < dma_y-1)){
			printf("x:%i y:%i dx:%i dmx:%i dy:%i dmy:%i\n", x, y, dm_x, dma_x, dm_y, dma_y);
			return 1;
	}else{
			return 0;
	}
}

void afficheBrick(Brick* brick){
	printf("Brique[x=%i, y=%i, hp=%i]", brick->x, brick->y, brick->hp);
}
