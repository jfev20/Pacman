#include "BigDot.h"

BigDot::BigDot(Vector2f aPosition, Graphic* aGraphic)
: StaticGameEntity(aPosition, aGraphic)
{
	gameEntityGraphic->SetImage("Big_Dot_32.png");
}

BigDot::~BigDot(void)
{
}
