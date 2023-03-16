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
