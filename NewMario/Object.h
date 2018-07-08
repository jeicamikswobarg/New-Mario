#pragma once
#include<SDL.h>
class Object
{
protected:
	double positionX, positionY;
	double width, height;
	SDL_Surface * currentAnimation;
public:
	Object(int positionX,int positionY, SDL_Surface * currentAnimation);
	SDL_Surface * getCurrentAnimation();
	double getPositionX();
	double getPositionY();
	void setPositionX(double x);
    void setPositionY(double y);
	double getWidth();
	double getHeight();
	virtual ~Object();
};

