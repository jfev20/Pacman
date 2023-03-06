#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "SDL_rect.h"

#include <map>
#include <string>
#include <list>


struct SDL_Texture;
class Drawer;

class Graphic {
public:
	static Graphic* Create(Drawer* drawer, std::list<std::string> texture_paths, int width, int height);
	~Graphic();

	void SetImage(std::string anImage);
	void Draw(Drawer* drawer, int x, int y);

private:
	Graphic(std::map<std::string, SDL_Texture*> texture_paths, SDL_Rect size);

	std::map<std::string, SDL_Texture*> paths;
	std::string currImage;
	SDL_Rect boundingBox;
};





#endif