#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

int ticTacToe(SDL_Renderer* gRenderer, SDL_Texture* tTexture,
	SDL_Texture* fieldTexture, SDL_Texture* x1Texture,
	SDL_Texture* xTexture, SDL_Texture* oTexture);


#endif
