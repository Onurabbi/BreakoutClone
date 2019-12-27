#pragma once
#include <SDL.h>
#include "main.h"
#include "Paddle.h"
#include "Brick.h"


enum brickCollisionType 
{
	noCollision,
	horizontalCollision,
	verticalCollision
};
class Ball
{
public:


	static const int BALL_WIDTH=16;
	static const int BALL_HEIGHT=16;



	Ball();
	~Ball();


	void move(Paddle* paddle, Brick brick[][9]);

	int getPosx();
	int getPosy();
	int getScore();

	bool checkCollisionPaddle(SDL_Rect a, SDL_Rect b);
	bool checkCollisionBrick(SDL_Rect a, SDL_Rect b);

	bool paddleCollision;
	bool brickCollision;

	double coeffX;
	brickCollisionType col;

private:

	int ballPosx, ballPosy;

	double ballVelx, ballVely;

	SDL_Rect ballCollider;
	
	int score;

};

