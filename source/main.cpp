#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Texture.h"
#include "Ball.h"
#include "main.h"
#include "Paddle.h"
#include "Brick.h"

bool init();
void close();
bool loadMedia();

SDL_Window* mainWindow = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

Texture ballTexture;
Texture paddleTexture;
Texture firstBrickTexture;
Texture secondBrickTexture;
Texture thirdBrickTexture;
Texture fourthBrickTexture;
Texture backgroundTexture;
Texture scoreBgTexture;
Texture scoreTexture;

Ball ball;
Paddle paddle;

Brick brick_array[4][9];
int Brick::brickCount = 36;

void renderBricks();


int main(int argc, char* args[])
{


	if (!init())
	{
		std::cout << "Failed to initialize!" << std::endl;
	}
	else 
	{
		if (!loadMedia())
		{
			std::cout << "Failed to load media!" << std::endl;
		}
		else
		{
			bool quit = false;

			SDL_Event e;


			//Create bricks and set their collision positions on the screen.
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 9; j++)
				{
					Brick brick;
					brick_array[i][j] = brick;
				}
			
			for (int i = 0; i < 9; i++)
			{
				brick_array[0][i].setPosx(120 * i + 100);
				brick_array[0][i].setPosy(120);
			}
			for (int i = 0; i < 9; i++)
			{
				brick_array[1][i].setPosx(120 * i + 100);
				brick_array[1][i].setPosy(180);
			}
			for (int i = 0; i < 9; i++)
			{
				brick_array[2][i].setPosx(120 * i + 100);
				brick_array[2][i].setPosy(240);
			}
			for (int i = 0; i < 9; i++)
			{
				brick_array[3][i].setPosx(120 * i + 100);
				brick_array[3][i].setPosy(300);
			}
			

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//paddle movement speed is updated with keyboard states
					paddle.handleEvents(e);
				}


				paddle.move();

				//move the ball see if it is colliding with the paddle or the bricks.
				ball.move(&paddle, brick_array);
				//we lose if the ball falls below the screen
				if (ball.getPosy() > SCREEN_HEIGHT)
				{
					quit = true;
				}
				if (Brick::brickCount == 0) quit = true; 

				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				SDL_RenderClear(renderer);
				//render the background, the bricks, the score, balls and the paddle to the screen
				backgroundTexture.render(0, 0, renderer, nullptr);

				renderBricks();

				//Render score
				scoreBgTexture.render(50, 50, renderer, nullptr);
				SDL_Color textColor = { 0, 0, 0 };
				if (!scoreTexture.loadFromRenderedText(ball, textColor, font, renderer))
				{
					printf("Failed to render text texture!\n");
				}

				scoreTexture.render(50, 50, renderer, nullptr);

				ballTexture.render(ball.getPosx(), ball.getPosy(), renderer, nullptr);

				paddleTexture.render(paddle.getPosx(), paddle.getPosy(), renderer, nullptr);

				SDL_RenderPresent(renderer);
				
			}

		}
	}
	close();
	return 0;
}

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialize SDL! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		mainWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (mainWindow == nullptr)
		{
			std::cout <<  "Failed to create SDL_Window SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (renderer == nullptr)
			{
				std::cout << "Failed to create SDL_Renderer SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0XFF, 0XFF);

				int imgFlags = IMG_Init(IMG_INIT_PNG);
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL Image could not initialize. SDL_Error: " << SDL_GetError() << std::endl;
					success = false;
				}
				if (TTF_Init() == -1)
				{
					std::cout << "Unable to initialize TTF. TTF_Error: " << TTF_GetError() << std::endl;
					success = false;
				}
			}
		}
	}
	return success;
}

void close()
{

	ballTexture.free();
	paddleTexture.free();
	
	backgroundTexture.free();
	firstBrickTexture.free();
	secondBrickTexture.free();
	thirdBrickTexture.free();
	fourthBrickTexture.free();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(mainWindow);
	mainWindow = nullptr;
	renderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool loadMedia()
{
	bool success = true;

	if (!backgroundTexture.loadImage("assets/bg.png", renderer))
	{
		std::cout << "Could not load birim!!" << std::endl;
		success = false;
	}

	if (!ballTexture.loadImage("assets/ball.png", renderer))
	{
		std::cout << "Could not load ball texture!!" << std::endl;
		success = false;
	}
	if (!paddleTexture.loadImage("assets/paddle.png", renderer))
	{
		std::cout << "Could not load paddle texture!!" << std::endl;
		success = false;
	}
	if (!firstBrickTexture.loadImage("assets/top_row_brick.png", renderer))
	{
		std::cout << "Could not load first row brick texture!!" << std::endl;
		success = false;
	}
	if (!secondBrickTexture.loadImage("assets/second_row_brick.png", renderer))
	{
		std::cout << "Could not load second row brick texture!!" << std::endl;
		success = false;
	}
	if (!thirdBrickTexture.loadImage("assets/third_row_brick.png", renderer))
	{
		std::cout << "Could not load third row brick texture!!" << std::endl;
		success = false;
	}
	if (!fourthBrickTexture.loadImage("assets/fourth_row_brick.png", renderer))
	{
		std::cout << "Could not load fourth row brick texture!!" << std::endl;
		success = false;
	}
	if (!scoreBgTexture.loadImage("assets/scorebg.png", renderer))
	{
		std::cout << "Could not load score board texture!!" << std::endl;
		success = false;
	}

	font = TTF_OpenFont("assets/Roboto-Regular.ttf", 28);
	if (font == nullptr)
	{
		std::cout << "Unable to load roboto font! TTF Error: " << TTF_GetError()<<std::endl;
		success = false;
	}

	return success;
}

void renderBricks()
{
	for (int i = 0; i < 9; i++)
	{
		if (brick_array[0][i].getPosx() > 0)
			firstBrickTexture.render(120 * i + 100, 120, renderer, nullptr);
	}
	for (int i = 0; i < 9; i++)
	{
		if (brick_array[1][i].getPosx() > 0)
			secondBrickTexture.render(120 * i + 100, 180, renderer, nullptr);
	}
	for (int i = 0; i < 9; i++)
	{
		if (brick_array[2][i].getPosx() > 0)
			thirdBrickTexture.render(120 * i + 100, 240, renderer, nullptr);
	}
	for (int i = 0; i < 9; i++)
	{
		if (brick_array[3][i].getPosx() > 0)
			fourthBrickTexture.render(120 * i + 100, 300, renderer, nullptr);
	}
}


