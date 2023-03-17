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

	timer.SetAnimationLength(frightenTime);

	pacman = myAvatar;
	setSpawnPosition(aPosition);
}

Ghost::~Ghost(void)
{
}

void Ghost::Die(World* aWorld)
{
	gameEntityGraphic->SetImage("Ghost_Dead_32.png");
	myPath.clear();
	myIsDeadFlag = true;
	speed = deathSpeed;
	targetTile = this->getSpawnPosition();
}

void Ghost::Update(float aTime, World* aWorld)
{	
	int nextTileX = GetCurrentTileX() + myDesiredMovementX;
	int nextTileY = GetCurrentTileY() + myDesiredMovementY;

	if (!myIsDeadFlag) {
		speed = standardSpeed;
		targetTile = this->getChaseTarget(pacman);
	}

	if (isFrightened() && !myIsDeadFlag) {
		timer.IncrementTime(aTime);
		if (timer.Compare()) {
			SetNormalState();
		}
	}
	

	if (IsAtDestination())
	{
		
		if (GetCurrentTileX() == getWanderTarget().myX && GetCurrentTileY() == getWanderTarget().myY) {
			hasVisitedWanderTarget = true;
		}

		if (!hasVisitedWanderTarget && !myIsDeadFlag) {
			targetTile = this->getWanderTarget();
		}

		if (atSpawn(GetCurrentTileX(), GetCurrentTileY(), myIsDeadFlag)) {
			SetNormalState();
			targetTile = aWorld->getSpawnExitVector();
		}

		neighbours = aWorld->getNeighbours(GetCurrentTileX(), GetCurrentTileY(), myPath);

		std::list<PathmapTile*> filteredNeighbours;
		direction.Normalize();
		std::copy_if(neighbours.begin(), neighbours.end(), std::back_inserter(filteredNeighbours),
			[this](PathmapTile* aTile) { 
				bool Backwards = (
					aTile->myX == GetCurrentTileX() - direction.myX && 
					aTile->myY == GetCurrentTileY() - direction.myY);

				return !Backwards || (myIsDeadFlag && isAboveSpawnEntrance(aTile->myX, aTile->myY));
			});

		if (filteredNeighbours.size() > 1)
		{
			if (frightenedFlag) {
				int randNum = rand() % (filteredNeighbours.size());
				auto fN_front = filteredNeighbours.begin();
				std::advance(fN_front, randNum);
				filteredNeighbours.push_front(*fN_front);
			}
			else {		
				filteredNeighbours.sort([&, this](PathmapTile* tileA, PathmapTile* tileB) {
					return aWorld->getDistance(tileA, targetTile) < aWorld->getDistance(tileB, targetTile);
				});
			}
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
	teleportEntity(aWorld->getTeleportAVector(), aWorld->getTeleportBVector());
}

void Ghost::SetFrightenedState() {
	if (atSpawn(GetCurrentTileX(), GetCurrentTileY(), myIsDeadFlag)) {
		return;
	}
	myDesiredMovementX = GetCurrentTileX() - direction.myX;
	myDesiredMovementY = GetCurrentTileY() - direction.myY;
	direction = direction * -1;
	frightenedFlag = myIsClaimableFlag = true;
	speed = frightenedSpeed;
	gameEntityGraphic->SetImage("Ghost_Vulnerable_32.png");
	
}

void Ghost::SetNormalState() {
	gameEntityGraphic->SetImage(getNormalGraphic());
	timer.ResetTime();
	frightenedFlag = myIsClaimableFlag = myIsDeadFlag = false;
	speed = standardSpeed;
}

bool Ghost::isFrightened() {
	return frightenedFlag;
}

bool Ghost::atSpawn(int x, int y, bool dead) { 
	return (x > 9 && x < 16 && y > (dead ? 11 : 10) && y < 15); 
}