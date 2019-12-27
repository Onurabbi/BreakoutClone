#include "Brick.h"



Brick::Brick()
{
	brickCollider.w = BRICK_WIDTH;
	brickCollider.h = BRICK_HEIGHT;
	brickPosx = 0;
	brickPosy = 0;
}


Brick::~Brick()
{
}

void Brick::setPosx(int x)
{
	brickPosx = x;
	brickCollider.x = brickPosx + 4;
}

void Brick::setPosy(int y)
{
	brickPosy = y;
	brickCollider.y = brickPosy + 4;
}

int Brick::getPosx()
{
	return brickPosx;
}

int Brick::getPosy()
{
	return brickPosy;
}

SDL_Rect Brick::getBrickCollider()
{
	return brickCollider;
}
void Brick::reduceBrickcount()
{
	brickCount--;
}