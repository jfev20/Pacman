#ifndef DRAWER_H
#define DRAWER_H

#include <map>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Rect;

class Drawer
{
public:
	static Drawer* Create(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	~Drawer(void);

	SDL_Texture* GetTexture(std::string path);
	SDL_Texture* GetTexture(SDL_Surface* aSurface);

	void Draw(SDL_Texture* texture, SDL_Rect boundingBox, int aCellX = 0, int aCellY = 0);
	void DrawText(const char* aText, const char* aFontFile, int aX, int aY);

private:
	Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	bool Init();

	
	
	std::map<std::string, SDL_Texture*> texture_paths;
	SDL_Window* myWindow;
	SDL_Renderer* myRenderer;
	SDL_Surface* world;
};

#endif // DRAWER_H