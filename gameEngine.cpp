#include "gameEngine.hpp"

//#include "game_objects.hpp"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
std::vector<SDL_Event> Engine::keyEvents;

Engine::Engine() {init();}

//This asks for the renderer in case something else needs to be drawn
SDL_Renderer* Engine::getRenderer() {
    return this->renderer; 
}; 

//Can use it to change the scene to what scene you want
void Engine::setScene(Scene *scene) {
    this -> scene = scene
;}


//This loops through the game over and over again until it quits
/*It gets delta time, and colleect inputs, update the scenes, renders and frame limits*/
void Engine::run() {
    //A frect a struct that is used to store x, and y positions with w, and h being widtha and height
    //SDL_FRect destRect = {100, 100, 500, 500};

    Uint64 frameStart = 0;
    Uint64 lastTime = SDL_GetTicks();
    Uint64 fpsLastTime = SDL_GetTicks();
    unsigned int frameCount = 0;



    running = true;
    while (running) {

        frameStart = SDL_GetTicks();
        frameCount++;

        //Get delta time
        Uint64 currentTime = SDL_GetTicks();

        //Gets delta time to make movemmement frame-rate independent
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        //FPS counter
        if (frameStart- fpsLastTime >= 1000) {
            float fps = frameCount / ((frameStart - fpsLastTime) / 1000.0f);
            SDL_Log("FPS: %.2f", fps);
            frameCount = 0;
            fpsLastTime = frameStart;
        }

        //These events are what are going ot handle inpiut
        Engine::keyEvents.clear();
        SDL_Event event;

        //This loop cplls to see if all events(input) are handled 
        while (SDL_PollEvent(&event)) {
            //This is a close event in a way 
            if (event.type == SDL_EVENT_QUIT) {
                SDL_Log("Shutting down ...");
                running = false; 
            }
            //This stores to see if a key is preessed and stores it
            //It doesn't do actually handle input it stores it

            if (event.type == SDL_EVENT_KEY_DOWN) {
                // Since we are storing copies of events, this
				// works.  Would not work if we were storing pointers
				// as event is a local variable to this function and
				// would always have the same address.
                Engine::keyEvents.push_back(event);
            }
        }

        /*
        if (scene) {
            scene->updateScene(deltaTime);
        }*/

        //Render starts doign its drawing
        SDL_SetRenderDrawColor(renderer, 136, 206 ,235 , 255);
        SDL_RenderClear(renderer);
        //TEST
        scene->updateScene(deltaTime);
        SDL_RenderPresent(renderer);
        // Naive delay that doesn't take into account
		// how long the loop ran.

        //This limits frames 
        Uint64 frameTime = SDL_GetTicks() - frameStart;
		if(frameTime < targetFrameTime) {
            SDL_Delay(targetFrameTime - frameTime);
        }
    }

}


//This creates the window,, and the renderer its like a startup system
bool Engine::init(){
    if (!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }


    //Creates a window, and this windo is what we draw on
    window = SDL_CreateWindow("My Game",
        1280, 800, 0
        //SDL_WINDOW_FULLSCREEN
    );
    //This checks to make sure the window was created
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    //This is the rendere the renderer is what draws to the window of the screen
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //Turn off Vysnc 
    /*from my understanding vysnc can sysnchronize the 
    frame rate with the motitors fresh rate, to prevent screen tearing
    The down side is that if can dip the frames to but 
    instead we will use the eninge and control it ourselves.*/
    SDL_SetRenderVSync(renderer, 0);

    return true;
}

//Destorys window, renderer and ssl
void Engine::shutdown() {
        //SDL_DestroyTexture(sprite);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
/* I realized this was done in components and didn't need it in engine :(
bool Engine::loadImage(const char* path){
    surface = IMG_Load(path);
    if (!surface) {
        printf("IMG_Load Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    sprite = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if(!sprite){
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1; 
    }

    return 0;
} */