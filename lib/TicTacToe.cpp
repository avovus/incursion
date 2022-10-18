#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "TicTacToe.hpp"
#include "Constants.hpp"

void ticTacToe(SDL_Renderer* gRenderer, SDL_Texture* tTexture, SDL_Texture* fieldTexture){
	SDL_RenderCopy( gRenderer, tTexture, NULL, NULL );
	SDL_RenderCopy( gRenderer, fieldTexture, NULL, NULL );
	SDL_RenderPresent( gRenderer );
	SDL_Delay(3000);
}
