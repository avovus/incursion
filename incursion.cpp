#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <SDL2/SDL_ttf.h>

#include "lib/Constants.hpp"
#include "lib/Menu.hpp"

#include "lib/Player.hpp"
#include "lib/Mob.hpp"
#include "lib/Clyn.hpp"
#include "lib/Car.hpp"

using namespace std;

bool init();

bool loadMedia();

void close();

SDL_Texture* loadTexture( std::string path );

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

string vercion = "alpha 2.5";
string creator = "Vovan kovan";

SDL_Texture* carTexture2 = NULL;
SDL_Texture* lazerTexture = NULL;
SDL_Texture* ufoTexture = NULL;
SDL_Texture* clynTexture = NULL;
SDL_Texture* clynTexture2 = NULL;
SDL_Texture* carTexture = NULL;
SDL_Texture* boomTexture = NULL;
SDL_Texture* gTexture = NULL;
SDL_Texture* playerTexture = NULL;
SDL_Texture* shotTexture = NULL;
SDL_Texture* menuTexture = NULL;

//SDL_Rect shotQuad = { x, y, 50, 20 }; //хидбокс выстрела персонажа
SDL_Rect lazerQuad = { -100, 0, 580, 30 };
SDL_Rect ufoQuad = { 0, -250, 500, 400 }; //хидбокс UFO


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
	//lazerTexture = loadTexture( "/home/vova/incursion/lazer3.png" );
	//ufoTexture = loadTexture( "/home/vova/incursion/ufo.png" );
	playerTexture = loadTexture( "images/ship.png" );
	//boomTexture = loadTexture( "/home/vova/incursion/boom.png" );
	//shotTexture = loadTexture( "/home/vova/incursion/shot2.png" );
	gTexture = loadTexture( "images/city2.png" );
	clynTexture = loadTexture( "images/clyn.png" );
	//clynTexture2 = loadTexture( "/home/vova/incursion/clyn2.png" );
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

	char moove = 'n'; //netral
	bool mob_boom = false;
	bool was_boom = false;
	long long score;
	int lives = 3;

void mobSpawn(bool &is_mob_on,SDL_Texture* mobTexture,
	SDL_Rect & mobQuad,int x_begin,int x_end, SDL_Rect targetQuad,
	int & targetLive, int speed){
	int oldQuad = mobQuad.x;
//	if(is_mob_on){
		if(targetQuad.x+targetQuad.w >= mobQuad.x+5 &&
			targetQuad.x <= mobQuad.x+mobQuad.w-5 &&
			targetQuad.y+targetQuad.h >= mobQuad.y+5 &&
			targetQuad.y <= mobQuad.y+mobQuad.h-5 &&
			is_mob_on){
			is_mob_on = false;
			if(!was_boom){
				mob_boom = true;
				was_boom = true;
			}
		}
		if(mobQuad.x == x_end){
			is_mob_on = false;
		}

		if(mob_boom){
			mob_boom = false;
			SDL_RenderCopy( gRenderer, boomTexture, NULL, &mobQuad );
//			cout << endl << "*BOOM!*"<< endl;
			SDL_RenderPresent( gRenderer );
			targetLive -= 1;
//			SDL_Delay(500);
		}
		mobQuad.x+=speed;
		if(!was_boom)
			SDL_RenderCopy( gRenderer, mobTexture, NULL, &mobQuad );
		SDL_RenderPresent( gRenderer );
//	}
}

/*
void moveClyn2(){
	if(clyn_is_on){
		if(clyn_fly_up){
			if(clynQuad.y >= 30){
				step++;
				if(step == 3){
					clynQuad.y -= 1;
					step = 0;
				}
			}
			else{
				clyn_fly_up = false;
			}
		}
		else{
			if(clynQuad.y+clynQuad.h <= SCREEN_H-100){
				step++;
				if(step == 3){
					clynQuad.y += 1;
					step = 0;
				}
			}
			else{
				clyn_fly_up = true;
			}
		}
		//lazerQuad.y = clynQuad.y+45;
	}
	else{
		if(clyn_boom){
			//SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
			SDL_RenderCopy( gRenderer, boomTexture, NULL, &clynQuad );
			SDL_RenderPresent( gRenderer );
			SDL_Delay(500);
			clynLive -= 1;
			clyn_boom = false;
		}
		clynQuad.x = 400;
		clynQuad.y = 200;

	}
}

bool checkClyn(SDL_Rect& playerQuad){
	if((playerQuad.x+playerQuad.w >= clynQuad.x+5 &&
		playerQuad.x <= clynQuad.x+clynQuad.w-5 &&
		playerQuad.y+playerQuad.h >= clynQuad.y+5 &&
		playerQuad.y <= clynQuad.y+clynQuad.h-5 && clyn_is_on) ||
		(clynLive <= 0 && clyn_is_on)) {
//					if(clynLive <= 0){
			clyn_is_on = false;
//		}
		clyn_boom = true;
		return true;
	}

	return false;
}
*/

void settings(){
}


void skins(){
	cout<<"in skins"<<endl;
}


