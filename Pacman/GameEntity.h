#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "Vector2f.h"
#include "Graphic.h"

class Drawer;

class GameEntity
{
public:
	GameEntity(const Vector2f& aPosition, Graphic* graphic);
	~GameEntity(void);

	Vector2f GetPosition() const { return myPosition; }
	void SetPosition(const Vector2f& aPosition){ myPosition = aPosition; }

	bool Intersect(GameEntity* aGameEntity);
	virtual void Draw(Drawer* aDrawer);

	void MarkForDelete() { myIdMarkedForDeleteFlag = true; }
	bool IsMarkedForDelete() const { return myIdMarkedForDeleteFlag; }

protected:

	bool myIdMarkedForDeleteFlag;
	Vector2f myPosition;
	Graphic* gameEntityGraphic;
};

#endif // GAMEENTITY_H