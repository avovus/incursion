#ifndef MENU_HPP
#define MENU_HPP
#include <string>
#include <vector>

using namespace std;

int menu(
	const vector <string> & items,
	SDL_Renderer* gRenderer,
	SDL_Texture* menuTexture);

#endif
