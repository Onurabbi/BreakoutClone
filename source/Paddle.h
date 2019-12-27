#pragma once
#include <SDL.h>
#include "main.h"

class Paddle
{
public:

	static const int PADDLE_WIDTH = 229;
	static const int PADDLE_HEIGHT = 47;

	static const int PADDLE_VEL = 16;

	Paddle();
	~Paddle();

	void move();
	void handleEvents(SDL_Event &e);

	int getPosx();
	int getPosy();
	SDL_Rect getPaddleCollision();

private:

	int paddlePosx;
	int paddlePosy;
	int paddleVelx;

	SDL_Rect paddleCollision;
};

