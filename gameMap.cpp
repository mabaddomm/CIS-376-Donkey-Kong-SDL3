#include "gameMap.hpp"
#include "gameEngine.hpp"
#include "gameObjects.hpp"
#include "scene.hpp"
#include <SDL3/SDL.h>

Platform::Platform(float x, float y, float w, float h) {

    SDL_Color color {139, 69, 19, 255};
    auto* box = addComponent<RedBoxComponent>(x, y, w, h, color);
    addComponent<CollisionComponent>(*box->getRect());
//    auto* sprite = addComponent<SpriteComponent>();
}
