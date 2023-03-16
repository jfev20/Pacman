#ifndef WORLD_H
#define WORLD_H

#include <list>
#include "Vector2f.h"

#include "Graphic.h"

class Drawer;
class PathmapTile;
class Dot;
class BigDot;
class Cherry;

class World
{
public:
	World(void);
	~World(void);

	void Init(Drawer* myDrawer);

	void Draw(Drawer* aDrawer);
	bool TileIsValid(int anX, int anY);

	bool HasIntersectedDot(const Vector2f& aPosition);
	bool HasIntersectedBigDot(const Vector2f& aPosition);
	bool HasIntersectedCherry(const Vector2f& aPosition);

	void Update();

	void GetPath(int aFromX, int aFromY, int aToX, int aToY, std::list<PathmapTile*>& aList);

	std::list<PathmapTile*> getNeighbours(int x, int y, std::list<PathmapTile*>& aList);
	//float getDistance(PathmapTile* tileFrom, PathmapTile* tileTo);
	float getDistance(PathmapTile* tileFrom, Vector2f outOfBounds);
	
	PathmapTile* GetTile(int aFromX, int aFromY);
	Vector2f getSpawnExitVector();

private:

	
	bool Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, std::list<PathmapTile*>& aList);
	bool ListDoesNotContain(PathmapTile* aFromTile, std::list<PathmapTile*>& aList);


	bool InitPathmap();
	bool InitDots(Drawer* myDrawer);
	bool InitBigDots(Drawer* myDrawer);

	std::list<PathmapTile*> myPathmapTiles;
	std::list<Dot*> myDots;
	std::list<BigDot*> myBigDots;
	std::list<Cherry*> myCherry;

	Graphic* environment;

};

#endif // WORLD_H