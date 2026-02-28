#ifndef     __HPP_SCENE__
#define     __HPP_SCENE__

#include <vector>


class GameObject;
// A Scene is a simple collection for game objects. You may also
// want to keep other information in a scene, like background color, etc.


class Scene {
  public: 

  static Scene& instance(){
      static Scene instance;
      return instance;
  }
    // Delete copy operators like Engine
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;


    void addObject(GameObject *go);
    void updateScene(float deltaTime);
    std::vector<GameObject*> & getObjects();

    private:
    Scene() = default;
    std::vector<GameObject *> game_objects;
};

#endif