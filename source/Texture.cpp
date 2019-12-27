#include "Texture.h"
#include <iostream>
#include <SDL.h>

Texture::Texture()
{
	texture = nullptr;
	tWidth = 0;
	tHeight = 0;

}


Texture::~Texture()
{
	free();
}

bool Texture::loadImage(std::string path, SDL_Renderer* renderer)
{
	
	free();

	SDL_Texture* tempTexture=nullptr;
	SDL_Surface* tempSurface = IMG_Load(path.c_str());

	if (tempSurface == nullptr)
	{
		std::cout << "Unable to load image. SDL_Error: " << SDL_GetError() << std::endl;
	}
	else 
	{
		SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));

		tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

		if (tempTexture == nullptr)
		{
			std::cout << "Unable to create texture from surface. SDL_Error:" << SDL_GetError() << std::endl;
		}
		else
		{
			tWidth = tempSurface->w;
			tHeight = tempSurface->h;
		}
		SDL_FreeSurface(tempSurface);
	}
	texture = tempTexture;
	return texture != nullptr;
}

void Texture::free()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		tWidth = 0;
		tHeight = 0;
	}
}

int Texture::getWidth()
{
	return tWidth;
}

int Texture::getHeight()
{
	return tHeight;
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* srcRect)
{
	SDL_Rect rectangle = {x,y,tWidth, tHeight};

	SDL_RenderCopy(renderer, texture, srcRect, &rectangle);
}
bool Texture::loadFromRenderedText(Ball &ball, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer)
{
	free();
	std::stringstream textureText;
	textureText.str(" ");
	SDL_Texture* tempTexture = nullptr;
	textureText << "Score: " << ball.getScore();
	SDL_Surface* tempSurface = TTF_RenderText_Solid(font,textureText.str().c_str(),textColor);

	if (tempSurface == nullptr)
	{
		std::cout << "Unable to render text surface. TTF Error: " << TTF_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));

		tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

		if (tempTexture == nullptr)
		{
			std::cout << "Unable to create texture from surface. SDL_Error:" << SDL_GetError() << std::endl;
		}
		else
		{
			tWidth = tempSurface->w;
			tHeight = tempSurface->h;
		}
		SDL_FreeSurface(tempSurface);
	}
	texture = tempTexture;
	return texture != nullptr;
}