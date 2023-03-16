#include "Ghost.h"
#include "World.h"
#include "PathmapTile.h"
#include "Drawer.h"

#include <algorithm>
#include <iterator>

Ghost::Ghost(const Vector2f& aPosition, Graphic* aGraphic, Avatar* myAvatar)
: MovableGameEntity(aPosition, aGraphic)
{
	myIsClaimableFlag = false;
	myIsDeadFlag = false;
	hasVisitedWanderTarget = false;

	myDesiredMovementX = 0;
	myDesiredMovementY = -1;

	pacman = myAvatar;
}

Ghost::~Ghost(void)
{
}

void Ghost::Die(World* aWorld)
{
	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, 13, 13, myPath);
}

void Ghost::Update(float aTime, World* aWorld)
{
	speed = 100.f;
	int nextTileX = GetCurrentTileX() + myDesiredMovementX;
	int nextTileY = GetCurrentTileY() + myDesiredMovementY;

	if (myIsDeadFlag)
		speed = 120.f;

	targetTile = this->getChaseTarget(pacman);

	if (IsAtDestination())
	{
		
		if (GetCurrentTileX() == getWanderTarget().myX && GetCurrentTileY() == getWanderTarget().myY) {
			hasVisitedWanderTarget = true;
		}

		if (!hasVisitedWanderTarget) {
			targetTile = inSpawn(GetCurrentTileX(), GetCurrentTileY()) ? aWorld->getSpawnExitVector() : this->getWanderTarget();
		}

		neighbours = aWorld->getNeighbours(GetCurrentTileX(), GetCurrentTileY(), myPath);

		std::list<PathmapTile*> filteredNeighbours;
		direction.Normalize();
		std::copy_if(neighbours.begin(), neighbours.end(), std::back_inserter(filteredNeighbours),
			[this](PathmapTile* aTile) { 
				// don't remove spawn if dead
				bool notBackwards = (
					aTile->myX != GetCurrentTileX() - direction.myX || 
					aTile->myY != GetCurrentTileY() - direction.myY);

				return ((notBackwards) && (!isSpawnEntrance(aTile->myX, aTile->myY)));
			});

		if (filteredNeighbours.size() > 1)
		{
			filteredNeighbours.sort([&, this](PathmapTile* tileA, PathmapTile* tileB) {
				return aWorld->getDistance(tileA, targetTile) < aWorld->getDistance(tileB, targetTile);
			});
		}
		nextTileX = filteredNeighbours.front()->myX;
		nextTileY = filteredNeighbours.front()->myY;

		if (!myPath.empty())
		{
			PathmapTile* nextTile = myPath.front();
			myPath.pop_front();
			SetNextTile(nextTile->myX, nextTile->myY);
		}
		else if (aWorld->TileIsValid(nextTileX, nextTileY))
		{
			SetNextTile(nextTileX, nextTileY);
		}
		else
		{
			myIsDeadFlag = false;
		}
	}

	

	int tileSize = 22;
	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	direction = destination - myPosition;

	if (!shouldLeaveSpawn()) {
		speed = 0.f;
		direction *= 0;
	}

	float distanceToMove = aTime * speed;

	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		direction.Normalize();
		myPosition += direction * distanceToMove;
	}
}

void Ghost::SetNormalImage()
{
	gameEntityGraphic->SetImage(getNormalGraphic());
}