#ifndef funkcje_hpp
#define funkcje_hpp
#include"SDL.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "klasy.hpp"
#include <time.h>
bool ustaw_pixel(Uint32 pixel, SDL_Surface *surface, int Pixel_X, int Pixel_Y)
{ 
    if ( SDL_MUSTLOCK(surface) )
    {
        if ( SDL_LockSurface(surface) < 0 )
        {
            return false;
        }
    }
 
    Uint32 *pixele= (Uint32 *)surface->pixels; 
    pixele [ ( Pixel_Y * surface->w ) + Pixel_X ] = pixel; 
 
    if ( SDL_MUSTLOCK(surface) )
    {
        SDL_UnlockSurface(surface);
    }
 
    return true;
}
void FiltrEkranu(SDL_Surface* surface)
{
	SDL_LockSurface(surface);

	SDL_UnlockSurface(surface);

}
void RandomStartFrame( int tempform[6][6])
{
	srand ( time(NULL) );
	for ( int i=0;i<6;i++)
	{
		for ( int ii=0;ii<6;ii++)
		{
			formacja.enemy_id.push_back(tempform[ii][i]);
			switch ( tempform[ii][i] )
			{
				case 0:
				{
					formacja.enemy_hp.push_back(0);
				}
				case 1:
				{
					formacja.enemy_hp.push_back(enemy1.health); 
					enemy1.frame.push_back(1+rand()%enemy2.totalframe);
				}	break;
				case 2: 
				{
					formacja.enemy_hp.push_back(enemy2.health); 
					enemy2.frame.push_back(1+rand()%enemy2.totalframe);
				}	break;
			}
			
		}
	}
}
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset) 
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
		};
};
void Blituj(SDL_Surface *source, SDL_Surface *dest, int dx, int dy)
{
	SDL_Rect Rdest;
	Rdest.x=dx;
	Rdest.y=dy;
	SDL_BlitSurface(source,NULL,dest,&Rdest);
}

bool CheckFile (const string& nazwa)
{
        fstream plik;
        plik.open(nazwa.c_str(), ios::in);
        if ( plik.is_open() )
        {
            plik.close();
            return true;
        }
        plik.close();
        return false;
}
void LoadFormation(char *source)
{
	int tab[6][6];
	if ( CheckFile(source)==true )
{
	ifstream in;
	in.exceptions ( ifstream::failbit | ifstream::badbit );
		try 
		{
   			in.open(source);
			
				for ( int y=0;y<6;y++)
				{
					for ( int x=0;x<6;x++)
					{	
						in >> tab[x][y];
					}
				} 
		}
	catch (ifstream::failure e) { }
		in.close();
		   }   
	RandomStartFrame(tab);
}
#endif
