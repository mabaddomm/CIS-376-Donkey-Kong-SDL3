#include "player.hpp"
#include "gameEngine.hpp"
#include "gameObjects.hpp"
#include <SDL3/SDL.h>

//We need a player constructor
Player::Player() {

    //This is adding a sprite compponet to the game object
    auto* spriteComponent = addComponent<SpriteComponent>();
    //load the pciturue s
    spriteComponent->loadSprite(Engine::instance().getRenderer(), "sprite.png");
    
	/*
    spriteComp->setX(100);
    spriteComp->setY(100);*/
    
    //Rect = SpriteComponent->getRect();
	auto* playerInputComponent = addComponent<PlayerInputComponent>();
}

/*
void Player::update(float deltaTime) {

    //
    GameObject::update(deltaTime);
	for(auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it){
		if(it->key.key == SDLK_W){
			up(deltaTime);
		}
		if(it->key.key == SDLK_S){
			down(deltaTime);
		}
		if(it->key.key == SDLK_A){
			left(deltaTime);
		}
		if(it->key.key == SDLK_D){
			right(deltaTime);
		}
	}
}

// Movement should be based on the time that has passed
// for smoothest motion.
void Player::up(float dt){
	rect->y -= pps * dt;
}

void Player::down(float dt){
	rect->y += pps * dt;
}

void Player::left(float dt){
	rect->x -= pps * dt;
}

void Player::right(float dt){
	rect->x += pps * dt;
} */

