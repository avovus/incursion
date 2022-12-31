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
#include "lib/Mod.hpp"
#include "lib/Explosion.hpp"

using namespace std;

bool init();

//cделать нормальный режим выживания
//сделать сложное движение клыну
//сделать модуль, убивающий всех на экране
//cделать самолет, кидающий бомбы

bool loadMedia();
bool spawnClyn = false;
bool spawnHil = false;
bool spawnRand = false;

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
SDL_Texture* battleCopterTexture6 = NULL;
SDL_Texture* carTexture2 = NULL;
SDL_Texture* clynTexture = NULL;
SDL_Texture* carTexture = NULL;
SDL_Texture* boomTexture = NULL;
SDL_Texture* rocketTexture = NULL;
SDL_Texture* gTexture = NULL;
SDL_Texture* playerTexture = NULL;
SDL_Texture* menuTexture = NULL;
SDL_Texture* modTexture = NULL;

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

				else{
					if( TTF_Init() == -1 )
					{
						printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n",
							TTF_GetError() );
						success = false;
					}
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
	copterTexture = loadTexture( "images/copter4R3.png" );
	planeTexture = loadTexture( "images/plane.png" );
	copterTexture2 = loadTexture( "images/copter2.png" );
	copterTexture3 = loadTexture( "images/copter3.png" );
	copterTexture4 = loadTexture( "images/copter.png" );
	battleCopterTexture6 = loadTexture( "images/copter4.png" );
	copterTexture5 = loadTexture( "images/copterZ.png" );
	fieldTexture = loadTexture( "images/ticTacToe.png" );
	x1Texture = loadTexture( "images/x1.png" );
	xTexture = loadTexture( "images/x.png" );
	oTexture = loadTexture( "images/o.png" );
	clynTexture = loadTexture( "images/clyn.png" );
	carTexture2 = loadTexture( "images/car2.png" );
	carTexture = loadTexture( "images/car.png" );
	modTexture = loadTexture( "images/mod1.png" );
	menuTexture = loadTexture( "images/menu.png" );
	boomTexture = loadTexture( "images/boom.png" );
	if( gTexture == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	TTF_Font* gFont = TTF_OpenFont( "fonts/Marske.ttf", 35 );

	if( gFont == NULL )
	{
		printf( "Failed to load Floripa font! SDL_ttf Error: %s\n",
			TTF_GetError() );
		return -1;
	}

	return success;
}

struct MenuTexture{
	SDL_Texture* mTexture;
	int w, h;
};

MenuTexture tf(TTF_Font* font, string item, SDL_Renderer* gRenderer,
	SDL_Color textColor){
		//Render text
		SDL_Surface* textSurface =
			TTF_RenderUTF8_Solid( font, item.c_str(), textColor );
		if( textSurface == NULL )
		{
			printf(
				"Unable to render text surface! SDL_ttf Error: %s\n",
				TTF_GetError() );
		}

		//Create texture from surface pixels
		SDL_Texture* mTexture =
			SDL_CreateTextureFromSurface( gRenderer, textSurface );
		MenuTexture mt{mTexture,textSurface->w,textSurface->h};
		SDL_FreeSurface( textSurface );
		if( mTexture == NULL )
		{
			printf(
			"Unable to create texture from rendered text! SDL Error: %s\n",
			SDL_GetError() );
		}

		return mt;
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
	TTF_Font* gFont = TTF_OpenFont( "fonts/Marske.ttf", 35 );

	if( gFont == NULL )
	{
		printf( "Failed to load Floripa font! SDL_ttf Error: %s\n",
			TTF_GetError() );
	}

	SDL_Color textColor = { 0, 0, 0 };


	MenuTexture tTexture = tf(gFont,"о мой бог, чёрт возьми,", gRenderer,
		textColor);
	SDL_Rect renderQuad = {
		SCREEN_W/2-tTexture.w/2,
		250,
		tTexture.w,
		tTexture.h};

//сделать функцию для этого всего

	MenuTexture tTexture2 = tf(gFont,"хорошая работа, Вован.", gRenderer,
		textColor);
	SDL_Rect renderQuad2 = {
		SCREEN_W/2-tTexture2.w/2,
		280,
		tTexture2.w,
		tTexture2.h};

	MenuTexture tTexture1 = tf(gFont,"У тебя получилось!", gRenderer,
		textColor);
	SDL_Rect renderQuad1 = {
		SCREEN_W/2-tTexture1.w/2,
		310,
		tTexture1.w,
		tTexture1.h};

	SDL_RenderCopy( gRenderer, menuTexture, NULL, NULL );

	SDL_RenderCopyEx( gRenderer, tTexture.mTexture, NULL,
		&renderQuad, 0, NULL, SDL_FLIP_NONE );

	SDL_RenderCopyEx( gRenderer, tTexture2.mTexture, NULL,
		&renderQuad2, 0, NULL, SDL_FLIP_NONE );

	SDL_RenderCopyEx( gRenderer, tTexture1.mTexture, NULL,
		&renderQuad1, 0, NULL, SDL_FLIP_NONE );

	SDL_RenderPresent( gRenderer );

	SDL_DestroyTexture(tTexture.mTexture);
	SDL_DestroyTexture(tTexture1.mTexture);
	SDL_DestroyTexture(tTexture2.mTexture);

	SDL_Delay(2000);
}

