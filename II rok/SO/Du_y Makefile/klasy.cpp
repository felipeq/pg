#include "klasy.hpp"
#include <math.h>

const double DragonSpeed=1; // predkosc poczotkowa smokow
const double DragonAccRatio=1; // wspolczynnik przyspieszenia 
const double PlayerSpeed=1.5;
const double BulletSpeed=1.5;
const double EnemyBulletSpeed=0.3;
const double ShotsPerSec=5;
const int DeadLine=95;
const int FPS=12;
const int GlobalAnimFrameTime=0.01;
const int shot_chance=25; //10 - 1%
const int predkoscformacji=35;
const int predkoscstrzelania=500;
const int WindowSizeX=640;
const int WindowSizeY=640;
const int GlobalMarginX=5;	// margines z prawej i lewej strony ekranu, oddzialuje na wszystko poza strzalami
const int GlobalMarginY=5;	//margines z gory i dolu, odzialuje na wszystko poza strzalami
const int SpaceBDragsX=-20;	// odeglosc X miedzy smokami w formacji
const int SpaceBDragsY=-25;
void Objpocisk::dodaj(Etype typik, int bron, int x, int y)
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
void Objpocisk::usun(int i)
	{
		posY.erase(posY.begin()+i);
		posX.erase(posX.begin()+i);
		typ.erase(typ.begin()+i);
		
	}
Objpocisk::Objpocisk()
{
	imgsize.x=15;
	imgsize.y=60;
	speed=predkoscstrzelania;
	SelectedTyp=gracz;	
}
void Objform::delete_enemy(int i)
	{
		enemy_id.erase(enemy_id.begin()+i);
		enemy_hp.erase(enemy_hp.begin()+i);
	}

Objform::Objform()
{
	posx=GlobalMarginX;
	posy=GlobalMarginY;
	kierunek=prawo;
	speed=predkoscformacji;
	movingdown=0;
}
void Objplayer::przesun(eKier kierunek, int dzielnikR, double delta)
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
Objtimer::Objtimer()
{
	zegarek=0;
	koniec=false;
}
void Objtimer::odlicz(double delta)	// odejmowanie delty od zegarka, az koniec bedzie true
	{
		zegarek=zegarek-delta;
		if (zegarek<=0)
			koniec=true;
		if (zegarek>0)
			koniec=false;
	};



