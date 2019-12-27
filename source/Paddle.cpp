#include "Paddle.h"



Paddle::Paddle()
{
	paddlePosx = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;

	paddlePosy = (SCREEN_HEIGHT - PADDLE_HEIGHT*2);
	paddleVelx = 0;

	paddleCollision.w = PADDLE_WIDTH;

	paddleCollision.h = PADDLE_HEIGHT;
	paddleCollision.y = SCREEN_HEIGHT - PADDLE_HEIGHT*2;
}


Paddle::~Paddle()
{
}


void Paddle::handleEvents(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN &&e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: paddleVelx -= PADDLE_VEL; break;
		case SDLK_RIGHT: paddleVelx += PADDLE_VEL; break;
		}
	}
	else if (e.type == SDL_KEYUP&&e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: paddleVelx +=PADDLE_VEL; break;
		case SDLK_RIGHT: paddleVelx -=PADDLE_VEL; break;
		}
	}
}

//move the paddle and the collision rectangle with it.
void Paddle::move()
{
	paddlePosx += paddleVelx;
	paddleCollision.x = paddlePosx;

	if ((paddlePosx < 0) || (paddlePosx + PADDLE_WIDTH > SCREEN_WIDTH))
	{
		paddlePosx -= paddleVelx;
		paddleCollision.x = paddlePosx;
	}
}

int Paddle::getPosx()
{
	return paddlePosx;
}

int Paddle::getPosy()
{
	return paddlePosy;
}

SDL_Rect Paddle::getPaddleCollision()
{
	return paddleCollision;
}