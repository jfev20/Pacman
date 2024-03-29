#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"
#include "Avatar.h"
#include <iostream>

class World;
class PathmapTile;

class Ghost : public MovableGameEntity
{
public:
	Ghost(const Vector2f& aPosition, Graphic* aGraphic, Avatar* myAvatar);
	~Ghost(void);

	virtual std::string getNormalGraphic() = 0;
	virtual Vector2f getWanderTarget() = 0;
	virtual Vector2f getChaseTarget(Avatar* myAvatar) = 0;
	virtual Vector2f getSpawnPosition() { return SpawnPosition; }
	virtual bool shouldLeaveSpawn() = 0;

	void Update(float aTime, World* aWorld);
	void SetFrightenedState();
	void SetNormalState();
	bool isFrightened();

	bool myIsClaimableFlag;
	bool myIsDeadFlag;

	void Die(World* aWorld);

protected:
	bool atSpawn(int x, int y, bool dead);
	bool isAboveSpawnEntrance(int x, int y) { return ((GetCurrentTileY() == 10) && (y == 11 && (x == 12 || x == 13))); }

	Vector2f homeVector;
	int myDesiredMovementX;
	int myDesiredMovementY;
	bool hasVisitedWanderTarget = false;
	void setSpawnPosition(Vector2f aPosition) { SpawnPosition = aPosition; }

	Vector2f direction = { 0,0 };
	Clock timer;
	bool frightenedFlag = false;
	float frightenTime = 7.f;

	PathmapTile* previousTile;

	Vector2f targetTile;
	std::list<PathmapTile*> myPath;
	std::list<PathmapTile*> neighbours;

	Graphic* ghostGraphic;

	Avatar* pacman;

	float speed;
	const float standardSpeed = 100.f;
	const float frightenedSpeed = 60.f;
	const float deathSpeed = 300.f;
	Vector2f SpawnPosition;

};

#endif // GHOST_H