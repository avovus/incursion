#ifndef ROCKET_HPP
#define ROCKET_HPP
#include "Mob.hpp"
#include "Constants.hpp"

class Rocket: public Mob{
	public:
		const static int W = 60, H = 32;
	private:
		SDL_Renderer* gRenderer = NULL;
		int speed = 0;
		int step = 0;
		SDL_Texture* texture;
	public:
		Rocket(int x, int y, int speedx,
			SDL_Renderer* gRenderer, SDL_Texture* rocketTexture);

		virtual ~Rocket() {};

		virtual void move();
		virtual void render();
};

#endif
