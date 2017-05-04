#include "SDL/SDL.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>
#include <fstream>
#include <iostream>
#include "config.h"
#include "klasy.hpp"

	#if defined(WINDOWS) || defined(WIN32) || defined(_WIN32)
#include<windows.h>
#endif
Uint8 * keystate = SDL_GetKeyState( NULL );
//--------------------------warstwy
int hspoints[10];
char hsname[10][3];
using namespace std;

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
Objplayer player;

enum eAppState
{
	logo_start,
	menu,
	game,
	highscore,
	you_lost,
	you_won,
	next_level,
};
int punkty;
eAppState AppState;
SDL_Surface *SurEkran=NULL;
SDL_Surface *charset=NULL;
SDL_Surface *SurBg=NULL;
SDL_Surface *SurEnemy=NULL;
SDL_Surface *SurFiltr=NULL;
SDL_Event zdarzenie;
SDL_Surface* fRect=NULL;
SDL_Surface* SurRain=NULL;

struct sHighscore
{
	int points;
	string name;
};



sHighscore HighscoreAdd;
SDL_Surface *Blood=NULL;
SDL_Surface* SurBlood=NULL;
bool fxPlayerBloodHit=false;
bool isLoaded=false;
int quit=0; 
int poziom=1;
int menu_pos=0;
double GlobalTime, WorldTime;
long double delta;
double temptime;
double LastEnemyShot=0;
double tHit=0;
int celnosc=100;
int ShotCount=1;
int HitCount=1;
int bron=1; // lewo - 1, prawo - 2
std::vector<int> rainy;
std::vector<int> rainx;

//----------------

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

