#include "NormalMob.h"
#include "World.h"


NormalMob::NormalMob(int x, int y, SDL_Surface * animationLeft, SDL_Surface * animationRight) :Creature::Creature(x, y, animationRight)
{
	horizontalForce = 100;
	this->animationLeft = animationLeft;
	this->animationRight = animationRight;
}

void NormalMob::changeAnimation()
{
	if (currentAnimation == animationLeft)
		currentAnimation = animationRight;
	else
		currentAnimation = animationLeft;
}

void NormalMob::update()
{
	gravitation();
	positionX += horizontalForce / World::FPS;
	positionY += verticalForce / World::FPS;

	animationTime += 1.00 / World::FPS;
	if (animationTime >= 0.25)
	{
		changeAnimation();
		animationTime = 0;
	}
}


void NormalMob::changeDirection()
{
	horizontalForce *= -1;
	if (horizontalForce > 0)
		positionX += 3;
	else
		positionX -= 3;
}

NormalMob::~NormalMob()
{
}
