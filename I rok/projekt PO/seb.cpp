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
#include <vector>
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
int WysEkranu=640;
int SzerEkranu=480;
bool Loaded=false;
int punkty;
eAppState AppState;
SDL_Surface *SurEkran=NULL;
SDL_Surface *SurBg=NULL;
SDL_Surface *SurMenu;
SDL_Event zdarzenie;
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

class postac
{
	public:
	int hp;
	int posx, posy;
	int speed;
};

class wrog : public postac
{
	public:
		int target_index;
		int targetX;
		int targetY;
		int dx,dy; // <-- docelowe do omijania fagasow
		int typ;
		wrog(int chp, int cx, int cy, int cv, int ctyp)
		{hp=chp;posx=cx;posy=cy;speed=cv;typ=ctyp;dx=dy=-1;
		};	
		~wrog(){};
		int choose_target(int nr);	
		void akcja(int targetX,int targetY,int target_index,int i);
	private:
		//void find_target(vector<wrog> przeciwnicy, vector<gracz> gracze,int i);
		//void atak();	
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
vector<atak*> vAttack;
struct poziom level1;
////KOD//////////////KOD//////////////KOD////////////////KOD//////////
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
			if( keystate[ SDLK_a+p1_dol])	{ vPlayer[i].Przesun(3); }		// dol
			if( keystate[ SDLK_a+p1_basic]) { vPlayer[i].atakuj(1);}
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
	vector<int> do_usuniecia;
	while( SDL_PollEvent( & zdarzenie ) )
			{
				if( zdarzenie.type == SDL_QUIT ) quit = true;
				if( zdarzenie.type == SDL_KEYDOWN )
				{
					switch( zdarzenie.key.keysym.sym )
					{
						case SDLK_a+p1_basic: vAttack.push_back(new kula_Iron(vPlayer[0]));
						break;
					}
				}
			}
	for(int i = 0; i < vAttack.size(); i++)
	{
		if(!vAttack[i]->animowany || vAttack[i]->posx > 600)
		{
			do_usuniecia.push_back(i);
		}
		if(!vAttack.empty())
			vAttack[i]->uzyj();
	}
	for(int i = 0; i < do_usuniecia.size(); i++)
	{
		delete vAttack[i];
		vAttack.erase(vAttack.begin() + do_usuniecia[i]);
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
	Collision();
	Move();
	Attack();
	SDL_Surface *SurE;
	if (Loaded==true)
	{	
		for ( int ii=0;ii<level1.Fale[currentfala].pot_slaby;ii++)
		{
			wrog temp(1,500+15*ii,20+70*ii,1,1);
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
void State_menu()
{
	AppState=logo_start;
	return;
	Loaded=true;
	SurMenu=SDL_LoadBMP("v/bg_menu.bmp");
	//SDL_FillRect(SurMenu, NULL, 0xFFFFFF);
	while( SDL_PollEvent( & zdarzenie ) )
	{
		if( zdarzenie.type == SDL_QUIT ) quit = true;
		if( zdarzenie.type == SDL_KEYDOWN )
			{
				switch( zdarzenie.key.keysym.sym )
				{
				case SDLK_ESCAPE:	quit=true;	break;
				case SDLK_DOWN:		menu_pos++; break;
				case SDLK_UP:		menu_pos--; break;
				case SDLK_a:		menu_pos--; break;
				case SDLK_a+1:		menu_pos++; break;
				case SDLK_RETURN:	
									{
										if (menu_pos<=0)
										{
											menu_pos=0;
											AppState=champ_select;
										}
										if(menu_pos>=1)
											quit=true;
									};			break;
				}
			}
	}
	SDL_Surface *SurTemp=NULL;
	//Blituj(SurTemp,SurMenu,80,20);
	SurTemp=SDL_LoadBMP("grafiki/newgame.bmp");
	Blituj(SurTemp,SurMenu,70,300);
	SDL_FreeSurface(SurTemp);
	SurTemp=SDL_LoadBMP("grafiki/koniec.bmp");
	Blituj(SurTemp,SurMenu,70,390);
	SDL_FreeSurface(SurTemp);
	if (menu_pos<=0)
	{
		menu_pos=0;
		SurTemp=SDL_LoadBMP("grafiki/dot.bmp");
		Blituj(SurTemp,SurMenu,400,305);
		SDL_FreeSurface(SurTemp);
	}
	if (menu_pos>=1)
	{
		menu_pos=1;
		SurTemp=SDL_LoadBMP("grafiki/dot.bmp");
		Blituj(SurTemp,SurMenu,400,405);
		SDL_FreeSurface(SurTemp);
	}
	Blituj(SurMenu,SurEkran,0,0);
	SDL_FreeSurface(SurTemp);
	SDL_FreeSurface(SurMenu);
	delete SurTemp;
};
void State_logo_start()
{
	SDL_Surface *temp=SDL_LoadBMP("v/bg_menu2.bmp");
	Blituj(temp,SurEkran,0,0);
	SDL_FreeSurface(temp);
	//delete temp;
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
	AppState=logo_start;
    SurEkran=SDL_SetVideoMode( WysEkranu,SzerEkranu, 32, SDL_SWSURFACE );
	SDL_WM_SetCaption( "Chuj", NULL );
	GlobalTime=SDL_GetTicks();
	while(!quit)
	{
				
		double TempTime=SDL_GetTicks();
		delta=(TempTime-GlobalTime)*0.001; // czas uplyniety od ostatniego rysowania ekranu
		GlobalTime=TempTime;
		WorldTime+=delta;
		switch (AppState)
		{
			case logo_start:	State_logo_start(); break;
			case menu:			State_menu();		break;
			case champ_select:	State_champ_select();break;
	//		case you_won:		State_you_won();	break;
	//		case you_lost:		State_you_lost();	break;
	//		case next_level:	State_next_level(); break;
			case game:			State_game();		break;
			case load:			State_load();		break;
		}
		SDL_Flip(SurEkran);
	};
	SDL_Quit();
	return 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////
int wrog::choose_target(int nr)//zwraca indeks gracza(celu) w vektorze
{
	int index=99;
	double najkrotsza=9999999;
	
	if(!vPlayer.empty())
	{
		for(int i=0;i<vPlayer.size();i++)
		{
			/*if(index==99)//jezeli nie ma wybranego najblizszego wpisuje pierwszego
			{
				
				najkrotsza=sqrt(pow((double)(vEnemy[nr].posx-vPlayer[i].posx),2)+pow((double)(vEnemy[nr].posy-vPlayer[i].posy),2));
				index=i;
				
			}*/
				
				double droga;
				droga=sqrt(pow((double)(vEnemy[nr].posy-vPlayer[i].posy),2)+pow((double)(vEnemy[nr].posy-vPlayer[i].posy),2));
				if(droga<najkrotsza)
				{
					najkrotsza=droga;
					index=i;
				}
		}
	vEnemy[nr].targetX=vPlayer[index].posx;
	vEnemy[nr].targetY=vPlayer[index].posy;
	}	
return index;
}
void wrog::akcja(int targetX,int targetY,int target_index,int i)//target index potrzerbne do odejmowania hp graczowi po ataku
{	struct allowed
	{
		int l,p,g,d;
	};
	struct allowed check;
	check.l=check.p=check.g=check.d=0;
	for ( int c=0;c<vEnemy.size();c++)
	{
		int px=vEnemy[i].posx;
		int py=vEnemy[i].posy;
		int ex=vEnemy[c].posx;
		int ey=vEnemy[c].posy;	// kolidujemy z kims!
		if (px<ex && px+cx>ex) { check.p=1; vEnemy[i].dy+=cy; }
		if (px>ex && ex+cx>px) { check.l=1; vEnemy[i].dy-=cy; }
		if (py>ey && ey+cy>py) { check.g=1; vEnemy[i].dx+=cx; }
		if (py<ey && py+cy>ey) { check.d=1; vEnemy[i].dx-=cx; }
	}
	/*
		if (vEnemy[i].dy!=-1 && vEnemy[i].dy>vEnemy[i].posy) 
	{
		vEnemy[i].posy+=ceil(vEnemy[i].speed*delta*0.75); 
		if (vEnemy[i].posy>=vEnemy[i].dy) vEnemy[i].dy=-1;
	}
	
	if (vEnemy[i].dy!=-1 && vEnemy[i].dy<vEnemy[i].posy) 
	{
		vEnemy[i].posy-=ceil(vEnemy[i].speed*delta*0.75); 
		if (vEnemy[i].posy<=vEnemy[i].dy) vEnemy[i].dy=-1;
	}
	
	if (vEnemy[i].dx!=-1 && vEnemy[i].dx>vEnemy[i].posx) 
	{
		vEnemy[i].posx+=ceil(vEnemy[i].speed*delta); 
		if (vEnemy[i].posx>=vEnemy[i].dx) vEnemy[i].dx=-1;
	}
	if (vEnemy[i].dx!=-1 && vEnemy[i].dx<vEnemy[i].posx) 
	{
		vEnemy[i].posx-=ceil(vEnemy[i].speed*delta); 
		if (vEnemy[i].posx<=vEnemy[i].dx) vEnemy[i].dx=-1;
	}*/
	if(vEnemy[i].posx<vEnemy[i].targetX && check.p==0) vEnemy[i].posx+=ceil(vEnemy[i].speed*delta*0.75);
	if(vEnemy[i].posx>vEnemy[i].targetX && check.l==0) vEnemy[i].posx-=ceil(vEnemy[i].speed*delta);
	if(vEnemy[i].posy<vEnemy[i].targetY && check.g==0) vEnemy[i].posy+=ceil(vEnemy[i].speed*delta*0.75);
	if(vEnemy[i].posy>vEnemy[i].targetY && check.d==0) vEnemy[i].posy-=ceil(vEnemy[i].speed*delta);	
	/////////////////////

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


//Gracz Funkcje/////////////////////////////////////////
void gracz::atakuj(int numer)
{
	switch(numer)
	{
		case 1:
		if(atak_basic.do_uzycia)
		{
			vAttack.push_back(new kula_Iron(*this));
			atak_basic.do_uzycia = false;
		}
		break;
	}
}

void gracz::sprawdz_ataki(double delta)
{
	if(!atak_basic.do_uzycia)
		atak_basic.sprawdz_gotowosc(delta);
}