int skins(){
	cout<<"in skins"<<endl;
}

int gameMod1(){
	int sec = 0;
	long long timer = 0;
	vector <Mob*> mobs;
	SDL_Rect livesQuad;
	livesQuad.w = 45;
	livesQuad.h = 29;
	livesQuad.x = -livesQuad.w;
	livesQuad.y = 0;
	SDL_Rect lQuad = livesQuad;

	Player p(200,300,gRenderer,playerTexture);

	TTF_Font* gFont = TTF_OpenFont( "fonts/Marske.ttf", 35 );

	if( gFont == NULL )
	{
		printf( "Failed to load Floripa font! SDL_ttf Error: %s\n",
			TTF_GetError() );
	}

	SDL_Color textColor = { 0, 0, 0 };

	mobs.push_back(
		new Car(600, SCREEN_H - Car::H - 35, -2, gRenderer, carTexture));

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

					case SDLK_F12:{
							string a;
							cin >> a;
							if(a == "GG"){
								p.lives = 99999;
							}

							else if(a == "BTTF"){
								timer = 39;
							}

							else if(a == "SLV"){
								cout << "https://slaves-of-zoyarskaya.vercel.app" << endl;
							}

							else if(a == "03"){
								spawnHil = true;
							}

							else if(a == "CLYN"){
								spawnClyn = true;
								cout << "CLYN!!!" << endl;
							}

							else if(a == "INFO"){
								cout << "lives:" << p.lives << endl;
								cout << "enemy:" << mobs.size() << endl;
								cout << "time:" << timer << endl;
							}

						}
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

		srand(time(0));

		if(spawnClyn){
			mobs.push_back(new Clyn(50 + rand() % SCREEN_W-100, -160, gRenderer, clynTexture));
			spawnClyn = false;
		}

		if(spawnHil){
			mobs.push_back(new Mod(SCREEN_W,100,1, gRenderer, modTexture));
			spawnHil = false;
		}

		if(timer == 5 && !sec){
			mobs.push_back(new Copter(-500, 150, 0, -1, gRenderer, copterTexture2, 0, false, 0, 550));

		}

		if(timer == 7 && !sec){
			mobs.push_back(new Copter(-100, 150, 0, 2, gRenderer, copterTexture3, 0, false, 0, 550));
		}

		if(timer == 10 && !sec){
			mobs.push_back(new Copter(430, -50, 1, 2, gRenderer, copterTexture, timer, true));
			mobs.push_back(
				new Car(600, SCREEN_H - Car::H - 20, 3, gRenderer, carTexture2));
			mobs.push_back(new Copter(1, -150, 0, -2, gRenderer, copterTexture4, 0, false, 0, 550));
		}

		if(timer == 15 && !sec){
		}

		if(timer == 20 && !sec){
			mobs.push_back(new Copter(-500, 160, 0, 2, gRenderer, copterTexture5, 0, false, 0, 550));
		}

		if(timer == 25 && !sec){
			mobs.push_back(new Copter(-500, 60, 0, -3, gRenderer, planeTexture, 0, false, 0, 200));
		}

		if(timer%15 == 0 && !sec && timer != 0){
			mobs.push_back(new Mod(SCREEN_W,100,1, gRenderer, modTexture));
		}

	if(timer == 40 && !sec){
			MenuTexture texture = tf(gFont,"земляне предлагают сыграть в игру:", gRenderer,
				textColor);
			SDL_Rect quad = {
				SCREEN_W/2-texture.w/2,
				250,
				texture.w,
				texture.h};

			MenuTexture texture1 = tf(gFont,"если вы победите, то земля ваша", gRenderer,
				textColor);
			SDL_Rect quad1 = {
				SCREEN_W/2-texture1.w/2,
				250+texture1.h,
				texture1.w,
				texture1.h};
			
			SDL_RenderCopy( gRenderer, menuTexture, NULL, NULL);
			SDL_RenderCopyEx( gRenderer, texture.mTexture, NULL,
				&quad, 0, NULL, SDL_FLIP_NONE );
			SDL_RenderCopyEx( gRenderer, texture1.mTexture, NULL,
				&quad1, 0, NULL, SDL_FLIP_NONE );
			SDL_RenderPresent(gRenderer);

			SDL_DestroyTexture(texture.mTexture);
			SDL_DestroyTexture(texture1.mTexture);

			bool quit1 = false;
			while(!quit1){
				while( SDL_PollEvent( &e ) != 0 ){
					if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.repeat == 0 )){
						quit1 = true;
					}
				}
			}

			switch(ticTacToe(gRenderer,menuTexture,fieldTexture, x1Texture, xTexture, oTexture)){
				case 0:{
					MenuTexture txt = tf(gFont,"вы сыграли в ничью", gRenderer,
						textColor);
					SDL_Rect qd = {
						SCREEN_W/2-txt.w/2,
						250,
						txt.w,
						txt.h};

					MenuTexture txt1 = tf(gFont,"вторжение не удалось", gRenderer,
						textColor);
					SDL_Rect qd1 = {
						SCREEN_W/2-txt1.w/2,
						250+txt1.h,
						txt1.w,
						txt1.h};

					SDL_RenderCopy( gRenderer, menuTexture, NULL, NULL);
					SDL_RenderCopyEx( gRenderer, txt.mTexture, NULL,
						&qd, 0, NULL, SDL_FLIP_NONE );
					SDL_RenderCopyEx( gRenderer, txt1.mTexture, NULL,
						&qd1, 0, NULL, SDL_FLIP_NONE );
					SDL_RenderPresent(gRenderer);
					bool quit1 = false;
					while(!quit1){
						while( SDL_PollEvent( &e ) != 0 ){
							if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.repeat == 0 )){
								quit1 = true;
							}
						}
					}
					SDL_DestroyTexture(txt.mTexture);
					SDL_DestroyTexture(txt1.mTexture);
					quit = true;
				}
				break;
				case -2:
				case -3:
					quit = true;
				break;
				case -1:{
					MenuTexture txt = tf(gFont,"вы проиграли", gRenderer,
						textColor);
					SDL_Rect qd = {
						SCREEN_W/2-txt.w/2,
						250,
						txt.w,
						txt.h};

					MenuTexture txt1 = tf(gFont,"вторжение не удалось", gRenderer,
						textColor);
					SDL_Rect qd1 = {
						SCREEN_W/2-txt1.w/2,
						250+txt1.h,
						txt1.w,
						txt1.h};

					SDL_RenderCopy( gRenderer, menuTexture, NULL, NULL);
					SDL_RenderCopyEx( gRenderer, txt.mTexture, NULL,
						&qd, 0, NULL, SDL_FLIP_NONE );
					SDL_RenderCopyEx( gRenderer, txt1.mTexture, NULL,
						&qd1, 0, NULL, SDL_FLIP_NONE );
					SDL_RenderPresent(gRenderer);
					bool quit1 = false;
					while(!quit1){
						while( SDL_PollEvent( &e ) != 0 ){
							if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.repeat == 0 )){
								quit1 = true;
							}
						}
					}
					SDL_DestroyTexture(txt.mTexture);
					SDL_DestroyTexture(txt1.mTexture);
					quit = true;
				}
				break;

				case 1:{
					MenuTexture txt = tf(gFont,"вы сделали невозможное", gRenderer,
						textColor);
					SDL_Rect qd = {
						SCREEN_W/2-txt.w/2,
						250,
						txt.w,
						txt.h};

					MenuTexture txt1 = tf(gFont,"вы победили ИИ", gRenderer,
						textColor);
					SDL_Rect qd1 = {
						SCREEN_W/2-txt1.w/2,
						250+txt1.h,
						txt1.w,
						txt1.h};

					SDL_RenderCopy( gRenderer, menuTexture, NULL, NULL);
					SDL_RenderCopyEx( gRenderer, txt.mTexture, NULL,
						&qd, 0, NULL, SDL_FLIP_NONE );
					SDL_RenderCopyEx( gRenderer, txt1.mTexture, NULL,
						&qd1, 0, NULL, SDL_FLIP_NONE );
					SDL_RenderPresent(gRenderer);
					bool quit1 = false;
					while(!quit1){
						while( SDL_PollEvent( &e ) != 0 ){
							if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.repeat == 0 )){
								quit1 = true;
							}
						}
					}
					SDL_DestroyTexture(txt.mTexture);
					SDL_DestroyTexture(txt1.mTexture);
					quit = true;
				}
				break;
				default:{
					MenuTexture txt = tf(gFont,"вы сыграли в ничью", gRenderer,
						textColor);
					SDL_Rect qd = {
						SCREEN_W/2-txt.w/2,
						250,
						txt.w,
						txt.h};

					MenuTexture txt1 = tf(gFont,"вторжение не удалось", gRenderer,
						textColor);
					SDL_Rect qd1 = {
						SCREEN_W/2-txt1.w/2,
						250+txt1.h,
						txt1.w,
						txt1.h};

					SDL_RenderCopy( gRenderer, menuTexture, NULL, NULL);
					SDL_RenderCopyEx( gRenderer, txt.mTexture, NULL,
						&qd, 0, NULL, SDL_FLIP_NONE );
					SDL_RenderCopyEx( gRenderer, txt1.mTexture, NULL,
						&qd1, 0, NULL, SDL_FLIP_NONE );
					SDL_RenderPresent(gRenderer);
					bool quit1 = false;
					while(!quit1){
						while( SDL_PollEvent( &e ) != 0 ){
							if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.repeat == 0 )){
								quit1 = true;
							}
						}
					}
					SDL_DestroyTexture(txt.mTexture);
					SDL_DestroyTexture(txt1.mTexture);
					quit = true;
				}
				break;
			}
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
				p.changeLives(mobs[i]->amountLivesToChange());
			}
		}

		for(int i = mobs.size()-1; i>=0; --i){
			if(mobs[i]->isDestroyed()){
				if(mobs[i]->needBoom()){
					mobs.push_back(new Explosion(mobs[i]->getQuad(), gRenderer, boomTexture));
				}
				mobs.erase(mobs.begin() + i);
			}
		}

		SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

		if(timer <= 3){
			MenuTexture message = tf(gFont,"продержитесь 40 сек", gRenderer,
				textColor);
			SDL_Rect mQuad = {
				SCREEN_W/2-message.w/2,
				200,
				message.w,
				message.h};

			MenuTexture message1 = tf(gFont,"для захвата Земли", gRenderer,
				textColor);
			SDL_Rect mQuad1 = {
				SCREEN_W/2-message1.w/2,
				200+message1.h,
				message1.w,
				message1.h};

			SDL_RenderCopyEx( gRenderer, message.mTexture, NULL,
				&mQuad, 0, NULL, SDL_FLIP_NONE );
			SDL_RenderCopyEx( gRenderer, message1.mTexture, NULL,
				&mQuad1, 0, NULL, SDL_FLIP_NONE );

			SDL_DestroyTexture(message.mTexture);
			SDL_DestroyTexture(message1.mTexture);
		}

		for(int i = 0; i < p.lives; ++i){
			livesQuad.x = livesQuad.x+livesQuad.w;
			SDL_RenderCopy( gRenderer, playerTexture, NULL, &livesQuad );
		}

		sec += 1;
		if(sec == 200){
			timer+=1;
			sec = 0;
		}

		MenuTexture tTexture = tf(gFont,to_string(40-timer), gRenderer,
			textColor);
		SDL_Rect renderQuad = {
			SCREEN_W/2-tTexture.w/2,
			30,
			tTexture.w,
			tTexture.h};
		SDL_RenderCopyEx( gRenderer, tTexture.mTexture, NULL,
			&renderQuad, 0, NULL, SDL_FLIP_NONE );

		livesQuad = lQuad;

		SDL_DestroyTexture(tTexture.mTexture);

		for(int i = 0; i<mobs.size(); ++i){
			mobs[i]->render();
		}

		if(!p.isAlive()){
			ans = 1;
			quit = true;
			SDL_Delay(500);
			MenuTexture txt = tf(gFont,"вы разбились", gRenderer,
				textColor);
			SDL_Rect qd = {
				SCREEN_W/2-txt.w/2,
				250,
				txt.w,
				txt.h};

			MenuTexture txt1 = tf(gFont,"вторжение не удалось", gRenderer,
				textColor);
			SDL_Rect qd1 = {
				SCREEN_W/2-txt1.w/2,
				250+txt1.h,
				txt1.w,
				txt1.h};

			SDL_RenderCopy( gRenderer, menuTexture, NULL, NULL);
			SDL_RenderCopyEx( gRenderer, txt.mTexture, NULL,
				&qd, 0, NULL, SDL_FLIP_NONE );
			SDL_RenderCopyEx( gRenderer, txt1.mTexture, NULL,
				&qd1, 0, NULL, SDL_FLIP_NONE );
			SDL_RenderPresent(gRenderer);
			bool quit1 = false;
			while(!quit1){
				while( SDL_PollEvent( &e ) != 0 ){
					if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.repeat == 0 )){
						quit1 = true;
					}
				}
			}
			SDL_DestroyTexture(txt.mTexture);
			SDL_DestroyTexture(txt1.mTexture);

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

