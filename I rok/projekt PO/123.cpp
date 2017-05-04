// CHUUUUUUUUJ
extern "C" {
#include"SDL.h"
}
#include "sdl/include/SDL.h"
#define _USE_MATH_DEFINES
#include <math.h>
//#include <cstdlib> 
//#include <stdlib.h>
#include "config.hpp"
#include "funkcje.hpp"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <math.h>
#include <sstream>
	#if defined(WINDOWS) || defined(WIN32) || defined(_WIN32)
#include<windows.h>
#endif
Uint8 * keystate = SDL_GetKeyState( NULL );
/////////////////////////////////////////////////////
using namespace std;
////////////////////////////////PLAYER 1
const int p1_lewo=0;	//	a
const int p1_prawo=3;	//	d
const int p1_gora=22;	//	w
const int p1_dol=18;	//	s
const int p1_basic=-48; //	1
const int p1_ext=-47;	//	2
const int p1_ult=-46;	//	3
////////////////////////////////PLAYER 2
const int p2_lewo=7;	//	h
const int p2_prawo=10;	//	k
const int p2_gora=20;	//	u
const int p2_dol=9;		//	j
const int p2_basic=-47; //	1
const int p2_ext=-47;	//	2
const int p2_ult=-46;	//	30
////////////////////////////////PLAYER 3
const int p3_lewo=276-97;	//	strzałki
const int p3_prawo=275-97;	//	
const int p3_gora=273-97;	//	
const int p3_dol=274-97;	//	
const int p3_basic=-46; //	1
const int p3_ext=-47;	//	2
const int p3_ult=-46;	//	30
int p1_select;
int p2_select;
int p3_select;
bool p1_picked=false;
bool p2_picked=false;
bool p3_picked=false;
enum eAppState
{
	logo_start,
	menu,
	game,
	highscore,
	you_lost,
	you_won,
	next_level,
	champ_select,
	load
};
Mix_Chunk *sound = NULL;
int WysEkranu=640;
int SzerEkranu=480;
bool Loaded=false;
int punkty;
eAppState AppState;
SDL_Surface *SurEkran=NULL;
SDL_Surface *SurBg=NULL;
SDL_Surface *SurMenu;
SDL_Event zdarzenie;
TTF_Font *font;
bool ZmianaMuzyki=false;
int quit=0; 
double GlobalTime, WorldTime;
long double delta;
/////////////////////////////////////////////////////
enum eKlasa
{
	ironman,
	hulk,
	thor,
};

int poziom=0;
int currentfala=0;
int menu_pos=0;
////////klasy//////////klasy///////klasy////////////klasy///////
int cx=50;
int cy=50;


////Deklaracje klas///////////////
class gracz;
class wrog;
class postac;
class atak
{
	public:
	bool animowany; //True kiedy atak jest rysowany na planszy, false usunie sie  z wektora
	bool do_uzycia;
	virtual void uzyj(){};
	void sprawdz_gotowosc(double delta);
	int posx, posy;
	vector<int> wybierz_cel(int zasieg, vector<wrog>& cele);
	
	protected:
	int sila;
	int zasieg;  //Zero dla lasera i kuli Iron Man'a
	double czas_regeneracji;
	double ile_minelo;
	bool nowy;  //Pobranie pozycji kiedy na true
	SDL_Surface* wyglad;
};
class kula_Iron : public atak //bez szukania celu
{
	public:
	kula_Iron();
	kula_Iron(gracz&);
	~kula_Iron(){}; //Animacja wybuchu
	void uzyj();
	void sprawdz_trafienie();
	private:
	int numer_trafionego; // -1 kiedy zaden
};

class laser_Iron : public atak
{
	public:
	int czas_trwania;
	bool obrazenia;
	laser_Iron();
	laser_Iron(gracz& bohater);
	void uzyj();
};

class rakiety_Iron : public atak
{
	public:
	rakiety_Iron();
	rakiety_Iron(gracz& bohater);
	void uzyj();
	vector<int> cele; // vector numerów celów
	int* pozycjex;  //Pozycje poszczególnych rakiet
	int* pozycjey;
	bool* trafienie; //True jezeli trafiony
	int ilosc_trafien;
};

class postac
{
	public:
	int hp;
	double posx, posy;
	int speed;
	vector<int> wybierz_cel(int zasieg, vector<wrog>& cele);
};

