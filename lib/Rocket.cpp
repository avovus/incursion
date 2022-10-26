#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdlib.h>

#include "Rocket.hpp"
#include "Constants.hpp"

using namespace std;

Rocket::Rocket(
	int x, int y, int speed,
	SDL_Renderer* gRenderer, SDL_Texture* rocketTexture)
	: Mob({ x, y, Rocket::W, Rocket::H })
{
	this->gRenderer = gRenderer;
	texture = rocketTexture;
	this->speed = speed;
}


void Rocket::move(){
	if(quad.y+quad.h <= SCREEN_H-100){
			quad.x += speed;
	}
	else{
		destroy();
	}
}

void Rocket::render(){
	SDL_RenderCopy( gRenderer, texture, NULL, &quad );
}
