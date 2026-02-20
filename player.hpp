#ifndef         __HPP_PLAYER__
#define         __HPP_PLAYER__ 

#include "gameObjects.hpp"
#include "SDL3/SDL.h"


class Player : public GameObject {
	public:
		Player();
		//void update(float deltaTime) override;
	private:
		//SDL_FRect* rect;
		//float pps = 10.0;
}; 

#endif