class wrog : public postac
{
        public:
                int target_index;
                int targetX;
                int targetY;
                int typ;
                wrog(int chp, int cx, int cy,int cv, int ctyp)
                {hp=chp;posx=cx;posy=cy;typ=ctyp;normal_cd=2; atakuje=0; cd_start=GlobalTime, speed=10;
                };        
                ~wrog(){};
                int choose_target(int nr);        
                void akcja(int targetX,int targetY,int target_index,int i);
                void wyswietl_normal(int target_index);
        private:
				const static int sila=100;//sila normalnego ataku wroga;
				const static int zasieg=250;//zasieg ataku wroga typu 2
				double normal_cd;
				double cd_start;
				bool atakuje;
                void normal_atak(int i,int target_index);
                //void strzal(int target_index);
};

class gracz : public postac
{
	public:
	eKlasa klasa;
	int kierunek;
	int id;
	bool isMoving;
	int frame;
	double frame_time;
	kula_Iron atak_basic;
	gracz(int cid, int chp, int cx, int cy, int cv, eKlasa cclass)
	{
		frame_time=0.15;
		isMoving=false;
		frame=0;
		id=cid;
		hp=chp;
		posx=cx;
		posy=cy;
		speed=cv;
		klasa=cclass;
	}
	~gracz(){};
	void Przesun( int x )
	{
		isMoving=true;
		if (frame_time<=0) {frame++; if (frame>2) frame=1;frame_time=0.15;}
		switch (x)
		{
			case 0: posx-=(ceil)(speed*delta/3); break;
			case 1: posx+=(ceil)(speed*delta/3); break;
			case 2: posy-=(ceil)(speed*delta/3); break;
			case 3: posy+=(ceil)(speed*delta/3); break;
		}
	}
		void atakuj(int numer);
	
	void sprawdz_ataki(double delta);
};

struct fale
{
	int pot_slaby;
	int pot_sredni;
	int boss;
};
struct poziom
{
	string tlo;
	double delay;
	fale Fale[2];
};
enum Eatak
{
	melee,
	range,
	aoe,
	aura
};
vector<wrog> vEnemy;
vector<gracz> vPlayer;
vector<kula_Iron> vAttack;
struct poziom level1;
//Obiekty klas uzywane do sprawdzania czy mozna uzyc ataku/////////////
kula_Iron Gkula_Iron; 
laser_Iron Glaser_Iron;
rakiety_Iron Grakiety_Iron;
////KOD//////////////KOD//////////////KOD////////////////KOD//////////
void Blituj(SDL_Surface *source, SDL_Surface *dest, int dx, int dy)
{
	SDL_Rect Rdest;
	Rdest.x=dx;
	Rdest.y=dy;
	SDL_BlitSurface(source,NULL,dest,&Rdest);
}
void Napisuj(char* napis,int x, int y)
{
		font=TTF_OpenFont("czcionki/menu.ttf", 50);
		SDL_Surface * text1;
		SDL_Color kolor;
		kolor.r=255;
		kolor.g=255;
		kolor.b=255;
		text1 = TTF_RenderText_Solid(font, napis, kolor);
		Blituj(text1,SurBg,x,y);
		TTF_CloseFont(font);
		SDL_FreeSurface(text1);
}

