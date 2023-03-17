#include "Drawer.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_rect.h"
#include "SDL_ttf.h"

Drawer* Drawer::Create(SDL_Window* aWindow, SDL_Renderer* aRenderer)
{
	Drawer* drawer = new Drawer(aWindow, aRenderer);

	if (!drawer->Init())
	{
		delete drawer;
		drawer = NULL;
	}

	return drawer;
}

Drawer::Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer)
: myWindow(aWindow)
, myRenderer(aRenderer)
{
}

Drawer::~Drawer(void)
{
}

bool Drawer::Init()
{
	if (!myWindow)
		return false;

	return true;
}

SDL_Texture* Drawer::GetTexture(std::string path) {
	SDL_Texture* texture = nullptr;

	if (texture_paths.count(path) > 0) {
		texture = texture_paths.at(path);
	}
	else {
		texture = IMG_LoadTexture(myRenderer, path.c_str());
		texture_paths[path] = texture;
	}

	return texture;
}

SDL_Texture* Drawer::GetTexture(SDL_Surface* aSurface) {
	return SDL_CreateTextureFromSurface(myRenderer, aSurface);
}

void Drawer::Draw(SDL_Texture* texture, SDL_Rect boundingBox, int aCellX, int aCellY)
{
    SDL_Rect posRect ;
    posRect.x = aCellX;
    posRect.y = aCellY;
	posRect.w = boundingBox.w;
	posRect.h = boundingBox.h;

	SDL_RenderCopy(myRenderer, texture, &boundingBox, &posRect);
}

void Drawer::DrawText(const char* aText, const char* aFontFile, int aX, int aY)
{
	TTF_Font* font=TTF_OpenFont(aFontFile, 24);

	SDL_Color fg={255,0,0,255};
	SDL_Surface* surface = TTF_RenderText_Solid(font, aText, fg);

	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(myRenderer, surface);

    SDL_Rect sizeRect;
    sizeRect.x = 0 ;
    sizeRect.y = 0 ;
    sizeRect.w = surface->w ;
    sizeRect.h = surface->h ;

    SDL_Rect posRect ;
    posRect.x = aX;
    posRect.y = aY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(myRenderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}
