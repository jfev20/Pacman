#ifndef DOT_H
#define DOT_H

#include "StaticGameEntity.h"
#include "Vector2f.h"

#include "Graphic.h"

class Dot : public StaticGameEntity
{
public:
	Dot(Vector2f aPosition, Graphic* aGraphic);
	~Dot(void);
};

#endif // DOT_H