void Muzyka(int a, int gdzie, int ile)
{
		int channel;
		if (a==0)
		sound = Mix_LoadWAV("muzyka/menu_theme.wav");
		if (a==1)
		sound = Mix_LoadWAV("muzyka/gametheme.wav");
		if (a==2)
		sound = Mix_LoadWAV("muzyka/finalboss.wav");
		if (a==3)
		sound = Mix_LoadWAV("muzyka/hulk0.wav");
		channel = Mix_PlayChannel(gdzie, sound, ile);
		ZmianaMuzyki=false;		
}
char* DoubleToChar(double way)
{
		std::stringstream str;
		str << way << std::ends;
		std::string result = str.str();
		char* penis=new char[result.length()]; // <--------------------------------
		for ( int w=0;w<result.length();w++)
		penis[w]=result[w];
		return penis; // WYCIEEEEEEEEEEEEEEEEEEK
}
void Move()
{
	if (vEnemy.size()>0)
	for ( int i=0;i<vEnemy.size();i++)
	{
		vEnemy[i].target_index=vEnemy[i].choose_target(i);
		vEnemy[i].akcja(vEnemy[i].targetX,vEnemy[i].targetY,vEnemy[i].target_index,i);
	}
	for ( int i=0;i<vPlayer.size();i++)
	{
		vPlayer[i].frame_time-=delta;
		if (vPlayer[i].id==1)
		{	
			if( keystate[ SDLK_a+p1_lewo])	{ vPlayer[i].Przesun(0); }
			if( keystate[ SDLK_a+p1_prawo])	{ vPlayer[i].Przesun(1); }		// praw
			if( keystate[ SDLK_a+p1_gora])	{ vPlayer[i].Przesun(2); } 		// gora
			if( keystate[ SDLK_a+p1_dol])	{ vPlayer[i].Przesun(3); }	
			if( keystate[ SDLK_a+p1_basic])  vPlayer[i].atakuj(1);												// dol
		}
		if (vPlayer[i].id==2)
		{
			if( keystate[ SDLK_a+p2_lewo])	vPlayer[i].Przesun(0);
			if( keystate[ SDLK_a+p2_prawo])	vPlayer[i].Przesun(1);		// praw
			if( keystate[ SDLK_a+p2_gora])	vPlayer[i].Przesun(2); 		// gora
			if( keystate[ SDLK_a+p2_dol])	vPlayer[i].Przesun(3);		// dol
		}
		if (vPlayer[i].id==3)
		{
			if( keystate[ SDLK_a+p3_lewo])	vPlayer[i].Przesun(0);
			if( keystate[ SDLK_a+p3_prawo])	vPlayer[i].Przesun(1);		// praw
			if( keystate[ SDLK_a+p3_gora])	vPlayer[i].Przesun(2); 		// gora
			if( keystate[ SDLK_a+p3_dol])	vPlayer[i].Przesun(3);		// dol
		}
		if (vPlayer[i].isMoving==false) vPlayer[i].frame=0;		
			vPlayer[i].isMoving=false;	
	}
};
void Collision()
{
	if (vEnemy.size()==0 && Loaded==false)
	{
		if (currentfala<2)
		currentfala++;
		Loaded=true;
	}
};
void Attack()
{
	while( SDL_PollEvent( & zdarzenie ) )
			{
				if( zdarzenie.type == SDL_QUIT ) quit = true;
				if( zdarzenie.type == SDL_KEYDOWN )
				{
					switch( zdarzenie.key.keysym.sym )
					{
						case SDLK_a+p1_basic:
						vPlayer[0].atakuj(1);
						break;
						
						case SDLK_a+p1_ext:
						vPlayer[0].atakuj(2);
						break;
						
						case SDLK_a+p1_ult:
						vPlayer[0].atakuj(3);
						break;
					}
				}
			}
	
	for(int i = 0; i < vPlayer.size(); i++)
	{
		vPlayer[i].sprawdz_ataki(delta);
	}
	for(int i = 0; i < vAttack.size(); i++)
	{
		if(!vAttack[i]->animowany || vAttack[i]->posx > 600)
		{
			delete vAttack[i];
			vAttack.erase(vAttack.begin() + i);
		}
		if(vAttack.empty())
			break;
			
		vAttack[i]->uzyj();
	}
}
void ShowInterface()
{
	SDL_Surface *temp;
	temp=SDL_LoadBMP("new_interface/bot.bmp");
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0xFFFFFF);
	Blituj(temp,SurBg,0,415);
	SDL_FreeSurface(temp);
	for ( int i=0;i<vPlayer.size();i++)
	{
		temp=SDL_LoadBMP("new_interface/ironman_off.bmp");
			SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0xFFFFFF);
			Blituj(temp,SurBg,13,425);
			SDL_FreeSurface(temp);
			temp=SDL_LoadBMP("new_interface/hulk_off.bmp");
			SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0xFFFFFF);
			Blituj(temp,SurBg,220,425);
			SDL_FreeSurface(temp);
			temp=SDL_LoadBMP("new_interface/thor_off.bmp");
			SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0xFFFFFF);
			Blituj(temp,SurBg,440,425);
			SDL_FreeSurface(temp);
	}
}
void State_game()
{
	SurBg=SDL_LoadBMP("v/bg.bmp");
	Attack();
	Collision();
	Move();
	SDL_Surface *SurE;
	if (Loaded==true)
	{	
		for ( int ii=0;ii<level1.Fale[currentfala].pot_slaby;ii++)
		{
			wrog temp(1,500+15*ii,20+70*ii,10,1);
			vEnemy.push_back(temp);
		}
		for ( int ii=0;ii<level1.Fale[currentfala].pot_sredni;ii++)
		{
			wrog temp(1,400,20+70*ii,1,2);
			vEnemy.push_back(temp);
		}
		Loaded=false;
	}
	if (vEnemy.size()==0)
		{ Loaded=true; currentfala=0; vPlayer.clear();AppState=menu; return; }
	else	
	for ( int i=0;i<vEnemy.size();i++)
	{
		if (vEnemy[i].typ==1)
			SurE=SDL_LoadBMP("v/enemy1.bmp");
		if (vEnemy[i].typ==2)
			SurE=SDL_LoadBMP("v/enemy2.bmp");
		SDL_SetColorKey(SurE, SDL_SRCCOLORKEY, 0xFFFFFF);
		Blituj(SurE,SurBg,vEnemy[i].posx,vEnemy[i].posy);	
		SDL_FreeSurface(SurE);	
	}
	for ( int i=0;i<vPlayer.size();i++)
	{
		if (vPlayer[i].klasa==ironman)
			SurE=SDL_LoadBMP("v/ironman.bmp");
		if (vPlayer[i].klasa==hulk)
		{
			if (vPlayer[i].frame==0)
				SurE=SDL_LoadBMP("v/hulk/ruch/0.bmp");
			if (vPlayer[i].frame==1)
				SurE=SDL_LoadBMP("v/hulk/ruch/1.bmp");
			if (vPlayer[i].frame==2)
				SurE=SDL_LoadBMP("v/hulk/ruch/2.bmp");	
		}
		if (vPlayer[i].klasa==thor)
			SurE=SDL_LoadBMP("v/thor.bmp");
		SDL_SetColorKey(SurE, SDL_SRCCOLORKEY, 0xFFFFFF);
		Blituj(SurE,SurBg,vPlayer[i].posx,vPlayer[i].posy);
		SDL_FreeSurface(SurE);
	}
	while( SDL_PollEvent( & zdarzenie ) )
		if( zdarzenie.type == SDL_QUIT ) quit = true;
	ShowInterface();
	Blituj(SurBg,SurEkran,0,0);
	SDL_FreeSurface(SurBg);
	Loaded=false;
};

