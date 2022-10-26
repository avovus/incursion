#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdlib.h>

#include "Copter.hpp"
#include "Rocket.hpp"
#include "Constants.hpp"
#include "Player.hpp"

using namespace std;

Copter::Copter(
	int x, int y, bool direction, int speed,
	SDL_Renderer* gRenderer, SDL_Texture* copterTexture,int timer,
	bool needSpawnChild, int randMin, int randMax)
	: Mob({ x, y, Copter::W, Copter::H })
{
	this->timer = timer;
	this->randMax = randMax;
	this->randMin = randMin;
	this->direction = direction;
	this->gRenderer = gRenderer;
	this->speed = speed;
	this->playerY = playerY;
	this->needSpawnChild = needSpawnChild;
	texture = copterTexture;
}

Mob* Copter::spawnChild(SDL_Texture* childTexture, long long timer,int sec){
	if(needSpawnChild){
		if(timer <= 45){
			if(!sec && timer%5 == 0){
				return new Rocket(quad.x, quad.y+10, -3, gRenderer, childTexture);
			}
		}
		else if(timer <= 90){
			if(!sec && timer%3 == 0){
				return new Rocket(quad.x, quad.y+10, -3, gRenderer, childTexture);
			}
		}
		else{
			if(!sec && timer%2 == 0){
				return new Rocket(quad.x, quad.y+10, -3, gRenderer, childTexture);
			}
		}
	}
	return NULL;
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
