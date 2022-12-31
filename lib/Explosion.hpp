#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP
#include "Mob.hpp"
#include "Constants.hpp"
#include <time.h>
#include <stdlib.h>

class Explosion: public Mob{
	public:
	private:
		SDL_Renderer* gRenderer = NULL;
		int step = 0;
		SDL_Texture* texture;
		int W = 50, H = 50;
		int x = SCREEN_W;
		int y = 100;
	public:
		Explosion(SDL_Rect quad, SDL_Renderer* gRenderer, SDL_Texture* boomTexture);

		virtual ~Explosion() {};
		virtual void move();
        virtual bool isCollidable();
        virtual bool needBoom();
		virtual int amountLivesToChange();
		virtual void render();
};

#endif