void Zaladuj()
{
	Blood=NULL;
	player.HP=3;
	formacja.enemy_hp.clear();
	formacja.enemy_id.clear();
	formacja.shift=0;
	formacja.speed=formacja.speed*(1+poziom/4);
	string tmp;
	sprintf((char*)tmp.c_str(), "%d", poziom);
	string str = tmp.c_str();
	string ssfil="poziomy/"+str+".txt";
	string ssmap="poziomy/"+str+".bmp";
	char patch[255];
	char lokalizacja[255]="poziomy/1.bmp";
	for ( int i=0;i<ssmap.size();i++)
	{
	patch[i]=ssfil[i];
	lokalizacja[i]=ssmap[i];
	}
	lokalizacja[14]=NULL;
	patch[14]=NULL;
	
	SurBg=SDL_LoadBMP(lokalizacja);

	Blituj(SurBg,SurEkran, 0, 0);
	LoadFormation(patch);
	formacja.kierunek=prawo;
	formacja.posx=GlobalMarginX;
	formacja.posy=GlobalMarginY;
}
void DrawPlayer()
{
	if (player.AnimKier==halt)
	{
		player.surface=SDL_LoadBMP("animacje/gracz/0.bmp");
		SDL_SetColorKey(player.surface, SDL_SRCCOLORKEY, 0x2a2626);
		Blituj(player.surface, SurEkran, player.pos.x, player.pos.y);
		return;
	}
	if (player.AnimKier!=halt && (player.AnimTime==0 || (player.AnimTime+delta)+player.AnimFrameTime<=WorldTime))
	{
		player.AnimTime=WorldTime;
		player.frame++;	
		if (player.frame==9)
		{
			player.AnimKier=halt;
			player.frame=1;
		}
	}
	if (player.AnimKier==lewo)
	{
		switch ( player.frame )
		{
			case 1: player.surface=SDL_LoadBMP("animacje/gracz/l0.bmp"); break;
			case 2: player.surface=SDL_LoadBMP("animacje/gracz/l1.bmp"); break;
			case 3: player.surface=SDL_LoadBMP("animacje/gracz/l2.bmp"); break;
			case 4: player.surface=SDL_LoadBMP("animacje/gracz/l3.bmp"); break;
			case 5: player.surface=SDL_LoadBMP("animacje/gracz/l4.bmp"); break;
			case 6: player.surface=SDL_LoadBMP("animacje/gracz/l5.bmp"); break;
			case 7: player.surface=SDL_LoadBMP("animacje/gracz/l6.bmp"); break;
			case 8: player.surface=SDL_LoadBMP("animacje/gracz/l7.bmp"); break;
		}
	}
	if (player.AnimKier==prawo)
	{
		switch ( player.frame )
		{
			case 1: player.surface=SDL_LoadBMP("animacje/gracz/0p.bmp"); break;
			case 2: player.surface=SDL_LoadBMP("animacje/gracz/1p.bmp"); break;
			case 3: player.surface=SDL_LoadBMP("animacje/gracz/2p.bmp"); break;
			case 4: player.surface=SDL_LoadBMP("animacje/gracz/3p.bmp"); break;
			case 5: player.surface=SDL_LoadBMP("animacje/gracz/4p.bmp"); break;
			case 6: player.surface=SDL_LoadBMP("animacje/gracz/5p.bmp"); break;
			case 7: player.surface=SDL_LoadBMP("animacje/gracz/6p.bmp"); break;
			case 8: player.surface=SDL_LoadBMP("animacje/gracz/7p.bmp"); break;
		}

	}
	
		SDL_SetColorKey(player.surface, SDL_SRCCOLORKEY, 0x2a2626);
		player.przesun(player.AnimKier,8, delta);
		Blituj(player.surface, SurEkran, player.pos.x, player.pos.y);
}
void DrawShots() // Przesuwanie i wyswietlanie strzalow
{
	for ( int i=0;i<pocisk.typ.size();i++)
	{

		if ( pocisk.typ.empty()==false)
		{
		if (pocisk.posY[i]<0 && pocisk.typ[i]==Objpocisk::gracz ) // usuwanie pocisku z wektora, jesli wylecial za ekran
			{
				pocisk.usun(i);
				continue;
			}
		if (pocisk.posY[i]>=WindowSizeY && pocisk.typ[i]==Objpocisk::przeciwnik)
			{
				pocisk.usun(i);
				continue;
			}
		if ( pocisk.typ.empty()==false)
		{
			switch ( pocisk.typ[i] )
			{
				case Objpocisk::gracz:
				{
					pocisk.posY[i]=pocisk.posY[i]-pocisk.speed*delta*BulletSpeed; 
					pocisk.surface=SDL_LoadBMP("grafika/bullet.bmp");
					SDL_SetColorKey(pocisk.surface, SDL_SRCCOLORKEY, 0xFFFFFF);
					Blituj(pocisk.surface, SurEkran, pocisk.posX[i], pocisk.posY[i]);

					Tbulletexp.odlicz(delta);
					if (Tbulletexp.koniec==false)
					{
						SDL_Surface *sbullexp=NULL;
						sbullexp=SDL_LoadBMP("grafika/exp2.bmp");
						SDL_SetColorKey(sbullexp, SDL_SRCCOLORKEY, 0x6F6F6F);
						if (player.AnimKier==halt)
						{
							Blituj(sbullexp,SurEkran,player.pos.x-3,player.pos.y-30);
							Blituj(sbullexp,SurEkran,player.pos.x+29,player.pos.y-30);
						}
						if (player.AnimKier==lewo)
						{
							Blituj(sbullexp,SurEkran,player.pos.x+10,player.pos.y-30);
							Blituj(sbullexp,SurEkran,player.pos.x+39,player.pos.y-30);
						}
						if (player.AnimKier==prawo)
						{
							Blituj(sbullexp,SurEkran,player.pos.x+10,player.pos.y-30);
							Blituj(sbullexp,SurEkran,player.pos.x+49,player.pos.y-30);
						}

					}
				} break;

				case Objpocisk::przeciwnik:
				{
					if (pocisk.posY[i]+pocisk.imgsize.y+19>=player.pos.y && pocisk.posX[i]+pocisk.imgsize.x>=player.pos.x && pocisk.posX[i]+pocisk.imgsize.y<=player.pos.x+player.imgsize.x)
					{
						Blood=SDL_LoadBMP("animacje/bloodsplash.bmp");
						SDL_SetColorKey(Blood, SDL_SRCCOLORKEY, 0xff0000);
						Blituj(Blood,SurBg,pocisk.posX[i],pocisk.posY[i]+50);
						if (player.HP==3) tHit=1;
						if (player.HP==2) tHit=2;
						if (player.HP==1) tHit=3;
						pocisk.usun(i);
						player.HP--;
						fxPlayerBloodHit=true;
						if (player.HP==0) AppState=you_lost;
						continue;
					}
					if ( pocisk.typ.empty()==false)
					{
						pocisk.posY[i]=pocisk.posY[i]+pocisk.speed*delta*EnemyBulletSpeed; 
						pocisk.surface=SDL_LoadBMP("grafika/widly.bmp");
						SDL_SetColorKey(pocisk.surface, SDL_SRCCOLORKEY, 0xFFFFFF);
						Blituj(pocisk.surface, SurEkran, pocisk.posX[i], pocisk.posY[i]);
					}
				} break;
			}
		}
		}
	}
}
void DrawEnemies()
{	
	double DownLimit=0;
	bool StillAlive=false;
	formacja.shift=formacja.speed*delta;
	int DlugoscFormacji=(enemy1.imgsize.x+SpaceBDragsX)*6;
	switch (formacja.kierunek)
	{
		case prawo: 
		{
			formacja.posx+=formacja.shift; 
			
			if (formacja.posx>=WindowSizeX-GlobalMarginX-DlugoscFormacji) 
				formacja.kierunek=dol;
		}	break;
		case lewo: 	
		{
			formacja.posx-=formacja.shift; 
			if (formacja.posx<=GlobalMarginY) 
				formacja.kierunek=dol;
		}	break;
		case dol:
		{
			formacja.movingdown+=formacja.shift;
			formacja.posy+=formacja.shift;
			if (formacja.movingdown>=enemy1.imgsize.y+SpaceBDragsY)
			{
				if (formacja.posx+DlugoscFormacji+formacja.shift>=WindowSizeX-GlobalMarginX)
					formacja.kierunek=lewo;
				else
					formacja.kierunek=prawo;
				formacja.movingdown=0;
			}

		}	break;
	}

	int kolumna=0;
	int wiersz=0;
	bool DoIShot=false;

	srand ( time(NULL) );
	for ( int i=0;i<formacja.enemy_id.size();i++)
	{

		if (i%6==0) {kolumna++;	wiersz=0;}
		if (formacja.enemy_id[i]>0)
		{
			StillAlive=true;
			double x=formacja.posx+wiersz*(SpaceBDragsX+enemy1.imgsize.x);
			double y=formacja.posy+kolumna*(SpaceBDragsY+enemy1.imgsize.y);
			int randx=rand()%1000;
			if (randx<=shot_chance && (LastEnemyShot+1<WorldTime || LastEnemyShot==0))
			{
				LastEnemyShot=WorldTime;
				pocisk.dodaj(Objpocisk::przeciwnik, 0, x+30, y);
			}
			for ( int q=0;q<pocisk.posX.size();q++)
			{
				if ( pocisk.typ[q]==Objpocisk::gracz && pocisk.posX[q]+pocisk.imgsize.x>=x && pocisk.posX[q]<=(x+enemy1.imgsize.x) && pocisk.posY[q]>=y && pocisk.posY[q]<=y+enemy1.imgsize.y)
				{
					HitCount++;
					int randBlood=rand()%2;
					if (randBlood==1)	Blood=SDL_LoadBMP("animacje/bloodsplash.bmp");
					if (randBlood==0)	Blood=SDL_LoadBMP("animacje/bloodsplash2.bmp");
					SDL_SetColorKey(Blood, SDL_SRCCOLORKEY, 0xff0000);
					Blituj(Blood,SurBg,pocisk.posX[q]-30,pocisk.posY[q]-30);

					
					if (formacja.enemy_hp[i]>0)
					formacja.enemy_hp[i]--;
					if (formacja.enemy_hp[i]==0)
					{
					if (formacja.enemy_id[i]==1)	Blood=SDL_LoadBMP("grafika/corpse.bmp");
					if (formacja.enemy_id[i]==2)	Blood=SDL_LoadBMP("grafika/corpse2.bmp");
					SDL_SetColorKey(Blood, SDL_SRCCOLORKEY, 0x2e0f00);
					Blituj(Blood,SurBg,pocisk.posX[q]-50,pocisk.posY[q]-50);
						formacja.enemy_id[i]=0;
						punkty+=10;
					}
					pocisk.usun(q);

				}
			}
			if (y+enemy1.imgsize.x>WindowSizeY-DeadLine) AppState=you_lost;
			switch (formacja.enemy_id[i])
			{
				case 1: Blituj(enemy1.surAlive, SurEkran, x, y); break;
				case 2:	Blituj(enemy2.surAlive, SurEkran, x, y); break;
			}
			
		}
		wiersz++;
	}
	if (StillAlive==false && poziom<5) AppState=next_level;
	if (StillAlive==false && poziom==5) AppState=you_won;
}
void State_game()
{
			if (isLoaded==false)
			{
			Zaladuj();
			isLoaded=true;
			}
		player.shift=ceil(player.speed*delta); // przesuniecie gracza
		while( SDL_PollEvent( & zdarzenie ) )
		{
			if( zdarzenie.type == SDL_QUIT ) quit = true;
			if( zdarzenie.type == SDL_KEYDOWN )
			{
                switch( zdarzenie.key.keysym.sym )
                {
				case SDLK_ESCAPE:
					AppState=menu; break;
				}
			}
		}
        if( keystate[ SDLK_RIGHT ] ) // przesuwanie w prawo
		{
			player.AnimKier=prawo;
		} 
		if (keystate[ SDLK_LEFT] ) // przesuwanie w lewo
		{
			player.AnimKier=lewo;
		}
		if (keystate [SDLK_SPACE])
		{
			if ( pocisk.LastShotTime==0 || pocisk.LastShotTime+1/ShotsPerSec<WorldTime) // jesli oddajemy pierszy strzal lub minal okreslony czas, to
			{
				ShotCount=ShotCount+2;
				Tbulletexp.zegarek=0.3;
				pocisk.LastShotTime=WorldTime;
				int x=player.pos.x;
				int y=player.pos.y;
					pocisk.dodaj(Objpocisk::gracz,1, x-2, y);
					pocisk.dodaj(Objpocisk::gracz,2, x-5, y);
			}
		}	
		char text[128];
		char cPlayerHP[128];
		char ccelnosc[128];
		celnosc=100*HitCount/(ShotCount);
		sprintf(text,"%d",punkty);
		sprintf(cPlayerHP,"%d",player.HP);
		sprintf(ccelnosc,"%d",celnosc);
		Blituj(SurBg, SurEkran, 0, 0);	
		Blituj(SurBlood,SurEkran, 0, 0);
		DrawEnemies();								// rysuj przeciwnikow									// rysuj pociski
		DrawPlayer();
		DrawShots();
		DrawString(SurEkran, WindowSizeX / 2 - strlen(text) * 8 / 2, 10, text, charset);
		DrawString(SurEkran, WindowSizeX / 2 - strlen(text) * 8 / 2, 25, cPlayerHP, charset);
		DrawString(SurEkran, WindowSizeX / 2 - strlen(text) * 8 / 2, 40, ccelnosc, charset);
				if (fxPlayerBloodHit==true)
		{
			SurFiltr=SDL_LoadBMP("filtry/playerblood.bmp");
			SDL_SetColorKey(SurFiltr, SDL_SRCCOLORKEY, 0xFF0000);
			tHit=tHit-delta;
			SDL_SetAlpha(SurFiltr, SDL_SRCALPHA, 255*tHit);
			if (tHit<=0) 
				{
					fxPlayerBloodHit=false;
					SurFiltr=NULL;
				}

		}
		//SDL_FillRect(fRect,NULL,0xFF0000);
	//	SDL_SetAlpha(fRect, SDL_SRCALPHA, 100);
		Blituj(SurFiltr, SurEkran, 0, 0);
		}
