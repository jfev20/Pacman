#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(const Vector2f& aPosition, Graphic* aGraphic)
: GameEntity(aPosition*22, aGraphic)
{
	myCurrentTileX = myNextTileX =  myPosition.myX / 22;
	myCurrentTileY = myNextTileY =  myPosition.myY / 22;
}

MovableGameEntity::~MovableGameEntity(void)
{
}

bool MovableGameEntity::IsAtDestination()
{
	return (myCurrentTileX == myNextTileX && myCurrentTileY == myNextTileY) ? true : false;
}

void MovableGameEntity::SetNextTile(int anX, int anY)
{
	myNextTileX = anX;
	myNextTileY = anY;
}

Vector2f MovableGameEntity::getTileVector() {
	return{
		static_cast<float>(myCurrentTileX),
		static_cast<float>(myCurrentTileY)
	};
}

void MovableGameEntity::teleportEntity(Vector2f portalLeft, Vector2f portalRight) {
	Vector2f offset = { 22,0 };
	if (getTileVector() == portalLeft) {
		SetPosition(portalRight *22 - offset);
		myCurrentTileX = myNextTileX = myPosition.myX / 22;
	}
		
	if (getTileVector() == portalRight) {
		SetPosition(portalLeft * 22 + offset);
		myCurrentTileX = myNextTileX = myPosition.myX / 22;
	}
}
