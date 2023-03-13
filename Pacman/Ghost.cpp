#include "Ghost.h"
#include "World.h"
#include "PathmapTile.h"
#include "Drawer.h"

Ghost::Ghost(const Vector2f& aPosition, Graphic* aGraphic)
: MovableGameEntity(aPosition, aGraphic)
{
	gameEntityGraphic->SetImage("ghost_32.png");

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
		neighbours = aWorld->getNeighbours(GetCurrentTileX(), GetCurrentTileY(), myPath);

		if (neighbours.size() > 1)
		{
			neighbours.sort([&, targetTile](PathmapTile* tileA, PathmapTile* tileB) {
				return aWorld->getDistance(tileA, targetTile) < aWorld->getDistance(tileB, targetTile);
			});
		}
		nextTileX = neighbours.front()->myX;
		nextTileY = neighbours.front()->myY;

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
	Vector2f direction = destination - myPosition;

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

void Ghost::SetImage(const char* anImage)
{
	ghostGraphic->SetImage(anImage);
}