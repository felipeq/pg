#ifndef config_h
#define config_h
	
// Deklaracja rozmiarow bitmap
//-------------

// Stale do sterowania aplikacja
extern const double DragonSpeed=1; // predkosc poczotkowa smokow
extern const double DragonAccRatio=1; // wspolczynnik przyspieszenia 
extern const double PlayerSpeed=1.5;
extern const double BulletSpeed=1.5;
extern const double EnemyBulletSpeed=0.3;
extern const double ShotsPerSec=5;
extern const int DeadLine=95;
extern const int FPS=12;
extern const int GlobalAnimFrameTime=0.01;
extern const int shot_chance=25; //10 - 1%
extern const int predkoscformacji=35;
extern const int predkoscstrzelania=500;
extern const int WindowSizeX=640;
extern const int WindowSizeY=640;
extern const int GlobalMarginX=5;	// margines z prawej i lewej strony ekranu, oddzialuje na wszystko poza strzalami
extern const int GlobalMarginY=5;	//margines z gory i dolu, odzialuje na wszystko poza strzalami
extern const int SpaceBDragsX=-20;	// odeglosc X miedzy smokami w formacji
extern const int SpaceBDragsY=-25;   // odeglosc Y miedzy smokami w formacji
//-------------

#endif
