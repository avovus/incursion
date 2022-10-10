#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Menu.hpp"
#include "Constants.hpp"

struct MenuTexture{
	SDL_Texture* mTexture;
	int w, h;
};

MenuTexture mtf(TTF_Font* font, string item, SDL_Renderer* gRenderer,
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

int menu(
	const vector <string>& items,
	SDL_Renderer* gRenderer,
	SDL_Texture* menuTexture)
{
	int ans = 0;
	SDL_Color textColor = { 0, 0, 0 };
	SDL_Color selectedColor = { 10, 150, 10 };
	vector <MenuTexture> menuTextures;
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n",
			TTF_GetError() );
		return -1;
	}

	TTF_Font* gFont = TTF_OpenFont( "fonts/Marske.ttf", 35 );

    if( gFont == NULL )
    {
        printf( "Failed to load Floripa font! SDL_ttf Error: %s\n",
			TTF_GetError() );
        return -1;
    }

	bool quit = false;

	int ind = 0;

	while( !quit )
	{
		int c = 100;
		for(int i = 0; i<items.size();++i){
			menuTextures.push_back(mtf(gFont,items[i], gRenderer,
				ind==i? selectedColor:textColor));
		}
		SDL_RenderCopy( gRenderer, menuTexture, NULL, NULL );
		for(int i = 0; i<menuTextures.size();++i){
			SDL_Rect renderQuad = {
				SCREEN_W/2-menuTextures[i].w/2,
				c+=50,
				ind==i? menuTextures[i].w+7:menuTextures[i].w,
				ind==i? menuTextures[i].h+7:menuTextures[i].h };
			SDL_RenderCopyEx( gRenderer, menuTextures[i].mTexture, NULL,
				&renderQuad, 0, NULL, SDL_FLIP_NONE );
			SDL_DestroyTexture(menuTextures[i].mTexture);
		}
		menuTextures.clear();
		SDL_RenderPresent( gRenderer );
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
						if(--ind<0){
							ind = items.size()-1;
						}
					break;

					case SDLK_s:
					case SDLK_DOWN:
						if(++ind>=items.size()){
							ind = 0;
						}
					break;

					case SDLK_SPACE:
						ans = ind;
						quit = true;
					break;

					case SDLK_ESCAPE:
						ans = -2;
						quit = true;
						break;
				}
			}
		}
	}
	TTF_CloseFont(gFont);
	return ans;
}
