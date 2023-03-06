#include "Graphic.h"
#include "Drawer.h"

#include "SDL_rect.h"
#include "SDL_image.h"
#include "SDL.h"

Graphic* Graphic::Create(Drawer* drawer, std::list<std::string> texture_paths, int width, int height) {
	std::map<std::string, SDL_Texture*> paths;
	std::list<std::string>::iterator iter;

	for (iter = texture_paths.begin(); iter != texture_paths.end(); iter++) {
		SDL_Texture* texture = drawer->GetTexture(*iter);
		paths[*iter] = texture;
	}

	SDL_Rect location;
	location.x = 0;
	location.y = 0;
	location.w = width;
	location.h = height;

	Graphic* newGraphic = new Graphic(paths, location);
	return newGraphic;

}

Graphic::Graphic(std::map<std::string, SDL_Texture*> texture_paths, SDL_Rect size)
	: boundingBox(size) {
	paths.insert(texture_paths.begin(), texture_paths.end());
}


void Graphic::SetImage(std::string anImage) {
	if (paths[anImage] != nullptr) {
		currImage = anImage;
	}
}

void Graphic::Draw(Drawer* drawer, int x, int y) {
	drawer->Draw(paths[currImage], boundingBox, x, y);
}