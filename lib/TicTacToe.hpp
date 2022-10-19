#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP
#include <string>
#include <vector>

using namespace std;

void draw(SDL_Rect tQuad, SDL_Texture* dTexture,
	SDL_Texture* fieldTexture, SDL_Renderer* gRenderer);

int ticTacToe(SDL_Renderer* gRenderer, SDL_Texture* tTexture,
	SDL_Texture* fieldTexture, SDL_Texture* x1Texture,
	SDL_Texture* xTexture, SDL_Texture* oTexture);


#endif
