#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Clyn.hpp"
#include "Constants.hpp"

using namespace std;

Clyn::Clyn(int x, int y,SDL_Renderer* gRenderer,SDL_Texture* texture){
	this->gRenderer = gRenderer;
	this->texture = texture;
	quad.x = x;
	quad.y = y;
}

void Clyn::move(){
	if(fly_up){
		if(quad.y >= 30){
			step++;
			if(step == 3){
				quad.y -= 1;
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
				quad.y += 1;
				step = 0;
			}
		}
		else{
			fly_up = true;
		}
	}
}

void Clyn::render(){
	SDL_RenderCopy( gRenderer, texture, NULL, &quad );
}
