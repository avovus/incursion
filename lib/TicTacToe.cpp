#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "TicTacToe.hpp"
#include "Constants.hpp"

void draw(SDL_Rect tQuad, int indX, int indY, SDL_Texture* dTexture,
	SDL_Renderer* gRenderer)
{
	tQuad.x += (tQuad.w+55)*indX;
	tQuad.y += (tQuad.h+55)*indY;
	SDL_RenderCopy( gRenderer, dTexture, NULL, &tQuad );
}

int ticTacToe(SDL_Renderer* gRenderer, SDL_Texture* tTexture,
	SDL_Texture* fieldTexture, SDL_Texture* x1Texture,
	SDL_Texture* xTexture, SDL_Texture* oTexture)
{
	SDL_Rect tQuad;

	tQuad.x = 100;
	tQuad.y = 100;
	tQuad.w = 100;
	tQuad.h = 100;

	vector <pair<int,int>> positions;
	pair<int,int> p1;
	pair<int,int> p2;
	pair<int,int> p3;
	pair<int,int> p4;
	pair<int,int> p5;
	pair<int,int> p6;
	pair<int,int> p7;
	pair<int,int> p8;
	pair<int,int> p9;
	int ans = 0;
	bool quit = false;
	while( !quit )
	{
		SDL_Event e;
		while( SDL_PollEvent( &e ) != 0 && !quit)
		{
			if( e.type == SDL_QUIT ){
				ans = -2;
				quit = true;
				break;
			}
			else if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
				switch( e.key.keysym.sym )
				{
					case SDLK_w:
					case SDLK_UP:
					break;

					case SDLK_s:
					case SDLK_DOWN:
					break;

					case SDLK_SPACE:
					break;

					case SDLK_ESCAPE:
						ans = -1;
						quit = true;
					break;
				}
			}
		}
	SDL_RenderCopy( gRenderer, tTexture, NULL, NULL );
	SDL_RenderCopy( gRenderer, fieldTexture, NULL, NULL );
	SDL_RenderCopy( gRenderer, x1Texture, NULL, &tQuad );
	draw({tQuad.x,tQuad.y,tQuad.w,tQuad.h},1,0,oTexture,gRenderer);
	draw({tQuad.x,tQuad.y,tQuad.w,tQuad.h},2,0,xTexture,gRenderer);
	draw({tQuad.x,tQuad.y,tQuad.w,tQuad.h},1,1,xTexture,gRenderer);
	draw({tQuad.x,tQuad.y,tQuad.w,tQuad.h},0,2,xTexture,gRenderer);
	SDL_RenderPresent( gRenderer );
	SDL_Delay(5);
	}
	return ans;
}
