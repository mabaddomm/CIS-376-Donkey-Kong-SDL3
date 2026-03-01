#include "player.hpp"
#include "gameEngine.hpp"
#include "gameObjects.hpp"
#include <SDL3/SDL.h>

//We need a player constructor
Player::Player() {

    //This is adding a sprite compponet to the game object
    auto* spriteComponent = addComponent<SpriteComponent>();
    //load the pciturue s
    spriteComponent->loadSprite(Engine::instance().getRenderer(), "sprite.png", {50, 160, 32, 32});
    
	/*
    spriteComp->setX(100);
    spriteComp->setY(100);*/
    
    //Rect = SpriteComponent->getRect();
	auto* playerInputComponent = addComponent<PlayerInputComponent>();
    auto* gravity = addComponent<GravityComponent>();
}

Barrel::Barrel(float x, float y, float w, float h) {
    auto* spriteComponent = addComponent<SpriteComponent>();
    spriteComponent->loadSprite(Engine::instance().getRenderer(), "sprite.png", {x, y, w, h});
    addComponent<GravityComponent>();
    addComponent<BarrelMovementComponent>(600.0f);
}