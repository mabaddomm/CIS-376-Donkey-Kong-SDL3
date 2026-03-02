#include "gameEngine.hpp"
#include "player.hpp"
#include "gameMap.hpp"

int main() {

    Engine& engine = Engine::instance();
    
    Scene& levelOne = Scene::instance();
    Player* mario = new Player();

    levelOne.addObject(mario);

    //Platfrom 1 ladder
    levelOne.addObject(new Ladder(320, 624, 32, 144, "newnormalLadders.png"));
    levelOne.addObject(new Ladder(960, 736, 32, 48, "newsmallLadders.png"));
    //Platform 2
    levelOne.addObject(new Ladder(928, 496, 32, 144, "newnormalLadders.png"));
    levelOne.addObject(new Ladder(128, 544, 32, 48, "newsmallLadders.png"));
    //Platfrom 3ladders 
    levelOne.addObject(new Ladder(800, 368, 32, 144, "newnormalLadders.png"));
    levelOne.addObject(new Ladder(288, 368, 32, 144, "newnormalLadders.png"));
    //Playfrom 4 ladders
    levelOne.addObject(new Ladder(992, 240, 32, 144, "newnormalLadders.png"));
    //Platform 5 ladders 
   levelOne.addObject(new Ladder(160, 288, 32, 48, "newsmallLadders.png"));

   levelOne.addObject(new Ladder(368, 112, 32, 144, "newnormalLadders.png"));
    levelOne.addObject(new Ladder(564, 112, 32, 144, "newnormalLadders.png"));

    
    //levelOne.addObject(new Platform(0, 768, 1280, 32));
    levelOne.addObject(new Platform2(0, 768, 1280, 32, "newbottomPlatform.png"));
    levelOne.addObject(new Platform2(230, 640, 1050, 32, "newSmallerBar.png"));
    levelOne.addObject(new Platform2(0, 512, 1050, 32, "newSmallerBar.png"));
    levelOne.addObject(new Platform2(230, 384, 1050, 32, "newSmallerBar.png"));
    levelOne.addObject(new Platform2(0, 256, 1050, 32, "newSmallerBar.png"));

    levelOne.addObject(new Platform2(336, 128, 288, 32, "newfinalPlatfrom.png"));

    for (int i = 0; i < 5; i++) {
    levelOne.addObject(new Barrel(100 + (i * 200), 160, 32, 32));
}

    engine.setScene(&levelOne);


    engine.run();
    engine.shutdown();

    return 0;
}