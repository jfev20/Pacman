#include "RedGhost.h"

RedGhost::RedGhost(const Vector2f& aPosition, Graphic* aGraphic, Avatar* myAvatar)
	: Ghost(aPosition, aGraphic, myAvatar)
{
	gameEntityGraphic->SetImage("ghost_32_red.png");
}

RedGhost::~RedGhost(void)
{
}
