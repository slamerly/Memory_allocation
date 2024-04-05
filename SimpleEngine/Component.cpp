#include "Component.h"
#include "Actor.h"
#include "Memory.h"

Component::Component(Actor* ownerP, int updateOrderP) :
	owner(*ownerP),
	updateOrder(updateOrderP)
{
	memory_alloc(sizeof(Actor), MEMORY_TAG_COMPONENT);
	owner.addComponent(this);
}

Component::~Component()
{
	owner.removeComponent(this);
}

void Component::processInput(const struct InputState& inputState)
{
}

void Component::update(float dt)
{
}
