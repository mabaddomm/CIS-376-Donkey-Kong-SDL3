// A Scene is a simple collection for game objects. You may also
// want to keep other information in a scene, like background color, etc.

#include "scene.hpp"
#include "gameObjects.hpp"

  void Scene::addObject(GameObject *go) { 
    game_objects.push_back(go); 
}
  
  
  void Scene::updateScene(float deltaTime) {
    for (auto it = game_objects.begin(); it != game_objects.end(); ++it) {
      (*it)->update(deltaTime);
    }
  }
