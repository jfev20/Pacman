#include "Cherry.h"

Cherry::Cherry(Vector2f aPosition, Graphic* aGraphic)
: StaticGameEntity(aPosition, aGraphic)
{
	gameEntityGraphic->SetImage("dot.png");
}

Cherry::~Cherry(void)
{
}
