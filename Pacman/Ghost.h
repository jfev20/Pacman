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

	void Update(float aTime, World* aWorld);

	bool myIsClaimableFlag;
	bool myIsDeadFlag;

	void SetImage(const char* anImage);

	void Die(World* aWorld);

	/*void Draw(Drawer* aDrawer);*/

protected:

	int myDesiredMovementX;
	int myDesiredMovementY;

	std::list<PathmapTile*> myPath;

	Graphic* ghostGraphic;

};

#endif // GHOST_H