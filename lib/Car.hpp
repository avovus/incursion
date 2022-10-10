#ifndef CAR_HPP
#define CAR_HPP
#include "Mob.hpp"
#include "Constants.hpp"

class Car: public Mob{
	public:
		const static int W = 80, H = 40;
	private:
		SDL_Rect quad = { 600, SCREEN_H-H-35, W, H };
		SDL_Renderer* gRenderer = NULL;
		bool boom = false;
		bool is_on = true;
		int live = 1;
		int speedx = 0;
		SDL_Texture* texture;
	public:
		Car(int x, int y, int speedx, SDL_Renderer* gRenderer, SDL_Texture* carTexture);

		virtual ~Car(){}

		virtual void move();
		virtual void render();
};

#endif
