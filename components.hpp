#ifndef __HPP_COMPONENTS__
#define __HPP_COMPONENTS__

#include <functional>
#include <SDL3/SDL.h>
//#include <glm/vec4.hpp>
#include <unordered_map>

class GameObject;

class Component {
	public:
		// We want these to be abstract (virtual in c++)
		virtual ~Component() = default;
		virtual void update(float deltaTime) {}

		//Who owns the gameObject
		GameObject* getOwner() const;

	private:
		//Only gameObject can call this so when we add a component it sets
		//its owner to a gameObject
		void setOwner(GameObject* go);

		// Make it easier to share information with GameObjects
		// by letting them see our private data.
		friend class GameObject;

		// To which game object do we belong?
		GameObject* owner = nullptr;
};

class SpriteComponent : public Component {
	public:
		void setX(int x);
		void setY(int y);
		// Load an image from a file.  Normally we would
		// probably have multiple images per sprite for
		// animations.
		bool loadSprite(SDL_Renderer* renderer, char* path, SDL_FRect rect = {0, 0, 32, 32});
		SDL_Texture* getSprite();
		void update(float deltaTime) override;
		SDL_FRect* getRect();

	private:
		// For convenience we can keep track of the renderer
		// from the engine.
		SDL_Renderer* renderer = nullptr;
		SDL_FRect destRect{};
		SDL_Texture* sprite = nullptr;
};

class PlayerInputComponent : public Component {
	public: 
	void update(float deltaTime) override;
	private:
	float pps = 1.0f;
};

class RedBoxComponent : public Component {
	public: 
		RedBoxComponent(float x, float y, float w, float h, SDL_Color color = {255,0,0,255});
		void update(float deltaTime) override;
		SDL_FRect* getRect();

	private: 
		SDL_FRect rect{};
		SDL_Color color;
};

class CollisionComponent: public Component {
	public: 
		CollisionComponent(SDL_FRect rect);
		SDL_FRect *getRect();
		void update(float deltaTime) override {};
	private: 
		SDL_FRect rect{};
};

#endif
