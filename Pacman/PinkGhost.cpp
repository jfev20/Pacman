#include "PinkGhost.h"

PinkGhost::PinkGhost(const Vector2f& aPosition, Graphic* aGraphic, Avatar* myAvatar)
	: Ghost(aPosition, aGraphic, myAvatar)
{
	gameEntityGraphic->SetImage("ghost_32_pink.png");
}

PinkGhost::~PinkGhost(void)
{
}

Vector2f PinkGhost::getChaseTarget(Avatar* myAvatar) { 
	// 4 tiles infront of player
	Vector2f target = myAvatar->getTileVector() + (myAvatar->getDirection() * 4);
	return target;
}