#pragma once
#include "Object.h"
class Creature :
	public Object
{
protected:
	double verticalForce, horizontalForce;
	bool leftDirection, rightDirection;
	double animationTime;
public:
	bool onFloor;
	static double GRAVITATION;
	static double MAX_SPEED_DOWN;
	void gravitation();
	void setHorizonralForce(double force);
	void setVerticalForce(double force);
	void addVerticalForce(double force);
    virtual void update() ;
	Creature(int x,int y, SDL_Surface * currentAnimation);
	~Creature();
};

