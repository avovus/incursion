#ifndef COPTER_HPP
#define COPTER_HPP
#include "Mob.hpp"
#include "Constants.hpp"

class Copter: public Mob{
	public:
		const static int W = 140, H = 60;
	private:
		SDL_Renderer* gRenderer = NULL;
		int speed = 0;
		int step = 0;
		bool direction;
		bool fly_up = true;
		SDL_Texture* texture;
		virtual void moveHor();
		virtual void moveVer();
	public:
		Copter(int x, int y, bool direction, int speedx, SDL_Renderer* gRenderer, SDL_Texture* copterTexture);

		virtual ~Copter(){}

		virtual void move();
		virtual void render();
};

#endif