void DodajPlayera( int ID, int champ)
{
	eKlasa temp;
	if (champ==1) temp=ironman;
	if (champ==2) temp=hulk;
	if (champ==3) temp=thor;
	vPlayer.push_back(gracz(ID,100,20,250,300,temp));
}
void State_champ_select()
{
	SurMenu=SDL_LoadBMP("v/bg_select2.bmp");
	SDL_Surface *temp;
	while( SDL_PollEvent( & zdarzenie ) )
	{
		if( zdarzenie.type == SDL_QUIT ) quit = true;
		if( zdarzenie.type == SDL_KEYDOWN )
			{
				switch( zdarzenie.key.keysym.sym )
				{
					case SDLK_ESCAPE:	quit=true;	break;
					case SDLK_a+p1_prawo:	if (p1_select<3 && p1_picked==false)	p1_select++; break;
					case SDLK_a+p1_lewo:	if (p1_select>0 && p1_picked==false)	p1_select--; break;
					case SDLK_a+p2_prawo:	if (p2_select<3 && p2_picked==false)	p2_select++; break;
					case SDLK_a+p2_lewo:	if (p2_select>0 && p2_picked==false) 	p2_select--; break;
					case SDLK_a+p3_prawo:	if (p3_select<3 && p3_picked==false)	p3_select++; break;
					case SDLK_a+p3_lewo:	if (p3_select>0 && p3_picked==false) 	p3_select--; break;
					case SDLK_a+p1_basic:	
					{
						if (p1_picked==false && p1_select>0)
						{
							p1_picked=true;	
							DodajPlayera(1,p1_select);
						}
					}; break;
					case SDLK_a+p2_basic:	
					{
						if (p2_picked==false && p2_select>0)
						{
							p2_picked=true;
							DodajPlayera(2,p2_select);
						}
					}; break;
					case SDLK_a+p3_basic:	
					{
						if (p3_picked==false && p3_select>0)
						{
							p3_picked=true;
							DodajPlayera(3,p3_select);
						}
					}; break;
					
					case SDLK_RETURN:	AppState=load; break;
				}
			}
	}
	for ( int i=0;i<3;i++)
	{
		if (i==0)
			temp=SDL_LoadBMP("v/player1_pasive.bmp");
		if (i==1)
			temp=SDL_LoadBMP("v/player2_pasive.bmp");
		if (i==2)
			temp=SDL_LoadBMP("v/player3_pasive.bmp");
		SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0x000000);
		Blituj(temp,SurMenu,70,250+i*75);
		SDL_FreeSurface(temp);
		temp=SDL_LoadBMP("v/ironman_passive.bmp");
		Blituj(temp,SurMenu,260,230+i*80);
		SDL_FreeSurface(temp);
		temp=SDL_LoadBMP("v/hulk_passive.bmp");
		Blituj(temp,SurMenu,370,230+i*80);
		SDL_FreeSurface(temp);
		temp=SDL_LoadBMP("v/thor_passive.bmp");
		Blituj(temp,SurMenu,480,230+i*80);
		SDL_FreeSurface(temp);
	}
	if (p1_select>0)
	{
		int i=0;
		temp=SDL_LoadBMP("v/player1_active.bmp");
		SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0x000000);
		Blituj(temp,SurMenu,70,250+i*75);
		SDL_FreeSurface(temp);
		if (p1_select==1)
		{
			temp=SDL_LoadBMP("v/ramka.bmp");
			if (p1_picked==true)
				temp=SDL_LoadBMP("v/ramkalock.bmp");
			Blituj(temp,SurMenu,255,225+i*80);
			SDL_FreeSurface(temp);
			temp=SDL_LoadBMP("v/ironman_active.bmp");
			Blituj(temp,SurMenu,260,230+i*80);
			SDL_FreeSurface(temp);
			
		}
		if (p1_select==2)
		{
			temp=SDL_LoadBMP("v/ramka.bmp");
						if (p1_picked==true)
				temp=SDL_LoadBMP("v/ramkalock.bmp");
			Blituj(temp,SurMenu,365,225+i*80);
			SDL_FreeSurface(temp);
			temp=SDL_LoadBMP("v/hulk_active.bmp");
			Blituj(temp,SurMenu,370,230+i*80);
			SDL_FreeSurface(temp);
		}
		if (p1_select>=3)
		{
			temp=SDL_LoadBMP("v/ramka.bmp");
						if (p1_picked==true)
				temp=SDL_LoadBMP("v/ramkalock.bmp");
			Blituj(temp,SurMenu,475,225+i*80);
			SDL_FreeSurface(temp);
			temp=SDL_LoadBMP("v/thor_active.bmp");
			Blituj(temp,SurMenu,480,230+i*80);
			SDL_FreeSurface(temp);
		}
	}
	if (p2_select>0)
	{
		int i=1;
		temp=SDL_LoadBMP("v/player2_active.bmp");
		SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0x000000);
		Blituj(temp,SurMenu,70,250+i*75);
		SDL_FreeSurface(temp);
		if (p2_select==1)
		{
			temp=SDL_LoadBMP("v/ramka.bmp");
						if (p2_picked==true)
				temp=SDL_LoadBMP("v/ramkalock.bmp");
			Blituj(temp,SurMenu,255,225+i*80);
			SDL_FreeSurface(temp);
			temp=SDL_LoadBMP("v/ironman_active.bmp");
			Blituj(temp,SurMenu,260,230+i*80);
			SDL_FreeSurface(temp);
			
		}
		if (p2_select==2)
		{
			temp=SDL_LoadBMP("v/ramka.bmp");
									if (p2_picked==true)
				temp=SDL_LoadBMP("v/ramkalock.bmp");
			Blituj(temp,SurMenu,365,225+i*80);
			SDL_FreeSurface(temp);
			temp=SDL_LoadBMP("v/hulk_active.bmp");
			Blituj(temp,SurMenu,370,230+i*80);
			SDL_FreeSurface(temp);
		}
		if (p2_select>=3)
		{
			temp=SDL_LoadBMP("v/ramka.bmp");
									if (p2_picked==true)
				temp=SDL_LoadBMP("v/ramkalock.bmp");
			Blituj(temp,SurMenu,475,225+i*80);
			SDL_FreeSurface(temp);
			temp=SDL_LoadBMP("v/thor_active.bmp");
			Blituj(temp,SurMenu,480,230+i*80);
			SDL_FreeSurface(temp);
		}
	}
	if (p3_select>0)
	{
		int i=2;
		temp=SDL_LoadBMP("v/player3_active.bmp");
		SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0x000000);
		Blituj(temp,SurMenu,70,250+i*75);
		SDL_FreeSurface(temp);
		if (p3_select==1)
		{
			temp=SDL_LoadBMP("v/ramka.bmp");
									if (p3_picked==true)
				temp=SDL_LoadBMP("v/ramkalock.bmp");
			Blituj(temp,SurMenu,255,225+i*80);
			SDL_FreeSurface(temp);
			temp=SDL_LoadBMP("v/ironman_active.bmp");
			Blituj(temp,SurMenu,260,230+i*80);
			SDL_FreeSurface(temp);
			
		}
		if (p3_select==2)
		{
			temp=SDL_LoadBMP("v/ramka.bmp");
										if (p3_picked==true)
				temp=SDL_LoadBMP("v/ramkalock.bmp");
			Blituj(temp,SurMenu,365,225+i*80);
			SDL_FreeSurface(temp);
			temp=SDL_LoadBMP("v/hulk_active.bmp");
			Blituj(temp,SurMenu,370,230+i*80);
			SDL_FreeSurface(temp);
		}
		if (p3_select>=3)
		{
			temp=SDL_LoadBMP("v/ramka.bmp");
										if (p3_picked==true)
				temp=SDL_LoadBMP("v/ramkalock.bmp");
			Blituj(temp,SurMenu,475,225+i*80);
			SDL_FreeSurface(temp);
			temp=SDL_LoadBMP("v/thor_active.bmp");
			Blituj(temp,SurMenu,480,230+i*80);
			SDL_FreeSurface(temp);
		}
	}
	Blituj(SurMenu,SurEkran,0,0);
	SDL_FreeSurface(SurMenu);
}
void State_logo_start()
{
	SDL_Surface *temp=SDL_LoadBMP("v/bg_menu2.bmp");
	Blituj(temp,SurEkran,0,0);
	SDL_FreeSurface(temp);
	while( SDL_PollEvent( & zdarzenie ) )
	{
		if( zdarzenie.type == SDL_QUIT ) quit = true;
		if( zdarzenie.type == SDL_KEYDOWN )
			{
				switch( zdarzenie.key.keysym.sym )
				{
					case SDLK_RETURN:	AppState=champ_select;	break;
				}
			}
	}
};

