#ifndef klasy_hpp
#define klasy_hpp
#include"SDL.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "config.hpp"
#include <string>

using namespace std;
struct Simgsize
{
	int x;
	int y;
};
enum eKier
{
	lewo,
	prawo,
	dol,
	halt
};

class Objplayer
{
public:
	Objplayer();
struct Simgsize imgsize;
	SDL_Surface *surface;
	SDL_Rect pos;
	long double shift;
	double speed;
	double AnimFrameTime;
	int typ;
	int HP;
	int frame;
	eKier AnimKier;

	double AnimTime;
	void przesun(eKier kierunek, int dzielnikR, double delta)
	{
		switch ( kierunek )
		{
			case prawo: 
				{
					if (pos.x+ceil(150*delta*shift/dzielnikR)<WindowSizeX-GlobalMarginX-imgsize.x)
					pos.x=pos.x+ceil(150*delta*shift/dzielnikR); 	
				}	break;
			case lewo: 	
				{	if (pos.x-0.75*ceil(150*delta*shift/dzielnikR)>GlobalMarginX)
					pos.x=pos.x-0.75*ceil(150*delta*shift/dzielnikR); 
				}	break;
			case halt:
				pos.x=pos.x; break;
		}	
	}
};
Objplayer::Objplayer()
{
	AnimFrameTime=0.1/PlayerSpeed;
	frame=0;
	AnimTime=0;
	speed=2;
	HP=3;
	imgsize.y=90;
	AnimKier=halt;
	pos.y=WindowSizeY-imgsize.y-GlobalMarginY;
	pos.x=WindowSizeX/2;

}
Objplayer player;
class Objpocisk
{
	public:
	Objpocisk();
	SDL_Surface *surface;
	enum Etype
	{
		gracz,
		przeciwnik
	};
	double speed;
	struct Simgsize imgsize;
	std::vector<double> posX; // wspolrzedne X pociskow
	std::vector<double> posY; // wspolrzedne Y pociskow
	std::vector<Etype> typ; // osobny wektor stowrzyc
	double LastShotTime;
	Etype SelectedTyp;
	void dodaj(Etype typik, int bron, int x, int y)
	{
		if ( bron==0)
		{
			posX.push_back(x);
			posY.push_back(y);
			typ.push_back(przeciwnik);
		}
		if ( bron==1)
		{
			posX.push_back(x+11);
			posY.push_back(player.pos.y-5);
			typ.push_back(gracz);
		}
		if ( bron==2)
		{
			posX.push_back(x+46);
			posY.push_back(player.pos.y-5);
			typ.push_back(gracz);
		}
	}
	void usun(int i)
	{
		posY.erase(posY.begin()+i);
		posX.erase(posX.begin()+i);
		typ.erase(typ.begin()+i);
		
	}	
};
Objpocisk::Objpocisk()
{
	imgsize.x=15;
	imgsize.y=60;
	speed=predkoscstrzelania;
	SelectedTyp=gracz;	
}

class Objenemy
{
	public:
		struct Simgsize imgsize;
	SDL_Surface * surAlive;
	SDL_Surface * surDead;
	SDL_Rect pos;
	int health;
	int totalframe;
	std::vector<int> frame;
	std::vector<double>posx;
	std::vector<double>posy;
};
class Objform
{
	public:
	Objform();
	eKier kierunek;
	double posx;
	double posy;
	double shift;
	std::vector<int> enemy_id;
	std::vector<int> enemy_hp;
	double speed;
	double movingdown;
	void delete_enemy(int i)
	{
		enemy_id.erase(enemy_id.begin()+i);
		enemy_hp.erase(enemy_hp.begin()+i);
	}
};
Objform::Objform()
{
	posx=GlobalMarginX;
	posy=GlobalMarginY;
	kierunek=prawo;
	speed=predkoscformacji;
	movingdown=0;
}
class Objprzeszkoda
{
	public:
	std::vector<int> posx;
	std::vector<int> posy;
};
class Objtimer
{
	public:
	double zegarek;				// czas trwania czegos-tam
	bool koniec;				
	Objtimer();
	void odlicz(double delta)	// odejmowanie delty od zegarka, az koniec bedzie true
	{
		zegarek=zegarek-delta;
		if (zegarek<=0)
			koniec=true;
		if (zegarek>0)
			koniec=false;
	};

};
Objtimer::Objtimer()
{
	zegarek=0;
	koniec=false;
}
Objtimer Tlogo_start;
Objtimer Tbulletexp;
Objprzeszkoda corpse;
Objform formacja;
Objpocisk pocisk;
Objpocisk pociskenemy;
Objenemy enemy1;
Objenemy enemy2;
Objtimer Tlost;
Objtimer Tenemyshot;
			
void LoadClassGraph()
{
	enemy1.surAlive=SDL_LoadBMP("animacje/chlopR.bmp");
	enemy2.surAlive=SDL_LoadBMP("animacje/chlop2R.bmp");
	player.surface=SDL_LoadBMP("animacje/gracz/0.bmp");
	SDL_SetColorKey(enemy1.surAlive, SDL_SRCCOLORKEY, 0x929477);
	SDL_SetColorKey(enemy2.surAlive, SDL_SRCCOLORKEY, 0x929477);
	SDL_SetColorKey(player.surface, SDL_SRCCOLORKEY, 0x2a2626);

	enemy1.imgsize.x=75;
	enemy1.imgsize.y=75;
	enemy2.imgsize.x=75;
	enemy2.imgsize.y=75;
	player.imgsize.x=90;
	player.imgsize.y=90;


}

#endif