void State_logo_start()
{
			SDL_Surface *Surlogo_start;
			Surlogo_start=SDL_LoadBMP("appstate/logostart.bmp");
			SDL_BlitSurface(Surlogo_start, NULL, SurEkran, NULL);
			Tlogo_start.odlicz(delta);
			if (Tlogo_start.koniec==true)
			{
				Surlogo_start=SDL_LoadBMP("appstate/press_enter.bmp");
				SDL_SetColorKey(Surlogo_start, SDL_SRCCOLORKEY, 0x151515);
				Blituj(Surlogo_start, SurEkran, 155, 500);
				while( SDL_PollEvent( & zdarzenie ) )
				{
					if( zdarzenie.type == SDL_KEYDOWN )
					
					{
						switch( zdarzenie.key.keysym.sym )
						{
							case SDLK_RETURN: 
								{
									AppState=menu; 
									SDL_FreeSurface(Surlogo_start);
								}	break;
							case SDLK_ESCAPE: quit=true; break;
						}
					}
				}
				
			}
}
void State_next_level()
{
	isLoaded=false;
			SDL_Surface* lostscreen=NULL;
			lostscreen=SDL_LoadBMP("appstate/next_level.bmp");
			Blituj(lostscreen,SurEkran,65,152);
			while( SDL_PollEvent( & zdarzenie ) )
			{
				if( zdarzenie.type == SDL_QUIT ) quit = true;
				if( zdarzenie.type == SDL_KEYDOWN )
				{
					switch( zdarzenie.key.keysym.sym )
					{
						case SDLK_ESCAPE:	AppState=menu;	break;
						case SDLK_RETURN:	
							{
								poziom++;
								punkty+=1000;
								AppState=game;	
							}	break;
					}
				}
			}
}
void State_you_won()
{
			isLoaded=false;
			SDL_Surface* lostscreen=NULL;
			lostscreen=SDL_LoadBMP("appstate/gamewon.bmp");
			Blituj(lostscreen,SurEkran,65,152);
			while( SDL_PollEvent( & zdarzenie ) )
			{
				if( zdarzenie.type == SDL_QUIT ) quit = true;
				if( zdarzenie.type == SDL_KEYDOWN )
				{
					switch( zdarzenie.key.keysym.sym )
					{
						case SDLK_ESCAPE:	AppState=menu;	break;
						case SDLK_RETURN:	
							{
								//poziom++;
								AppState=menu;	
							}	break;
					}
				}
			}
}
void State_menu()
{
			poziom=1;
			formacja.speed=predkoscformacji;
			SDL_Surface *Surmenu=NULL;
			Surmenu=SDL_LoadBMP("appstate/menu/bg.bmp");
			
			Blituj(Surmenu, SurEkran, 0, 0);


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
						case SDLK_RETURN:	
											{
												if (menu_pos==0)
													AppState=game;
												if(menu_pos==2)
													quit=true;
											};			break;
						}
					}
				}
			if ( menu_pos>2) menu_pos=2;
			if ( menu_pos<0) menu_pos=0;
			if ( menu_pos==0)
			{
				Surmenu=SDL_LoadBMP("appstate/menu/newgame.bmp");
				SDL_SetColorKey(Surmenu, SDL_SRCCOLORKEY, 0xFFFFFF);
				Blituj(Surmenu, SurEkran, 0, 143);
				Surmenu=SDL_LoadBMP("appstate/menu/rekordy3.bmp");
				SDL_SetColorKey(Surmenu, SDL_SRCCOLORKEY, 0xFFFFFF);
				Blituj(Surmenu, SurEkran, 0, 262);
				Surmenu=SDL_LoadBMP("appstate/menu/wyjscie4.bmp");
				SDL_SetColorKey(Surmenu, SDL_SRCCOLORKEY, 0xFFFFFF);
				Blituj(Surmenu, SurEkran, 0, 382);
			}
			if ( menu_pos==1)
			{
				Surmenu=SDL_LoadBMP("appstate/menu/newgame2.bmp");
				SDL_SetColorKey(Surmenu, SDL_SRCCOLORKEY, 0xFFFFFF);
				Blituj(Surmenu, SurEkran, 0, 143);
				Surmenu=SDL_LoadBMP("appstate/menu/rekordy.bmp");
				SDL_SetColorKey(Surmenu, SDL_SRCCOLORKEY, 0xFFFFFF);
				Blituj(Surmenu, SurEkran, 0, 262);
				Surmenu=SDL_LoadBMP("appstate/menu/wyjscie4.bmp");
				SDL_SetColorKey(Surmenu, SDL_SRCCOLORKEY, 0xFFFFFF);
				Blituj(Surmenu, SurEkran, 0, 382);
			}
			if ( menu_pos==2)
			{
				Surmenu=SDL_LoadBMP("appstate/menu/newgame2.bmp");
				SDL_SetColorKey(Surmenu, SDL_SRCCOLORKEY, 0xFFFFFF);
				Blituj(Surmenu, SurEkran, 0, 143);
				Surmenu=SDL_LoadBMP("appstate/menu/rekordy3.bmp");
				SDL_SetColorKey(Surmenu, SDL_SRCCOLORKEY, 0xFFFFFF);
				Blituj(Surmenu, SurEkran, 0, 262);
				Surmenu=SDL_LoadBMP("appstate/menu/wyjscie.bmp");
				SDL_SetColorKey(Surmenu, SDL_SRCCOLORKEY, 0xFFFFFF);
				Blituj(Surmenu, SurEkran, 0, 381);
			}
			Surmenu=SDL_LoadBMP("appstate/menu/index.bmp");
			SDL_SetColorKey(Surmenu, SDL_SRCCOLORKEY, 0x00FF00);
			Blituj(Surmenu, SurEkran, 367, 142);
			SDL_FreeSurface(Surmenu);

}
void State_you_lost()
{
	{
			isLoaded=false;
			SDL_Surface* lostscreen=NULL;
			lostscreen=SDL_LoadBMP("appstate/gamelost2.bmp");
			Blituj(lostscreen,SurEkran,65,152);
			if (Tlost.koniec==true) AppState=menu;
			while( SDL_PollEvent( & zdarzenie ) )
			{
				if( zdarzenie.type == SDL_QUIT ) quit = true;
				if( zdarzenie.type == SDL_KEYDOWN )
				{
					switch( zdarzenie.key.keysym.sym )
					{
						case SDLK_ESCAPE:	AppState=menu;	break;
						case SDLK_RETURN:	AppState=menu;	break;
					}
				}
			}
		}
}
void AnimujDeszcz()
{
	SurRain=SDL_LoadBMP("filtry/raindrop.bmp");
	SDL_SetColorKey(SurRain, SDL_SRCCOLORKEY, 0x6a97ff);
	srand( time(NULL) );
		int Ranrainy=rand()%640+1;
		int Ranrainx=rand()%400;
		if (rainy.size()<5); 
		{
			rainy.push_back(Ranrainy);
			rainx.push_back(Ranrainx);
		}
	for ( int i=0;i<rainx.size();i++)
	{
		rainy[i]=rainy[i]+ceil(delta);
			Blituj(SurRain,SurEkran,rainx[i] ,ceil((double)rainy[i]));
			if (rainy[i]>=400)
			{
				rainy.erase(rainy.begin()+i);
				rainx.erase(rainx.begin()+i);
				continue;
			}

	}

}
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
int main(int argc, const char **argv) 
{
	// -------------------------------------INICJACJA--------------------------------------
	SDL_Init( SDL_INIT_EVERYTHING );
	AppState=logo_start;
    SurEkran =SDL_SetVideoMode( WindowSizeX, WindowSizeY, 32, SDL_SWSURFACE );
	SDL_WM_SetCaption( "Filip Biedrzycki, 137248", NULL );
	enemy1.health=1;
	enemy2.health=3;
	enemy1.totalframe=12;
	enemy2.totalframe=12;
	LoadClassGraph();
//	SDL_FillRect(SurFiltr, NULL, 0x000000);
//	SDL_SetAlpha(SurFiltr, SDL_SRCALPHA, 100);
	Tlogo_start.zegarek=1;
	SurBg=SDL_LoadBMP("poziomy/1.bmp");
	//SDL_SetAlpha(SurBg, SDL_SRCALPHA, 1); 
	charset=SDL_LoadBMP("CS8X8.BMP");
	SDL_SetColorKey(charset, SDL_SRCCOLORKEY, 0x000000);
	// Liczenie czasu dzialania aplikacji i uplynietego od ostatniego rysowania ekranu
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
			case you_won:		State_you_won();	break;
			case you_lost:		State_you_lost();	break;
			case next_level:	State_next_level(); break;
			case game:			State_game();		break;
		}
		SDL_Flip(SurEkran);
	};
	SDL_Quit();
	return 0;
};
