#ifndef CLYN_HPP
#define CLYN_HPP
#include "Mob.hpp"

class Clyn: public Mob{
	private:
		SDL_Renderer* gRenderer = NULL;
		bool boom = false;
		bool fly_up = true;
		int live = 20;
		bool angry = false;
		int step = 0;
		SDL_Texture* texture = NULL;

	public:
		Clyn(int x, int y,SDL_Renderer* gRenderer,SDL_Texture* texture);

		virtual ~Clyn() {};

		virtual void move();

		virtual void render();
};

#endif
