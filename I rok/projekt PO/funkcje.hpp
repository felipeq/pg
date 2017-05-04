#ifndef funkcje_hpp
#define funkcje_hpp
#include"SDL.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <time.h>
void Blituj(SDL_Surface *source, SDL_Surface *dest, int dx, int dy)
{
	SDL_Rect Rdest;
	Rdest.x=dx;
	Rdest.y=dy;
	SDL_BlitSurface(source,NULL,dest,&Rdest);
}
#endif
