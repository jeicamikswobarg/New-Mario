#pragma once
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<SDL.h>
#include "World.h"
#include "Mario.h"
#include "Object.h"
#include "Creature.h"
#include "NormalMob.h"
#include<vector>
#undef main
#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define FPS 60




bool loadMarioData(SDL_Surface *marioAnimations[])
{
	marioAnimations[0] = SDL_LoadBMP("./Animations/marioJumpLeft.bmp");
	marioAnimations[1] = SDL_LoadBMP("./Animations/marioJumpRight.bmp");
	marioAnimations[2] = SDL_LoadBMP("./Animations/marioLoseLife.bmp");
	marioAnimations[3] = SDL_LoadBMP("./Animations/marioMoveLeft1.bmp");
	marioAnimations[4] = SDL_LoadBMP("./Animations/marioMoveLeft2.bmp");
	marioAnimations[5] = SDL_LoadBMP("./Animations/marioMoveRight1.bmp");
	marioAnimations[6] = SDL_LoadBMP("./Animations/marioMoveRight2.bmp");
	marioAnimations[7] = SDL_LoadBMP("./Animations/marioStandLeft.bmp");
	marioAnimations[8] = SDL_LoadBMP("./Animations/marioStandRight.bmp");
	marioAnimations[9] = SDL_LoadBMP("./Animations/floor.bmp");
	marioAnimations[10] = SDL_LoadBMP("./Animations/block.bmp");
	marioAnimations[11] = SDL_LoadBMP("./Animations/mob1.bmp");
	marioAnimations[12] = SDL_LoadBMP("./Animations/mob2.bmp");
	for (int k = 0; k < 13; k++)
		if (marioAnimations[k] == NULL)
			return false;

	return true;
}



int main()
{
	int rc,quit = 0;
	SDL_Event event;
	SDL_Surface *screen;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface* marioAnimations[20];

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}
	//rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
	//	&window, &renderer);  //fullscrean
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
			&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetWindowTitle(window, "Mario");
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);
	//SDL_ShowCursor(SDL_DISABLE);
	if (!loadMarioData(marioAnimations))
	{
		printf("Lack of animations");
		return 1;
	}
	Mario mario(marioAnimations,400,400);
	Object floor(300, 450, marioAnimations[9]);
	NormalMob mob1(300, 100, marioAnimations[11], marioAnimations[12]);
	NormalMob mob2(350, 100, marioAnimations[11], marioAnimations[12]);
	NormalMob mob3(250, 100, marioAnimations [11], marioAnimations[12]);
	Object block1(600, 430, marioAnimations[10]);
	Object block2(200, 430, marioAnimations[10]);
	Object block3(100, 430, marioAnimations[10]);
	std::vector<Object *>objects;
	objects.push_back(&mario);
	objects.push_back(&floor);
	objects.push_back(&block1);
	objects.push_back(&block2);
	objects.push_back(&block3);
	objects.push_back(&mob1);
	objects.push_back(&mob2);
	objects.push_back(&mob3);
	World world(renderer, screen, scrtex,&objects);

	while (!quit)
	{
		world.countTime();

		if (world.isNextFrame())
		{
			world.update();
			world.draw();

			while (SDL_PollEvent(&event)) {
					if(event.type == SDL_KEYUP)
					{
						if (event.key.keysym.sym == SDLK_RIGHT) { mario.setRightDirection(false); }
						if (event.key.keysym.sym == SDLK_LEFT) { mario.setLeftDirection(false); }
						if (event.key.keysym.sym == SDLK_UP) {}
					}
					else if (event.type == SDL_KEYDOWN)
					{
						if (event.key.keysym.sym == SDLK_ESCAPE) { quit = 1; };
						if (event.key.keysym.sym == SDLK_n) {}
						if (event.key.keysym.sym == SDLK_RIGHT) {
							mario.setRightDirection(true); mario.setLeftDirection(false);}
						if (event.key.keysym.sym == SDLK_LEFT) { mario.setLeftDirection(true); mario.setRightDirection(false);}
						if (event.key.keysym.sym == SDLK_UP) {	mario.addVerticalForce(Mario::JUMP); }
						if (event.key.keysym.sym == SDLK_s) {}
						if (event.key.keysym.sym == SDLK_l) {}
					}
					else if(event.type ==  SDL_QUIT)
					{
						quit = 1;
					}

			}
		}
	}
	return 0;

	//usunac wszystko
}
