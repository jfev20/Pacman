#include "Dot.h"

Dot::Dot(Vector2f aPosition, Graphic* aGraphic)
: StaticGameEntity(aPosition, aGraphic)
{
	gameEntityGraphic->SetImage("Small_Dot_32.png");
}

Dot::~Dot(void)
{
}
