#ifndef         __HPP_MAP__
#define         __HPP_MAP__

#include "gameObjects.hpp"
#include <SDL3/SDL.h>

class Platform : public GameObject {
    public: 
        Platform(float x, float y, float w, float h);

    private: 
};

class Ladder : public GameObject {
    public:
        Ladder(float x, float y, float w, float h, const char* imagePath);
    private:
};

class Platform2: public GameObject {
    public: 
        Platform2(float x, float y, float w, float h, const char* imagePath);
    private:
};


#endif 