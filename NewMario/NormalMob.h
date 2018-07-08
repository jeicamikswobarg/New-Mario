#pragma once
#include<SDL.h>
#include "Creature.h"

class World;

class NormalMob :
	public Creature
{
private:
	SDL_Surface * animationLeft, *animationRight;
	void changeAnimation();
public:
	NormalMob(int x, int y, SDL_Surface * animationLeft, SDL_Surface * animationRight);
	void update();
	void changeDirection();
	~NormalMob();

};

