#ifndef MOD_HPP
#define MOD_HPP
#include "Mob.hpp"
#include "Constants.hpp"
#include <time.h>
#include <stdlib.h>

class Mod: public Mob{
	public:
		const static int W = 30, H = 30;
	private:
		SDL_Renderer* gRenderer = NULL;
		int speed = 0;
		int step = 0;
		int x = SCREEN_W;
		int y = 100;//50 + rand() % 450;
		SDL_Texture* texture;
	public:
		Mod(int x, int y, int speed,SDL_Renderer* gRenderer, SDL_Texture* modTexture);

		virtual ~Mod() {};

		virtual void move();
		virtual void render();
		virtual int amountLivesToChange();
};

#endif
