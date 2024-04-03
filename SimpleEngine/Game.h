#pragma once
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Vector2.h"
#include "RendererOGL.h"
#include "Camera.h"
#include "Character.h"
#include "InputSystem.h"
#include "Achievements.h"
#include "PhysicsSystem.h"
#include "PlaneActor.h"

using std::vector;

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() : isRunning(true), 
		isUpdatingActors(false), 
		//camera(nullptr), 
		chara(nullptr) {}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	RendererOGL& getRenderer() { return renderer; }
	PhysicsSystem& getPhysicsSystem() { return physicsSystem; }

	// Game Specific
	Character* getCharacter() { return chara; }
	//Camera* getCamera() { return camera; }
	void addPlane(class PlaneActor* plane);
	void removePlane(class PlaneActor* plane);
	vector<PlaneActor*>& getPlanes() { return planes; }
	void addMovableActor(class Actor* actor);
	void removeMovableActor(class Actor* actor);
	vector<Actor*>& getMovableActors() { return movableActors; }

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	RendererOGL renderer;
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	// Game Specific
	//Camera* camera;
	Character* chara;
	Achievements* achieve;
	vector<PlaneActor*> planes;
	vector<Actor*> movableActors;
};

