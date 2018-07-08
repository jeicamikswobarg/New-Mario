#include "Creature.h"
#include "World.h"

double Creature::GRAVITATION = 600;
double Creature::MAX_SPEED_DOWN = 400;
Creature::Creature(int x,int y, SDL_Surface * currentAnimation):Object::Object(x,y,currentAnimation)
{
	animationTime = 0;
	leftDirection = false;
	rightDirection = false;
	verticalForce = 0;
	horizontalForce = 0;
	onFloor = false;
}

Creature::~Creature()
{
}

void Creature::setHorizonralForce(double force) {
	horizontalForce = force;
}

void Creature::setVerticalForce(double force) {
	if (force == 0)
	{
		if (verticalForce < 0)
			verticalForce = 0;

	}
	else
	verticalForce = force;
}

void Creature::addVerticalForce(double force) {
	if (force > 0 && onFloor)
	{
		verticalForce -= force;
		onFloor = false;
		positionY -= 2;
	}
	else if (force < 0 && verticalForce <MAX_SPEED_DOWN)
		verticalForce -= force;
}

void Creature::gravitation()
{
	if (!onFloor)
	{

		addVerticalForce(-GRAVITATION / World::FPS);
	}
	else
		verticalForce = 0;
}

void Creature::update() {

}