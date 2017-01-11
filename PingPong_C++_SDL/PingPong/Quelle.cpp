#include <iostream>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "QLerner.h"

#define WIDTH 400
#define HEIGHT 400
#define VELOCITY_X 10
#define VELOCITY_Y 10
#define TIMEDIFFMILLI 50

using namespace std;

int main(int argc, char* argv[])
{
	// SDL Standard
	SDL_Surface* screen = NULL;
	SDL_Window* sdlWindow = NULL;
	SDL_Renderer* sdlRenderer = NULL;
	SDL_Surface* surfaceMessage = NULL;
	SDL_Texture* textureMessage = NULL;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) == -1)
	{
		cerr << "SDL konnte nicht initialisiert werden! Fehler: " << SDL_GetError() << endl;
	}

	sdlWindow = SDL_CreateWindow("Test", 100, 100, WIDTH, HEIGHT, SDL_WindowFlags::SDL_WINDOW_SHOWN);
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);

	TTF_Init();
	screen = SDL_GetWindowSurface(sdlWindow);

	// Font & Points
	TTF_Font* os = TTF_OpenFont("C:\\Windows\\Fonts\\calibri.ttf", 12);
	SDL_Color white = {255, 255, 255};
	SDL_Rect mrect; mrect.h = 12; mrect.w = 60; mrect.x = 1; mrect.y = 1;
	SDL_Rect ball; ball.h = 10; ball.w = 10; ball.x = rand()%100; ball.y = rand()%100;
	SDL_Rect paddle; paddle.h = 20; paddle.w = 60; paddle.y = HEIGHT-paddle.h-2; paddle.x = WIDTH/2 - paddle.w/2;
	unsigned long points = 0;
	char* buff = new char[strlen("score: 00000")+1];

	// Game
	bool run = true, pointSet = true;
	float velocityX = VELOCITY_X;
	float velocityY = VELOCITY_Y;
	float deltaTime = 0.0f;
	float deltaTimeSum = 0.0f;
	int thisTime = 0;
	int lastTime = 0;

	QLerner qlerner(mrect.w, mrect.h, 0.1);

	while(run)
	{
		SDL_Event event;
		SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 1);
		SDL_RenderClear(sdlRenderer);

		thisTime = SDL_GetTicks();
		deltaTime = (float)(thisTime-lastTime);
		deltaTimeSum += deltaTime;
		lastTime = thisTime;

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					run = false;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							run = false;
							break;

						case SDLK_LEFT:
							paddle.x = (paddle.x - 5 < 0 ) ? 0 : paddle.x -10;
							break;

						case SDLK_RIGHT:
							paddle.x = (paddle.x + 5 > screen->w-paddle.w ) ? screen->w-paddle.w : paddle.x + 10;
							break;
					}
					break;
			}
		}

		if((int)abs(deltaTimeSum) > TIMEDIFFMILLI)
		{
			ball.x += velocityX;
			ball.y += velocityY;
			deltaTimeSum = 0;
		}

		if(ball.x >= screen->w-ball.w)
			velocityX = -VELOCITY_X;
		else if(ball.x <= 0)
			velocityX = VELOCITY_X;

		if(ball.y <= 0)
		{
			pointSet = true;
			velocityY = VELOCITY_Y;
		}
		else if(SDL_HasIntersection(&paddle, &ball))
		{
			velocityY = -VELOCITY_Y;

			if(pointSet)
			{
				points++;
				pointSet = false;
			}
		}
		else if(ball.y >= screen->h)
			run = false;


		SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 1);
		SDL_RenderDrawRect(sdlRenderer, &paddle);
		SDL_RenderDrawRect(sdlRenderer, &ball);
		sprintf(buff, "Score: %d", points);
		surfaceMessage = TTF_RenderText_Solid(os, buff, white);
		textureMessage = SDL_CreateTextureFromSurface(sdlRenderer, surfaceMessage);
		SDL_RenderCopy(sdlRenderer, textureMessage, NULL, &mrect);
		SDL_RenderPresent(sdlRenderer);
	}

	//SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	TTF_CloseFont(os);

	SDL_Quit();
	return 0;
}