#ifndef CHERRY_H
#define CHERRY_H

#include "StaticGameEntity.h"
#include "Vector2f.h"

class Cherry : public StaticGameEntity
{
public:
	Cherry(Vector2f aPosition, Graphic* aGraphic);
	~Cherry(void);
};

#endif // CHERRY_H