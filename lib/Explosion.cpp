#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

#include "Explosion.hpp"
#include "Constants.hpp"

using namespace std;

Explosion::Explosion( SDL_Rect quad,
	SDL_Renderer* gRenderer, SDL_Texture* boomTexture)
	: Mob({ quad.x-10, quad.y-10, quad.w+20, quad.h+20 })
{
	this->gRenderer = gRenderer;
	texture = boomTexture;
}

int Explosion::amountLivesToChange(){
	return 0;
}

void Explosion::move(){
	step++;
	if(step == 100){
		destroy();
        step = 0;
	}
}

bool Explosion::isCollidable(){
    return false;
}

bool Explosion::needBoom(){
    return false;
}

void Explosion::render(){
	SDL_RenderCopy( gRenderer, texture, NULL, &quad );
}
