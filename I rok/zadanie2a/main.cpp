/*
Projekt 2a - Space Invaders
autor: Filip Biedrzycki
nr albumu: 137248
*/
extern "C" {
#include"SDL.h"
}
#define _USE_MATH_DEFINES
#include <cstdlib> 
#include<math.h>
#include<stdio.h>
#include<string.h>
#include <time.h>
#include <vector>
#if defined(WINDOWS) || defined(WIN32) || defined(_WIN32)
#include<windows.h>
#endif
Uint8 * keystate = SDL_GetKeyState( NULL );
//--------------------------warstwy
SDL_Surface *SurEkran=NULL;
SDL_Surface *SurGracz=NULL;
SDL_Surface *SurBg=NULL;
SDL_Surface *SurPocisk=NULL;
SDL_Surface *SurDragon=NULL;
//---------------------------------
std::vector<double> pociskX;	// wspolrzedne X pociskow
std::vector<double> pociskY;	// wspolrzedne Y pociskow
std::vector<int> 	pociskT;		// typ pocisku ( 0 - oginisty, 1 - lodowy )

//-------------Obszary do wklejania na warstwy dla smoka, gracza i pocisku
SDL_Rect RDrag;
SDL_Rect RGracz;
SDL_Rect RStrzal;
//-----------------
const int iloscklatek=12; // ilosc klatek animacji przeciwnikow
// Zmienne pomocnicze	
int quit; // decyduje o wyjsciu z programu
int CurrentShiftX;			// odlegosc smokow od wartosci poczatkowej w osi X
int CurrentShiftY;			// odleglosc smokow od wartosci poczatkowej w osi Y
int DragFrame[6][6];			// nr aktualnej klatki animacji dla kazdego smoka
int TypeOfPocisk; 			// aktualnie strzelany typ pocisku ( 0 - ognisty, 1 - lodowy )
int kierunek;					// kierunek poruszania sie formacji smokow: 0 - w prawo, 1 - w lewo
double GlobalTime, WorldTime;	// czas dzialania aplikacji
double DragAnimControl;		// pilnowanie plynnosci animacji
double LastShotTime;			// czas oddania ostatniego strzalu
//----------------
// Deklaracja rozmiarow bitmap
const int PlayerBMPsize_X=90;
const int PlayerBMPsize_Y=60;
const int DragonBMPsize_X=60;
const int DragonBMPsize_Y=52;
const int PociskBMPsize_X=27;
const int PociskBMPsize_Y=39;
//-------------
// Stale do sterowania aplikacja
const double DragonSpeed=0.2; 	// predkosc poczatkowa smokow
const double DragonAccRatio=2; 	// wspolczynnik przyspieszenia 
const double PlayerSpeed=1.0;	// predkosc przesuwania sie gracza
const double BulletSpeed=1.5;	// predkosc pociskow
const double ShotsPerSec=3;		// ilosc strzalow mozliwych do oddania na sekunde
const double DragAnimSpeed=0.04;// czas odtwarzania kazdej klatki
const int WindowSizeX=640;
const int WindowSizeY=640;
const int GlobalMarginX=5;		// margines z prawej i lewej strony ekranu, oddzialuje na wszystko poza strzalami
const int GlobalMarginY=5;		// margines z gory i dolu, odzialuje na wszystko poza strzalami
const int SpaceBDragsX=-10;		// odeglosc X miedzy smokami w formacji
const int SpaceBDragsY=-10;   	// odeglosc Y miedzy smokami w formacji
//-------------
void DrawShots(double delta) // Przesuwanie i wyswietlanie strzalow
{
	for ( int i=0;i<pociskY.size();i++)
	{
		if (pociskY[i]+PociskBMPsize_Y-300*delta*BulletSpeed<0) // usuwanie pocisku z wektora, jesli wylecial za ekran
		{
			pociskY.erase(pociskY.begin()+i);
			pociskX.erase(pociskX.begin()+i);
			pociskT.erase(pociskT.begin()+i);
		}

		if ( pociskY.empty()==false) // przesuwanie strzalu, jesli w wektorach sa jakies elementy
		{
		pociskY[i]=pociskY[i]-300*delta*BulletSpeed; 
		RStrzal.x=pociskX[i];
		RStrzal.y=pociskY[i];
		if ( pociskT[i]==0)
			SurPocisk=SDL_LoadBMP("grafika/pocisk.bmp");
		else
			SurPocisk=SDL_LoadBMP("grafika/pociskfrost.bmp");
		SDL_SetColorKey(SurPocisk, SDL_SRCCOLORKEY, 0x000000);
		SDL_BlitSurface(SurPocisk,NULL,SurEkran,&RStrzal);
		}
	}
} // rysowanie wszystkich strzalow na ekranie
void AddShotToVector() // dodanie nowego strzalu do wektora
	 {
		 pociskX.push_back(RGracz.x+(PlayerBMPsize_X-PociskBMPsize_X)/2);
		 pociskY.push_back(WindowSizeY-(PlayerBMPsize_Y+GlobalMarginY));
		 pociskT.push_back(TypeOfPocisk);
	 } // dodawanie strzalow do wektora strzalow
