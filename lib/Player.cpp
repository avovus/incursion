#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Player.hpp"
#include "Constants.hpp"

using namespace std;

Player::Player(
	int x, int y,
	SDL_Renderer* gRenderer,
	SDL_Texture* texture)
{
	this->gRenderer = gRenderer;
	this->texture = texture;
	quad.x = x;
	quad.y = y;
}

void Player::move() {
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

void Player::speedYUp(){
	if(speedY < 1){
		speedY += SPEED;
	}
}

void Player::speedYDown(){
	if(speedY > -1){
		speedY -= SPEED;
	}
}

void Player::speedXUp(){
	if(speedX < 1){
		speedX += SPEED;
	}
}

void Player::speedXDown(){
	if(speedX > -1){
		speedX -= SPEED;
	}
}

void Player::printSpeed(){
	cout << "speedX:" << speedX << endl;
	cout << "speedY:" << speedY << endl;
}

void Player::render(){
	SDL_RenderCopy( gRenderer, texture, NULL, &quad );
}
