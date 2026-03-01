#include "gameEngine.hpp"
#include "player.hpp"
#include "gameMap.hpp"

int main() {

    Engine& engine = Engine::instance();
    
    Scene& levelOne = Scene::instance();
    Player* mario = new Player();

    levelOne.addObject(mario);
    levelOne.addObject(new Platform(0, 768, 1280, 32));
    levelOne.addObject(new Platform(0, 192, 1100, 32));
    levelOne.addObject(new Platform(180, 320, 1100, 32));
    levelOne.addObject(new Platform(0, 448, 1100, 32));
    levelOne.addObject(new Platform(180, 576, 1100, 32));

    levelOne.addObject(new Ladder(200, 160, 32, 160));
    //levelOne.addObject(new Barrel(100, 160, 32, 32));
    //levelOne->addObject(new Platform())

    for (int i = 0; i < 5; i++) {
    levelOne.addObject(new Barrel(100 + (i * 200), 160, 32, 32));
}

    engine.setScene(&levelOne);


    engine.run();
    engine.shutdown();

    return 0;
}