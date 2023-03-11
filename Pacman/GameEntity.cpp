#include "GameEntity.h"
#include "Drawer.h"
#include "Graphic.h"

GameEntity::GameEntity(const Vector2f& aPosition, Graphic* graphic)
:myPosition(aPosition)
,gameEntityGraphic(graphic)
,myIdMarkedForDeleteFlag(false)
{
}

GameEntity::~GameEntity(void)
{
}

bool GameEntity::Intersect(GameEntity* aGameEntity)
{

	return false;	
}

void GameEntity::Draw(Drawer* aDrawer)
{
	gameEntityGraphic->Draw(aDrawer, (int)myPosition.myX + 220, (int)myPosition.myY + 60);
}
