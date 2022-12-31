#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "TicTacToe.hpp"
#include "Constants.hpp"

int checkV(vector <int> val, int ind);
int checkH(vector <int> val, int ind);
int minimax(vector <int> val, bool isX);
pair<int,int> selectMove(vector <int> val, bool isX) {
	int ii = -1;
	int bestVal = isX? -2: 2;
	int bestI = -1;
	for(int i = 0; i<val.size(); ++i){
		if(ii != -1){
			val[ii] = 0;
		}
		if(val[i] == 0){
			val[i] = isX? 1: -1;
			ii = i;
			int cur = minimax(val, !isX);
			if(isX){
				if(cur > bestVal){
					bestVal = cur;
					bestI = i;
				}
			}
			else{
				if(cur < bestVal){
					bestVal = cur;
					bestI = i;
				}
			}
		}
	}
	return {bestVal, bestI};
}

//returns "-1" if zero wins,
//         "1" if X wins 
//     and "0" if drow or game can continue
int check(vector <int> val){
	int ans = 0;
	for(int i = 0; i<3;++i){
		ans = checkV(val, i);
		if(ans != 0){
			return ans;
		}
	}

	for(int i = 0; i<=6;i+=3){
		ans = checkH(val, i);
		if(ans != 0){
			return ans;
		}
	}

	if((val[0] == 1 && val[4] == 1 && val[8] == 1) || (val[2] == 1 && val[4] == 1 && val[6] == 1)){
		return 1;
	}

	if((val[0] == -1 && val[4] == -1 && val[8] == -1) || (val[2] == -1 && val[4] == -1 && val[6] == -1)){
		return -1;
	}

	bool isD = true;

	for(int i = 0; i<9; ++i){
		if(val[i] == 0){
			isD = false;
			break;
		}
	}

	if(isD){
		return 0;
	}

	return 2;
}

int minimax(vector <int> val, bool isX){
	int ans = check(val);
	if(ans == 2){
		return selectMove(val, isX).first;
	}

	return ans;
}

void draw(SDL_Rect tQuad, int ind, SDL_Texture* dTexture,
	SDL_Renderer* gRenderer)
{
	int indX = ind%3, indY = ind/3;
	tQuad.x += (tQuad.w+55)*indX;
	tQuad.y += (tQuad.h+55)*indY;
	SDL_RenderCopy( gRenderer, dTexture, NULL, &tQuad );
}

int checkV(vector <int> val, int ind){
	if(val[ind] == 1 && val[ind+3] == 1 && val[ind+6] == 1){
		return 1;
	}

	else if(val[ind] == -1 && val[ind+3] == -1 && val[ind+6] == -1){
		return -1;
	}

	return 0;
}

int checkH(vector <int> val,int ind){
	if(val[ind] == 1 && val[ind+1] == 1 && val[ind+2] == 1){
		return 1;
	}

	else if(val[ind] == -1 && val[ind+1] == -1 && val[ind+2] == -1){
		return -1;
	}

	return 0;
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

	SDL_Rect winQuad;
	winQuad.x = 250;
	winQuad.y = 250;
	winQuad.w = 100;
	winQuad.h = 100;

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
	int ans = 2;
	int ind = 0;
	bool quit = false;
	bool isX = true;
	SDL_Event e;
	while( SDL_PollEvent( &e ) != 0) {};
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
						if(!val[ind]){
							val[ind] = 1;
							ans = check(val);
							if(ans == 2){
								val[selectMove(val,false).second] = -1;
								ans = check(val);
							}
						}
					break;

					case SDLK_ESCAPE:
						ans = -3;
						quit = true;
					break;
				}
			}
		}

		//have moves
		// move of O

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

		// if(have moves)
		SDL_RenderCopy( gRenderer, x1Texture, NULL, &tQuad );

		if(ans != 2){
			SDL_RenderCopy( gRenderer, tTexture, NULL, NULL );
			if(ans){
				if(ans == -2 || ans == -3){

				}
				else{
					SDL_RenderCopy( gRenderer, ans==-1? oTexture: xTexture, NULL, &winQuad );
				}
			}
			else{
				winQuad.x -= winQuad.w/2;
				SDL_RenderCopy( gRenderer, oTexture, NULL, &winQuad );
				winQuad.x += winQuad.w;
				SDL_RenderCopy( gRenderer, xTexture, NULL, &winQuad );
			}
			SDL_RenderPresent( gRenderer );
			quit = true;
			SDL_Delay(500);
		}

		SDL_RenderPresent( gRenderer );
		SDL_Delay(5);

	}
	return ans;
}
