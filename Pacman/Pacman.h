#ifndef PACMAN_H
#define PACMAN_H

#include "Vector2f.h"
#include <string>

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

	Drawer* myDrawer;

	float myTimeToNextUpdate;
	float myGhostGhostCounter;

	int myLives;
	int myScore;
	int myFps;

	std::string scoreString;
	std::string livesString;
	std::string fpsString;

	Vector2f myNextMovement;

	Avatar* myAvatar;
	Ghost* myGhost;
	World* myWorld;

};

#endif // PACMAN_H