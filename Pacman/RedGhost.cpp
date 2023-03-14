#include "RedGhost.h"

RedGhost::RedGhost(const Vector2f& aPosition, Graphic* aGraphic)
	: Ghost(aPosition, aGraphic)
{
	gameEntityGraphic->SetImage("ghost_32_red.png");
}

RedGhost::~RedGhost(void)
{
}
