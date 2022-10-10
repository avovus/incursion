#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Car.hpp"
#include "Constants.hpp"

using namespace std;

Car::Car(int x, int y, int speedx, SDL_Renderer* gRenderer, SDL_Texture* carTexture){
	this->gRenderer = gRenderer;
	texture = carTexture;
	quad.x = x;
	quad.y = y;
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

void Car::render(){
	SDL_RenderCopy( gRenderer, texture, NULL, &quad );
}
