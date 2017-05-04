#ifndef stale_hpp
#define stale_hpp
	
// Deklaracja rozmiarow bitmap
//-------------
// Stale do sterowania aplikacja
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
const int SpaceBDragsY=-25;   // odeglosc Y miedzy smokami w formacji
//-------------
#endif
