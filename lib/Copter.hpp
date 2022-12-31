#ifndef COPTER_HPP
#define COPTER_HPP
#include "Mob.hpp"
#include "Constants.hpp"
#include "Rocket.hpp"

class Copter: public Mob{
	public:
		const static int W = 170, H = 65;
	private:
		SDL_Renderer* gRenderer = NULL;
		int speed = 0;
		int step = 0;
		int randMax = 0;
		int randMin = 0;
		int timer = 0;
		int playerY = 0;

		bool direction;
		bool fly_up = true;
		bool needSpawnChild = false;
		SDL_Texture* texture;
		SDL_Texture* childTexture;
		virtual void moveHor();
		virtual void moveVer();
	public:
		Copter(int x, int y, bool direction, int speedx,
			SDL_Renderer* gRenderer, SDL_Texture* copterTexture,
			int timer = 0, bool needSpawnChild = false,
			int randMin = 100, int randMax = 100);

		virtual ~Copter(){}

		virtual Mob* spawnChild(SDL_Texture* childTexture, long long timer,int sec);

		virtual void move();
		virtual void render();
		virtual int amountLivesToChange();
};

#endif
