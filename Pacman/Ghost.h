#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"

class World;
class PathmapTile;

class Ghost : public MovableGameEntity
{
public:
	Ghost(const Vector2f& aPosition, Graphic* aGraphic);
	~Ghost(void);

	virtual std::string getNormalGraphic() = 0;
	virtual Vector2f getWanderTarget() = 0;

	void Update(float aTime, World* aWorld, PathmapTile* targetTile);

	bool myIsClaimableFlag;
	bool myIsDeadFlag;

	void SetNormalImage();

	void Die(World* aWorld);

protected:

	bool Ghost::inHome(int x, int y);

	Vector2f homeVector;
	int myDesiredMovementX;
	int myDesiredMovementY;
	bool hasVisitedWanderTarget = false;

	Vector2f direction = { 0,0 };

	PathmapTile* previousTile;

	std::list<PathmapTile*> myPath;
	std::list<PathmapTile*> neighbours;

	Graphic* ghostGraphic;

};

#endif // GHOST_H