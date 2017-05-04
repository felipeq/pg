/* bonus:
		Projekt z PO, semestr 2
	Mateusz Pakulski
 * 	Sebastian Miałkowski
 * 	Filip Biedrzycki
 * 	
 * 
 * */
extern "C" {
#include"SDL.h"
}
#include "sdl/include/SDL.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib> 
#include <stdlib.h>
#include "config.hpp"
#include "funkcje.hpp"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
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
const int p2_basic=-41; //	7
const int p2_ext=-40;	//	8
const int p2_ult=-39;	//	9
////////////////////////////////PLAYER 3
const int p3_lewo=276-97;	//	strzałki
const int p3_prawo=275-97;	//	
const int p3_gora=273-97;	//	
const int p3_dol=274-97;	//	
const int p3_basic=-45; //	4
const int p3_ext=-44;	//	5
const int p3_ult=-43;	//	6
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
int currentlevel=1;
int currentfala=0;
int menu_pos=0;
////////klasy//////////klasy///////klasy////////////klasy///////
int cx=50;
int cy=50;
////Deklaracje klas///////////////
class gracz;
class wrog;
class postac;
class smieci;
class atak
{
	public:
	bool animowany; //True kiedy atak jest rysowany na planszy, false usunie sie  z wektora
	bool do_uzycia;
	virtual void uzyj(){};
	virtual void koniec(){};
	void sprawdz_gotowosc(double delta);
	int posx, posy;
	vector<int> wybierz_cel(int zasieg, vector<wrog>& cele);
	
	protected:
	int numer_boh;
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
	kula_Iron(gracz&,int boh_num);
	~kula_Iron(); //Animacja wybuchu
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
	laser_Iron(gracz& bohater,int boh_num);
	void uzyj();
	void koniec(){};
};

class rakiety_Iron : public atak
{
	public:
	rakiety_Iron();
	rakiety_Iron(gracz& bohater,int boh_num);
	void uzyj();
	void koniec(){};
	vector<int> cele; // vector numerów celów
	int* pozycjex;  //Pozycje poszczególnych rakiet
	int* pozycjey;
	bool* trafienie; //True jezeli trafiony
	int ilosc_trafien;
};


class obszarowy_Hulk : public atak
{
	public:
	obszarowy_Hulk();
	obszarowy_Hulk(gracz&,int boh_num);
	void uzyj();
	void koniec(){};
	vector<int> cele;
	int czas_trwania;
	bool atakuje; //Kiedy true odbiera zycie
	
	protected:
	SDL_Surface* klatki_anim[2];
	int numer_klatki;
	int numer_gracza;

};

class obszarowy_Hulk2 : public atak
{
	public:
	obszarowy_Hulk2();
	obszarowy_Hulk2(gracz&,int boh_num);
	void uzyj();
	void koniec(){};
	vector<int> cele;
	int czas_trwania;
	bool atakuje; //Kiedy true odbiera zycie
};

class furia_Hulk : public atak
{
	public:
	furia_Hulk();
	furia_Hulk(gracz& bohater, int i,int boh_num);
	void uzyj();
	void koniec(){};
	
	protected:
	int czas_trwania;
	int cel;
};

class mlot_Thor : public atak
{
	public:
	mlot_Thor();
	mlot_Thor(gracz& bohater,int boh_num);
	void uzyj();
	void koniec(){};
	
	protected:
	int cel;
	bool atakuje;
	int czas_trwania;
};
	
class piorun_Thor : public atak
{
	public:
	piorun_Thor();
	piorun_Thor(gracz& bohater,int boh_num);
	void uzyj();
	void koniec(){};
	
	protected:
	int cel;
	bool atakuje;
	int czas_trwania;
};

class leczenie_Thor : public atak
{
	public:
	leczenie_Thor();
	leczenie_Thor(gracz& bohater,int boh_num);
	void uzyj();
	void koniec(){};
	
	protected:
	bool leczy;
	int czas_trwania;
};

class postac
{
	public:
	int hp;
	double posx, posy;
	int speed;
	vector<int> wybierz_cel(int zasieg, vector<wrog>& cele);
	int wybierz_cel(vector<wrog>& cele, int zasieg);
};
class strzal_wrog : public atak
{
        public:
        strzal_wrog();
        strzal_wrog(int bohater_numer, int wrog_numer);
        void uzyj();
        protected:
        int poczatek;
        int koniec;
};
class wrog : public postac
{
        public:
				bool ogluszony;//0 nieogluszony 1 ogluszony
                int target_index;
                int targetX;
                int targetY;
                int typ;
                bool kierunek;
                wrog(int chp, int cx, int cy,int cv, int ctyp)
                {
					
					hp=chp;posx=cx;posy=cy;typ=ctyp;normal_cd=2;kierunek=0; atakuje=0; cd_start=GlobalTime;ogluszony_start=0; speed=10,ogluszony=0;
                };        
                ~wrog(){};
                int choose_target(int nr);        
                void akcja(int targetX,int targetY,int target_index,int i);
                void wyswietl_normal(int target_index,int i);
                void wyswietl_stun(int enemyX,int enemyY,int i);
                void die(int i);
        private:
				double ogluszony_start;
                const static int czas_ogluszenia=3;
                void ogluszeni(double ogluszony_start, int i);//i numer gracze
				const static int sila=100;//sila normalnego ataku wroga;
				const static int zasieg=250;//zasieg ataku wroga typu 2
				double normal_cd;
				double cd_start;
				bool atakuje;
                void normal_atak(int i,int target_index);
                //void strzal(int target_index);
};
class smieci
{
        public:
                        SDL_Surface *grafika;
                        int posx,posy;
                        smieci(int cposx,int cposy)
                        {
                                grafika=IMG_Load("v/enemies/corpse1.gif");
                                posx=cposx;
                                posy=cposy;
                        }
                        ~smieci(){};
                        void wyswietl(int i);
                        
};
class gracz : public postac
{
	public:
	void die(int i);
	eKlasa klasa;
	int kierunek;
	int id;
	bool isMoving;
	int frame;
	double frame_time;
	int tab[7];
	kula_Iron atak_basic;
	gracz(int cid, int chp, int cx, int cy, int cv, eKlasa cclass)
	{
		for ( int i=0;i<7;i++)
			tab[i]=0;
		frame_time=0.15;
		isMoving=false;
		frame=0;
		id=cid;
		hp=chp*100000;
		posx=cx;
		posy=cy;
		speed=cv;
		klasa=cclass;
		okres_regeneracji = 3;
		kiedy_regeneracja = 0;
		wartosc_regeneracji = 10;
	}
	~gracz(){};
	void Przesun( int x )
	{
		isMoving=true;
		if (frame_time<=0) {frame++; if (frame==3) frame=1;frame_time=0.15;}
		switch (x)
		{
			case 0: if(posx>5) 		posx-=(speed*delta/3); break;
			case 1: if(posx<590) 	posx+=(speed*delta/3); break;
			case 2: if(posy>5)		posy-=(speed*delta/3); break;
			case 3: if(posy<335)	posy+=(speed*delta/3); break;
		}
	}
	void NextFrame()
	{
		if (frame_time<=0) 
		{
			frame++;
			frame_time=0.15;
			if (frame>9) frame=0;
		}
	}
	void atakuj(int numer, int);
	void sprawdz_ataki(double delta);
	void regeneruj();
	protected:
	int okres_regeneracji;
	double kiedy_regeneracja;
	int wartosc_regeneracji;
};

