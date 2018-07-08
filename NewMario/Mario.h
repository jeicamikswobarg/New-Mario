#ifndef MARIO_H
#define MARIO_H

#include<SDL.h>
#include "Creature.h"

class World;
class Mario:public Creature
{
	private:
		SDL_Surface * marioMoveRight1, * marioMoveRight2, * marioMoveLeft1, * marioMoveLeft2,
			* marioStandRight, * marioStandLeft, * marioJumpRight, * marioJumpLeft, * marioLoseLife;
		void changeAnimation(int nr);

	public:
		static double MAXSPEED;
		static double JUMP;
		void update();
		void setLeftDirection(bool d);
		void setRightDirection(bool d);


		Mario(SDL_Surface * animations[9],int x,int y);
		~Mario();
};

#endif