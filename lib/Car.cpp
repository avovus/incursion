#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Car.hpp"
#include "Constants.hpp"
#include "Player.hpp"
#include "Mob.hpp"

using namespace std;

Car::Car(
	int x, int y, int speedx,
	SDL_Renderer* gRenderer, SDL_Texture* carTexture)
	: Mob({ x, y, Car::W, Car::H })
{
	this->gRenderer = gRenderer;
	texture = carTexture;
	this->speedx = speedx;
}

void Car::move(){
	quad.x += speedx;
	if(speedx < 0){
		if(quad.x+quad.w <= 0){
			quad.x = SCREEN_W+quad.w;
		}
	}
	else{
		if(quad.x >= SCREEN_W){
			quad.x = 0;
		}
	}
}

int Car::amountLivesToChange(){
		return -2;
}

void Car::render(){
	SDL_RenderCopy( gRenderer, texture, NULL, &quad );
}
