#ifndef PACMAN_H
#define PACMAN_H

#include "Vector2f.h"
#include <list>
#include <string>
#include "PathmapTile.h"
#include <functional>

struct SDL_Surface;
class Drawer;
class Avatar;
class World;
class Ghost;

class Pacman
{
public:
	static Pacman* Create(Drawer* aDrawer);
	~Pacman(void);

	bool Update(float aTime);
	bool Draw();

private:
	Pacman(Drawer* aDrawer);
	bool Init();
	bool UpdateInput();
	void MoveAvatar();
	bool CheckWinCondition();

	void UpdateScore(int aScore);
	void UpdateLives(int aLife);
	void UpdateFPS(int frames);
	void UpdateEndText(bool win);

	void ApplyToAllGhosts(std::function<void(Ghost *aGhost)>func);

	Drawer* myDrawer;

	float myTimeToNextUpdate;

	int myLives;
	int myScore;
	int myFps;

	std::string scoreString;
	std::string livesString;
	std::string fpsString;
	std::string endGameString;
	int dotCounter;

	Vector2f myNextMovement;
	Vector2f target;
	PathmapTile* myGhostTarget;

	std::list<Ghost*> allGhosts;

	Avatar* myAvatar;
	Ghost* myRedGhost;
	Ghost* myPinkGhost;
	Ghost* myOrangeGhost;
	Ghost* myCyanGhost;
	World* myWorld;

};

#endif // PACMAN_H