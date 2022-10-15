#ifndef CAR_HPP
#define CAR_HPP
#include "Mob.hpp"
#include "Constants.hpp"

class Car: public Mob{
	public:
		const static int W = 80, H = 40;
	private:
		SDL_Renderer* gRenderer = NULL;
		bool boom = false;
		int speedx = 0;
		SDL_Texture* texture;
	public:
		Car(int x, int y, int speedx, SDL_Renderer* gRenderer, SDL_Texture* carTexture);

		virtual ~Car(){}

		virtual void move();
		virtual void render();
};

#endif
