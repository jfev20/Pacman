#include "OrangeGhost.h"

OrangeGhost::OrangeGhost(const Vector2f& aPosition, Graphic* aGraphic, Avatar* myAvatar)
	: Ghost(aPosition, aGraphic, myAvatar)
{
	gameEntityGraphic->SetImage("ghost_32_orange.png");
}

OrangeGhost::~OrangeGhost(void)
{
}

Vector2f OrangeGhost::getChaseTarget(Avatar* myAvatar) { 
	// chase pacman unless under 8 tiles away, then return to wander
	Vector2f displacement = myAvatar->getTileVector() - this->getTileVector();
	if (displacement.Length() >= 8) {
		return myAvatar->getTileVector();
	}
	return getWanderTarget();
}


bool OrangeGhost::shouldLeaveSpawn() { 
	return (*pacman->getScore() >= 810);
}