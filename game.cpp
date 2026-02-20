#include "gameEngine.hpp"
#include "player.hpp"

int main() {

    Engine& engine = Engine::instance();
    
    Scene* levelOne = new Scene();
    Player* mario = new Player();

    levelOne->addObject(mario);
    engine.setScene(levelOne);


    engine.run();
    engine.shutdown();

    return 0;
}