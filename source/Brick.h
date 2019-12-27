#pragma once
#include <SDL.h>
class Brick
{
public:

	static const int BRICK_WIDTH = 111;
	static const int BRICK_HEIGHT = 51;
	static int brickCount;

	Brick();
	~Brick();

	int getPosx();
	int getPosy();
	void setPosx(int x);
	void setPosy(int y);

	SDL_Rect getBrickCollider();
	void reduceBrickcount();

private:

	int brickPosx, brickPosy;

	SDL_Rect brickCollider;
};

