#include "World.h"
#include "Mario.h"
#include "Object.h"
#include "Creature.h"
#include "NormalMob.h"
#include<vector>

double World::diffTime = 0;
World::World(SDL_Renderer * renderer, SDL_Surface *screen, SDL_Texture *scrtex, std::vector<Object *> *objects)
{
	this->objects = objects;
	delta = 0;
	worldTime = 0;
	distance = 0;
	black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	t1 = SDL_GetTicks();
	this->renderer = renderer;
	this->screen = screen;
	this->scrtex = scrtex;

}

bool World::isNextFrame() {
	if (nextFrame)
	{
		nextFrame = false;
		return true;
	}
	return false;
}
void World::countTime() {
	this->t2 = SDL_GetTicks();
	delta += (t2 - t1)*0.001;
	diffTime= (t2 - t1)*0.001;
	worldTime += (t2 - t1)*0.001;
	t1 = t2;
	if (delta >= 1.00 / FPS)
	{
		delta  -= 1.00 / FPS;
		nextFrame = true;
	}

}


void World::DrawSurface(SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, this->screen, &dest);
};

void World::draw()
{
	SDL_FillRect(screen, NULL, blue);

	//marioDraw
	for (int k = 0; k < objects->size(); k++)
		this->DrawSurface((*objects)[k]->getCurrentAnimation(), (*objects)[k]->getPositionX(), (*objects)[k]->getPositionY());
	
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void World::update()
{

	for (int k = 0; k < objects->size(); k++)
		if (dynamic_cast<Creature *>((*objects)[k]) != nullptr)
			((Creature *)((*objects)[k]))->update();

	//repair all colision

	for (int k = 0; k < objects->size(); k++)
		if (dynamic_cast<Creature *>((*objects)[k]) != nullptr)
		{
			bool isEnemy = false;
			Creature * creature = dynamic_cast<Creature *>((*objects)[k]);
			NormalMob *mob = dynamic_cast<NormalMob *>(creature);
			if (mob != nullptr)
				isEnemy = true;
			creature->onFloor = false;
			for (int z = 0; z < objects->size(); z++)
			{
				if (z != k )
				{				

					if (
						(*objects)[z]->getPositionX() - creature->getPositionX() >(creature->getWidth() + (*objects)[z]->getWidth()) / 2 - Mario::MAXSPEED / 40.00 &&
						(*objects)[z]->getPositionX() - creature->getPositionX() < (creature->getWidth() + (*objects)[z]->getWidth()) / 2 + Mario::MAXSPEED / 40.00 &&
						abs((*objects)[z]->getPositionY() - creature->getPositionY()) < (creature->getHeight() + (*objects)[z]->getHeight() )/2 - Creature::MAX_SPEED_DOWN / 80.00)
						{
						creature->setPositionX((*objects)[z]->getPositionX() - (creature->getWidth() + (*objects)[z]->getWidth()) / 2);
						if (isEnemy)
						{
							mob->changeDirection();
							NormalMob *mob1 = dynamic_cast<NormalMob *>((*objects)[z]);
							if (mob1 != nullptr)
								mob1->changeDirection();

						}
							else
								creature->setHorizonralForce(0);

						}


						if (
							creature->getPositionX() - (*objects)[z]->getPositionX() > (creature->getWidth() + (*objects)[z]->getWidth()) / 2 - Mario::MAXSPEED / 40.00 &&
							creature->getPositionX() - (*objects)[z]->getPositionX() < (creature->getWidth() + (*objects)[z]->getWidth()) / 2 + Mario::MAXSPEED / 40.00&&
							abs((*objects)[z]->getPositionY() - creature->getPositionY()) < (creature->getHeight() + (*objects)[z]->getHeight()) / 2 - Creature::MAX_SPEED_DOWN / 80.00)
							{

								creature->setPositionX((*objects)[z]->getPositionX() + (creature->getWidth() + (*objects)[z]->getWidth()) / 2);
								if (isEnemy)
								{
									mob->changeDirection();
									NormalMob *mob2 = dynamic_cast<NormalMob *>((*objects)[z]);
									if (mob2 != nullptr)
										mob2->changeDirection();
								}
								else
									creature->setHorizonralForce(0);
							}

							if ((*objects)[z]->getPositionY() - creature->getPositionY() > (creature->getHeight() + (*objects)[z]->getHeight()) / 2 - Creature::MAX_SPEED_DOWN / 80.00 &&
								(*objects)[z]->getPositionY() - creature->getPositionY() < (creature->getHeight() + (*objects)[z]->getHeight()) / 2 + Creature::MAX_SPEED_DOWN / 80.00 &&
								abs((*objects)[z]->getPositionX() - creature->getPositionX()) < (creature->getWidth() + (*objects)[z]->getWidth()) / 2 - Mario::MAXSPEED / 40.00)
							{
								creature->setPositionY((*objects)[z]->getPositionY() - (creature->getHeight() + (*objects)[z]->getHeight()) / 2);
								creature->onFloor = true;
							}

							 if (creature->getPositionY() - (*objects)[z]->getPositionY() > (creature->getHeight() + (*objects)[z]->getHeight()) / 2 - Mario::JUMP / 80.00 &&
								creature->getPositionY() - (*objects)[z]->getPositionY()  < (creature->getHeight() + (*objects)[z]->getHeight()) / 2 + Mario::JUMP / 80.00 &&
								abs((*objects)[z]->getPositionX() - creature->getPositionX()) < (creature->getWidth() + (*objects)[z]->getWidth()) / 2 - Mario::MAXSPEED / 40.00)
							{
								creature->setPositionY((*objects)[z]->getPositionY() + (creature->getHeight() + (*objects)[z]->getHeight()) / 2);
								creature->setVerticalForce(0);
							}
						
							 if (
								 (*objects)[z]->getPositionX() - creature->getPositionX() >0 &&
								 (*objects)[z]->getPositionX() - creature->getPositionX() < (creature->getWidth() + (*objects)[z]->getWidth()) / 2 &&
								 creature->getPositionY() - (*objects)[z]->getPositionY() > 0 &&
								 creature->getPositionY() - (*objects)[z]->getPositionY()  < (creature->getHeight() + (*objects)[z]->getHeight()) / 2)
							 {
								 creature->setPositionX((*objects)[z]->getPositionX() - (creature->getWidth() + (*objects)[z]->getWidth()) / 2 );
								// creature->setPositionY((*objects)[z]->getPositionY() + (creature->getHeight() + (*objects)[z]->getHeight()) / 2 );
							 }


							 if (
								 (*objects)[z]->getPositionX() - creature->getPositionX() > 0 &&
								 (*objects)[z]->getPositionX() - creature->getPositionX() < (creature->getWidth() + (*objects)[z]->getWidth()) / 2 &&
								 (*objects)[z]->getPositionY() - creature->getPositionY()> 0 &&
								 (*objects)[z]->getPositionY() - creature->getPositionY() < (creature->getHeight() + (*objects)[z]->getHeight()) / 2)
							 {
								 creature->setPositionX((*objects)[z]->getPositionX() - (creature->getWidth() + (*objects)[z]->getWidth()) / 2 );
								// creature->setPositionY((*objects)[z]->getPositionY() - (creature->getHeight() + (*objects)[z]->getHeight()) / 2 );
								// creature->onFloor = true;
							 }

							 if (
								 creature->getPositionX() - (*objects)[z]->getPositionX() > 0 &&
								 creature->getPositionX() - (*objects)[z]->getPositionX() < (creature->getWidth() + (*objects)[z]->getWidth()) / 2 &&
								 creature->getPositionY() - (*objects)[z]->getPositionY() > 0 &&
								 creature->getPositionY() - (*objects)[z]->getPositionY()  < (creature->getHeight() + (*objects)[z]->getHeight()) / 2)
							 {
								 creature->setPositionX((*objects)[z]->getPositionX() + (creature->getWidth() + (*objects)[z]->getWidth()) / 2);
								// creature->setPositionY((*objects)[z]->getPositionY() + (creature->getHeight() + (*objects)[z]->getHeight()) / 2);
							 }

							 if (
								 creature->getPositionX() - (*objects)[z]->getPositionX() > 0 &&
								 creature->getPositionX() - (*objects)[z]->getPositionX() < (creature->getWidth() + (*objects)[z]->getWidth()) / 2 &&
								 (*objects)[z]->getPositionY() - creature->getPositionY() > 0 &&
								 (*objects)[z]->getPositionY() - creature->getPositionY() < (creature->getHeight() + (*objects)[z]->getHeight()) / 2)
							 {
								 creature->setPositionX((*objects)[z]->getPositionX() + (creature->getWidth() + (*objects)[z]->getWidth()) / 2);
								// creature->setPositionY((*objects)[z]->getPositionY() - (creature->getHeight() + (*objects)[z]->getHeight()) / 2);
								// creature->onFloor = true;
							 }

				}
			}
		}

}

World::~World()
{
}
