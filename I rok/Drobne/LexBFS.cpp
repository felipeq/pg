/*
Filip Biedrzycki, grupa 5, nr 137248
Projekt na AiSD, semestr 2, PG ETI Informatyka, 2012


Algorytm wczytuje do listy list wierzcho�k�w relacje pomi�dzy nimi, 
potem tworzy zbi�r Lv zawieraj�cy wszystkie wierzcho�ki ( np. {1,2,3,4} ),
dodaje do zbioru Ls s�siad�w wybranego pierwszego wierzcho�ka oraz 
oznacza pierwszy wierzcho�ek jak "odwiedzony" w zbiorze Lv.
Nast�pnie przechodzi do g��wnej p�tli programu: pobiera wierzcho�ek ( skrajny lewy ) 
z skrajnie lewego ( lub g�rnego, chodzi o front() ) zbioru, 
zaznacza go w Lv jako oznaczony, dodaje nowy zbi�r ( na g�r� lub na lewo ) 
takich s�siad�w wierzcho�ka, kt�rzy nie zostali oznaczeni
w Lv jako "odwiedzeni".  Puste zbiory usuwa. I tak porusza si� po zbiorach a� Ls b�dzie puste.

*/
#include <list>
#include <iostream>
using namespace std;

struct N
{
    bool odwiedzony;
	int wartosc;
	list<N> MyS; // lista s�siad�w w�z�a
	N(bool odwiedzony,int val): odwiedzony(odwiedzony),wartosc(val) {}
};
int main()
{
	 // lista list zawieraj�cych informacje o s�siedztwie
	int LiczbaTestow;
	cin >> LiczbaTestow; // Ilo�� graf�w i test�w
	for ( int LTi=0;LTi<LiczbaTestow;LTi++)
	{
		list<list<N> > LListN; //lista przechowuj�ca listy przechowuj�ce informacje o s�siadach
		int LiczbaN; // Ilo�� w�z��w grafu
		cin >> LiczbaN;
		for ( int LNii=0;LNii<LiczbaN;LNii++) // tworzymy w pami�ci ( narazie ) puste listy, do kt�rych odwo�ywa� si� b�d� w�z�y podanej ni�ej
		{
			list<N> temp;
			LListN.push_back(temp);
		}
		for (list<list<N> >::iterator iter=LListN.begin();iter!=LListN.end();iter++)
		{
				int LiczbaS;
				cin >> LiczbaS; // Ilo�� s�siad�w w�z�a danego w�z�a
				for ( int LSi=0;LSi<LiczbaS;LSi++)
				{
					int x;
					cin >> x;
					N *temp;
					temp=new N(false,x-1); // tworz� w�ze� o warto�ci X (-1, �eby unikn�� b��d�w z indeksami liczonymi od 0
					int iiter=0;
					for (list<list<N> >::iterator iter=LListN.begin();iter!=LListN.end();iter++)
					{
						if (iiter==(x-1))
						{
							temp->MyS=*iter; // szukamy na li�cie wybranego wierzcho�ka i podpinamy w�ze� do jego listy s�siedztwa											
							break;
						}
						iiter+=1;
					}
					iter->push_front(*temp);
					delete temp;
				}
		}
		int IloscTestow;
		cin >> IloscTestow;
		for ( int ITi=0;ITi<IloscTestow;ITi++)
		{
			int Typ;
			cin >> Typ;
			if (Typ==1)
			{
				int startowy;		// Od jakiego w�z�a zaczynamy
				cin >> startowy;
				cout << startowy;
				startowy-=1;		// Zmniejszamy o 1 dla �atwiejszej obs�ugi indeks�w i iterator�w
				list<list<N> > kopia;
				kopia=LListN;		
				list<list<N> > Ls;	// lista przechowuj�ca listy s�siedztwa w odpowiednio dodawanej kolejno�ci
				list<N> Lv;			// lista samych wierzcho�k�w do por�wnywania przed dodaniem nowych wierz do Ls, aby unikn�� dublowania
				for ( int i=0;i<LiczbaN;i++) // zape�niamy Lv, tworz�c nowe w�z�y, kt�rych s�siad�w pobieramy z listy list s�siedztw 
				{
					N *temp;
					temp=new N(false,i);
					int help=0;
					for (list<list<N> >::iterator iter=kopia.begin();iter!=kopia.end();iter++)
					{
						if (help==i)
						{
							temp->MyS=*iter;
							break;
						}
						help++;
					}
					Lv.push_back(*temp);
					delete temp;
				}
				for (list<N>::iterator iter=Lv.begin();iter!=Lv.end();iter++)	// odnajdujemy pocz�tkowy wierzcho�ek w Lv i zaznaczamy go jako "odwiedzony"
				{																
					if (iter->wartosc==startowy)
					{
						Ls.push_back(iter->MyS);
						iter->odwiedzony=true;
						break;
					}
				}
				while (Ls.size()>0) // Dop�ki na li�cie s�siedztw do przenanalizowania znajduj� si� dane:
				{
					if (Ls.front().size()==0)	// Je�li zbi�r "najbardziej z lewej" jest pusty, to go usuwamy i analizujemy od pocz�tku
					{							// "najbardziej z lewej" - analogia do przyk�adu z instrukcji, gdzie wierzcho�ki by�y brane "od lewej"
						Ls.pop_front();
						continue;
					} // Zaznaczamy wierzcho�ek najbardziej z lewej Ls jako "odwiedzony" w zbiorze Lv i wyrzucamy na ekran
					for (list<N>::iterator iter2=Lv.begin();iter2!=Lv.end();iter2++)
					{
						if (iter2->wartosc==Ls.front().front().wartosc)
						{
							if (iter2->odwiedzony==false)
								cout << " " << Ls.front().front().wartosc+1; // Drukujemy powi�kszone o 1
							else
							{ 
								Ls.front().pop_front(); // Je�li natrafimy na ju� odwiedzony, wyrzucamy go i analizujemy zbiory od nowa
								continue;
							}
							iter2->odwiedzony=true;
						}
					}
					list<N> temp; 
					int pom=0;
					for ( list<list<N> >::iterator iter=kopia.begin();iter!=kopia.end();iter++) 
					{	// Przeszukujemy globaln� list� s�siedztw w poszukiwaniu s�siad�w wydrukowanego wierzcho�ka
						// Teoretycznie powinni�my mie� bezpo�redni dost�p do tej listy z N.MyS ( wska�nik do listy s�siad�w )
						// ale problemy z pami�ci� poch�on�y mi wi�kszo�� czasu i nie zd��y�em poprawnie tego zaimplementowa�
						if (pom==Ls.front().front().wartosc)
						{
							for ( list<N>::iterator it2=iter->begin();it2!=iter->end();it2++) 
							{	
								for ( list<N>::iterator it3=Lv.begin();it3!=Lv.end();it3++)
								{
						// Por�wnujemy s�siad�w wybranego wierzcho�ka z Lv, aby unikn�� dodawania do Ls ju� odwiedzonych wierzcho�k�w
									if (it3->wartosc==it2->wartosc && it3->odwiedzony==false)
									{
										temp.push_back(*it3);
										break;
									}
								}
							}
							break;
						}
						pom++;
					}
					if (temp.size()>0) // Nie dodajemy pustego zbioru, bo i tak zosta�by usuni�ty na pocz�tku p�tli
						Ls.push_front(temp); // dodajemy najbardziej "do lewej" nowy zbi�r z nieodwiedzonymi s�siadami
				}
				cout << endl;
			}

		}
		
	}
	return 0;
}
