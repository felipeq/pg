#ifndef klasy_hpp
#define klasy_hpp
#include "SDL/SDL.h"
#include <vector>
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
	void przesun(eKier kierunek, int dzielnikR, double delta);
	
};


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
	void dodaj(Etype typik, int bron, int x, int y);
	void usun(int i);		
};


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
	void delete_enemy(int i);
};
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
	void odlicz(double delta);	// odejmowanie delty od zegarka, az koniec bedzie true
};

extern Objtimer Tlogo_start;
extern Objtimer Tbulletexp;
extern Objprzeszkoda corpse;
extern Objform formacja;
extern Objpocisk pocisk;
extern Objpocisk pociskenemy;
extern Objenemy enemy1;
extern Objenemy enemy2;
extern Objtimer Tlost;
extern Objtimer Tenemyshot;
extern Objplayer player;
			
#endif
