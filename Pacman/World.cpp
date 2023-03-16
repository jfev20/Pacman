#include "World.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "PathmapTile.h"
#include "Dot.h"
#include "BigDot.h"
#include "Drawer.h"

World::World(void)
{
}

World::~World(void)
{
}

void World::Init(Drawer* myDrawer)
{
	std::list<std::string> paths;
	paths.push_front("playfield.png");
	environment = Graphic::Create(myDrawer, paths, 1024, 768);
	environment->SetImage("playfield.png");
	
	InitPathmap();
	InitDots(myDrawer);
	InitBigDots(myDrawer);
}

bool World::InitPathmap()
{
	std::string line;
	std::ifstream myfile ("map.txt");
	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			std::getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				PathmapTile* tile = new PathmapTile(i, lineIndex, (line[i] == 'x'));
				myPathmapTiles.push_back(tile);
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

bool World::InitDots(Drawer* myDrawer)
{
	std::string line;
	std::ifstream myfile ("map.txt");

	Graphic* dotGraphic = nullptr;
	std::list<std::string> dotAssets{ "Small_Dot_32.png" };

	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			std::getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == '.')
				{
					dotGraphic = Graphic::Create(myDrawer, dotAssets, 32, 32);
					Dot* dot = new Dot(Vector2f(i*22, lineIndex*22), dotGraphic);
					myDots.push_back(dot);
				}
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

bool World::InitBigDots(Drawer* myDrawer)
{
	std::string line;
	std::ifstream myfile ("map.txt");

	Graphic* bigDotGraphic = nullptr;
	std::list<std::string> bigDotAssets{ "Big_Dot_32.png" };

	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			std::getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == 'o')
				{
					bigDotGraphic = Graphic::Create(myDrawer, bigDotAssets, 32, 32);
					BigDot* dot = new BigDot(Vector2f(i*22, lineIndex*22), bigDotGraphic);
					myBigDots.push_back(dot);
				}
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

void World::Draw(Drawer* aDrawer)
{
	environment->Draw(aDrawer, 0, 0);

	for(std::list<Dot*>::iterator list_iter = myDots.begin(); list_iter != myDots.end(); list_iter++)
	{
		Dot* dot = *list_iter;
		dot->Draw(aDrawer);
	}

	for(std::list<BigDot*>::iterator list_iter = myBigDots.begin(); list_iter != myBigDots.end(); list_iter++)
	{
		BigDot* dot = *list_iter;
		dot->Draw(aDrawer);
	}
}

bool World::TileIsValid(int anX, int anY)
{
	for(std::list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;

		if (anX == tile->myX && anY == tile->myY && !tile->myIsBlockingFlag)
			return true;
	}

	return false;
}

bool World::HasIntersectedDot(const Vector2f& aPosition)
{
	for(std::list<Dot*>::iterator list_iter = myDots.begin(); list_iter != myDots.end(); list_iter++)
	{
		Dot* dot = *list_iter;
		if ((dot->GetPosition() - aPosition).Length() < 5.f)
		{
			myDots.remove(dot);
			delete dot;
			return true;
		}
	}

	return false;
}

bool World::HasIntersectedBigDot(const Vector2f& aPosition)
{
	for(std::list<BigDot*>::iterator list_iter = myBigDots.begin(); list_iter != myBigDots.end(); list_iter++)
	{
		BigDot* dot = *list_iter;
		if ((dot->GetPosition() - aPosition).Length() < 5.f)
		{
			myBigDots.remove(dot);
			delete dot;
			return true;
		}
	}

	return false;
}

bool World::HasIntersectedCherry(const Vector2f& aPosition)
{
	return true;
}

void World::GetPath(int aFromX, int aFromY, int aToX, int aToY, std::list<PathmapTile*>& aList)
{
	PathmapTile* fromTile = GetTile(aFromX, aFromY);
	PathmapTile* toTile = GetTile(aToX, aToY);

	for(std::list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		tile->myIsVisitedFlag = false;
	}

	Pathfind(fromTile, toTile, aList);
}

PathmapTile* World::GetTile(int aFromX, int aFromY)
{

	for(std::list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		if (tile->myX == aFromX && tile->myY == aFromY)
		{
			return tile;
		}
	}

	return NULL;
}

bool World::ListDoesNotContain(PathmapTile* aFromTile, std::list<PathmapTile*>& aList)
{
	for(std::list<PathmapTile*>::iterator list_iter = aList.begin(); list_iter != aList.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		if (tile == aFromTile)
		{
			return false;
		}
	}

	return true;
}

bool SortFromGhostSpawn(PathmapTile* a, PathmapTile* b)
{
	int la = abs(a->myX - 13) + abs(a->myY - 13);
	int lb = abs(b->myX - 13) + abs(b->myY - 13);

    return la < lb;
}

bool World::Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, std::list<PathmapTile*>& aList)
{
	aFromTile->myIsVisitedFlag = true;

	if (aFromTile->myIsBlockingFlag)
		return false;

	if (aFromTile == aToTile)
		return true;

	std::list<PathmapTile*> neighborList = getNeighbours(aFromTile->myX, aFromTile->myY, aList);

	neighborList.sort(SortFromGhostSpawn);

	for(std::list<PathmapTile*>::iterator list_iter = neighborList.begin(); list_iter != neighborList.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;

		aList.push_back(tile);

		if (Pathfind(tile, aToTile, aList))
			return true;

		aList.pop_back();
	}

	return false;
}

std::list<PathmapTile*> World::getNeighbours(int x, int y, std::list<PathmapTile*>& aList) {
	std::list<PathmapTile*> neighborList;

	PathmapTile* up = GetTile(x, y - 1);
	if (up && !up->myIsVisitedFlag && !up->myIsBlockingFlag && ListDoesNotContain(up, aList))
		neighborList.push_front(up);

	PathmapTile* down = GetTile(x, y + 1);
	if (down && !down->myIsVisitedFlag && !down->myIsBlockingFlag && ListDoesNotContain(down, aList))
		neighborList.push_front(down);

	PathmapTile* right = GetTile(x + 1, y);
	if (right && !right->myIsVisitedFlag && !right->myIsBlockingFlag && ListDoesNotContain(right, aList))
		neighborList.push_front(right);

	PathmapTile* left = GetTile(x - 1, y);
	if (left && !left->myIsVisitedFlag && !left->myIsBlockingFlag && ListDoesNotContain(left, aList))
		neighborList.push_front(left);

	return neighborList;
}

/*float World::getDistance(PathmapTile* tileFrom, PathmapTile* tileTo) {
	float distX = tileFrom->myX - tileTo->myX;
	float distY = tileFrom->myY - tileTo->myY;

	return sqrt(pow(distX,2.0)+pow(distY,2.0));

}*/

float World::getDistance(PathmapTile* tileFrom, Vector2f outOfBounds) {
	float distX = tileFrom->myX - outOfBounds.myX;
	float distY = tileFrom->myY - outOfBounds.myY;

	return sqrt(pow(distX, 2.0) + pow(distY, 2.0));

}

Vector2f World::getSpawnExitVector() {
	return{ 13, 10 };
}