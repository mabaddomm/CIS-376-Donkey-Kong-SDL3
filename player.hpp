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

class Barrel : public GameObject {
    public:
        Barrel(float x, float y, float w, float h);
	private:
};

#endif