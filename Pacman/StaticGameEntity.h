#ifndef STATICGAMEENTITY_H
#define STATICGAMEENTITY_H

#include "GameEntity.h"
#include "Vector2f.h"

class StaticGameEntity : public GameEntity
{
public:
	StaticGameEntity(Vector2f aPosition, Graphic* aGraphic);
	~StaticGameEntity(void);
};

#endif // STATICGAMEENTITY_H