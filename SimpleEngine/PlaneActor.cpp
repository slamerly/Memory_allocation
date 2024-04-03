#include "PlaneActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "Game.h"
#include "BoxCollisionComponent.h"

PlaneActor::PlaneActor() : Actor()
{
	setScale(10.0f);
	MeshComponent* mc = new MeshComponent(this);
	Mesh* mesh = &Assets::getMesh("Mesh_Plane");
	mc->setMesh(*mesh);
	box = new BoxCollisionComponent(this);
	box->setObjectBox(mesh->getBox());

	getGame().addPlane(this);
}

PlaneActor::~PlaneActor()
{
	getGame().removePlane(this);
}
