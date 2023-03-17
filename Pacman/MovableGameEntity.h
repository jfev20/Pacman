#ifndef MOVABLEGAMEENTITY_H
#define MOVABLEGAMEENTITY_H

#include "GameEntity.h"
#include "Vector2f.h"
#include "Clock.h"

class MovableGameEntity : public GameEntity
{
public:
	MovableGameEntity(const Vector2f& aPosition, Graphic* aGraphic);
	~MovableGameEntity(void);

	void SetNextTile(int anX, int anY);
	int GetCurrentTileX() const { return myCurrentTileX; }
	int GetCurrentTileY() const { return myCurrentTileY; }
	Vector2f getTileVector();

	void SetPosition(const Vector2f& aPosition);
	void teleportEntity(Vector2f portalA, Vector2f portalB);
	

	bool IsAtDestination();
	
protected:
	Clock timer;
	int myCurrentTileX;
	int myCurrentTileY;

	int myNextTileX;
	int myNextTileY;

};

#endif // MOVABLEGAMEENTITY_H