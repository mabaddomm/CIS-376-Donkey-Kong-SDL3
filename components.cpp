#include "components.hpp"
#include "gameObjects.hpp"
#include "gameEngine.hpp"
#include "scene.hpp"

//#include <glm/vec4.hpp>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>

GameObject* Component::getOwner() const {
    return owner;
}

void Component::setOwner(GameObject* go) {
    owner = go;
}

void SpriteComponent::setX(int x) {
    destRect.x = x;
}

void SpriteComponent::setY(int y) {
    destRect.y = y;
}

bool SpriteComponent::loadSprite(SDL_Renderer* renderer, char* path, SDL_FRect rect) {
    // Hard coding this for my sample game that uses 64x64 sprites.
    // You may need to adjust and/or have variable sizes.
    destRect = rect;
    this->renderer = renderer;

    // Surfaces are software based, so slow.  But, we need them
    // when loading.
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("IMG_Load Error: %s", SDL_GetError());
        return false;
    }

    // Now create a hardware-based renderer and delete the software one.
    sprite = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    return sprite != nullptr;
}

// Sometimes we might need to get the image.
SDL_Texture* SpriteComponent::getSprite() {
    return sprite;
}

void SpriteComponent::update(float) {
    if (sprite) {
        SDL_RenderTexture(renderer, sprite, nullptr, &destRect);
    } else {
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
        SDL_RenderFillRect(renderer, &destRect);
    }
}

// The destRect is where and how much of the image will be drawn.
SDL_FRect* SpriteComponent::getRect(){
    return &destRect;
}


void PlayerInputComponent::update(float dt){
    auto* owner = getOwner();

    auto* playerSprite = owner->getComponent<SpriteComponent>();

    SDL_FRect* playerRect = playerSprite->getRect();

    for (auto it = Engine::keyEvents.begin(); 
        it != Engine::keyEvents.end(); ++it){

            float originalX = playerRect->x;
            float originalY = playerRect->y;
    
            if (it->type == SDL_EVENT_KEY_DOWN) {

            if (it->key.key == SDLK_W){
                playerRect->y -= pps *dt;
            }
            if (it->key.key == SDLK_S){
                playerRect->y += pps *dt;
            }
            if(it->key.key == SDLK_A){
                playerRect->x -= pps *dt;
            }
            if (it->key.key == SDLK_D){
                playerRect->x += pps *dt;
            }

            bool collided = false;
            for (auto* go : Scene::instance().getObjects()) {
                auto* col = go->getComponent<CollisionComponent>();
                if (col) {
                    if (SDL_HasRectIntersectionFloat(playerRect, col->getRect())) {
                        collided = true;
                        break;
                    }
                }
            } 

            // If collided revert position
            if (collided) {
                playerRect->x = originalX;
                playerRect->y = originalY;
            } 
        }
    }
}

RedBoxComponent::RedBoxComponent(float x, float y, float w, float h, SDL_Color color)
    : rect {x, y, w, h}, color(color){}

void RedBoxComponent::update(float) {
    SDL_Renderer* renderer = Engine::instance().getRenderer();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

SDL_FRect* RedBoxComponent::getRect() { return &rect; }


//Declaring the Collision component
CollisionComponent::CollisionComponent(SDL_FRect rect) 
    : rect(rect){}

SDL_FRect* CollisionComponent::getRect() {
    return &rect;
}