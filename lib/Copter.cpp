#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdlib.h>

#include "Copter.hpp"
#include "Constants.hpp"

using namespace std;

Copter::Copter(
	int x, int y, bool direction, int speed,
	SDL_Renderer* gRenderer, SDL_Texture* copterTexture,int randMin, int randMax)
	: Mob({ x, y, Copter::W, Copter::H })
{
	this->randMax = randMax;
	this->randMin = randMin;
	this->direction = direction;
	this->gRenderer = gRenderer;
	texture = copterTexture;
	this->speed = speed;
}


void Copter::moveVer(){
	if(fly_up){
		if(quad.y >= 30){
			step++;
			if(step == 3){
				quad.y -= speed;
				step = 0;
			}
		}
		else{
			fly_up = false;
		}
	}
	else{
		if(quad.y+quad.h <= SCREEN_H-100){
			step++;
			if(step == 3){
				quad.y += speed;
				step = 0;
			}
		}
		else{
			fly_up = true;
		}
	}
}

void Copter::moveHor(){
	srand(time(0));
	quad.x += speed;
	if(speed < 0){
		if(quad.x+quad.w <= 0){
			quad.x = SCREEN_W+quad.w;
//			quad.y = rand(SCREEN_H/2-200,SCREEN_H/2+200);
			quad.y = randMin + rand() % randMax;
		}
	}
	else{
		if(quad.x >= SCREEN_W){
			quad.x = 0-quad.w;
//			quad.y = rand(SCREEN_H/2-200,SCREEN_H/2+200);
			quad.y = randMin + rand() % randMax;
		}
	}
}

void Copter::move(){
	if(direction == 0){
		moveHor();
	}
	else{
		moveVer();
	}
}

void Copter::render(){
	SDL_RenderCopy( gRenderer, texture, NULL, &quad );
}
