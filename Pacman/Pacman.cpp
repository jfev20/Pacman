#include "Pacman.h"
#include "Drawer.h"
#include "SDL.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Avatar.h"
#include "World.h"
#include "Ghost.h"
#include "RedGhost.h"
#include "PinkGhost.h"
#include "OrangeGhost.h"
#include "CyanGhost.h"
#include "Graphic.h"

Pacman* Pacman::Create(Drawer* aDrawer)
{
	Pacman* pacman = new Pacman(aDrawer);

	if (!pacman->Init())
	{
		delete pacman;
		pacman = NULL;
	}

	return pacman;
}

Pacman::Pacman(Drawer* aDrawer)
: myDrawer(aDrawer)
, myTimeToNextUpdate(0.f)
, myNextMovement(-1.f,0.f)
, myScore(0)
, myFps(0)
, myLives(3)
, myGhostGhostCounter(0.f)
{
	Graphic* avatarGraphic = nullptr;
	Graphic* redGhostGraphic = nullptr;
	Graphic* pinkGhostGraphic = nullptr;
	Graphic* orangeGhostGraphic = nullptr;
	Graphic* cyanGhostGraphic = nullptr;

	std::list<std::string> avatarGraphicPaths{ 
		"closed_right_32.png",
		"open_right_32.png",
		"closed_down_32.png",
		"open_down_32.png",
		"closed_left_32.png",
		"open_left_32.png",
		"closed_up_32.png",
		"open_up_32.png"
	};
	std::list<std::string> redGhostGraphicPaths{
		"ghost_32_red.png",
		"Ghost_Dead_32.png",
		"Ghost_Vulnerable_32.png"
	};
	std::list<std::string> pinkGhostGraphicPaths{
		"ghost_32_pink.png",
		"Ghost_Dead_32.png",
		"Ghost_Vulnerable_32.png"
	};
	std::list<std::string> orangeGhostGraphicPaths{
		"ghost_32_orange.png",
		"Ghost_Dead_32.png",
		"Ghost_Vulnerable_32.png"
	};
	std::list<std::string> cyanGhostGraphicPaths{
		"ghost_32_cyan.png",
		"Ghost_Dead_32.png",
		"Ghost_Vulnerable_32.png"
	};

	avatarGraphic = Graphic::Create(myDrawer, avatarGraphicPaths, 32, 32);
	myAvatar = new Avatar(Vector2f(13,22), avatarGraphic, &myScore);

	redGhostGraphic = Graphic::Create(myDrawer, redGhostGraphicPaths, 32, 32);
	myRedGhost = new RedGhost(Vector2f(12.5, 10), redGhostGraphic, myAvatar);
	allGhosts.push_back(myRedGhost);

	pinkGhostGraphic = Graphic::Create(myDrawer, pinkGhostGraphicPaths, 32, 32);
	myPinkGhost = new PinkGhost(Vector2f(12.5, 13), pinkGhostGraphic, myAvatar);
	allGhosts.push_back(myPinkGhost);

	orangeGhostGraphic = Graphic::Create(myDrawer, orangeGhostGraphicPaths, 32, 32);
	myOrangeGhost = new OrangeGhost(Vector2f(14, 13), orangeGhostGraphic, myAvatar);
	allGhosts.push_back(myOrangeGhost);

	cyanGhostGraphic = Graphic::Create(myDrawer, cyanGhostGraphicPaths, 32, 32);
	myCyanGhost = new CyanGhost(Vector2f(11, 13), cyanGhostGraphic, myRedGhost, myAvatar);
	allGhosts.push_back(myCyanGhost);
	

	myWorld = new World();

	UpdateScore(0);
	UpdateLives(0);
	UpdateFPS(0);
}

Pacman::~Pacman(void)
{
}

bool Pacman::Init()
{
	myWorld->Init(myDrawer);

	return true;
}

