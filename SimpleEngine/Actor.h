#pragma once
#include <vector>
#include "Vector2.h"
#include <SDL_stdinc.h>
#include "Matrix4.h"
#include "Heap.h"
using std::vector;

class Game;
class Component;

class Actor
{
public:

	enum class ActorState
	{
		Active, Paused, Dead
	};

	Actor();
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	//static void* operator new(size_t size);
	//static void operator delete(void* p, size_t size);

	Game& getGame() const { return game; }
	const ActorState getState() const { return state; }
	const Vector3 getPosition() const { return position; }
	const float getScale() const { return scale; }
	const Quaternion getRotation() const { return rotation; }
	const Matrix4& getWorldTransform() const { return worldTransform; }

	void setPosition(Vector3 positionP);
	void setScale(float scaleP);
	void setRotation(Quaternion rotationP);
	void setState(ActorState stateP);
	void setAngle(const Vector3& axis, float angle);

	Vector3 getForward() const;
	Vector3 getRight() const;
	void computeWorldTransform();
	void rotate(const Vector3& axis, float angle);
	void rotateToNewForward(const Vector3& newForward);

	void processInput(const struct InputState& inputState);
	virtual void actorInput(const struct InputState& inputState);
	void update(float dt);
	void updateComponents(float dt);
	virtual void updateActor(float dt);
	void addComponent(Component* component);
	void removeComponent(Component* component);

private:
	Game& game;
	ActorState state;
	Vector3 position;
	float scale;
	Quaternion rotation;
	Matrix4 worldTransform;
	bool mustRecomputeWorldTransform;

	//DECLARE_HEAP;
	//static Heap* s_pHeap;

	vector<Component*> components;
};
