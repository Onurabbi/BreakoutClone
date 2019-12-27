#pragma once
#include <string>
#include <SDL.h>
#include <SDL_Image.h>
#include "main.h"
#include <SDL_ttf.h>
#include <sstream>
#include "Ball.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool loadImage(std::string path, SDL_Renderer* renderer);

	bool loadFromRenderedText(Ball &ball, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer);

	void free();
	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* srcRect=nullptr);

	int getWidth();
	int getHeight();

	

private:

	SDL_Texture* texture;

	int tWidth;
	int tHeight;
};