bool Pacman::Update(float aTime)
{
	if (!UpdateInput())
		return false;

	if (CheckWinCondition())
	{
		myDrawer->DrawText("You win!", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 70);
		return true;
	}
	else if (myLives <= 0)
	{
		myDrawer->DrawText("You lose!", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 70);	
		return true;
	}

	std::list<Ghost*>::iterator allGhostItr;

	MoveAvatar();
	myAvatar->Update(aTime, myWorld);

	Vector2f avatarPos = myAvatar->GetPosition();

	for (allGhostItr = allGhosts.begin(); allGhostItr != allGhosts.end(); allGhostItr++) {
		(*allGhostItr)->Update(aTime, myWorld); // move ghost
	}

	if (myWorld->HasIntersectedDot(avatarPos))
		UpdateScore(10);

	myGhostGhostCounter -= aTime;

	if (myWorld->HasIntersectedBigDot(avatarPos))
	{
		UpdateScore(20);
		myGhostGhostCounter = 20.f;
		for (allGhostItr = allGhosts.begin(); allGhostItr != allGhosts.end(); allGhostItr++)
			(*allGhostItr)->myIsClaimableFlag = true;
	}
	for (allGhostItr = allGhosts.begin(); allGhostItr != allGhosts.end(); allGhostItr++) {
		if (myGhostGhostCounter <= 0)
		{
			(*allGhostItr)->myIsClaimableFlag = false;
		}

		if (((*allGhostItr)->GetPosition() - avatarPos).Length() < 10.f)
		{
			if (myGhostGhostCounter <= 0.f)
			{
				UpdateLives(-1);

				myAvatar->SetPosition(Vector2f(13*22,22*22));
				(*allGhostItr)->SetPosition(Vector2f(13*22,13*22));
				// reset my next position for all moveable game entities
			}
			else if ((*allGhostItr)->myIsClaimableFlag && !(*allGhostItr)->myIsDeadFlag)
			{
				UpdateScore(50);
				(*allGhostItr)->myIsDeadFlag = true;
				(*allGhostItr)->Die(myWorld);
			}
		}
	}
	if (aTime > 0)
		UpdateFPS((int) (1 / aTime));

	return true;
}

bool Pacman::UpdateInput()
{
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_UP])
		myNextMovement = Vector2f(0.f, -1.f);
	else if (keystate[SDL_SCANCODE_DOWN])
		myNextMovement = Vector2f(0.f, 1.f);
	else if (keystate[SDL_SCANCODE_RIGHT])
		myNextMovement = Vector2f(1.f, 0.f);
	else if (keystate[SDL_SCANCODE_LEFT])
		myNextMovement = Vector2f(-1.f, 0.f);

	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;

	return true;
}

void Pacman::MoveAvatar()
{
	int nextTileX = myAvatar->GetCurrentTileX() + myNextMovement.myX;
	int nextTileY = myAvatar->GetCurrentTileY() + myNextMovement.myY;

	if (myAvatar->IsAtDestination())
	{
		if (myWorld->TileIsValid(nextTileX, nextTileY))
		{
			myAvatar->SetNextTile(nextTileX, nextTileY);
		}
	}
}

bool Pacman::CheckWinCondition()
{
	return false; // check if current score is equal to max score
}

void Pacman::UpdateScore(int aScore) {

	myScore += aScore;

	std::stringstream scoreStream;
	scoreStream << "Score " << myScore;
	scoreString = scoreStream.str();
	
}

void Pacman::UpdateLives(int aLife) {

	myLives += aLife;

	std::stringstream liveStream;
	liveStream << "Lives " << myLives;
	livesString = liveStream.str();

}

void Pacman::UpdateFPS(int frames) {

	myFps = frames;

	std::stringstream fpsStream;
	fpsStream << "FPS " << myFps;
	fpsString = fpsStream.str();

}

bool Pacman::Draw()
{
	myWorld->Draw(myDrawer);
	myAvatar->Draw(myDrawer);
	myRedGhost->Draw(myDrawer);
	myPinkGhost->Draw(myDrawer);
	myOrangeGhost->Draw(myDrawer);
	myCyanGhost->Draw(myDrawer);

	myDrawer->DrawText(scoreString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 20, 50);
	myDrawer->DrawText(livesString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 20, 80);
	myDrawer->DrawText(fpsString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 880, 50);

	return true;
}
