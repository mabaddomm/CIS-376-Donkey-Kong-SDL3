#include "gameEngine.hpp"

int main() {

    Engine& engine = Engine::instance();
    
    Scene* levelOne = new Scene();
    
    engine.setScene(levelOne);


    engine.run();
    engine.shutdown();

    return 0;
}