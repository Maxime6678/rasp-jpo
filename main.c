#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <pthread.h>

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
#define WIDTH 90

const int arr[] = {7, 0, 1, 2, 3, 4, 5, 6};
int run = 1;
BrickManager brickManager;
int lose = 0;
pthread_t displayTh;
char pseudo[8];
FILE* HS;

void* displayThread(){
	while(run){
		tick(&brickManager);
		usleep(75 * 1000);
		if(digitalRead(GAUCHE) == 0){
			if(brickManager.cursor->x >=((brickManager.cursor->width/2)+0)){
				brickManager.cursor->x-=2;
			}
			continue;
		}
		if(digitalRead(DROITE) == 0){
			if(brickManager.cursor->x <= (WIDTH-2-(brickManager.cursor->width/2))){
				brickManager.cursor->x+=2;
			}
		}
	}
}

void setup(){
	
	init(&brickManager, &lose);
	// TODO Thread affichage et main thread la ou on recupère les entrées
	if(pthread_create(&displayTh, NULL, displayThread, NULL) == -1){
		printf("Erreur: impossible de créer le thread\n");
		exit(1);
		return;
	}
	while(run){
		display(&brickManager);
		if(isNotEmpty(&brickManager) != 1){
			run =0;
		}
		usleep(100 * 1000);
	}
	printf("%i", lose);
	if(lose) {
		system("clear");
		printf("Perdu\n");
		printf("%s",pseudo);
		char* ligne = NULL;
		size_t taille = 0;
		//printf("Le contenu du fichier est:\n");
		//getline(&ligne, &taille, HS);
		//printf("%s", ligne);
	}
}

void clear(){

}

void stop(){
	for (int i = 0; i < TAILLE; ++i)
	{
		if (digitalRead(arr[i])==HIGH){
			digitalWrite(arr[i],LOW);
		}
	}
	if (digitalRead(LEDVERTE)==HIGH){
		digitalWrite(LEDVERTE,LOW);
	}
}


void loop(){

}
int main(){
	wiringPiSetup();
	pinMode(DROITE, INPUT);
	pinMode(GAUCHE, INPUT);
	pinMode(LEDROUGE, OUTPUT);
	pinMode(LEDVERTE, OUTPUT);
	for (int i = 0; i < TAILLE; ++i)
	{
		pinMode(arr[i], OUTPUT);
	}
	printf("Veuillez entrer votre nom : (moins de 8 lettres)\n");
	HS = fopen("HSFile","rw");
	for (int i = 0; i < 8; ++i)
	{
		pseudo[i]=getchar();
	}
	fprintf(HS,"%s",pseudo);
	setup();
	stop();
	return 0;
}
