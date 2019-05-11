#include <stdlib.h>
#include <stdio.h>
//#include <wiringPi.h>
#include <unistd.h>

#include "header/ball.h"
#include "header/brick.h"
#include "header/cursor.h"
#include "header/brickmanager.h"

#define LEDVERTE 26
#define LEDROUGE 22
#define TAILLE 8
#define DROITE 29
#define GAUCHE 21
#define DELAY 1250

const int arr[] = {7, 0, 1, 2, 3, 4, 5, 6};
int run = 1;
BrickManager brickManager;
void setup(){
	init(&brickManager);
	while(run){
		tick(&brickManager);
		display(&brickManager);
		sleep(1);
	}
}

void clear(){

}

void stop(){
	run = 0;
}


void loop(){

}
int main(){
	//wiringPiSetup();
	//pinMode(DROITE, INPUT);
	//pinMode(GAUCHE, INPUT);
	setup();
	return 0;
}
