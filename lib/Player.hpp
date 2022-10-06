#include "Constants.hpp"

class Player{
	private:
		SDL_Rect quad = { 200, 300, W, H }; //хидбокс игрока	
		SDL_Texture* texture = NULL;
		const static int W = 80, H = 50, SPEED = 1;
		int speedX = 0;
		int speedY = 0;
	public:
		Player(int x, int y, SDL_Texture* texture){
			this -> texture = texture;
			quad.x = x;
			quad.y = y;
		}
		
		void move(){
			if(speedY > 0){
				if(quad.y+speedY+H >= SCREEN_H){
					quad.y+=(SCREEN_H - (quad.y+H));
				}											
				else{
					quad.y += speedY;
				}
			}
			else{
				if(quad.y+speedY < 0){
					quad.y = 0;
				}											
				else{
					quad.y += speedY;
				}				
			}
			if(speedX > 0){
				if(quad.x+speedX+W >= SCREEN_W){
					quad.x +=(SCREEN_W - (quad.x+W));
				}											
				else{
					quad.x += speedX;
				}
			}
			else{
				if(quad.x+speedX < 0){
					quad.x = 0;
				}											
				else{
					quad.x += speedX;
				}				
			}
			
			
		}
		void speedYUp(){
			if(speedY < 1){
				speedY += SPEED;
			}
		}
		void speedYDown(){
			if(speedY > -1){
				speedY -= SPEED;
			}
		}
		void speedXUp(){
			if(speedX < 1){
				speedX += SPEED;
			}
		}
		void speedXDown(){
			if(speedX > -1){
				speedX -= SPEED;
			}
		}
		
		void printSpeed(){
			cout << "speedX:" << speedX << endl;
			cout << "speedY:" << speedY << endl;
		}
		void render(){
			SDL_RenderCopy( gRenderer, texture, NULL, &quad );
		}	
		
		
};