int game(){
	vector <Mob*> mobs;

	Player p(200,300,gRenderer,playerTexture);
	mobs.push_back(new Clyn(50, 300, gRenderer, clynTexture));
	mobs.push_back(new Clyn(350, 0, gRenderer, clynTexture));
	mobs.push_back(
		new Car(600, SCREEN_H - Car::H - 35, -3, gRenderer, carTexture));
	mobs.push_back(
		new Car(600, SCREEN_H - Car::H - 20, 4, gRenderer, carTexture2));

	int ans = 0;
	bool quit = false;
	SDL_Event e;
	while(!quit){
		while( SDL_PollEvent( &e ) != 0 ){
			if( e.type == SDL_QUIT )
			{
				quit = true;
				ans = -1;
//				close();
			}

			else if(e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
				switch(e.key.keysym.sym){
					case SDLK_ESCAPE:
						switch(menu({"resume","exit"}, gRenderer, menuTexture)){
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
						cout << "KD: UP b" << endl;
						p.printSpeed();
						p.speedYDown();
						p.printSpeed();
						cout << "KD: UP e" << endl;
						break;

					case SDLK_s:
					case SDLK_DOWN:
						cout << "KD: DOWN b" << endl;
						p.printSpeed();
						p.speedYUp();
						p.printSpeed();
						cout << "KD: DOWN e" << endl;
						break;

					case SDLK_a:
					case SDLK_LEFT:
						cout << "KD: LEFT b" << endl;
						p.printSpeed();
						p.speedXDown();
						p.printSpeed();
						cout << "KD: LEFT e" << endl;
						break;

					case SDLK_d:
					case SDLK_RIGHT:
						cout << "KD: RIGHT b" << endl;
						p.printSpeed();
						p.speedXUp();
						p.printSpeed();
						cout << "KD: RIGHT e" << endl;
						break;

					case SDLK_F1:
						cout <<"версия: "<< vercion << endl <<
							"разработчик: " << creator << endl;
						break;

					case SDLK_SPACE:
						//is_shot = true;
						break;
				}
			}

			else if(e.type == SDL_KEYUP && e.key.repeat == 0 ){
				switch(e.key.keysym.sym){
					case SDLK_w:
					case SDLK_UP:
						cout << "KU: UP b" << endl;
						p.printSpeed();
						p.speedYUp();
						p.printSpeed();
						cout << "KU: UP e" << endl;
						break;

					case SDLK_s:
					case SDLK_DOWN:
						cout << "KU: DOWN b" << endl;
						p.printSpeed();
						p.speedYDown();
						p.printSpeed();
						cout << "KU: DOWN e" << endl;
						break;

					case SDLK_a:
					case SDLK_LEFT:
						cout << "KU: LEFT b" << endl;
						p.printSpeed();
						p.speedXUp();
						p.printSpeed();
						cout << "KU: LEFT e" << endl;
						break;

					case SDLK_d:
					case SDLK_RIGHT:
						cout << "KU: RIGHT b" << endl;
						p.printSpeed();
						p.speedXDown();
						p.printSpeed();
						cout << "KU: RIGHT e" << endl;
						break;
				}
			}
		}
		p.move();

		for(int i = 0; i<mobs.size(); ++i){
			(*mobs[i]).move();
		}

		SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
//		SDL_RenderCopy( gRenderer, playerTexture, NULL, NULL );

		for(int i = 0; i<mobs.size(); ++i){
			mobs[i]->render();
		}

		p.render();

		SDL_RenderPresent( gRenderer );
		SDL_Delay(5);
	}

	for(int i = 0; i<mobs.size(); ++i){
		delete mobs[i];
	}
	return ans;
}
/*
void game2(){
	for(int i = 50; i<300; ++i){
		playerQuad.x = 230;
		ufoQuad.x = -250;
		SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
		SDL_RenderCopy( gRenderer, playerTexture, NULL, &playerQuad );
		SDL_RenderCopy( gRenderer, ufoTexture, NULL, &ufoQuad );
		playerQuad.y = i;
		SDL_RenderPresent( gRenderer );
		ufoQuad.y-=1;
		SDL_Delay(5);
	}

	bool car_is_on = true;
	bool car_is_on2 = true;
	bool menu_is_on = true;
	bool car_boom = false;
	bool car_boom2 = false;
	long long cScore;
	int oneLive = 1;
	bool is_shot = false;

	bool quit = false;
	score = 0;
	clynQuad.x = 400;
	clynQuad.y = 200;
	lives = 3;
	playerQuad.x = 230;
	playerQuad.y = 300;

	moove = 'n';
	SDL_Event e;

	while(!quit){
		while( SDL_PollEvent( &e ) != 0 )
		if(checkClyn(playerQuad)) {
			quit = true;
		}


		if(playerQuad.x+playerQuad.w >= carQuad.x+5 &&
			playerQuad.x <= carQuad.x+carQuad.w-5 &&
			playerQuad.y+playerQuad.h >= carQuad.y+5 &&
			playerQuad.y <= carQuad.y+carQuad.h-5 &&
			car_is_on){
			car_is_on = false;
			car_boom = true;
		}

		//if(y <= SCREEN_H && y >= 0){
			//playerQuad.x = x;
		//}

		
		//if(x <= SCREEN_W && x >= 0){
			//playerQuad.y = y;
		//}
*/


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
					{"начать","skins","settings","exit"},
					gRenderer,
					menuTexture))
				{
					case 0:
						if(game()==-1){quit = true;}
						break;
					case 1:
						skins();
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
