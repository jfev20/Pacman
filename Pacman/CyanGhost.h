#ifndef CYANGHOST_H
#define CYANGHOST_H

#include <list>
#include "Ghost.h"

class World;
class PathmapTile;

class CyanGhost : public Ghost
{
public:
	CyanGhost(const Vector2f& aPosition, Graphic* aGraphic, Ghost* redGhost, Avatar* myAvatar);
	~CyanGhost(void);

	std::string getNormalGraphic() { return "ghost_32_cyan.png"; }
	Vector2f getWanderTarget() { return{ 18,22 }; }
	Vector2f getChaseTarget(Avatar* myAvatar);
	bool shouldLeaveSpawn();

protected:

	Ghost* blinky;

};

#endif // CYANGHOST_H
