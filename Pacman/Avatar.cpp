#include "Avatar.h"

Avatar::Avatar(const Vector2f& aPosition, Graphic* aGraphic)
: MovableGameEntity(aPosition, aGraphic)
{
	gameEntityGraphic->SetImage("open_right_32.png");

}

Avatar::~Avatar(void)
{
}

void Avatar::Update(float aTime)
{
	int tileSize = 22;

	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f direction = destination - myPosition;

	float distanceToMove = aTime * 30.f;

	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		direction.Normalize();
		myPosition += direction * distanceToMove;
	}
	UpdateFacingDirection(direction);
}

void Avatar::UpdateFacingDirection(Vector2f dir) {
	dir.Normalize();
	if (dir.myX + dir.myY == 0) return;	// return if moving into wall
	currentDirectionGraphics = graphicOrientation[{dir.myX, dir.myY}]; // list of graphics in facing direction
	// check if mouth open or closed
	gameEntityGraphic->SetImage(currentDirectionGraphics[0]);

}