void EnemyMovement (double delta )
{ 
	double TempTime=DragonAccRatio*WorldTime/50;
	if (TempTime<1) TempTime=1;
	double NextMove=delta*150*DragonSpeed+TempTime; // wartosc przesuniecia formacji
	int LastDragX=(DragonBMPsize_X+SpaceBDragsX)*6; // szerokosc calej formacji
	if (LastDragX+CurrentShiftX+NextMove+GlobalMarginX>=WindowSizeX && kierunek==0) // jest smoki sa przy prawej krawedzi ekranu, to:
	{
		CurrentShiftY=CurrentShiftY+DragonBMPsize_Y;			// obnizenie formacje o wysokosc smoka								
		kierunek=1;											// zmiana kierunku
	}
	if (CurrentShiftX-NextMove*0.75-GlobalMarginX<=0 && kierunek==1) // to samo, ale dla lewej krawedzi
	{
		CurrentShiftY=CurrentShiftY+DragonBMPsize_Y;
		kierunek=0;	 
	}
	switch (kierunek)// w zaleznosci od kierunku przesuniecie formacji:
	{	
		case 0: CurrentShiftX+=NextMove; break;			// w prawo ( dodawanie wartosci )
		case 1: CurrentShiftX-=NextMove*0.75; break;	// w lewo ( odejmowanie )
	}

	DragAnimControl+=delta; // dodawanie czasu uplynietego od ostatniego wywolania funkcji by sprawdzic, czy nalezy zmienic klatke animacji
	RDrag.y=CurrentShiftY+GlobalMarginY; // ustawienie pozycji smoka Y
	if (RDrag.y+6*(DragonBMPsize_Y+SpaceBDragsY)>WindowSizeY-PlayerBMPsize_Y-GlobalMarginY) // dojscie formacji do pozycji gracza zamyka aplikacje
	{
		quit=true;
		return;
	}
	for ( int i=0;i<6;i++) // glowna petla rysuja smoki na ekran
	{
		for ( int ii=0;ii<6;ii++)
		{
			
			RDrag.x=(DragonBMPsize_X+SpaceBDragsX)*ii+CurrentShiftX;// obliczanie lokalizacji X smoka nr ii w kolumnie nr i
			switch (DragFrame[i][ii]) // wybieranie odpowiedniej klatki animacji
			{
				case 0:	SurDragon=SDL_LoadBMP("grafika/dragon/Dragon1_0011_Warstwa 1.bmp");	break;
				case 1:	SurDragon=SDL_LoadBMP("grafika/dragon/Dragon1_0010_Warstwa 2.bmp");	break;
				case 2:	SurDragon=SDL_LoadBMP("grafika/dragon/Dragon1_0009_Warstwa 3.bmp");	break;
				case 3:	SurDragon=SDL_LoadBMP("grafika/dragon/Dragon1_0008_Warstwa 4.bmp");	break;
				case 4:	SurDragon=SDL_LoadBMP("grafika/dragon/Dragon1_0007_Warstwa 5.bmp");	break;
				case 5:	SurDragon=SDL_LoadBMP("grafika/dragon/Dragon1_0006_Warstwa 6.bmp");	break;
				case 6:	SurDragon=SDL_LoadBMP("grafika/dragon/Dragon1_0005_Warstwa 7.bmp");	break;
				case 7:	SurDragon=SDL_LoadBMP("grafika/dragon/Dragon1_0004_Warstwa 8.bmp");	break;
				case 8:	SurDragon=SDL_LoadBMP("grafika/dragon/Dragon1_0003_Warstwa 9.bmp");	break;
				case 9:	SurDragon=SDL_LoadBMP("grafika/dragon/Dragon1_0002_Warstwa 10.bmp");break;
				case 10:SurDragon=SDL_LoadBMP("grafika/dragon/Dragon1_0001_Warstwa 11.bmp");break;
				case 11:SurDragon=SDL_LoadBMP("grafika/dragon/Dragon1_0000_Warstwa 12.bmp");break;
			}

			SDL_SetColorKey(SurDragon, SDL_SRCCOLORKEY, 0x000000);
			SDL_BlitSurface(SurDragon,NULL,SurEkran,&RDrag); // rysowanie smoka [i][ii] na ekran

			if (DragAnimControl>DragAnimSpeed) // sprawdzanie, czy uplynal czas, aby wyswietlic kolejna klatke animacji
			{
				DragFrame[i][ii]=(DragFrame[i][ii]+1)%iloscklatek;// zmiana klatki na kolejna
				 // liczenie czasu od nowa
			}
		}
		RDrag.y+=DragonBMPsize_Y+SpaceBDragsY; // przesuwamy sie wiersz nizej 
	}
	if ( DragAnimControl>DragAnimSpeed) // sprawdzenie, czy nalezy liczyc czas do kolejnej klatki od nowa
	DragAnimControl=0;


	 }// przesuwanie i wyswietlanie formacji smokow
