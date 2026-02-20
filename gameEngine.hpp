#ifndef         __HPP_ENGINE__
#define         __HPP_ENGINE__

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "gameObjects.hpp"
#include "scene.hpp"
#include <vector>


#define FPS 60
#define MAX_EVENTS 128
#define targetFrameTime 1000.0 / FPS

class Scene;

class Engine {

    public: 
    //This should return just one instance of the Game Engine 
    //This follows the signleton game pattern
    static Engine& instance(){
        static Engine instance;
        return instance;
    }

    //Delete copy operators (Like code provided by woodring)
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    //This lets other classes draw without owning the renderer
    SDL_Renderer* getRenderer();
    
    //Changes the scene to scene we enter
    void setScene(Scene* scene);
    //Starts the enginge
    void run();

    Engine();
    ~Engine() = default;

    bool init();

    //bool loadImage(const char* path);

    void shutdown();


    //Here were are defining window as a SDL_windo
    SDL_Window* window; 

    //This is our Render for the game
    SDL_Renderer* renderer;

    SDL_Surface* surface;
    SDL_Texture* sprite;

    bool running = false; 

    //We are storing copies of events not pointers/ references each frame
    //Events are like our inputs and stuff
    //We can uses this to let scenes gameobjects or components see what inputs occured
    static std::vector<SDL_Event> keyEvents;

    //This is an example scene
    Scene* scene;

};

#endif