#include "Mario.h"
#include "World.h"

Mario::Mario(SDL_Surface * animations[9],int x, int y):Creature::Creature(x,y,animations[8])
{
	marioJumpLeft = animations[0];
	marioJumpRight = animations[1];
	marioLoseLife = animations[2];
	marioMoveLeft1 = animations[3];
	marioMoveLeft2 = animations[4];
	marioMoveRight1 = animations[5];
	marioMoveRight2 = animations[6];
	marioStandLeft = animations[7];
	marioStandRight = animations[8];
	currentAnimation = marioStandRight;
	width = marioStandRight->w;
	height = marioStandRight->h;
}


double Mario::MAXSPEED = 150.00;
double Mario::JUMP =300;

void Mario::setLeftDirection(bool d)
{
	if (d != leftDirection && d)
	{
		animationTime = 0.15;
			currentAnimation = marioStandLeft;
			positionX -= 2;
	}
	if (!rightDirection && d != leftDirection)
			currentAnimation = marioStandLeft;

	leftDirection = d;

}

void Mario::setRightDirection(bool d)
{
	if (d != rightDirection && d)
	{
		animationTime = 0.15;
		currentAnimation = marioStandRight;
		positionX += 2;
	}
	if(!leftDirection && d != rightDirection)
			currentAnimation = marioStandRight;
	rightDirection = d;
}

void Mario::changeAnimation(int nr)
{
	switch (nr) {
		case 1:
		{
			if (currentAnimation == marioMoveRight1)
				currentAnimation = marioMoveRight2;
			else
				if (currentAnimation == marioMoveRight2)
					currentAnimation = marioMoveRight1;
				else
					if (currentAnimation == marioStandRight)
						currentAnimation = marioMoveRight1;
			break;
		}
		case 2:
		{
			if (currentAnimation == marioMoveLeft1)
				currentAnimation = marioMoveLeft2;
			else
				if (currentAnimation == marioMoveLeft2)
					currentAnimation = marioMoveLeft1;
				else
					if (currentAnimation == marioStandLeft)
						currentAnimation = marioMoveLeft1;
			break;
		}

	}
}

void Mario::update()
{
	if (rightDirection)
	{
		animationTime += 1.00 / World::FPS;
		horizontalForce = MAXSPEED;
		if (animationTime >= 0.15)
		{
			changeAnimation(1);
			animationTime = 0;
		}
	}
	else
	{
		if (leftDirection)
		{
			animationTime += 1.00 / World::FPS;
			horizontalForce = -MAXSPEED;
			if (animationTime >= 0.15)
			{
				changeAnimation(2);
				animationTime = 0;
			}
		}

	}
	if (!onFloor)
	{
		if (currentAnimation == marioMoveLeft1 || currentAnimation == marioMoveLeft2 || currentAnimation == marioStandLeft)
			currentAnimation = marioJumpLeft;
		else if (currentAnimation == marioMoveRight1 || currentAnimation == marioMoveRight2 || currentAnimation == marioStandRight)
			currentAnimation = marioJumpRight;

	}
	else
	{
		if (currentAnimation == marioJumpLeft)
			currentAnimation = marioStandLeft;
		else if (currentAnimation == marioJumpRight)
			currentAnimation = marioStandRight;
	}
	gravitation();
	positionX += horizontalForce/World::FPS;
	positionY += verticalForce/World::FPS;


	horizontalForce *= (1 - (1.00 / World::FPS)*5);
}

Mario::~Mario()
{
}
