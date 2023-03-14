#include "Ghost.h"
#include "World.h"
#include "PathmapTile.h"
#include "Drawer.h"

#include <algorithm>
#include <iterator>
#include <iostream>

Ghost::Ghost(const Vector2f& aPosition, Graphic* aGraphic)
: MovableGameEntity(aPosition, aGraphic)
{
	myIsClaimableFlag = false;
	myIsDeadFlag = false;

	myDesiredMovementX = 0;
	myDesiredMovementY = -1;
}

Ghost::~Ghost(void)
{
}

void Ghost::Die(World* aWorld)
{
	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, 13, 13, myPath);
}

void Ghost::Update(float aTime, World* aWorld, PathmapTile* targetTile)
{
	float speed = 30.f;
	int nextTileX = GetCurrentTileX() + myDesiredMovementX;
	int nextTileY = GetCurrentTileY() + myDesiredMovementY;

	if (myIsDeadFlag)
		speed = 120.f;

	if (IsAtDestination())
	{
		Vector2f homeVector = getWanderTarget();
		if (GetCurrentTileX() == homeVector.myX && GetCurrentTileY() == homeVector.myY) {
			hasVisitedWanderTarget = true;
		}

		if (!hasVisitedWanderTarget) {
			targetTile = aWorld->GetTile(homeVector.myX, homeVector.myY);
		}

		neighbours = aWorld->getNeighbours(GetCurrentTileX(), GetCurrentTileY(), myPath);

		std::list<PathmapTile*> filteredNeighbours;
		direction.Normalize();
		std::copy_if(neighbours.begin(), neighbours.end(), std::back_inserter(filteredNeighbours),
			[this](PathmapTile* aTile) { 
				return (
					aTile->myX != GetCurrentTileX() - direction.myX ||
					aTile->myY != GetCurrentTileY() - direction.myY
					); 
			});

		if (filteredNeighbours.size() > 1)
		{
			filteredNeighbours.sort([&, targetTile](PathmapTile* tileA, PathmapTile* tileB) {
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

bool Ghost::inHome(int x, int y) {
	return (x > 9 && x < 16 && y > 10 && y < 15);
}

void Ghost::SetNormalImage()
{
	gameEntityGraphic->SetImage(getNormalGraphic());
}