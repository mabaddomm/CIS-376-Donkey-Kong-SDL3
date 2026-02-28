#include "gameEngine.hpp"
#include "player.hpp"
#include "gameMap.hpp"

int main() {

    Engine& engine = Engine::instance();
    
    Scene& levelOne = Scene::instance();
    Player* mario = new Player();

    levelOne.addObject(mario);
    levelOne.addObject(new Platform(0, 768, 1280, 32));
    levelOne.addObject(new Platform(0, 200, 1100, 32));
    levelOne.addObject(new Platform(180, 332, 1100, 32));
    levelOne.addObject(new Platform(0, 464, 1100, 32));
    levelOne.addObject(new Platform(180, 600, 1100, 32));
    //levelOne->addObject(new Platform())

    engine.setScene(&levelOne);


    engine.run();
    engine.shutdown();

    return 0;
}