void State_load()
{
	Loaded=true;
	Muzyka(1,0,-1);
	AppState=game;
};
#if defined(WINDOWS) || defined(WIN32) || defined(_WIN32)
int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR str, int show) {
#else
int main(int argc, const char **argv) 
{
#endif
	// -------------------------------------INICJACJA--------------------------------------
	level1.tlo="v/bg.bmp";
	level1.Fale[0].pot_slaby=5;
	level1.Fale[0].pot_sredni=2;
	level1.Fale[0].boss=0;
	level1.Fale[1].pot_slaby=7;
	level1.Fale[1].pot_sredni=4;
	level1.Fale[1].boss=0;
	SDL_Init( SDL_INIT_EVERYTHING );
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024);
	TTF_Init();
	AppState=logo_start;
    SurEkran=SDL_SetVideoMode( WysEkranu,SzerEkranu, 32, SDL_SWSURFACE );
	SDL_WM_SetCaption( "Chuj", NULL );
	GlobalTime=SDL_GetTicks();
	Muzyka(0,0,-1);
	while(!quit)
	{
				
		double TempTime=SDL_GetTicks();
		delta=(TempTime-GlobalTime)*0.001; // czas uplyniety od ostatniego rysowania ekranu
		GlobalTime=TempTime;
		WorldTime+=delta;
		switch (AppState)
		{
			case logo_start:	State_logo_start(); break;
			case champ_select:	State_champ_select();break;
	//		case you_won:		State_you_won();	break;
	//		case you_lost:		State_you_lost();	break;
	//		case next_level:	State_next_level(); break;
			case game:			State_game();		break;
			case load:			State_load();		break;
		}

		SDL_Flip(SurEkran);
	};
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////
int wrog::choose_target(int nr)//zwraca indeks gracza(celu) w vektorze
{
		int way=900000;
		int i=nr;
		int p_index;
		for ( int q=0;q<vPlayer.size();q++)
		{
			if (way>(fabs(vPlayer[q].posx-vEnemy[i].posx)+fabs(vPlayer[q].posy-vEnemy[i].posy)))
			{
				vEnemy[i].targetX=vPlayer[q].posx;
				vEnemy[i].targetY=vPlayer[q].posy;
				vEnemy[i].target_index=q;
				way=(fabs(vPlayer[q].posx-vEnemy[i].posx)+fabs(vPlayer[q].posy-vEnemy[i].posy));
				p_index=q;
			}
		}
		return p_index;
}
////////////////////////////////kolizje przeciwnikow///////////////////////////////////////////
void wrog::akcja(int targetX,int targetY,int target_index,int i)//target index potrzerbne do odejmowania hp graczowi po ataku
{
	struct allowed
	{
		int l,p,g,d;
	};
	struct allowed check;
	check.l=check.p=check.g=check.d=0;
	//////////////////////////////////////typ 1///////////////////////////////////////////////////
	if(vEnemy[i].typ==1)
	{
		if(check.p==0 && vEnemy[i].posx<vEnemy[i].targetX) vEnemy[i].posx+=ceil(vEnemy[i].speed*delta);
		if(check.l==0 && vEnemy[i].posx>vEnemy[i].targetX) vEnemy[i].posx-=ceil(vEnemy[i].speed*delta);
		if(check.d==0 && vEnemy[i].posy<vEnemy[i].targetY) vEnemy[i].posy+=ceil(vEnemy[i].speed*delta);
		if(check.g==0 && vEnemy[i].posy>vEnemy[i].targetY) vEnemy[i].posy-=ceil(vEnemy[i].speed*delta);	
		if(vEnemy[i].posx>vEnemy[i].targetX-10 && vEnemy[i].posy>vEnemy[i].targetY-10 && vEnemy[i].posx<vEnemy[i].targetX+15 && vEnemy[i].posx>vEnemy[i].targetX-10)
		{
			normal_atak(i,vEnemy[i].target_index);
		}
	}
	if(vEnemy[i].typ==2)
	{
		if(sqrt(pow((double)(vEnemy[i].posy-vPlayer[target_index].posy),2)+pow((double)(vEnemy[i].posy-vPlayer[target_index].posy),2))>zasieg)
		{
			if(check.l==0 && vEnemy[i].posx>vEnemy[i].targetX) vEnemy[i].posx-=ceil(vEnemy[i].speed*delta);
			if(check.p==0 && vEnemy[i].posx<vEnemy[i].targetX) vEnemy[i].posx+=ceil(vEnemy[i].speed*delta);
			if(check.g==0 && vEnemy[i].posy>vEnemy[i].targetY) vEnemy[i].posy-=ceil(vEnemy[i].speed*delta);
			if(check.d==0 && vEnemy[i].posy<vEnemy[i].targetY) vEnemy[i].posy+=ceil(vEnemy[i].speed*delta);
		}
		if(sqrt(pow((double)(vEnemy[i].posy-vPlayer[target_index].posy),2)+pow((double)(vEnemy[i].posy-vPlayer[target_index].posy),2))<zasieg)
		{
			if(check.p==0 && vEnemy[i].posx>vEnemy[i].targetX) vEnemy[i].posx+=ceil(vEnemy[i].speed*delta);
			if(check.l==0 && vEnemy[i].posx<vEnemy[i].targetX) vEnemy[i].posx-=ceil(vEnemy[i].speed*delta);
			if(check.d==0 && vEnemy[i].posy>vEnemy[i].targetY) vEnemy[i].posy+=ceil(vEnemy[i].speed*delta);
			if(check.g==0 && vEnemy[i].posy<vEnemy[i].targetY) vEnemy[i].posy-=ceil(vEnemy[i].speed*delta);
		}
		if(sqrt(pow((double)(vEnemy[i].posy-vPlayer[target_index].posy),2)+pow((double)(vEnemy[i].posy-vPlayer[target_index].posy),2))<zasieg+10)
		{
			//strzal do target
		}
	}
}
////Atak funkcje/////////////////
void atak::sprawdz_gotowosc(double delta)
{
	ile_minelo += delta;
	if(ile_minelo >= czas_regeneracji)
	{
		ile_minelo = 0;
		do_uzycia = true;
	}
}
////kula_Iron funkcje///////////////////////
kula_Iron::kula_Iron()
{
	posx = 0;
	posy = 0;
	sila = 20;
	zasieg = 0;
	animowany = true;
	do_uzycia = true;
	czas_regeneracji = 1.5;
	ile_minelo = 0;
	numer_trafionego = -1;
	wyglad = SDL_LoadBMP("kula_iron.bmp");
}

kula_Iron::kula_Iron(gracz& bohater)
{
	posx = bohater.posx;
	posy = bohater.posy;
	sila = 20;
	zasieg = 0;
	animowany = true;
	do_uzycia = false;
	czas_regeneracji = 1.5;
	ile_minelo = 0;
	numer_trafionego = -1;
	wyglad = SDL_LoadBMP("kula_iron.bmp");
}
	
	

void kula_Iron::uzyj()
{
	sprawdz_trafienie();
	if(numer_trafionego != -1)
	{
		vEnemy[numer_trafionego].hp -= sila;
		animowany = false;
	}
	posx += 1;
	Blituj(wyglad,SurBg,posx,posy);
}

void kula_Iron::sprawdz_trafienie()
{
	double odleglosc;
	for(int i = 0; i < vEnemy.size(); i++)
	{
		odleglosc = sqrt(pow(posx - vEnemy[i].posx,double(2)) + pow(posy - vEnemy[i].posy,double(2)));
		if(odleglosc == 0)
		{
			numer_trafionego = i;
			break;
		}
	}
}

////laser_Iron funkcje///////////////////////////////////
laser_Iron::laser_Iron()
{
	posx = 0;
	posy = 0;
	sila = 20;
	czas_regeneracji  = 2;
	do_uzycia = true;
	ile_minelo = 0;
	animowany = true;
	wyglad = SDL_LoadBMP("laser_Iron.bmp");
}

laser_Iron::laser_Iron(gracz& bohater)
{
	posx = bohater.posx;
	posy = bohater.posy;
	sila = 20;
	czas_regeneracji  = 2;
	do_uzycia = true;
	ile_minelo = 0;
	animowany = true;
	czas_trwania = 1;
	wyglad = SDL_LoadBMP("laser_Iron.bmp");;
}

void laser_Iron::uzyj()
{
	if(obrazenia)
	{
		for(int i = 0; i < vEnemy.size(); i++)
		{
			if(vEnemy[i].posx == posx)
				vEnemy[i].hp -= sila;
		}
		obrazenia = false;
	}
	Blituj(wyglad,SurBg,posx,posy);
	ile_minelo += delta;
	if(ile_minelo >= czas_trwania)
	{
		ile_minelo = 0;
		animowany = false;
	}
}
	
////rakiety_Iron funkcje//////////////////////////
rakiety_Iron::rakiety_Iron()
{
	sila = 30;
	czas_regeneracji  = 2;
	do_uzycia = true;
	ile_minelo = 0;
	animowany = true;
	wyglad = SDL_LoadBMP("laser_Iron.bmp");
}

rakiety_Iron::rakiety_Iron(gracz& bohater)
{
	cele = bohater.wybierz_cel(zasieg,vEnemy);
	pozycjex = new int[cele.size()];
	pozycjey = new int[cele.size()];
	trafienie  = new bool[cele.size()];
	for(int i = 0; i < cele.size(); i++)
	{
		pozycjex[i] = bohater.posx;
		pozycjey[i] = bohater.posy;
		trafienie[i] = false;
	}
	int ilosc_trafien = 0;
	sila = 30;
	wyglad = SDL_LoadBMP("rakiety_Iron.bmp");
}

void rakiety_Iron::uzyj()
{
	if(animowany)
	{
		for(int i = 0; i < cele.size();i++)
		{
			if(!trafienie[i])
			{
				if(pozycjex[i] < vEnemy[i].posx) pozycjex[i]++;
				if(pozycjex[i] > vEnemy[i].posx) pozycjex[i]--;
				if(pozycjey[i] < vEnemy[i].posy) pozycjey[i]++;
				if(pozycjey[i] > vEnemy[i].posy) pozycjey[i]--;
				Blituj(wyglad,SurBg,pozycjex[i],pozycjey[i]);
			}
			if(pozycjex[i] == vEnemy[i].posx && pozycjey[i] == vEnemy[i].posy)
			{
				trafienie[i] = true;
				ilosc_trafien++;
			}
		}
	}
	if(ilosc_trafien == (cele.size()-1))
		animowany = false;
	
}
	
//Gracz Funkcje/////////////////////////////////////////
void gracz::atakuj(int numer)
{
	switch(id)
	{
		case 1:
		if(numer == 1)
		if(Gkula_Iron.do_uzycia)
		{
			vAttack.push_back(new kula_Iron(*this));
			Gkula_Iron.do_uzycia = false;
		}
		if(numer == 2)
		if(Glaser_Iron.do_uzycia)
		{
			vAttack.push_back(new laser_Iron(*this));
			Glaser_Iron.do_uzycia = false;
		}
		if(numer == 3)
		if(Grakiety_Iron.do_uzycia)
		{
			vAttack.push_back(new rakiety_Iron(*this));
			Grakiety_Iron.do_uzycia = false;
		}
		break;
	}
}

void gracz::sprawdz_ataki(double delta)
{
	if(id == 1)
	{
		if(!Gkula_Iron.do_uzycia)
			Gkula_Iron.sprawdz_gotowosc(delta);
			
		if(!Glaser_Iron.do_uzycia)
			Glaser_Iron.sprawdz_gotowosc(delta);
		
		if(!Grakiety_Iron.do_uzycia)
			Grakiety_Iron.sprawdz_gotowosc(delta);
	}
}
void wrog::normal_atak(int i,int target_index)
{
        if(atakuje==0)
        {
                vPlayer[target_index].hp-=vEnemy[i].sila;
                vEnemy[i].cd_start=GlobalTime;
                atakuje=1;
        }
        if(GlobalTime-vEnemy[i].cd_start>vEnemy[i].normal_cd) atakuje=0;
        if(GlobalTime-vEnemy[i].cd_start<0.15) wyswietl_normal(target_index);
}
void wrog::wyswietl_normal(int target_index)
{
                SDL_Surface *temp;
                temp=SDL_LoadBMP("v/2_hit.bmp");
                SDL_SetColorKey(temp, SDL_SRCCOLORKEY, 0x000000);
                Blituj(temp,SurBg,vEnemy[target_index].posx+20,vEnemy[target_index].posy+25);
                SDL_FreeSurface(temp);
}
