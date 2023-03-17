#ifndef ORANGEGHOST_H
#define ORANGEGHOST_H

#include <list>
#include "Ghost.h"

class World;
class PathmapTile;

class OrangeGhost : public Ghost
{
public:
	OrangeGhost(const Vector2f& aPosition, Graphic* aGraphic, Avatar* myAvatar);
	~OrangeGhost(void);

	std::string getNormalGraphic() { return "ghost_32_prange.png"; }
	Vector2f getWanderTarget() { return{ 7,22 }; }
	Vector2f getChaseTarget(Avatar* myAvatar);
	bool shouldLeaveSpawn();

protected:


};

#endif // ORANGEGHOST_H