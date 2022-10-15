#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Mob.hpp"

class Player{
	private:
		SDL_Rect quad = { 200, 300, W, H }; //хидбокс игрока
		SDL_Renderer* gRenderer = NULL;
		SDL_Texture* texture = NULL;
		int lives = 3;
		const static int W = 80, H = 50, SPEED = 1;
		int speedX = 0;
		int speedY = 0;
	public:
		Player(
			int, int,
			SDL_Renderer*,
			SDL_Texture*
		);
		bool isAlive();
		bool isCollided(Mob*);
		void decrLives();
		void move();
		void speedYUp();
		void speedYDown();
		void speedXUp();
		void speedXDown();
		void printSpeed();
		void render();
};

#endif
