#include "Object.h"



Object::Object(int positionX,int positionY, SDL_Surface * currentAnimation)
{
	this->positionX = positionX;
	this->positionY = positionY;
	this->currentAnimation =  currentAnimation;
	width = currentAnimation->w;
	height = currentAnimation->h;
}

double Object::getPositionX() {
	return this->positionX;
}
double Object::getPositionY() {
	return this->positionY;
}

SDL_Surface * Object::getCurrentAnimation() {
	return this->currentAnimation;
}

Object::~Object()
{
}

double Object::getWidth() {
	return width;
}
double Object::getHeight() {

	return height;
}

void Object::setPositionX(double x) {
	positionX = x;
}
void Object::setPositionY(double y) {
	positionY = y;
}