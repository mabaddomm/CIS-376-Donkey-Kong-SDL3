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

bool SpriteComponent::loadSprite(SDL_Renderer* renderer, const char* path, SDL_FRect rect) {
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

/*
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
                    SDL_FRect* platformRect = col->getRect();
                    if (SDL_HasRectIntersectionFloat(playerRect, col->getRect())) {
                        collided = true;
                        SDL_Log("Collision detected!");
            SDL_Log("Player rect: x:%.1f y:%.1f w:%.1f h:%.1f", 
                playerRect->x, playerRect->y, playerRect->w, playerRect->h);
            SDL_Log("Platform rect: x:%.1f y:%.1f w:%.1f h:%.1f", 
                platformRect->x, platformRect->y, platformRect->w, platformRect->h);
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
}*/

/* getting rid of this for a version with potential gravity left right
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
                playerRect->y -= pps * dt;
            }
            if (it->key.key == SDLK_S){
                playerRect->y += pps * dt;
            }
            if(it->key.key == SDLK_A){
                playerRect->x -= pps * dt;
            }
            if (it->key.key == SDLK_D){
                playerRect->x += pps * dt;
            }

            if (it->key.key == SDLK_SPACE) {
                auto* gravity = getOwner()->getComponent<GravityComponent>();
                if (gravity) gravity->jump();
            }

            bool collided = false;
            for (auto* go : Scene::instance().getObjects()) {
                auto* col = go->getComponent<CollisionComponent>();
                if (col) {
                    SDL_FRect* platformRect = col->getRect();
                    if (SDL_HasRectIntersectionFloat(playerRect, platformRect)) {
                        // Calculate actual Y overlap
                        float playerBottom = playerRect->y + playerRect->h;
                        float overlapY = playerBottom - platformRect->y;

                        // Calculate actual X overlap
                        float playerRight = playerRect->x + playerRect->w;
                        float overlapX = playerRight - platformRect->x;

                       // SDL_Log("overlapX:%.1f overlapY:%.1f platform y:%.1f",  overlapX, overlapY, platformRect->y);

                        // Only count as real collision if overlap is significant
                        if (overlapY > 0.5f && overlapX > 18.0f) {
                            collided = true;
                            break;
                        }
                    }
                }
            } 

            if (collided) {
                playerRect->x = originalX;
                playerRect->y = originalY;
            } 
        }
    }
}*/

/* Was working but now need to do ladders 
void PlayerInputComponent::update(float dt){
    auto* owner = getOwner();
    auto* playerSprite = owner->getComponent<SpriteComponent>();
    SDL_FRect* playerRect = playerSprite->getRect();

    for (auto it = Engine::keyEvents.begin(); 
        it != Engine::keyEvents.end(); ++it){
    
        if (it->type == SDL_EVENT_KEY_DOWN) {

            // Handle jumping
            if (it->key.key == SDLK_SPACE) {
                auto* gravity = getOwner()->getComponent<GravityComponent>();
                if (gravity) gravity->jump();
            }

            // Handle horizontal movement
            if (it->key.key == SDLK_A || it->key.key == SDLK_D) {
    float originalX = playerRect->x;

    if (it->key.key == SDLK_A) playerRect->x -= pps * dt;
    if (it->key.key == SDLK_D) playerRect->x += pps * dt;

    SDL_Log("Trying to move, new x: %.1f", playerRect->x);

    bool collided = false;
    for (auto* go : Scene::instance().getObjects()) {
        auto* col = go->getComponent<CollisionComponent>();
        if (col) {
            SDL_FRect* platformRect = col->getRect();
            if (SDL_HasRectIntersectionFloat(playerRect, platformRect)) {
                float playerBottom = playerRect->y + playerRect->h;
                float overlapY = playerBottom - platformRect->y;
                SDL_Log("Hit platform! overlapY: %.1f platformH: %.1f", overlapY, platformRect->h);
                if (overlapY > 2.0f && overlapY < platformRect->h) {
                    collided = true;
                    break;
                }
            }
        }
    }

    SDL_Log("collided: %d, final x: %.1f", collided, playerRect->x);
    if (collided) playerRect->x = originalX;
                }
            }
        }
    } */

void PlayerInputComponent::update(float dt){
    auto* owner = getOwner();
    auto* playerSprite = owner->getComponent<SpriteComponent>();
    SDL_FRect* playerRect = playerSprite->getRect();
    auto* gravity = owner->getComponent<GravityComponent>();

    for (auto it = Engine::keyEvents.begin(); 
        it != Engine::keyEvents.end(); ++it){
    
        if (it->type == SDL_EVENT_KEY_DOWN) {

            // Check if W is pressed and player is overlapping a ladder
            if (it->key.key == SDLK_W) {
                bool nearLadder = false;
                for (auto* go : Scene::instance().getObjects()) {
                    auto* ladder = go->getComponent<LadderComponent>();
                    if (ladder) {
                        if (SDL_HasRectIntersectionFloat(playerRect, ladder->getRect())) {
                            nearLadder = true;
                            break;
                        }
                    }
                }
                if (nearLadder) {
                    if (gravity) gravity->setOnLadder(true);
                    playerRect->y -= pps * dt;
                } 
            }

            // S climbs down if on ladder
            if (it->key.key == SDLK_S) {
                if (gravity && gravity->isOnLadder()) {
                    playerRect->y += pps * dt;
                }
            }

            // Horizontal movement
            if (it->key.key == SDLK_A || it->key.key == SDLK_D) {
                // Leave ladder when moving horizontally
                if (gravity) gravity->setOnLadder(false);
                
                float originalX = playerRect->x;

                if (it->key.key == SDLK_A) playerRect->x -= pps * dt;
                if (it->key.key == SDLK_D) playerRect->x += pps * dt;

                bool collided = false;
                for (auto* go : Scene::instance().getObjects()) {
                    auto* col = go->getComponent<CollisionComponent>();
                    if (col) {
                        SDL_FRect* platformRect = col->getRect();
                        if (SDL_HasRectIntersectionFloat(playerRect, platformRect)) {
                            float playerBottom = playerRect->y + playerRect->h;
                            float overlapY = playerBottom - platformRect->y;
                            if (overlapY > 2.0f && overlapY < platformRect->h) {
                                collided = true;
                                break;
                            }
                        }
                    }
                }
                if (collided) playerRect->x = originalX;
            }

            // Jump - only when grounded, not on ladder
            if (it->key.key == SDLK_SPACE) {
                if (gravity && !gravity->isOnLadder()) gravity->jump();
            }
        }
    }

    // If on ladder but no longer overlapping it, release
    if (gravity && gravity->isOnLadder()) {
        bool stillOnLadder = false;
        for (auto* go : Scene::instance().getObjects()) {
            auto* ladder = go->getComponent<LadderComponent>();
            if (ladder) {
                if (SDL_HasRectIntersectionFloat(playerRect, ladder->getRect())) {
                    stillOnLadder = true;
                    break;
                }
            }
        }
        if (!stillOnLadder) gravity->setOnLadder(false);
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

//New stuff

void GravityComponent::update(float dt) {
    auto* owner = getOwner();
    auto* spriteComp = owner->getComponent<SpriteComponent>();
    SDL_FRect* rect = spriteComp->getRect();
    //SDL_Log("velocityY: %.1f rect y: %.1f", velocityY, rect->y);

    if (onLadder) {
        velocityY = 0.0f;
        return;
    }

    // Apply gravity
    velocityY += gravity * dt;

    // Move down
    rect->y += velocityY * dt;

    // Check collision with platforms
    grounded = false;
    for (auto* go : Scene::instance().getObjects()) {
        auto* col = go->getComponent<CollisionComponent>();
        if (col) {
            SDL_FRect* platformRect = col->getRect();
            if (SDL_HasRectIntersectionFloat(rect, platformRect)) {
                // Only resolve if falling down
                if (velocityY > 0) {
                    rect->y = platformRect->y - rect->h;
                    velocityY = 0.0f;
                    grounded = true;
                }
            }
        }
    }
}

void GravityComponent::jump() {
    if (grounded) {
        velocityY = -jumpForce;
        grounded = false;
    }
}

LadderComponent::LadderComponent(SDL_FRect rect) 
    : rect(rect) {}

SDL_FRect* LadderComponent::getRect() {
    return &rect;
}

void BarrelMovementComponent::update(float dt) {
    auto* owner = getOwner();
    auto* spriteComp = owner->getComponent<SpriteComponent>();
    SDL_FRect* rect = spriteComp->getRect();

    // Move horizontally
    rect->x += speed * direction * dt;

    // Flip direction at screen edges
    if (rect->x <= 0) {
        rect->x = 0;
        direction = 1.0f;
    }
    if (rect->x + rect->w >= 1280) {
        rect->x = 1280 - rect->w;
        direction = -1.0f;
    }
}