// WinMain
#if defined(WINDOWS) || defined(WIN32) || defined(_WIN32)
int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR str, int show) {
#else
int main(int argc, const char **argv) {
#endif
	// -------------------------------------INICJACJA--------------------------------------
	SDL_Init( SDL_INIT_EVERYTHING );
    SurEkran =SDL_SetVideoMode( WindowSizeX, WindowSizeY, 24, SDL_SWSURFACE );
	SDL_WM_SetCaption( "Skyrim Invaders, Filip Biedrzycki, 137248, 2A", NULL );
	SDL_Event zdarzenie;
	//--------------------
	// Zapelnianie tablicy przeciwnikow losowymi klatami poczatkujacymi
	srand ( time(NULL) );
	for ( int i=0;i<6;i++)
	{
		for ( int ii=0;ii<6;ii++)
		DragFrame[i][ii]=rand()%iloscklatek;
	}
	// -------------------------------------
	RGracz.x=WindowSizeX/2; 
	RGracz.y=WindowSizeY-PlayerBMPsize_Y-GlobalMarginY;
	SurBg=SDL_LoadBMP("grafika/background.bmp");
	SurGracz=SDL_LoadBMP("grafika/dovakiin.bmp");
	SDL_SetColorKey(SurGracz, SDL_SRCCOLORKEY, 0xFFFFFF);
	// Liczenie czasu dzialania aplikacji i uplynietego od ostatniego rysowania ekranu
	GlobalTime=SDL_GetTicks();
		while(!quit)
	{
		double TempTime=SDL_GetTicks();
		double delta=(TempTime-GlobalTime)*0.001; // czas uplyniety od ostatniego rysowania ekranu
		GlobalTime=TempTime;
		WorldTime+=delta;
	//--------------------------
		double PlayerShift=350*delta*PlayerSpeed; // przesuniecie gracza
		while( SDL_PollEvent( & zdarzenie ) )
		{
			if( zdarzenie.type == SDL_QUIT ) quit = true;
			if( zdarzenie.type == SDL_KEYDOWN )
			{
                switch( zdarzenie.key.keysym.sym )
                {
				case SDLK_a:						// jesli nacisniemy klawisz [a], to zmieniamy typ pocisku
					{
						if ( TypeOfPocisk==0)
						TypeOfPocisk=1;
						else 
						TypeOfPocisk=0;
					}; break;
				case SDLK_ESCAPE: 
						quit=true; break;
				}
			}
		}
        if( keystate[ SDLK_RIGHT ] && RGracz.x+GlobalMarginX+PlayerBMPsize_X<WindowSizeX ) // przesuwanie w prawo
		{
			RGracz.x+=PlayerShift;
		}
		if (keystate[ SDLK_LEFT] && RGracz.x-GlobalMarginX>0 ) // przesuwanie w lewo
			RGracz.x-=0.75*PlayerShift;
		if (keystate [SDLK_SPACE])
		{
			if ( LastShotTime==0 || LastShotTime+1/ShotsPerSec<WorldTime) // jesli oddajemy pierszy strzal lub minal okreslony czas, to
			{
			LastShotTime=WorldTime;
			AddShotToVector();
			}
		}
		SDL_BlitSurface(SurBg,NULL,SurEkran,NULL);			// rysuj tlo		
		EnemyMovement(delta);								// rysuj przeciwnikow
		DrawShots(delta);									// rysuj pociski
		SDL_BlitSurface(SurGracz,NULL,SurEkran,&RGracz);	// rysuj gracza
		SDL_Flip( SurEkran );								// wyswietl wszystko
	};
	SDL_Surface *GameOver = NULL;
	GameOver=SDL_LoadBMP("grafika/gameover.bmp");
	SDL_BlitSurface(GameOver, NULL, SurEkran, NULL);
	SDL_Flip( SurEkran);
	SDL_Delay(1000);
	SDL_Quit();
	return 0;
};
