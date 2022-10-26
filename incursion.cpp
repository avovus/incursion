#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <SDL2/SDL_ttf.h>

#include "lib/Constants.hpp"
#include "lib/Menu.hpp"

#include "lib/TicTacToe.hpp"
#include "lib/Player.hpp"
#include "lib/Mob.hpp"
#include "lib/Clyn.hpp"
#include "lib/Car.hpp"
#include "lib/Copter.hpp"
#include "lib/Rocket.hpp"

using namespace std;

bool init();

bool loadMedia();

void close();

SDL_Texture* loadTexture( std::string path );

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Texture* fieldTexture = NULL;
SDL_Texture* x1Texture = NULL;
SDL_Texture* xTexture = NULL;
SDL_Texture* oTexture = NULL;
SDL_Texture* copterTexture = NULL;
SDL_Texture* copterTexture5 = NULL;
SDL_Texture* planeTexture = NULL;
SDL_Texture* copterTexture2 = NULL;
SDL_Texture* copterTexture3 = NULL;
SDL_Texture* copterTexture4 = NULL;
SDL_Texture* carTexture2 = NULL;
SDL_Texture* clynTexture = NULL;
SDL_Texture* carTexture = NULL;
SDL_Texture* boomTexture = NULL;
SDL_Texture* rocketTexture = NULL;
SDL_Texture* gTexture = NULL;
SDL_Texture* playerTexture = NULL;
SDL_Texture* menuTexture = NULL;

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n",
			SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "вторжение",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W,
			SCREEN_H, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n",
				SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1,
				SDL_RENDERER_ACCELERATED );

			if( gRenderer == NULL )
			{
				printf("Renderer could not be created! SDL Error: %s\n",
					SDL_GetError() );
				success = false;
			}

			else
			{
				SDL_SetRenderDrawColor(
					gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf(
				"SDL_image could not initialize! SDL_image Error: %s\n",
				IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;
	rocketTexture = loadTexture( "images/rocket.png" );
	playerTexture = loadTexture( "images/ship.png" );
	gTexture = loadTexture( "images/city2.png" );
	copterTexture = loadTexture( "images/copter4.png" );
	planeTexture = loadTexture( "images/plane.png" );
	copterTexture2 = loadTexture( "images/copter2.png" );
	copterTexture3 = loadTexture( "images/copter3.png" );
	copterTexture4 = loadTexture( "images/copter.png" );
	copterTexture5 = loadTexture( "images/copterZ.png" );
	fieldTexture = loadTexture( "images/ticTacToe.png" );
	x1Texture = loadTexture( "images/x1.png" );
	xTexture = loadTexture( "images/x.png" );
	oTexture = loadTexture( "images/o.png" );
	clynTexture = loadTexture( "images/clyn.png" );
	carTexture2 = loadTexture( "images/car2.png" );
	carTexture = loadTexture( "images/car.png" );
	menuTexture = loadTexture( "images/menu.png" );
	if( gTexture == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}
/*
	if( boomTexture == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}
*/
	return success;
}


void close()
{
	SDL_DestroyTexture( gTexture );
	gTexture = NULL;

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
SDL_Texture* loadTexture( std::string path )
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n",
			path.c_str(), IMG_GetError() );
	}
	else
	{
        newTexture = SDL_CreateTextureFromSurface( gRenderer,
			loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n",
				path.c_str(), SDL_GetError() );
		}

		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void settings(){
}

int skins(){
	cout<<"in skins"<<endl;
}

int game(){
	int sec = 0;
	long long timer = 0;
	vector <Mob*> mobs;
	SDL_Rect livesQuad;
	livesQuad.w = 45;
	livesQuad.h = 27;
	livesQuad.x = -livesQuad.w;
	livesQuad.y = 0;
	SDL_Rect lQuad = livesQuad;

	Player p(200,300,gRenderer,playerTexture);
	mobs.push_back(new Copter(450, -50, 1, 2, gRenderer, copterTexture, timer, true));
	mobs.push_back(new Copter(-500, 150, 0, -1, gRenderer, copterTexture2, 0, false, 0, 550));

	int ans = 0;
	bool quit = false;
	SDL_Event e;
	while(!quit){
		while( SDL_PollEvent( &e ) != 0 ){
			if( e.type == SDL_QUIT )
			{
				quit = true;
				ans = -1;
			}

			else if(e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
				switch(e.key.keysym.sym){
					case SDLK_ESCAPE:
						switch(menu({"продолжить","выход"}, gRenderer, menuTexture)){
							case -2:
							case 0:
								break;
							default:
								ans = 0;
								quit = true;
						}
						break;

					case SDLK_w:
					case SDLK_UP:
						p.speedYDown();
						break;

					case SDLK_s:
					case SDLK_DOWN:
						p.speedYUp();
						break;

					case SDLK_a:
					case SDLK_LEFT:
						p.speedXDown();
						break;

					case SDLK_d:
					case SDLK_RIGHT:
						p.speedXUp();
						break;

					case SDLK_F1:
						break;

					case SDLK_SPACE:
					case SDLK_RETURN:
					case SDLK_RETURN2:
						break;
				}
			}

			else if(e.type == SDL_KEYUP && e.key.repeat == 0 ){
				switch(e.key.keysym.sym){
					case SDLK_w:
					case SDLK_UP:
						p.speedYUp();
						break;

					case SDLK_s:
					case SDLK_DOWN:
						p.speedYDown();
						break;

					case SDLK_a:
					case SDLK_LEFT:
						p.speedXUp();
						break;

					case SDLK_d:
					case SDLK_RIGHT:
						p.speedXDown();
						break;
				}
			}
		}

		if(timer == 5 && !sec){
			mobs.push_back(
				new Car(600, SCREEN_H - Car::H - 20, 3, gRenderer, carTexture2));
			mobs.push_back(new Copter(-500, 60, 0, -3, gRenderer, planeTexture, 0, false, 0, 200));
		}

		if(timer == 10 && !sec){
			mobs.push_back(new Copter(-100, 150, 0, 2, gRenderer, copterTexture3, 0, false, 0, 550));
		}

		if(timer == 15 && !sec){
			mobs.push_back(new Copter(1, -150, 0, -2, gRenderer, copterTexture4, 0, false, 0, 550));
		}

		if(timer == 20 && !sec){
			mobs.push_back(
				new Car(600, SCREEN_H - Car::H - 35, -2, gRenderer, carTexture));
		}

		if(timer == 30 && !sec){
			mobs.push_back(new Copter(-500, 160, 0, 2, gRenderer, copterTexture5, 0, false, 0, 550));
		}

		if(timer == 40 && !sec){
			mobs.push_back(new Clyn(200, -160, gRenderer, clynTexture));
		}

		for(int i = 0; i < mobs.size();++i){
			Mob* c = mobs[i]->spawnChild(rocketTexture,timer,sec);
			if(c != NULL){
				mobs.push_back(c);
			}
		}

		p.move();

		for(int i = 0; i < mobs.size(); ++i){
			(*mobs[i]).move();
		}

		for(int i = 0; i < mobs.size();++i){
			if(p.isCollided(mobs[i])){
				mobs[i]->destroy();
				p.decrLives();
			}
		}

		for(int i = mobs.size()-1; i>=0; --i){
			if(mobs[i]->isDestroyed()){
				mobs.erase(mobs.begin() + i);
			}
		}

		SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

		for(int i = 0; i < p.lives; ++i){
			livesQuad.x = livesQuad.x+livesQuad.w;
			SDL_RenderCopy( gRenderer, playerTexture, NULL, &livesQuad );
		}

		livesQuad = lQuad;


		for(int i = 0; i<mobs.size(); ++i){
			mobs[i]->render();
		}

		if(!p.isAlive()){
			ans = 1;
			quit = true;
		}

		p.render();

		sec += 1;
		if(sec == 200){
			timer+=1;
			sec = 0;
			cout << timer << endl;
		}
		SDL_RenderPresent( gRenderer );
		SDL_Delay(5);
	}

	for(int i = 0; i<mobs.size(); ++i){
		delete mobs[i];
	}
	return ans;
}

int main(int argc, char* args[]){
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			while( !quit )
			{
				switch(menu(
					{"крестики-нолики","начать","настройки","выход"},
					gRenderer,
					menuTexture))
				{
					case 0:
						switch(ticTacToe(gRenderer,menuTexture,fieldTexture, x1Texture, xTexture, oTexture)){
							case 0:
							break;
							case 1:
							break;
							case -1:
							break;
							case -2:
								quit = true;
							break;
							default:
							break;
						}
						break;
					case 1:
						if(game()==-1){quit = true;}
						break;
					case 2:
						settings();
						break;
					default:
						quit = true;
						break;
				}
			}
		}
	}

	close();

	return 0;
}
