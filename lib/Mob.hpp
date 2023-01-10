#ifndef MOB_HPP
#define MOB_HPP
#include <SDL2/SDL.h>

class Mob{
	private:
		bool isAlive = true;
		int c = 0;
	protected:
		SDL_Rect quad;
	public:
		Mob(SDL_Rect quad){
			this->quad = quad;
		};
		virtual void move() = 0;
		virtual void render() = 0;

		virtual Mob* spawnChild(SDL_Texture* childTexture,long long timer, int sec){
			return NULL;
		}

		virtual bool isCollidable(){
			return true;
		}

		virtual bool needBoom(){
			return true;
		}

		virtual bool needKill(){
			return false;
		}

		virtual int amountLivesToChange(){
			return -1;
		}

		SDL_Rect getQuad(){
			return quad;
		}

/*
		SDL_Rect getQuadPtr(){
			return &quad;
		}
*/

		void destroy(){
//			c++;
//			if(c == 10){
				isAlive = false;
//				c = 0;
//			}
		}
		bool isDestroyed(){
			return !isAlive;
		}

		virtual ~Mob() {};
};

#endif
