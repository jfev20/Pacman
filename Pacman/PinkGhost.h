#ifndef PINKGHOST_H
#define PINKGHOST_H

#include <list>
#include "Ghost.h"

class World;
class PathmapTile;

class PinkGhost : public Ghost
{
public:
	PinkGhost(const Vector2f& aPosition, Graphic* aGraphic, Avatar* myAvatar);
	~PinkGhost(void);

	std::string getNormalGraphic() { return "ghost_32_pink.png"; }
	Vector2f getWanderTarget() { return{ 3,0 }; }
	Vector2f getChaseTarget(Avatar* myAvatar);
	bool shouldLeaveSpawn() { return true; }

protected:


};

#endif // PINKGHOST_H