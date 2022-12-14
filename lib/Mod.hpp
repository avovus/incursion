#ifndef MOD_HPP
#define MOD_HPP
#include "Mob.hpp"
#include "Constants.hpp"
#include <time.h>
#include <stdlib.h>
#include <vector>

class Mod: public Mob{
	public:
		const static int W = 40, H = 40;
	private:
		SDL_Renderer* gRenderer = NULL;
		int speed = 0;
		int step = 0;
		int x = SCREEN_W;
		bool nKill;
		int y = 100;//50 + rand() % 450;
		SDL_Texture* texture;
	public:
		Mod(int x, int y, int speed,SDL_Renderer* gRenderer, SDL_Texture* modTexture, bool nKill = false);

		virtual ~Mod() {};

		virtual void move();
		virtual void render();
		virtual bool isCollidable();
		virtual bool needBoom();
		virtual bool needKill();
		virtual int amountLivesToChange();
};

#endif
