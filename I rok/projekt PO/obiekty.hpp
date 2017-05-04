/* Dopisany wybór ataku, kod wyboru ataków, argumenty wyboru celow, kod wyboru celów(inny postac, inny wojownik), atak postaci, zakres w umiejetnosc i postac zmieniony na protected*/

#ifndef obiekty_hpp
#define obiekty_hpp
#include <SDL.h>
#include<fstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib> 
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <iostream>

using namespace std;

//////////////////Stałe///////////////////////
enum kierunek{gora, dol,lewo,prawo};
kierunek kierunek_ruchu;
/////////////Deklaracje///////////////////////
class postac;
class gracz;
class wrog;
class umiejetnosc;
class normalny_atak;
class leczenie;
class wybawienie;
class podwojenie;
class blink;
class trzesienie;
class kamienna_skora;
class magiczna_kula;
class piorun_slaby;
class piorun_mocny;
class kula_energii;
class kula_ognia;
class ognisty_deszcz;
int WysEkranu=640;
int SzerEkranu=480;
class umiejetnosc
{
public:
	virtual void uzyj(postac&,bool czy_atakuje = true);//Moze lepiej dac tablice wskaznikow na cele

protected:
	int zasieg;
	int sila;
	int czas_regeneracji;
	//tablica klatek animacji lot;
	//tablca klatek animacji uderzenie;
	//obrazek na pasek stanu
};
class normalny_atak: public umiejetnosc
{
public:
	normalny_atak()
	{
		zasieg = 10;
		sila = 20;
		czas_regeneracji = 3;
	}
	~normalny_atak();
	void uzyj(postac&,bool czy_atakuje = true);
};

class leczenie:public umiejetnosc  ///Mag
{
public:
	//leczenie();
	//~leczenie();
	void uzyj(postac&,bool czy_atakuje = true);
};

class wybawienie:public umiejetnosc
{
public:
	wybawienie();
	~wybawienie();
	void uzyj(postac&,bool czy_atakuje = true);
	//ujemna wartosc sily
};

class podwojenie : public umiejetnosc
{
public:
	podwojenie();
	~podwojenie();
	void uzyj(postac&,bool czy_atakuje = true);
};

class blink : public umiejetnosc
{
public:
	blink();
	~blink();
	void uzyj(postac&,bool czy_atakuje = true);
	
private:
	int cel_skoku(); //Pojwienie sie celownika okreslajacego miejsce skoku
};

class trzesienie : public umiejetnosc
{
public:
	trzesienie();
	~trzesienie();
	void uzyj(postac&,bool czy_atakuje = true);
};

class kamienna_skora : public umiejetnosc
{
public:
	kamienna_skora();
	~kamienna_skora();
	void uzyj(postac&,bool czy_atakuje = false);
private:
	int czas_dzialania;  // Wymyslic sposob na usuniecie wplywu funkcji
};

class magiczna_kula : public umiejetnosc
{
public:
	magiczna_kula();
	~magiczna_kula();
	void uzyj(postac&, bool czy_atakuje = true);
};

class piorun_slaby : public umiejetnosc
{
	piorun_slaby();
	~piorun_slaby();
	void uzyj(postac&, bool czy_atakuje = true);
};

class piorun_mocny : public umiejetnosc // To samo co slaby ale silniejszy, wiekszy zasieg inna animacja
{
	piorun_mocny();
	~piorun_mocny();
	void uzyj(postac&, bool czy_atakuje = true);
};

class kula_energii : public umiejetnosc
{
public:
	kula_energii();
	~kula_energii();
	void uzyj(postac&, bool czy_atakuje = true);
};

class kula_ognia : public umiejetnosc
{
public:
	kula_ognia();
	~kula_ognia();
	void uzyj(postac&, bool czy_atakuje = true);
};

class ognisty_deszcz : public umiejetnosc
{
public:
	ognisty_deszcz();
	~ognisty_deszcz();
	void uzyj(postac&, bool czy_atakuje = true);
};

class postac
{
public:
	double pozY;
	double pozX;
	int zycie;
	virtual void atak(postac&, int numer);
	postac* wybierz_cel(vector<wrog>& cele, int zasieg);
	int predkosc;

protected:
	SDL_Surface* ruch[3];
	SDL_Surface* atak_wyglad;
};


