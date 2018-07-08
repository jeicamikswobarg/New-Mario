#ifndef WORLD_H
#define WORLD_H
#include<SDL.h>
#include<vector>

class Mario;
class Object;
class World
{

	private:
		SDL_Surface *screen;
		SDL_Texture *scrtex;
		SDL_Renderer *renderer;
		int t1, t2, rc;
		double delta, worldTime, distance;
		char text[128];
		int black, green, red, blue;
		std::vector<Object *> *objects;
		void DrawSurface(SDL_Surface *sprite, int x, int y);
	public:
		static double diffTime;
		static const int FPS = 60;
		bool nextFrame;
		World(SDL_Renderer * renderer, SDL_Surface *screen, SDL_Texture *scrtex, std::vector<Object *> *objects);
		void draw();
		bool isNextFrame();
		void countTime();
		void update();
		~World();
};
	
#endif