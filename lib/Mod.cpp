#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

#include "Mod.hpp"
#include "Constants.hpp"

using namespace std;

Mod::Mod( int x, int y,
	int speed, SDL_Renderer* gRenderer, SDL_Texture* modTexture, bool nKill)
	: Mob({ x, y, Mod::W, Mod::H })
{
	this->gRenderer = gRenderer;
	this->nKill = nKill;
	texture = modTexture;
	this->speed = speed;
	quad.y = 50 + rand() % 450;
}

int Mod::amountLivesToChange(){
	if(!nKill)
		return 1;
	else{
		return 0;
	}
}

bool Mod::isCollidable(){
    return true;
}

bool Mod::needKill(){
    return nKill;
}

bool Mod::needBoom(){
    return false;
}

void Mod::move(){
	step++;
	if(step == 2){
		quad.x -= speed;
		step = 0;
	}
	if(quad.x+quad.w <= 0){
		destroy();
	}
}

void Mod::render(){
	SDL_RenderCopy( gRenderer, texture, NULL, &quad );
}
