#ifndef REDGHOST_H
#define REDGHOST_H

#include <list>
#include "Ghost.h"

class World;
class PathmapTile;

class RedGhost : public Ghost
{
public:
	RedGhost(const Vector2f& aPosition, Graphic* aGraphic, Avatar* myAvatar);
	~RedGhost(void);

	std::string getNormalGraphic() { return "ghost_32_red.png"; }
	Vector2f getWanderTarget() { return{ 22,0 }; }
	Vector2f getChaseTarget(Avatar* myAvatar) { return myAvatar->getTileVector(); }
	bool shouldLeaveSpawn() {return true;}

	Vector2f getSpawnPosition() { return {22, 0}; }

protected:


};

#endif // REDGHOST_H