#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player{
	private:
		SDL_Rect quad = { 200, 300, W, H }; //хидбокс игрока
		SDL_Renderer* gRenderer = NULL;
		SDL_Texture* texture = NULL;
		const static int W = 80, H = 50, SPEED = 1;
		int speedX = 0;
		int speedY = 0;
	public:
		Player(
			int x, int y,
			SDL_Renderer* gRenderer,
			SDL_Texture* texture);
		void move();
		void speedYUp();
		void speedYDown();
		void speedXUp();
		void speedXDown();
		void printSpeed();
		void render();
};

#endif
