#include "Avatar.h"

Avatar::Avatar(const Vector2f& aPosition, Graphic* aGraphic)
	: MovableGameEntity(aPosition, aGraphic)
{
	gameEntityGraphic->SetImage("open_right_32.png");
	this->timer.SetAnimationLength(animationTime);

}

Avatar::~Avatar(void)
{
}

int Avatar::ReturnGraphicIndex(std::string anImage) {
	for (int i = 0; i < currentDirectionGraphics.size(); i++) {
		if (currentDirectionGraphics[i] == anImage) {
			return i;
		}
		return -1;
	}
};

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
	UpdateFacingDirection(direction, aTime);
}

void Avatar::UpdateFacingDirection(Vector2f dir, float aTime) {
	dir.Normalize();
	if (dir.myX + dir.myY == 0) return;	// return if moving into wall
	currentDirectionGraphics = graphicOrientation[{dir.myX, dir.myY}]; // list of graphics in facing direction
	// check if mouth open or closed
	UpdateGraphicAnimation(aTime);
}

void Avatar::UpdateGraphicAnimation(float aTime) {
	timer.IncrementTime(aTime);
	int currIndex = ReturnGraphicIndex(gameEntityGraphic->GetImage());  // game crash on death due to currentDirectionGraphics having a size of 0
	if (timer.Compare()) {
		selectedAnimation = ((currIndex + 1)% currentDirectionGraphics.size());
		gameEntityGraphic->SetImage(currentDirectionGraphics[selectedAnimation]);
		timer.ResetTime();
	}

}
