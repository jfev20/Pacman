#include "CyanGhost.h"
#include "Ghost.h"

CyanGhost::CyanGhost(const Vector2f& aPosition, Graphic* aGraphic, Ghost* redGhost, Avatar* myAvatar)
	: Ghost(aPosition, aGraphic, myAvatar)
{
	gameEntityGraphic->SetImage("ghost_32_cyan.png");
	blinky = redGhost;
}

CyanGhost::~CyanGhost(void)
{
}

Vector2f CyanGhost::getChaseTarget(Avatar* myAvatar) { 
	// 2 tiles infront of player plus vector + vector difference of red
	Vector2f playerFront = myAvatar->getTileVector() + (myAvatar->getDirection() * 2);
	Vector2f displacement = myAvatar->getTileVector() - blinky->getTileVector();
	return (playerFront + displacement); 
}

bool CyanGhost::shouldLeaveSpawn() {
	return (*pacman->getScore() >= 300);
}