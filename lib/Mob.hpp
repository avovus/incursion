#ifndef MOB_HPP
#define MOB_HPP
#include <SDL2/SDL.h>

class Mob{
	private:
		bool isAlive = true;
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

		SDL_Rect getQuad(){
			return quad;
		}
		void destroy(){
			isAlive = false;
		}
		bool isDestroyed(){
			return !isAlive;
		}
		virtual ~Mob() {};
};

#endif
