#include "gameMap.hpp"
#include "gameEngine.hpp"
#include "gameObjects.hpp"
#include "scene.hpp"
#include <SDL3/SDL.h>

Platform::Platform(float x, float y, float w, float h) {

    SDL_Color color {139, 69, 19, 255};
    //auto* spriteComponent = addComponent<SpriteComponent>();
    //auto* box = spriteComponent->loadSprite(Engine::instance().getRenderer(), "resized_one of the bars.png"); //{0, 768, 1280, 32});
    auto* box = addComponent<RedBoxComponent>(x, y, w, h, color);
    addComponent<CollisionComponent>(*box->getRect());
//    auto* sprite = addComponent<SpriteComponent>();
}

/*
Ladder::Ladder(float x, float y, float w, float h) {
    addComponent<RedBoxComponent>(x, y, w, h, SDL_Color{139, 69, 19, 255});
    
    addComponent<LadderComponent>(SDL_FRect{x, y, w, h});
}*/

Ladder::Ladder(float x, float y, float w, float h, const char* imagePath) {
    if (imagePath) {
        auto* spriteComponent = addComponent<SpriteComponent>();
        spriteComponent->loadSprite(Engine::instance().getRenderer(), imagePath, {x, y, w, h});
    } else {
        addComponent<RedBoxComponent>(x, y, w, h, SDL_Color{139, 69, 19, 255});
    }
    addComponent<LadderComponent>(SDL_FRect{x, y, w, h});
}

Platform2::Platform2(float x, float y, float w, float h, const char* imagePath) {
    auto* spriteComponent = addComponent<SpriteComponent>();
    spriteComponent->loadSprite(Engine::instance().getRenderer(), imagePath, {x, y, w, h});
    addComponent<CollisionComponent>(SDL_FRect{x, y, w, h});
}