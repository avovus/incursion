#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "TicTacToe.hpp"
#include "Constants.hpp"

void draw(SDL_Rect tQuad, int ind, SDL_Texture* dTexture,
	SDL_Renderer* gRenderer)
{
	int indX = ind%3, indY = ind/3;
	tQuad.x += (tQuad.w+55)*indX;
	tQuad.y += (tQuad.h+55)*indY;
	SDL_RenderCopy( gRenderer, dTexture, NULL, &tQuad );
}

int ticTacToe(SDL_Renderer* gRenderer, SDL_Texture* tTexture,
	SDL_Texture* fieldTexture, SDL_Texture* x1Texture,
	SDL_Texture* xTexture, SDL_Texture* oTexture)
{
	vector <int> val = {0,0,0,
						0,0,0,
						0,0,0};
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
	int ind = 0;
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
					case SDLK_d:
					case SDLK_RIGHT:
						if(ind == 8){
							ind = 0;
						}
						else{
							ind += 1;
						}
					break;

					case SDLK_a:
					case SDLK_LEFT:
						if(ind == 0){
							ind = 8;
						}
						else{
							ind -= 1;
						}
					break;

					case SDLK_w:
					case SDLK_UP:
						if(ind/3 == 0){
							ind+=6;
						}
						else{
							ind-=3;
						}
					break;

					case SDLK_s:
					case SDLK_DOWN:
						if(ind/3 == 2){
							ind-=6;
						}
						else{
							ind+=3;
						}
					break;

					case SDLK_SPACE:
					case SDLK_RETURN:
					case SDLK_RETURN2:
						if(!val[ind])
							val[ind] = 1;
					break;

					case SDLK_ESCAPE:
						ans = -1;
						quit = true;
					break;
				}
			}
		}

	int indX = ind%3, indY = ind/3;
	tQuad.x = 100 + (tQuad.w+55)*indX;
	tQuad.y = 100 + (tQuad.h+55)*indY;

	SDL_RenderCopy( gRenderer, tTexture, NULL, NULL );
	SDL_RenderCopy( gRenderer, fieldTexture, NULL, NULL );

	for(int i = 0;i<val.size();++i){
		if(val[i] == -1){
			draw({100,100,tQuad.w,tQuad.h},i,oTexture,gRenderer);
		}
		else if(val[i] == 1){
			draw({100,100,tQuad.w,tQuad.h},i,xTexture,gRenderer);
		}
	}

	SDL_RenderCopy( gRenderer, x1Texture, NULL, &tQuad );

	SDL_RenderPresent( gRenderer );
	SDL_Delay(5);
	}
	return ans;
}