void spawnRandomMob(vector <Mob*> & mobs){
	srand(time(0));
	int a = rand() % 7;
	switch(a){
		case 0:
			mobs.push_back(
				new Car(600, SCREEN_H - Car::H - 35, -2, gRenderer, carTexture));
		break;
		case 1:
			mobs.push_back(
				new Car(600, SCREEN_H - Car::H - 20, 3, gRenderer, carTexture2));
		break;
		case 2:
			mobs.push_back(new Copter(-2500, 150, 0, -2, gRenderer, copterTexture2, 0, false, 0, 550));
		break;
		case 3:
			mobs.push_back(new Copter(-100, 150, 0, 2, gRenderer, copterTexture3, 0, false, 0, 550));
		break;
		case 4:
			mobs.push_back(new Copter(1, -150, 0, -2, gRenderer, copterTexture4, 0, false, 0, 550));
		break;
		case 5:
			mobs.push_back(new Copter(-500, 160, 0, 2, gRenderer, copterTexture5, 0, false, 0, 550));
		break;
		case 6:
			mobs.push_back(new Copter(-2500, 150, 0, -2, gRenderer, battleCopterTexture6, 0, false, 0, 550));
		break;
		case 7:
			mobs.push_back(new Copter(-5500, 60, 0, -3, gRenderer, planeTexture, 0, false, 0, 200));
		break;
	}
}

