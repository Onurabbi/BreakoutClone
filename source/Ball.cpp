#include "Ball.h"
#include <iostream>
#include <cmath>
#include "Paddle.h"
#include "main.h"

Ball::Ball()
{
	ballPosx = 500;
	ballPosy = 500;

	ballCollider.w = BALL_WIDTH;
	ballCollider.h = BALL_HEIGHT;

	ballVelx = 7.0;
	ballVely = -7.0;

	paddleCollision = false;
	brickCollision = false;

	col = brickCollisionType::noCollision;
	score = 0;
}


Ball::~Ball()
{
}


void Ball::move(Paddle* paddle, Brick brick[][9])
{

	double velSquared = ballVelx * ballVelx + ballVely * ballVely;

	//move the ball collider together with the ball
	ballPosx += int(ballVelx);
	ballCollider.x = ballPosx;

	ballPosy += int(ballVely);
	ballCollider.y = ballPosy;

	//ball bounces back if it collides with screen bounds.
	if (ballPosx < 0)
	{
		ballPosx = 0;
		ballVelx = -ballVelx;
	}
	if (ballPosx + BALL_WIDTH > SCREEN_WIDTH)
	{
		ballPosx = SCREEN_WIDTH - BALL_WIDTH;
		ballVelx = -ballVelx;
	}

	if (ballPosy < 0)
	{
		ballPosy = 0;
		ballVely = -ballVely;
	}
	//checking if we are colliding with any bricks. it's okay to check all the bricks since it is fast and we have a relatively low amount of bricks. 
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (checkCollisionBrick(ballCollider, brick[i][j].getBrickCollider()))
			{
				if (col == brickCollisionType::horizontalCollision)
				{
					ballVelx = -ballVelx;
					brick[i][j].setPosx(-1000); //send the brick off the screen.
					brick[i][j].reduceBrickcount();
					score += 10;

				}
				else if (col == brickCollisionType::verticalCollision)
				{
					ballVely = -ballVely;
					brick[i][j].setPosx(-1000);
					brick[i][j].reduceBrickcount();
					score += 10;
				}
				else return;

			}
		}
	}

	//collision with the paddle. it is different from brick or wall collision since ball bounces differently depending on where it hits the paddle.

	paddleCollision = checkCollisionPaddle(ballCollider, paddle->getPaddleCollision());

	if (paddleCollision)
	{
		if (coeffX == 0)
		{
			ballVelx = -ballVelx;
		}
		else
		{
			ballVelx += coeffX;

			if (ballVelx > 9.0) ballVelx = 9.0;
			else if (ballVelx < -9.0) ballVelx = -9.0;
			//the y-velocity of the ball after collision should be interlocked with the x velocity to prevent the ball from gaining momentum from collisions.
			ballVely = sqrt(velSquared - (ballVelx * ballVelx));
			ballVely = -ballVely;
		}
	}
}


int Ball::getPosx()
{
	return ballPosx;
}

int Ball::getPosy()
{
	return ballPosy;
}

bool Ball::checkCollisionPaddle(SDL_Rect a, SDL_Rect b)
{
	//we use a circle collision to check if the ball collides with the paddle. 
	//If the distance of the ball to the closest location on the paddle is below ball radius, we are colliding with the paddle.
	int cX, cY;//closest location on the paddle to the ball/

	int ballCenterX = a.x + BALL_WIDTH / 2;
	int ballCenterY = a.y + BALL_HEIGHT / 2;


	if (ballCenterX < b.x)
	{
		cX = b.x;
	}
	else if (ballCenterX > b.x + b.w)
	{
		cX = b.x + b.w;
	}
	else
	{
		cX = ballCenterX;
	}
	if (ballCenterY < b.y)
	{
		cY = b.y;
	}
	else if (ballCenterY > b.y + b.h)
	{
		cY = b.y + b.h;
	}
	else
	{
		cY = ballCenterY;
	}
	//Using square distances because using sqrt afterwards wouldn't change the outcome.
	double squareX = (cX - ballCenterX)*(cX - ballCenterX);
	double squareY = (cY - ballCenterY)*(cY - ballCenterY);
	double squareDelta = squareX+squareY;

	
	double squareRadius = (BALL_WIDTH / 2.0)*(BALL_WIDTH / 2.0);


	if (squareRadius > squareDelta)
	{
		if (squareY>squareX) 
		{
			//coefficient to be added to the ball velocity, depending on the collision location on the paddle.
			coeffX = -5*((b.x + b.w / 2.0 - ballCenterX) / (b.w / 2.0));
			ballPosy = cY-BALL_HEIGHT;
			return true;
		}
		else
		{
			if (cX == b.x)
			{
				ballPosx = b.x; //colliding from left
			}
			else
			{
				ballPosx = b.x + BALL_WIDTH; //colliding from right
			}
			coeffX = 0;
			return true;
		}
	}	
	else
	return false;
}

bool Ball::checkCollisionBrick(SDL_Rect a, SDL_Rect b)
{
	//similar to paddle collision but there's no need for a velocity coefficient. it is either a vertical collision or horizontal collision.
	int cX, cY;
	int ballCenterX = a.x + BALL_WIDTH / 2;
	int ballCenterY = a.y + BALL_HEIGHT / 2;

	if (ballCenterX < b.x)
	{
		cX = b.x;
	}
	else if (ballCenterX > b.x + b.w)
	{
		cX = b.x + b.w;
	}
	else
	{
		cX = ballCenterX;
	}

	if (ballCenterY < b.y)
	{
		cY = b.y;
	}
	else if (ballCenterY > b.y + b.h)
	{
		cY = b.y + b.h;
	}
	else
	{
		cY = ballCenterY;
	}

	double squareX = (cX - ballCenterX)*(cX - ballCenterX);
	double squareY = (cY - ballCenterY)*(cY - ballCenterY);
	double squareDelta = squareX + squareY;


	double squareRadius = (BALL_WIDTH / 2.0)*(BALL_WIDTH / 2.0);


	if (squareRadius > squareDelta)
	{
		if (squareY > squareX)
		{
			col = brickCollisionType::verticalCollision;
			if (cY == b.y)
			{
				ballPosy = cY - BALL_HEIGHT;
			}
			else
			{
				ballPosy = cY + BALL_HEIGHT;
			}
			return true;
		}
		else
		{
			col = brickCollisionType::horizontalCollision;
			if (cX == b.x)
				ballPosx = cX - BALL_WIDTH;
			else
				ballPosx = cX + BALL_WIDTH;
			return true;
		}

	}
	else return false;
}

int Ball::getScore()
{
	return score;
}