struct fale
{
	int pot_slaby;
	int pot_sredni;
	int boss;
};
struct poziom
{
	char tlo[14];
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
vector<smieci> vSmieci;
vector<wrog> vEnemy;
vector<gracz> vPlayer;
vector<atak*> vAttack;
struct poziom level;
//Obiekty klas uzywane do sprawdzania czy mozna uzyc ataku/////////////
kula_Iron Gkula_Iron; 
laser_Iron Glaser_Iron;
rakiety_Iron Grakiety_Iron;
obszarowy_Hulk Gobszarowy_Hulk;
obszarowy_Hulk2 Gobszarowy_Hulk2;
furia_Hulk Gfuria_Hulk;
mlot_Thor Gmlot_Thor;
piorun_Thor Gpiorun_Thor;
leczenie_Thor Gleczenie_Thor;
strzal_wrog Gstrzal_wrog;
////KOD//////////////KOD//////////////KOD////////////////KOD//////////
void Napisuj(char* napis,int x, int y) // Wyświetlanie napisu "napis" na pozycji x,y
{
		font=TTF_OpenFont("czcionki/menu.ttf", 50);
		SDL_Surface * text1;
		SDL_Color kolor;
		kolor.r=255;
		kolor.g=255;
		kolor.b=255;
		text1 = TTF_RenderText_Solid(font, napis, kolor);
		Blituj(text1,SurEkran,x,y);
		TTF_CloseFont(font);
		SDL_FreeSurface(text1);
}

void Muzyka(int a, int gdzie, int ile) // Obsługa muzyki na kanale "gdzie" z ilością odtworzeń "ile"
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
char* DoubleToChar(double way) // konwersja
{
		std::stringstream str;
		str << way << std::ends;
		std::string result = str.str();
		char* penis=new char[result.length()]; // <--------------------------------
		for ( int w=0;w<result.length();w++)
		penis[w]=result[w];
		return penis; // WYCIEEEEEEEEEEEEEEEEEEK
}
char *StrToChar(string way) // konwersja
{
		string result;
		char* penis=new char[way.length()]; // <--------------------------------
		for ( int w=0;w<=result.length();w++)
		penis[w]=result[w];
		Napisuj(penis,50,50);
		return penis; // WYCIEEEEEEEEEEEEEEEEEEK
}
void Move() // przsuwanie postaci na ekranie zgodnie z zadeklarowaną globalnie klawiszologią
{
	if (vEnemy.size()>0)
	for ( int i=0;i<vEnemy.size();i++)
	{
		vEnemy[i].target_index=vEnemy[i].choose_target(i);
		vEnemy[i].akcja(vEnemy[i].targetX,vEnemy[i].targetY,vEnemy[i].target_index,i);
	}
	for ( int i=0;i<vPlayer.size();i++)
	{
	//	vPlayer[i].frame_time-=delta;
		if (vPlayer[i].id==1)
		{	
			if( keystate[ SDLK_a+p1_lewo])	{ vPlayer[i].Przesun(0); }
			if( keystate[ SDLK_a+p1_prawo])	{ vPlayer[i].Przesun(1); }		// praw
			if( keystate[ SDLK_a+p1_gora])	{ vPlayer[i].Przesun(2); } 		// gora
			if( keystate[ SDLK_a+p1_dol])	{ vPlayer[i].Przesun(3); }												// dol
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
void Collision() // Odtwarzanie kolejnej fali, gdy zginie pierwsza
{
	if (vEnemy.size()==0 && Loaded==false)
	{
		if (currentfala<2)
		currentfala++;
		Loaded=true;
	}
};
void Atak_wroga(int wrog_numer, int bohater_numer);
void Attack() 	// obsługa klawiszy ataku
{
	vector<int> do_usuniecia;
	while( SDL_PollEvent( & zdarzenie ) )
			{
				if( zdarzenie.type == SDL_QUIT ) quit = true;
				if( zdarzenie.type == SDL_KEYDOWN )
				{
					for ( int i=0;i<vPlayer.size();i++)
					{
												if (vPlayer[i].id==3)
							{
								if(vPlayer[i].klasa == ironman)
								{
									switch( zdarzenie.key.keysym.sym )
									{
									case SDLK_a+p3_basic:
									vPlayer[i].atakuj(1,i);
									break;
							
									case SDLK_a+p3_ext:
									vPlayer[i].atakuj(2,i);
									break;
							
									case SDLK_a+p3_ult:
									vPlayer[i].atakuj(3,i);
									break;
									}
								}
								
								if(vPlayer[i].klasa == hulk)
								{
									switch( zdarzenie.key.keysym.sym )
									{
									case SDLK_a+p3_basic:
									vPlayer[i].atakuj(1,i);
									break;
							
									case SDLK_a+p3_ext:
									vPlayer[i].atakuj(2,i);
									break;
							
									case SDLK_a+p3_ult:
									vPlayer[i].atakuj(3,i);
									break;
									}
								}
								
								if(vPlayer[i].klasa == thor)
								{
									switch( zdarzenie.key.keysym.sym )
									{
									case SDLK_p:
									vPlayer[i].atakuj(1,i);
									break;
									
									case SDLK_a+p3_ext:
									vPlayer[i].atakuj(2,i);
									break;
									
									case SDLK_a+p3_ult:
									vPlayer[i].atakuj(3,i);
									break;
									}
								}
							}
						if (vPlayer[i].id==2)
							{
								if(vPlayer[i].klasa == ironman)
								{
									switch( zdarzenie.key.keysym.sym )
									{
									case SDLK_a+p2_basic:
									vPlayer[i].atakuj(1,i);
									break;
							
									case SDLK_a+p2_ext:
									vPlayer[i].atakuj(2,i);
									break;
							
									case SDLK_a+p2_ult:
									vPlayer[i].atakuj(3,i);
									break;
									}
								}
								
								if(vPlayer[i].klasa == hulk)
								{
									switch( zdarzenie.key.keysym.sym )
									{
									case SDLK_a+p2_basic:
									vPlayer[i].atakuj(1,i);
									break;
							
									case SDLK_a+p2_ext:
									vPlayer[i].atakuj(2,i);
									break;
							
									case SDLK_a+p2_ult:
									vPlayer[i].atakuj(3,i);
									break;
									}
								}
								
								if(vPlayer[i].klasa == thor)
								{
									switch( zdarzenie.key.keysym.sym )
									{
									case SDLK_p:
									vPlayer[i].atakuj(1,i);
									break;
									
									case SDLK_a+p2_ext:
									vPlayer[i].atakuj(2,i);
									break;
									
									case SDLK_a+p2_ult:
									vPlayer[i].atakuj(3,i);
									break;
									}
								}
							}

							if (vPlayer[i].id==1)
							{
								if(vPlayer[i].klasa == ironman)
								{
									switch( zdarzenie.key.keysym.sym )
									{
									case SDLK_a+p1_basic:
									vPlayer[i].atakuj(1,i);
									break;
							
									case SDLK_a+p1_ext:
									vPlayer[i].atakuj(2,i);
									break;
							
									case SDLK_a+p1_ult:
									vPlayer[i].atakuj(3,i);
									break;
									}
								}
								
								if(vPlayer[i].klasa == hulk)
								{
									switch( zdarzenie.key.keysym.sym )
									{
									case SDLK_a+p1_basic:
									vPlayer[i].atakuj(1,i);
									break;
							
									case SDLK_a+p1_ext:
									vPlayer[i].atakuj(2,i);
									break;
							
									case SDLK_a+p1_ult:
									vPlayer[i].atakuj(3,i);
									break;
									}
								}
								
								if(vPlayer[i].klasa == thor)
								{
									switch( zdarzenie.key.keysym.sym )
									{
									case SDLK_p:
									vPlayer[i].atakuj(1,i);
									break;
									
									case SDLK_a+p1_ext:
									vPlayer[i].atakuj(2,i);
									break;
									
									case SDLK_a+p1_ult:
									vPlayer[i].atakuj(3,i);
									break;
									}
								}
							}
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
			do_usuniecia.push_back(i);
		}
		if(vAttack.empty())
			break;
			
		vAttack[i]->uzyj();
	}

	for(int i = 0; i < do_usuniecia.size();i++)
	{
		delete vAttack[do_usuniecia[i]];
		vAttack.erase(vAttack.begin() + do_usuniecia[i]);
	}
}
void ShowInterface() // wyświetlanie interfejsu gry u dołu ekranu
{
	SDL_Surface *temp;	
	temp=IMG_Load("interfejs/iron_off.gif");
	Blituj(temp,SurBg,10,425);
	SDL_FreeSurface(temp);
	temp=IMG_Load("interfejs/hulk_off.bmp");
	Blituj(temp,SurBg,223,423);
	SDL_FreeSurface(temp);
	temp=IMG_Load("interfejs/thor_off.gif");
	Blituj(temp,SurBg,438,425);
	SDL_FreeSurface(temp);		
	temp=IMG_Load("interfejs/bot.gif");
	Blituj(temp,SurBg,0,415);
	SDL_FreeSurface(temp);
	temp=IMG_Load("interfejs/iron_soff.gif");
	Blituj(temp,SurBg,108,435);
	SDL_FreeSurface(temp);
	temp=IMG_Load("interfejs/hulk_soff.gif");
	Blituj(temp,SurBg,322,435);
	SDL_FreeSurface(temp);
		temp=IMG_Load("interfejs/thor_soff.gif");
	Blituj(temp,SurBg,535,435);
	SDL_FreeSurface(temp);
	for ( int i=0;i<vPlayer.size();i++)
	{
		if (vPlayer[i].klasa==ironman)
		{
			temp=IMG_Load("interfejs/iron_on.gif");
			Blituj(temp,SurBg,10,425);
			SDL_FreeSurface(temp);
			if (Gkula_Iron.do_uzycia==true)
				{
					temp=IMG_Load("interfejs/iron_on1.gif");
					Blituj(temp,SurBg,108,435);
					SDL_FreeSurface(temp);
				}
			if (Glaser_Iron.do_uzycia==true)
				{
					temp=IMG_Load("interfejs/iron_on2.gif");
					Blituj(temp,SurBg,133,435);
					SDL_FreeSurface(temp);
				}
			if (Grakiety_Iron.do_uzycia==true)
				{
					temp=IMG_Load("interfejs/iron_on3.gif");
					Blituj(temp,SurBg,158,435);
					SDL_FreeSurface(temp);
				}
		}
		if (vPlayer[i].klasa==hulk)
		{
			temp=IMG_Load("interfejs/hulk_on.gif");
			Blituj(temp,SurBg,223,425);
			SDL_FreeSurface(temp);
			if (Gobszarowy_Hulk.do_uzycia==true)
				{
					temp=IMG_Load("interfejs/hulk_on1.gif");
					Blituj(temp,SurBg,322,435);
					SDL_FreeSurface(temp);
				}
			if (Gobszarowy_Hulk2.do_uzycia==true)
				{
					temp=IMG_Load("interfejs/hulk_on2.gif");
					Blituj(temp,SurBg,347,435);
					SDL_FreeSurface(temp);
				}
			if (Gfuria_Hulk.do_uzycia==true)
				{
					temp=IMG_Load("interfejs/hulk_on3.gif");
					Blituj(temp,SurBg,372,435);
					SDL_FreeSurface(temp);
				}
		}
		if (vPlayer[i].klasa==thor)
		{
			temp=IMG_Load("interfejs/thor_on.gif");
			Blituj(temp,SurBg,435,425);
		/*	if (Gmlot_Thor.do_uzycia==true)
				{
					temp=IMG_Load("interfejs/thor_on1.gif");
					Blituj(temp,SurBg,535,435);
					SDL_FreeSurface(temp);
				}
			if (Gpiorun_Thor.do_uzycia==true)
				{
					temp=IMG_Load("interfejs/thor_on2.gif");
					Blituj(temp,SurBg,560,435);
					SDL_FreeSurface(temp);
				}
			if (Gleczenie_Thor.do_uzycia==true)
				{
					temp=IMG_Load("interfejs/thor_on3.gif");
					Blituj(temp,SurBg,585,435);
					SDL_FreeSurface(temp);
				}*/
			SDL_FreeSurface(temp);
		}
	}
	
}
void State_game() // GLOWNA PETLA GRY
{
	if (currentlevel==1)
		SurBg=IMG_Load("v/levels/1.bmp");
	if (currentlevel==2)
		SurBg=IMG_Load("v/levels/2.bmp");
	if (currentlevel==3)
		SurBg=IMG_Load("v/levels/3.bmp");
		if (vPlayer.size()==0) {quit=true; return;}
	Attack();
	Collision();
	Move();
	SDL_Surface *SurE;
	if (Loaded==true)	// Ładowanie przeciwników do wektora vEnemy
	{	
		for ( int ii=0;ii<level.Fale[currentfala].pot_slaby;ii++)
		{
			wrog temp(200,500+15*ii,20+70*ii,10,1);
			vEnemy.push_back(temp);
		}
		for ( int ii=0;ii<level.Fale[currentfala].pot_sredni;ii++)
		{
			wrog temp(200,400,20+70*ii,1,2);
			vEnemy.push_back(temp);
		}
		Loaded=false;
	}
	
	for ( int i=0;i<vPlayer.size();i++) // wybieranie odpowiedniej klatki animacji postaci do wyświetlenia
	{
		vPlayer[i].frame_time-=delta;
		//vPlayer[i].NextFrame();
		if (vPlayer[i].klasa==ironman)
		{
			if (vPlayer[i].frame==0)
				SurE=IMG_Load("v/ironman/ruch/0.gif");
			if (vPlayer[i].frame==1)
				SurE=IMG_Load("v/ironman/ruch/1.gif");
			if (vPlayer[i].frame==2)
				SurE=IMG_Load("v/ironman/ruch/2.gif");
			if (vPlayer[i].frame==3)
				SurE=IMG_Load("v/ironman/ruch/0.gif");	
			if (vPlayer[i].frame==4)
				SurE=IMG_Load("v/ironman/ataki/10.gif");
			if (vPlayer[i].frame==5)
				SurE=IMG_Load("v/ironman/ataki/10.gif");
			if (vPlayer[i].frame==6)
				SurE=IMG_Load("v/ironman/ataki/10.gif");
			if (vPlayer[i].frame==7)
				SurE=IMG_Load("v/ironman/ataki/10.gif");
			if (vPlayer[i].frame==8)
				SurE=IMG_Load("v/ironman/ataki/20.gif");
			if (vPlayer[i].frame==9)
				SurE=IMG_Load("v/ironman/ataki/30.gif");	
		}
		if (vPlayer[i].klasa==hulk)
		{
			if ( Gfuria_Hulk.do_uzycia==false)
			{
				SurE=SDL_LoadBMP("v/hulk/rage.bmp");
				SDL_SetColorKey(SurE, SDL_SRCCOLORKEY, 0xFFFFFF);
				Blituj(SurE,SurBg,vPlayer[i].posx-20,vPlayer[i].posy-20);
				SDL_FreeSurface(SurE);
			}
			if (vPlayer[i].frame==0)
				SurE=SDL_LoadBMP("v/hulk/ruch/0.bmp");
			if (vPlayer[i].frame==1)
				SurE=SDL_LoadBMP("v/hulk/ruch/1.bmp");
			if (vPlayer[i].frame==2)
				SurE=SDL_LoadBMP("v/hulk/ruch/2.bmp");	
			if (vPlayer[i].frame==3)
				SurE=SDL_LoadBMP("v/hulk/ruch/0.bmp");
			if (vPlayer[i].frame==4)
				SurE=SDL_LoadBMP("v/hulk/ataki/10.bmp");
			if (vPlayer[i].frame==5)
				SurE=SDL_LoadBMP("v/hulk/ataki/11.bmp");
			if (vPlayer[i].frame==6)
				SurE=SDL_LoadBMP("v/hulk/ataki/12.bmp");	
			if (vPlayer[i].frame==7)
				SurE=SDL_LoadBMP("v/hulk/ataki/13.bmp");
			if (vPlayer[i].frame==8)
				SurE=SDL_LoadBMP("v/hulk/ataki/20.bmp");
			if (vPlayer[i].frame==9)
				SurE=SDL_LoadBMP("v/hulk/ruch/0.bmp");
		SDL_SetColorKey(SurE, SDL_SRCCOLORKEY, 0xFFFFFF);
		}
		if (vPlayer[i].klasa==thor)
		{
			if (vPlayer[i].frame==0)
				SurE=IMG_Load("v/thor/ruch/0.gif");
			if (vPlayer[i].frame==1)
				SurE=IMG_Load("v/thor/ruch/1.gif");
			if (vPlayer[i].frame==2)
				SurE=IMG_Load("v/thor/ruch/2.gif");	
			if (vPlayer[i].frame==3)
				SurE=IMG_Load("v/thor/ruch/3.gif");
			if (vPlayer[i].frame==4)
				SurE=IMG_Load("v/thor/ataki/10.gif");
			if (vPlayer[i].frame==5)
				SurE=IMG_Load("v/thor/ataki/11.gif");
			if (vPlayer[i].frame==6)
				SurE=IMG_Load("v/thor/ataki/12.gif");	
			if (vPlayer[i].frame==7)
				SurE=IMG_Load("v/thor/ataki/13.gif");
			if (vPlayer[i].frame==8)
				SurE=IMG_Load("v/thor/ataki/20.gif");
			if (vPlayer[i].frame==9)
				SurE=IMG_Load("v/thor/ataki/30.gif");	
		}
		
		Blituj(SurE,SurBg,vPlayer[i].posx,vPlayer[i].posy);
		SDL_FreeSurface(SurE);
	}
	if (vEnemy.size()==0)
		{ Loaded=true; currentfala=0; currentlevel++;AppState=champ_select; return; } 
	else	
	for ( int i=0;i<vEnemy.size();i++) // wybieranie klatki animacji przeciwników
	{
		if (vEnemy[i].kierunek==0)
		{
			if (vEnemy[i].typ==1)
				SurE=IMG_Load("v/enemies/enemy1l.png");
			if (vEnemy[i].typ==2)
				SurE=IMG_Load("v/enemies/enemy2l0.png");
		}
		if (vEnemy[i].kierunek==1)
		{
			if (vEnemy[i].typ==1)
				SurE=IMG_Load("v/enemies/enemy1p.png");
			if (vEnemy[i].typ==2)
				SurE=IMG_Load("v/enemies/enemy2p0.png");
		}
		Blituj(SurE,SurBg,vEnemy[i].posx,vEnemy[i].posy);	
		SDL_FreeSurface(SurE);	
	}
	while( SDL_PollEvent( & zdarzenie ) )
		if( zdarzenie.type == SDL_QUIT ) quit = true;
	for( int i=0;i<vPlayer.size();i++) // obsługa śmierci graczy
	{
		vPlayer[i].die(i);
	}
	for(int i=0;i<vEnemy.size();i++)
	{
		vEnemy[i].wyswietl_normal(vEnemy[i].target_index,i); //wyswietl animacje/klatke ataku na targecie
		if(vEnemy[i].ogluszony==1)
			vEnemy[i].wyswietl_stun(vEnemy[i].posx,vEnemy[i].posy,i);
	}
	ShowInterface();
	Blituj(SurBg,SurEkran,0,0);
	SDL_FreeSurface(SurBg);
	Loaded=false;
};

void DodajPlayera( int ID, int champ) // Dodawanie gracza do vPlayer
{
	eKlasa temp;
	if (champ==1) temp=ironman;
	if (champ==2) temp=hulk;
	if (champ==3) temp=thor;
	vPlayer.push_back(gracz(ID,100,20,250,300,temp));
}
void State_champ_select() // wybieranie postaci do grania
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
					case SDLK_a+p1_ext:	
					{
						if (p2_picked==false && p2_select>0)
						{
							p2_picked=true;
							DodajPlayera(2,p2_select);
						}
					}; break;
					case SDLK_a+p1_ult:	
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
void LoadLevel() // załaduj poziom z pliku
{
	string s;
	s="v/levels/0.bmp";
	
	char num=currentlevel+48;
	for ( int i=0;i<14;i++)
		level.tlo[i]=s[i];
	level.tlo[9]=num;
	char* source=level.tlo;
	for ( int i=0;i<14;i++)
		source[i]=level.tlo[i];
	source[13]=source[11]='t';
	source[12]='x';
	ifstream in;
	in.exceptions ( ifstream::failbit | ifstream::badbit );
		try 
		{
   			in.open(source);
			in >> level.Fale[0].pot_slaby;
			in >> level.Fale[0].pot_sredni;
			in >> level.Fale[0].boss;
			in >> level.Fale[1].pot_slaby;
			in >> level.Fale[1].pot_sredni;
			in >> level.Fale[1].boss; 
		}
		catch (ifstream::failure e) { }
			in.close();  
}
void State_load()
{
	LoadLevel();
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
//LoadLevel();
	// -------------------------------------INICJACJA--------------------------------------
	/*
	level1.Fale[0].pot_sredni=2;
	level1.Fale[0].boss=0;
	level1.Fale[1].pot_slaby=7;
	level1.Fale[1].pot_sredni=4;
	level1.Fale[1].boss=0;*//*
	printf("%i", level.Fale[1].pot_slaby*2);
	printf("%i", level.Fale[1].pot_sredni);
	printf("He22llo world!\n");*/
	SDL_Init( SDL_INIT_EVERYTHING );
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024);
	TTF_Init();
	AppState=logo_start;
    SurEkran=SDL_SetVideoMode( WysEkranu,SzerEkranu, 32, SDL_SWSURFACE );
	SDL_WM_SetCaption( "The Avengers", NULL );
	GlobalTime=SDL_GetTicks();
	Muzyka(0,0,-1);
	while(!quit)
	{
				
		double TempTime=SDL_GetTicks();
		delta=(TempTime-GlobalTime)*0.001; // czas uplyniety od ostatniego rysowania ekranu
		GlobalTime=TempTime;
		WorldTime+=delta;
		switch (AppState) // obsłuż stany aplikacji
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
                                if(vEnemy[i].typ==1)
                                {
                                        if(i>3)
                                        {
                                                vEnemy[i].targetX=vPlayer[q].posx-40;
                                                if(i%3==2)
                                                {
                                                        vEnemy[i].targetY=vPlayer[q].posy-(i%3)*10;
                                                }
                                                else
                                                {
                                                        vEnemy[i].targetY=vPlayer[q].posy+(i%3)*40;
                                                }
                                        }
                                        else
                                        {
                                                vEnemy[i].targetX=vPlayer[q].posx+50;
                                                if(i%3==2)
                                                {
                                                        vEnemy[i].targetY=vPlayer[q].posy-(i%3)*20;
                                                }
                                                else
                                                {
                                                        vEnemy[i].targetY=vPlayer[q].posy+(i%3)*40;
                                                }
                                        }
                                }
                                else
                                {
                                         vEnemy[i].targetX=vPlayer[q].posx;
                     vEnemy[i].targetY=vPlayer[q].posy;
                                }
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
        //////////////////////////////////////////////////////////////////////
        //sprawdzenie czy sa ogluszeni
        ogluszeni(vEnemy[i].ogluszony_start,i);
        for(int i=0;i<vEnemy.size();i++) vEnemy[i].die(i);
        //////////////////////////////////////////////////////////////////////
        struct allowed
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
                int ey=vEnemy[c].posy;        // kolidujemy z kims!
                if (px<ex && px+cx>ex) { check.p=1;}
                if (px>ex && ex+cx>px) { check.l=1;}
                if (py>ey && ey+cy>py) { check.g=1;}
                if (py<ey && py+cy>ey) { check.d=1;}
        }
        //////////////////////////////////////typ 1///////////////////////////////////////////////////
        //ruch i sprawdzanie czy moze zaatakowac
        if(vEnemy[i].typ==1)
        {
                if(vEnemy[i].posx<vEnemy[i].targetX && vEnemy[i].ogluszony!=1) {vEnemy[i].posx+=ceil(vEnemy[i].speed*delta); vEnemy[i].kierunek=1;}
                if(vEnemy[i].posx>vEnemy[i].targetX && vEnemy[i].ogluszony!=1) {vEnemy[i].posx-=ceil(vEnemy[i].speed*delta); vEnemy[i].kierunek=0;}
                if(vEnemy[i].posy<vEnemy[i].targetY && vEnemy[i].ogluszony!=1) vEnemy[i].posy+=ceil(vEnemy[i].speed*delta);
                if(vEnemy[i].posy>vEnemy[i].targetY && vEnemy[i].ogluszony!=1) vEnemy[i].posy-=ceil(vEnemy[i].speed*delta);        
                if(vEnemy[i].posx>vEnemy[i].targetX-10 && vEnemy[i].posy>vEnemy[i].targetY-10 && vEnemy[i].posx<vEnemy[i].targetX+15 && vEnemy[i].posx>vEnemy[i].targetX-10)
                {
                        normal_atak(i,vEnemy[i].target_index);
                }
        }
        if(vEnemy[i].typ==2)
        {
                if(fabs(vEnemy[i].posy-vPlayer[target_index].posy)+fabs(vEnemy[i].posy-vPlayer[target_index].posy)>zasieg+40)
                {
                        if((vEnemy[i].posx-ceil(vEnemy[i].speed*delta)>0) && check.l==0 && vEnemy[i].posx>vEnemy[i].targetX && vEnemy[i].ogluszony!=1) vEnemy[i].posx-=ceil(vEnemy[i].speed*delta);
                        if((vEnemy[i].posx+ceil(vEnemy[i].speed*delta)<WysEkranu) && check.p==0 && vEnemy[i].posx<vEnemy[i].targetX && vEnemy[i].ogluszony!=1) vEnemy[i].posx+=ceil(vEnemy[i].speed*delta);
                        if((vEnemy[i].posy-ceil(vEnemy[i].speed*delta)>0) && check.g==0 && vEnemy[i].posy>vEnemy[i].targetY && vEnemy[i].ogluszony!=1) vEnemy[i].posy-=ceil(vEnemy[i].speed*delta);
                        if((vEnemy[i].posy-ceil(vEnemy[i].speed*delta)<SzerEkranu-80) && check.d==0 && vEnemy[i].posy<vEnemy[i].targetY && vEnemy[i].ogluszony!=1) vEnemy[i].posy+=ceil(vEnemy[i].speed*delta);
                }
                if(fabs(vEnemy[i].posy-vPlayer[target_index].posy)+fabs(vEnemy[i].posy-vPlayer[target_index].posy)<zasieg)
                {
                        if((vEnemy[i].posx+ceil(vEnemy[i].speed*delta)<WysEkranu) && check.p==0 && vEnemy[i].posx>vEnemy[i].targetX && vEnemy[i].ogluszony!=1) vEnemy[i].posx+=ceil(vEnemy[i].speed*delta);
                        if((vEnemy[i].posx-ceil(vEnemy[i].speed*delta)>0 && check.l==0) && vEnemy[i].posx<vEnemy[i].targetX && vEnemy[i].ogluszony!=1) vEnemy[i].posx-=ceil(vEnemy[i].speed*delta);
                        if((vEnemy[i].posy-ceil(vEnemy[i].speed*delta)<SzerEkranu-80) && check.d==0 && vEnemy[i].posy>vEnemy[i].targetY && vEnemy[i].ogluszony!=1) vEnemy[i].posy+=ceil(vEnemy[i].speed*delta);
                        if((vEnemy[i].posy-ceil(vEnemy[i].speed*delta)>0) && check.g==0 && vEnemy[i].posy<vEnemy[i].targetY && vEnemy[i].ogluszony!=1) vEnemy[i].posy-=ceil(vEnemy[i].speed*delta);
                }
                if(sqrt(pow((double)(vEnemy[i].posy-vPlayer[target_index].posy),2)+pow((double)(vEnemy[i].posy-vPlayer[target_index].posy),2))<zasieg+10)
                {
                        Atak_wroga(i,target_index);
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

kula_Iron::kula_Iron(gracz& bohater,int boh_num)
{
	posx = bohater.posx;
	posy = bohater.posy;
	sila = 50;
	zasieg = 0;
	animowany = true;
	do_uzycia = false;
	czas_regeneracji = 1.5;
	numer_boh = boh_num;
	ile_minelo = 0;
	numer_trafionego = -1;
	wyglad = SDL_LoadBMP("v/r_omw2.bmp");
	SDL_SetColorKey(wyglad, SDL_SRCCOLORKEY, 0xFFFFFF);
}
	
kula_Iron::~kula_Iron()
{}

void kula_Iron::uzyj()
{
	SDL_Surface* bum = SDL_LoadBMP("v/r_hit.bmp");
	SDL_SetColorKey(bum, SDL_SRCCOLORKEY, 0xFFFFFF);
	sprawdz_trafienie();
	if(numer_trafionego != -1)
	{
		vEnemy[numer_trafionego].hp -= sila;
		Blituj(bum,SurBg,posx,posy);
		animowany = false;
	}
	posx += 1;
	Blituj(wyglad,SurBg,posx,posy);
	SDL_FreeSurface(bum);
}

void kula_Iron::sprawdz_trafienie()
{
	double odleglosc;
	for(int i = 0; i < vEnemy.size(); i++)
	{
		odleglosc = sqrt(pow(posx - vEnemy[i].posx,double(2)) + pow(posy - vEnemy[i].posy,double(2)));
		if(odleglosc < 50)
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
	wyglad = IMG_Load("v/effects/ironman2.gif");
}

laser_Iron::laser_Iron(gracz& bohater,int boh_num)
{
	posx = bohater.posx;
	posy = bohater.posy;
	sila = 20;
	czas_regeneracji  = 2;
	do_uzycia = true;
	ile_minelo = 0;
	animowany = true;
	numer_boh = boh_num;
	czas_trwania = 1;
	wyglad = IMG_Load("v/effects/ironman2.gif");
}

void laser_Iron::uzyj()
{
	SDL_Surface* bum = SDL_LoadBMP("v/2_hit.bmp");
	SDL_SetColorKey(bum, SDL_SRCCOLORKEY, 0xFFFFFF);
	if( ile_minelo < 1 || obrazenia)
	{
		for(int i = 0; i < vEnemy.size(); i++)
		{
			if(vEnemy[i].posy == posy)
			{
				Blituj(bum,SurBg,vEnemy[i].posx,vEnemy[i].posy);
				vEnemy[i].hp -= sila;
			}
		}
		obrazenia = false;
	}
	SDL_LoadBMP("laser_Iron.bmp");
	Blituj(wyglad,SurBg,posx,posy);
	ile_minelo += delta;
	if(ile_minelo >= czas_trwania)
	{
		ile_minelo = 0;
		animowany = false;
	}
	SDL_FreeSurface(bum);
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

rakiety_Iron::rakiety_Iron(gracz& bohater,int boh_num)
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
	numer_boh = boh_num;
	sila = 30;
	wyglad = SDL_LoadBMP("rakiety_Iron.bmp");
}

void rakiety_Iron::uzyj()
{
	SDL_Surface* bum = SDL_LoadBMP("v/r_hit.bmp");
	SDL_SetColorKey(bum, SDL_SRCCOLORKEY, 0xFFFFFF);
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
				Blituj(bum,SurBg,vEnemy[i].posx,vEnemy[i].posy);
				ilosc_trafien++;
			}
		}
	}
	if(ilosc_trafien == (cele.size()-1))
		animowany = false;
	SDL_FreeSurface(bum);
}
	
	
////obszarowy_Hulk///////////////////
obszarowy_Hulk::obszarowy_Hulk()
{
	czas_regeneracji = 2;
	do_uzycia = true;
	ile_minelo = 0;
	wyglad  = SDL_LoadBMP("obszarowy_Hulk.bmp");
}

obszarowy_Hulk::obszarowy_Hulk(gracz& bohater,int boh_num)
{
	posx = bohater.posx;
	posy = bohater.posy;
	cele = bohater.wybierz_cel(zasieg,vEnemy);
	sila = 30;
	czas_regeneracji = 2;
	animowany = true;
	klatki_anim[0] = SDL_LoadBMP("v/hulk/ataki/13.bmp");
	klatki_anim[1] = SDL_LoadBMP("v/hulk/ataki/20.bmp");
	czas_trwania = 3;
	numer_klatki = 0;
	numer_boh = boh_num;
	atakuje = true;
	
}

void obszarowy_Hulk::uzyj()
{
	if(atakuje)
	{
		for(int i = 0; i < cele.size(); i++)
		{
			vEnemy[cele[i]].hp -= sila;
		}
		atakuje = false;
	}
	if(animowany)
	{
		Blituj(klatki_anim[0],SurBg,posx,posy);
		ile_minelo += delta;
		if(ile_minelo >= czas_trwania)
		{
			ile_minelo = 0;
			animowany = false;
		}
	}
}


////obszarowy_Hulk2 funkcje/////////////////////////////
obszarowy_Hulk2::obszarowy_Hulk2()
{
	czas_regeneracji = 3;
	do_uzycia = true;
	ile_minelo = 0;
	wyglad  = SDL_LoadBMP("obszarowy_Hulk2.bmp");
}

obszarowy_Hulk2::obszarowy_Hulk2(gracz& bohater,int boh_num)
{
	posx = bohater.posx;
	posy = bohater.posy;
	cele = bohater.wybierz_cel(zasieg,vEnemy);
	sila = 30;
	czas_regeneracji = 2;
	numer_boh = boh_num;
	animowany = true;
	wyglad = SDL_LoadBMP("obszarowy_Hulk2.bmp");
	czas_trwania = 3;
	atakuje = true;
}

void obszarowy_Hulk2::uzyj()
{
	if(atakuje)
	{
		for(int i = 0; i < cele.size(); i++)
		{
			vEnemy[cele[i]].hp -= sila;
			vEnemy[cele[i]].ogluszony = true;
		}
		atakuje = false;
	}
	if(animowany)
	{
		vPlayer[numer_boh].frame=8;
		Blituj(wyglad,SurBg,posx,posy);
		ile_minelo += delta;
		if(ile_minelo >= czas_trwania)
		{
			ile_minelo = 0;
			animowany = false;
		}
	}
}

////furia_Hulk funkcje////////////////////////////
furia_Hulk::furia_Hulk()
{
	czas_regeneracji = 4;
	do_uzycia = true;
	ile_minelo = 0;
	wyglad = SDL_LoadBMP("furia_Hulk.bmp");
}

furia_Hulk::furia_Hulk(gracz& bohater, int i,int boh_num)
{
	posx = bohater.posx;
	posy = bohater.posy;
	sila = 20;
	czas_trwania = 3;
	animowany = true;
	numer_boh = boh_num;
	cel = i;
	wyglad = SDL_LoadBMP("furia_Hulk.bmp");
}

void furia_Hulk::uzyj()
{
	if(animowany)
	{
		vPlayer[cel].hp+= sila;
		ile_minelo += delta;
		posx = vPlayer[cel].posx;
		posy = vPlayer[cel].posy;
		vPlayer[numer_boh].frame=9;
		Blituj(wyglad,SurBg,posx,posy);
		if(ile_minelo >= czas_trwania)
		{
			ile_minelo = 0;
			animowany = false;
		}
	}
}

////mlot_Thor funkcje//////////////////////////////
mlot_Thor::mlot_Thor()
{
	ile_minelo = 0;
	do_uzycia = true;
	czas_regeneracji = 2;
};

mlot_Thor::mlot_Thor(gracz& bohater,int boh_num)
{
	czas_trwania = 1;
	posx = bohater.posx;
	posy = bohater.posy;
	sila = 20;
	zasieg = 15;
	animowany = true;
	numer_boh = boh_num;
	cel = bohater.wybierz_cel(vEnemy,zasieg);
	atakuje = true;
	wyglad = SDL_LoadBMP("mlot_Thor.bmp");
}

void mlot_Thor::uzyj()
{
	if(animowany)
	{
		if(atakuje)
		{
			if(cel != -1)
				vEnemy[cel].hp -= sila;
			atakuje = false;
		}
		vPlayer[numer_boh].frame=5;
		Blituj(wyglad,SurBg,posx,posy);
		ile_minelo += delta;
		if(ile_minelo >= czas_trwania)
		{
			ile_minelo = 0;
			animowany = false;
		}
	}
}

////piorun_Thor funkcje///////////////////////////////
piorun_Thor::piorun_Thor()
{
	ile_minelo = 0;
	czas_regeneracji = 3;
	do_uzycia = true;
}

piorun_Thor::piorun_Thor(gracz& bohater,int boh_num)
{
	zasieg = 4000;
	cel = rand() % vEnemy.size();
	posx = vEnemy[cel].posx;
	posy = vEnemy[cel].posy - 700;
	ile_minelo = 0;
	numer_boh = boh_num;
	czas_trwania = 2;
	animowany = true;
	atakuje = true;
	wyglad = SDL_LoadBMP("piorun_Thor.bmp");
}

void piorun_Thor::uzyj()
{
	if(animowany)
	{
		if(atakuje)
		{
			vEnemy[cel].hp -= sila;
			atakuje = false;
		}
		vPlayer[numer_boh].frame=8;
		Blituj(wyglad,SurBg,posx,posy);
		ile_minelo += delta;
		if(ile_minelo >= czas_trwania)
		animowany = false;
	}
}

////lecznie_Thor funkcje////////////////////////
leczenie_Thor::leczenie_Thor()
{
	ile_minelo = 0;
	czas_regeneracji = 5;
	do_uzycia = true;
}

leczenie_Thor::leczenie_Thor(gracz& bohater,int boh_num)
{
	posx = bohater.posx;
	posy = bohater.posy;
	ile_minelo = 0;
	czas_trwania = 1;
	sila = 20;
	leczy = true;
	animowany = true;
	wyglad  = SDL_LoadBMP("leczenie_Thor.bmp");
}

void leczenie_Thor::uzyj()
{
	if(animowany)
	{
		if(leczy)
		{
			for(int i = 0; i < vPlayer.size(); i++)
				vPlayer[i].hp += sila;
		}
		
		if(ile_minelo < 0.5)
			Blituj(wyglad,SurBg,posx,posy);
			
		if(ile_minelo >= czas_trwania)
			animowany = false;
	}
}

//Gracz Funkcje/////////////////////////////////////////
void gracz::atakuj(int numer, int numer_gracza) 
{
	switch(klasa)
	{
		case ironman:
			if(numer == 1)
			if(Gkula_Iron.do_uzycia)
			{
				vAttack.push_back(new kula_Iron(*this,numer_gracza));
				Gkula_Iron.do_uzycia = false;
			}
			if(numer == 2)
			if(Glaser_Iron.do_uzycia)
			{
				vAttack.push_back(new laser_Iron(*this,numer_gracza));
				Glaser_Iron.do_uzycia = false;
			}
			if(numer == 3)
			if(Grakiety_Iron.do_uzycia)
			{
				vAttack.push_back(new rakiety_Iron(*this,numer_gracza));
				Grakiety_Iron.do_uzycia = false;
			}
		break;
		
		case hulk:
			if(numer == 1)
			if(Gobszarowy_Hulk.do_uzycia)
			{
				vAttack.push_back(new obszarowy_Hulk(*this,numer_gracza));
				Gobszarowy_Hulk.do_uzycia = false;
			}
			if(numer == 2)
			if(Gobszarowy_Hulk2.do_uzycia)
			{
				vAttack.push_back(new obszarowy_Hulk2(*this,numer_gracza));
				Gobszarowy_Hulk2.do_uzycia = false;
			}
			if(numer == 3)
			if(Gfuria_Hulk.do_uzycia)
			{
				vAttack.push_back(new furia_Hulk(*this,numer_gracza,numer_gracza));
				Gfuria_Hulk.do_uzycia = false;
			}
		break;
		
		case thor:
			if(numer == 1)
			if(Gmlot_Thor.do_uzycia)
			{
				vAttack.push_back(new mlot_Thor(*this,numer_gracza));
				Gmlot_Thor.do_uzycia = false;
			}
			if(numer == 2)
			if(Gpiorun_Thor.do_uzycia)
			{
				vAttack.push_back(new piorun_Thor(*this,numer_gracza));
				Gpiorun_Thor.do_uzycia = false;
			}
			if(numer == 3)
			if(Gleczenie_Thor.do_uzycia)
			{
				vAttack.push_back(new leczenie_Thor(*this,numer_gracza));
				Gleczenie_Thor.do_uzycia = false;
			}
		break;
	}
}


void gracz::sprawdz_ataki(double delta) //Sprawdzanie czy można użyć ataków
{
	if(klasa == ironman)
	{
		if(!Gkula_Iron.do_uzycia)
			Gkula_Iron.sprawdz_gotowosc(delta);
			
		if(!Glaser_Iron.do_uzycia)
			Glaser_Iron.sprawdz_gotowosc(delta);
		
		if(!Grakiety_Iron.do_uzycia)
			Grakiety_Iron.sprawdz_gotowosc(delta);
	}
	
	else if(klasa == hulk)
	{
		if(!Gobszarowy_Hulk.do_uzycia)
			Gobszarowy_Hulk.sprawdz_gotowosc(delta);
			
		if(!Gobszarowy_Hulk2.do_uzycia)
			Gobszarowy_Hulk2.sprawdz_gotowosc(delta);
			
		if(!Gfuria_Hulk.do_uzycia)
			Gfuria_Hulk.sprawdz_gotowosc(delta);
	}
	else if(klasa == thor)
	{
		if(!Gmlot_Thor.do_uzycia)
			Gmlot_Thor.sprawdz_gotowosc(delta);
		
		if(!Gpiorun_Thor.do_uzycia)
			Gpiorun_Thor.sprawdz_gotowosc(delta);
			
		if(!Gleczenie_Thor.do_uzycia)
			Gleczenie_Thor.sprawdz_gotowosc(delta);
	}
}

void gracz::regeneruj()
{
	if(okres_regeneracji <= kiedy_regeneracja)
	{
		hp += wartosc_regeneracji;
		kiedy_regeneracja = 0;
	}
	else
	{
		kiedy_regeneracja += delta;
	}
}

////Znajdywanie celów postac///////////
////znajdwywanie celow//////////////
vector<int> postac::wybierz_cel(int zasieg, vector<wrog>& cele)
{
	vector<int> wybrane_cele;
	int odleglosc;
	for(int i = 0; i < cele.size(); i++)
	{
		odleglosc = sqrt((pow(cele[i].posx - this->posx,double(2)) - pow(cele[i].posy - this->posy,double(2))));
		if(odleglosc <= zasieg)
			wybrane_cele.push_back(i);
	}
	return wybrane_cele;
}
int postac::wybierz_cel(vector<wrog>& cele, int zasieg)
{
	int cel = -1;
	double odleglosc;
	for(int i = 0; i < cele.size(); i++)
	{
		odleglosc = sqrt((pow(cele[i].posx - this->posx,double(2)) + pow(cele[i].posy - this->posy,double(2))));
		if(odleglosc <= zasieg)
		{
			cel  = i;
			break;
		}
	}
	return cel;
}
/////Wrog Funkcje///////////////////////////
void wrog::normal_atak(int i,int target_index)//normalny atak wrogow
{
        if(atakuje==0)
        {
                vPlayer[target_index].hp-=vEnemy[i].sila;
                vEnemy[i].cd_start=GlobalTime;
                atakuje=1;
        }
        if(GlobalTime-vEnemy[i].cd_start>vEnemy[i].normal_cd) atakuje=0;
}
void wrog::wyswietl_normal(int target_index, int i)//wsyswiatlanie animacji nowrmalnego ataku wrogow
{
        if(GlobalTime-vEnemy[i].cd_start<0.15)
        {
                SDL_Surface *temp;
                temp=IMG_Load("v/effects/lavahit.gif");
                Blituj(temp,SurBg,vPlayer[target_index].posx+20,vPlayer[target_index].posy+25);
                SDL_FreeSurface(temp);
        }
}
void wrog::ogluszeni(double ogluszony_start,int i)//sprawdzanie czy wrogowie sa ogluszeni
{
        if(vEnemy[i].ogluszony==1)
        {
                vEnemy[i].ogluszony_start+=delta;
                if(vEnemy[i].ogluszony_start>=vEnemy[i].czas_ogluszenia) 
                {
                        vEnemy[i].ogluszony=0;
                        vEnemy[i].ogluszony_start;
                }
        }
}
void wrog::wyswietl_stun(int enemyX,int enemyY,int i)//wyswietlanie stuna nad ogluszonm wrogiem
{
    SDL_Surface *temp;
    temp=IMG_Load("v/effects/stun.gif");
    Blituj(temp,SurBg,vEnemy[i].posx,vEnemy[i].posy-25);
    SDL_FreeSurface(temp);
}

void wrog::die(int i)//smierc wrogow
{
        if(vEnemy[i].hp<0)
        {
                smieci tmp=smieci(vEnemy[i].posx,vEnemy[i].posy);
                vSmieci.push_back(tmp);
                vEnemy.erase(vEnemy.begin()+i);
        }        
}
void Atak_wroga(int wrog_numer, int bohater_numer)//funkcja pomocnicza do strzalow wroga
{
        if(Gstrzal_wrog.do_uzycia)
        {
                vAttack.push_back(new strzal_wrog(bohater_numer, wrog_numer));
                Gstrzal_wrog.do_uzycia = false;
        }
        else if(!Gstrzal_wrog.do_uzycia)
        {
                Gstrzal_wrog.sprawdz_gotowosc(delta);
        }
}

void smieci::wyswietl(int i)//wyswietlanie cial
{
        Blituj(vSmieci[i].grafika,SurBg,vSmieci[i].posx,vSmieci[i].posy);
}
/////////////////////strzal wrogow
strzal_wrog::strzal_wrog()
{
        ile_minelo = 0;
        do_uzycia = 0;
        czas_regeneracji = 3;
}

strzal_wrog::strzal_wrog(int bohater_numer,int wrog_numer)
{
        posx = vEnemy[wrog_numer].posx;
        posy = vEnemy[wrog_numer].posy;
        poczatek = wrog_numer;
        koniec = bohater_numer;
        animowany = true;
        wyglad = IMG_Load("v/effects/rangehit2.gif");
}

void strzal_wrog::uzyj()
{
        if((posx > (vPlayer[koniec].posx -30) && posx < (vPlayer[koniec].posx + 30)) || (posy > (vPlayer[koniec].posy -30) && posy < (vPlayer[koniec].posy + 30)))
        {
                if(posx < vPlayer[koniec].posx) posx++;
                if(posx > vPlayer[koniec].posx) posx--;
                if(posy < vPlayer[koniec].posy) posy++;
                if(posy > vPlayer[koniec].posy) posy--;
        }
        else
        {
                animowany = false;
        }
        Blituj(wyglad,SurBg,posx,posy);
}
void gracz::die(int i)// smierc gracza
{
	if (vPlayer[i].hp<0)
	{
		smieci tmp=smieci(vPlayer[i].posx,vPlayer[i].posy);
		vSmieci.push_back(tmp);
		vPlayer.erase(vPlayer.begin()+i);
	}
}