class gracz
{
public:
	gracz();
//	~gracz();
	postac* bohater; //Wskaznik na wybraną postać
	void ruch(kierunek strona, double);
	void atak(postac &,int numer);

private:
	void uzyj_ataku(umiejetnosc &, postac&);
	int predkosc;
	postac& wybierz_cel();
	//tablica klatek animacji pokazujacych obrazenia, leczenie i atak
	//int czasy_regeneracji[3]; //Zmienne okreslajace ile czasu beda sie regenerowac poszczegolne ataki
};



class wrog : public postac 
{
public:
	wrog();
private:
	void przeciwnicy_wybor_celu(vector<wrog> przeciwnicy);
	int czasy_regeneracji[2]; //CZasy regeneracji posczegolnych atakow
	//tablica kalatek animacji
	//tablica klatek animacji pokazuj¹cych obraznie, ataki
};

class kaplan : public postac
{
public:
	kaplan();
	~kaplan();
private:
	normalny_atak umiejetnosc1;
	leczenie umiejetnosc2;
	wybawienie umiejetnosc3;
};

class wojownik : public postac
{
public:
	wojownik();
	~wojownik();
	vector<postac*> wybierz_cel(vector<wrog>& cele, int zasieg);
private:
	normalny_atak umiejetnosc1;
	trzesienie umiejetnosc2;
	kamienna_skora umiejetnosc3;
};

class mag : public postac
{
public:
	mag();
	~mag();
private:
	normalny_atak umiejetnosc1;
	podwojenie umiejetnosc2;
	magiczna_kula umiejetnosc3;
};
class potwor_sredni : public wrog
{
public:
	potwor_sredni();
	~potwor_sredni();
	normalny_atak umiejetnosc1;
	piorun_slaby umiejetnosc2;
};

class boss1 : public wrog
{
public:
	boss1();
	~boss1();
	kula_ognia umiejetnosc1;
	ognisty_deszcz umiejetnosc2;
};
class gra
{
public:
	gra();
	~gra();
	vector<wrog> przeciwnicy;
	vector<gracz> gracze;
};
void gracz::ruch(kierunek strona, double TempTime)
{
	if(strona == gora && bohater->pozY > 0)
	{
		bohater->pozY = ceil(bohater->pozY - TempTime*bohater->predkosc);
	}
	else if(strona == dol && bohater->pozY < WysEkranu)
	{
		bohater->pozY = ceil(bohater->pozY + TempTime * bohater->predkosc);
	}
	else if(strona == prawo && bohater->pozY < SzerEkranu)
	{
		bohater->pozX = ceil(bohater->pozX + TempTime * bohater->predkosc);
	}
	else if(strona == lewo && bohater->pozX > 0)
	{
		bohater->pozX = ceil(bohater->pozX - TempTime * bohater->predkosc);
	}

}

void gracz::atak(postac& cel, int numer)
{
	if(numer == 1)
	{
		bohater->atak(cel,numer);
	}
	else if(numer == 2)
	{
		bohater->atak(cel,numer);
	}
	else if(numer == 3)
	{
		bohater->atak(cel,numer);
	}
}




////Funkcje postac///////////////////////

postac* postac::wybierz_cel(vector<wrog>& cele, int zasieg)
{
	postac* wybrany_cel = NULL;
	double odleglosc;
	for(int i = 0; i < cele.size(); i++)
	{
		odleglosc = sqrt((pow(cele[i].pozX - this->pozX,double(2)) + pow(cele[i].pozY - this->pozY,double(2))));
		if(odleglosc <= zasieg)
		{
			wybrany_cel = &cele[i];
			break;
		}
	}
	return wybrany_cel;
}
vector<postac*> wojownik::wybierz_cel(vector<wrog>& cele, int zasieg)
{
	vector<postac*> wybrane_cele;
	int odleglosc;
	for(int i = 0; i < cele.size(); i++)
	{
		odleglosc = sqrt((pow(cele[i].pozX - this->pozX,double(2)) - pow(cele[i].pozY - this->pozY,double(2))));
		if(odleglosc <= zasieg)
			wybrane_cele.push_back(&cele[i]);
	}
	return wybrane_cele;
}
#endif