int gameMod2(){
	int sec = 0;
	long long timer = 0;
	vector <Mob*> mobs;
	SDL_Rect livesQuad;
	livesQuad.w = 45;
	livesQuad.h = 29;
	livesQuad.x = -livesQuad.w;
	livesQuad.y = 0;
	SDL_Rect lQuad = livesQuad;

	Player p(200,300,gRenderer,playerTexture);

	TTF_Font* gFont = TTF_OpenFont( "fonts/Marske.ttf", 35 );

	if( gFont == NULL )
	{
		printf( "Failed to load Floripa font! SDL_ttf Error: %s\n",
			TTF_GetError() );
	}

	SDL_Color textColor = { 0, 0, 0 };

//	mobs.push_back(new Copter(-5500, 60, 0, -3, gRenderer, planeTexture, 0, false, 0, 200));

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

					case SDLK_F12:{
							string a;
							cin >> a;
							if(a == "GG"){
								p.lives = 99999;
							}

							else if(a == "BTTF"){
								timer += 60;
								cout << "JUMPING!" << endl;
							}

							else if(a == "SLV"){
								cout << "https://slaves-of-zoyarskaya.vercel.app" << endl;
							}

							else if(a == "03"){
								spawnHil = true;
							}

							else if(a == "CLYN"){
								spawnClyn = true;
								cout << "CLYN!!!" << endl;
							}

							else if(a == "INFO"){
								cout << "lives:" << p.lives << endl;
								cout << "enemy:" << mobs.size() << endl;
								cout << "time:" << timer << endl;
							}

							else if(a == "SR"){
								cout << "summon" << endl;
								spawnRand = true;
							}

						}
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

		if(spawnClyn){
			mobs.push_back(new Clyn(50 + rand() % SCREEN_W-100, -160, gRenderer, clynTexture));
			spawnClyn = false;
		}

		if(spawnHil){
			mobs.push_back(new Mod(SCREEN_W,100,1, gRenderer, modTexture));
			spawnHil = false;
		}

		if(spawnRand){
			spawnRandomMob(mobs);
			spawnRand = false;
		}

		if(timer >= 3 && timer < 5 && mobs.size() < 2 && !sec){
			spawnRandomMob(mobs);
		}

		if(timer >= 5 && timer < 15 && mobs.size() < 4 && !sec){
			spawnRandomMob(mobs);
		}

		if(timer >= 15 && timer < 30 && mobs.size() < 6 && !sec){
			spawnRandomMob(mobs);
		}

		if(timer >= 30 && timer < 60 && mobs.size() < 7 && !sec){
			spawnRandomMob(mobs);
		}

		if(timer >= 60 && timer < 90 && mobs.size() < 10 && !sec){
			spawnRandomMob(mobs);
		}

		if(timer == 75 && !sec){
			mobs.push_back(new Copter(430, -50, 1, 2, gRenderer, copterTexture, timer, true));
		}

/*
		if(timer >= 5 && timer <= 15 && mobs.size() < 2 && !sec){
			mobs.push_back(
				new Car(600, SCREEN_H - Car::H - 35, -2, gRenderer, carTexture));
			mobs.push_back(new Copter(-2500, 150, 0, -1, gRenderer, copterTexture2, 0, false, 0, 550));
		}

		if(timer > 15 && timer <= 45 && mobs.size() < 5 && !sec){
			mobs.push_back(new Copter(-100, 150, 0, 2, gRenderer, copterTexture3, 0, false, 0, 550));
			mobs.push_back(new Copter(1, -150, 0, -2, gRenderer, copterTexture4, 0, false, 0, 550));
			mobs.push_back(
				new Car(600, SCREEN_H - Car::H - 20, 3, gRenderer, carTexture2));
		}

		if(timer > 45 && timer <= 90 && mobs.size() < 8 && !sec){
			mobs.push_back(new Copter(-500, 160, 0, 2, gRenderer, copterTexture5, 0, false, 0, 550));
			mobs.push_back(new Copter(-2500, 150, 0, -3, gRenderer, copterTexture2, 0, false, 0, 550));
			mobs.push_back(new Copter(-2500, 150, 0, -2, gRenderer, battleCopterTexture6, 0, false, 0, 550));

		}

		if(timer == 75 && !sec){
			mobs.push_back(new Copter(430, -50, 1, 2, gRenderer, copterTexture, timer, true));
		}


		if((timer == 20 || (timer%40 == 0 && timer>60)) && !sec){
			mobs.push_back(
				new Car(600, SCREEN_H - Car::H - 35, -2, gRenderer, carTexture));
		}

		if((timer == 30 || (timer%40 == 0 && timer>40)) && !sec){
			mobs.push_back(new Copter(-500, 160, 0, 2, gRenderer, copterTexture5, 0, false, 0, 550));
		}

		if(timer%30 == 0 && timer >=30 && !sec){
			mobs.push_back(new Copter(-500, 150, 0, -2, gRenderer, copterTexture2, 0, false, 0, 550));
		}
*/

		if(timer%30 == 0 && !sec && timer != 0){
			mobs.push_back(new Mod(SCREEN_W,100,1, gRenderer, modTexture));
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
				p.changeLives(mobs[i]->amountLivesToChange());
			}
		}

		for(int i = mobs.size()-1; i>=0; --i){
			if(mobs[i]->isDestroyed()){
				if(mobs[i]->needBoom()){
					mobs.push_back(new Explosion(mobs[i]->getQuad(), gRenderer, boomTexture));
				}
				mobs.erase(mobs.begin() + i);
			}
		}

		SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

		MenuTexture tTexture = tf(gFont,to_string(timer), gRenderer,
			textColor);
		SDL_Rect renderQuad = {
			SCREEN_W/2-tTexture.w/2,
			30,
			tTexture.w,
			tTexture.h};
		SDL_RenderCopyEx( gRenderer, tTexture.mTexture, NULL,
			&renderQuad, 0, NULL, SDL_FLIP_NONE );

		for(int i = 0; i < p.lives; ++i){
			livesQuad.x = livesQuad.x+livesQuad.w;
			SDL_RenderCopy( gRenderer, playerTexture, NULL, &livesQuad );
		}

		SDL_DestroyTexture(tTexture.mTexture);

		livesQuad = lQuad;

		for(int i = 0; i<mobs.size(); ++i){
			mobs[i]->render();
		}

		if(!p.isAlive()){
			ans = 1;
			quit = true;
			SDL_Delay(500);
			MenuTexture txt = tf(gFont,"ваш счёт", gRenderer,
				textColor);
			SDL_Rect qd = {
				SCREEN_W/2-txt.w/2,
				250,
				txt.w,
				txt.h};

			MenuTexture txt1 = tf(gFont,to_string(timer), gRenderer,
				textColor);
			SDL_Rect qd1 = {
				SCREEN_W/2-txt1.w/2,
				250+txt1.h,
				txt1.w,
				txt1.h};

			SDL_RenderCopy( gRenderer, menuTexture, NULL, NULL);
			SDL_RenderCopyEx( gRenderer, txt.mTexture, NULL,
				&qd, 0, NULL, SDL_FLIP_NONE );
			SDL_RenderCopyEx( gRenderer, txt1.mTexture, NULL,
				&qd1, 0, NULL, SDL_FLIP_NONE );
			SDL_RenderPresent(gRenderer);
			bool quit1 = false;
			while(!quit1){
				while( SDL_PollEvent( &e ) != 0 ){
					if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.repeat == 0 )){
						quit1 = true;
					}
				}
			}
			SDL_DestroyTexture(txt.mTexture);
			SDL_DestroyTexture(txt1.mTexture);
		}

		p.render();

		sec += 1;
		if(sec == 200){
			timer+=1;
			sec = 0;
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
	TTF_Font* gFont = TTF_OpenFont( "fonts/Marske.ttf", 35 );

	if( gFont == NULL )
	{
		printf( "Failed to load Floripa font! SDL_ttf Error: %s\n",
			TTF_GetError() );
	}

	SDL_Color textColor = { 0, 0, 0 };

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
					{"классика","выживание", "крестики-нолики", "выход"},
					gRenderer,
					menuTexture))
				{
					case 2:{
						switch(ticTacToe(gRenderer,menuTexture,fieldTexture, x1Texture, xTexture, oTexture)){
/*							case 0:{
								MenuTexture txt = tf(gFont,"вы сыграли в ничью", gRenderer,
									textColor);
								SDL_Rect qd = {
									SCREEN_W/2-txt.w/2,
									250,
									txt.w,
									txt.h};

								MenuTexture txt1 = tf(gFont,"ожидаемо", gRenderer,
									textColor);
								SDL_Rect qd1 = {
									SCREEN_W/2-txt1.w/2,
									250+txt1.h,
									txt1.w,
									txt1.h};

								SDL_RenderCopy( gRenderer, menuTexture, NULL, NULL);
								SDL_RenderCopyEx( gRenderer, txt.mTexture, NULL,
									&qd, 0, NULL, SDL_FLIP_NONE );
								SDL_RenderCopyEx( gRenderer, txt1.mTexture, NULL,
									&qd1, 0, NULL, SDL_FLIP_NONE );
								SDL_RenderPresent(gRenderer);
								bool quit1 = false;
								while(!quit1){
									while( SDL_PollEvent( &e ) != 0 ){
										if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.repeat == 0 )){
											quit1 = true;
										}
									}
								}
								SDL_DestroyTexture(txt.mTexture);
								SDL_DestroyTexture(txt1.mTexture);
							}break;
							case 1:{
								MenuTexture txt = tf(gFont,"вы победили", gRenderer,
									textColor);
								SDL_Rect qd = {
									SCREEN_W/2-txt.w/2,
									250,
									txt.w,
									txt.h};

								MenuTexture txt1 = tf(gFont,"читер чертов", gRenderer,
									textColor);
								SDL_Rect qd1 = {
									SCREEN_W/2-txt1.w/2,
									250+txt1.h,
									txt1.w,
									txt1.h};

								SDL_RenderCopy( gRenderer, menuTexture, NULL, NULL);
								SDL_RenderCopyEx( gRenderer, txt.mTexture, NULL,
									&qd, 0, NULL, SDL_FLIP_NONE );
								SDL_RenderCopyEx( gRenderer, txt1.mTexture, NULL,
									&qd1, 0, NULL, SDL_FLIP_NONE );
								SDL_RenderPresent(gRenderer);
								bool quit1 = false;
								while(!quit1){
									while( SDL_PollEvent( &e ) != 0 ){
										if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.repeat == 0 )){
											quit1 = true;
										}
									}
								}
								SDL_DestroyTexture(txt.mTexture);
								SDL_DestroyTexture(txt1.mTexture);
							}break;
							case -1:{
								MenuTexture txt = tf(gFont,"вы проиграли", gRenderer,
									textColor);
								SDL_Rect qd = {
									SCREEN_W/2-txt.w/2,
									250,
									txt.w,
									txt.h};

								MenuTexture txt1 = tf(gFont,"с кем не бывает", gRenderer,
									textColor);
								SDL_Rect qd1 = {
									SCREEN_W/2-txt1.w/2,
									250+txt1.h,
									txt1.w,
									txt1.h};

								SDL_RenderCopy( gRenderer, menuTexture, NULL, NULL);
								SDL_RenderCopyEx( gRenderer, txt.mTexture, NULL,
									&qd, 0, NULL, SDL_FLIP_NONE );
								SDL_RenderCopyEx( gRenderer, txt1.mTexture, NULL,
									&qd1, 0, NULL, SDL_FLIP_NONE );
								SDL_RenderPresent(gRenderer);
								bool quit1 = false;
								while(!quit1){
									while( SDL_PollEvent( &e ) != 0 ){
										if( e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.repeat == 0 )){
											quit1 = true;
										}
									}
								}
								SDL_DestroyTexture(txt.mTexture);
								SDL_DestroyTexture(txt1.mTexture);
							}break;
*/							case -2:
								quit = true;
							break;
							default:
							break;
						}
					}break;
					case 0:{
						if(gameMod1()==-1){quit = true;}
					}break;
					case 1:{
						if(gameMod2()==-1){quit = true;}
					}break;
					default:{
						quit = true;
					}break;
				}
			}
		}
	}

	close();

	return 0;
}
