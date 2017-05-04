/*
Filip Biedrzycki, grupa 5, nr 137248
Projekt na AiSD, semestr 2, PG ETI Informatyka, 2012


Algorytm wczytuje do listy list wierzcho³ków relacje pomiêdzy nimi, 
potem tworzy zbiór Lv zawieraj¹cy wszystkie wierzcho³ki ( np. {1,2,3,4} ),
dodaje do zbioru Ls s¹siadów wybranego pierwszego wierzcho³ka oraz 
oznacza pierwszy wierzcho³ek jak "odwiedzony" w zbiorze Lv.
Nastêpnie przechodzi do g³ównej pêtli programu: pobiera wierzcho³ek ( skrajny lewy ) 
z skrajnie lewego ( lub górnego, chodzi o front() ) zbioru, 
zaznacza go w Lv jako oznaczony, dodaje nowy zbiór ( na górê lub na lewo ) 
takich s¹siadów wierzcho³ka, którzy nie zostali oznaczeni
w Lv jako "odwiedzeni".  Puste zbiory usuwa. I tak porusza siê po zbiorach a¿ Ls bêdzie puste.

*/
#include <list>
#include <iostream>
using namespace std;

struct N
{
    bool odwiedzony;
	int wartosc;
	list<N> MyS; // lista s¹siadów wêz³a
	N(bool odwiedzony,int val): odwiedzony(odwiedzony),wartosc(val) {}
};
int main()
{
	 // lista list zawieraj¹cych informacje o s¹siedztwie
	int LiczbaTestow;
	cin >> LiczbaTestow; // Iloœæ grafów i testów
	for ( int LTi=0;LTi<LiczbaTestow;LTi++)
	{
		list<list<N> > LListN; //lista przechowuj¹ca listy przechowuj¹ce informacje o s¹siadach
		int LiczbaN; // Iloœæ wêz³ów grafu
		cin >> LiczbaN;
		for ( int LNii=0;LNii<LiczbaN;LNii++) // tworzymy w pamiêci ( narazie ) puste listy, do których odwo³ywaæ siê bêd¹ wêz³y podanej ni¿ej
		{
			list<N> temp;
			LListN.push_back(temp);
		}
		for (list<list<N> >::iterator iter=LListN.begin();iter!=LListN.end();iter++)
		{
				int LiczbaS;
				cin >> LiczbaS; // Iloœæ s¹siadów wêz³a danego wêz³a
				for ( int LSi=0;LSi<LiczbaS;LSi++)
				{
					int x;
					cin >> x;
					N *temp;
					temp=new N(false,x-1); // tworzê wêze³ o wartoœci X (-1, ¿eby unikn¹æ b³êdów z indeksami liczonymi od 0
					int iiter=0;
					for (list<list<N> >::iterator iter=LListN.begin();iter!=LListN.end();iter++)
					{
						if (iiter==(x-1))
						{
							temp->MyS=*iter; // szukamy na liœcie wybranego wierzcho³ka i podpinamy wêze³ do jego listy s¹siedztwa											
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
				int startowy;		// Od jakiego wêz³a zaczynamy
				cin >> startowy;
				cout << startowy;
				startowy-=1;		// Zmniejszamy o 1 dla ³atwiejszej obs³ugi indeksów i iteratorów
				list<list<N> > kopia;
				kopia=LListN;		
				list<list<N> > Ls;	// lista przechowuj¹ca listy s¹siedztwa w odpowiednio dodawanej kolejnoœci
				list<N> Lv;			// lista samych wierzcho³ków do porównywania przed dodaniem nowych wierz do Ls, aby unikn¹æ dublowania
				for ( int i=0;i<LiczbaN;i++) // zape³niamy Lv, tworz¹c nowe wêz³y, których s¹siadów pobieramy z listy list s¹siedztw 
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
				for (list<N>::iterator iter=Lv.begin();iter!=Lv.end();iter++)	// odnajdujemy pocz¹tkowy wierzcho³ek w Lv i zaznaczamy go jako "odwiedzony"
				{																
					if (iter->wartosc==startowy)
					{
						Ls.push_back(iter->MyS);
						iter->odwiedzony=true;
						break;
					}
				}
				while (Ls.size()>0) // Dopóki na liœcie s¹siedztw do przenanalizowania znajduj¹ siê dane:
				{
					if (Ls.front().size()==0)	// Jeœli zbiór "najbardziej z lewej" jest pusty, to go usuwamy i analizujemy od pocz¹tku
					{							// "najbardziej z lewej" - analogia do przyk³adu z instrukcji, gdzie wierzcho³ki by³y brane "od lewej"
						Ls.pop_front();
						continue;
					} // Zaznaczamy wierzcho³ek najbardziej z lewej Ls jako "odwiedzony" w zbiorze Lv i wyrzucamy na ekran
					for (list<N>::iterator iter2=Lv.begin();iter2!=Lv.end();iter2++)
					{
						if (iter2->wartosc==Ls.front().front().wartosc)
						{
							if (iter2->odwiedzony==false)
								cout << " " << Ls.front().front().wartosc+1; // Drukujemy powiêkszone o 1
							else
							{ 
								Ls.front().pop_front(); // Jeœli natrafimy na ju¿ odwiedzony, wyrzucamy go i analizujemy zbiory od nowa
								continue;
							}
							iter2->odwiedzony=true;
						}
					}
					list<N> temp; 
					int pom=0;
					for ( list<list<N> >::iterator iter=kopia.begin();iter!=kopia.end();iter++) 
					{	// Przeszukujemy globaln¹ listê s¹siedztw w poszukiwaniu s¹siadów wydrukowanego wierzcho³ka
						// Teoretycznie powinniœmy mieæ bezpoœredni dostêp do tej listy z N.MyS ( wskaŸnik do listy s¹siadów )
						// ale problemy z pamiêci¹ poch³onê³y mi wiêkszoœæ czasu i nie zd¹¿y³em poprawnie tego zaimplementowaæ
						if (pom==Ls.front().front().wartosc)
						{
							for ( list<N>::iterator it2=iter->begin();it2!=iter->end();it2++) 
							{	
								for ( list<N>::iterator it3=Lv.begin();it3!=Lv.end();it3++)
								{
						// Porównujemy s¹siadów wybranego wierzcho³ka z Lv, aby unikn¹æ dodawania do Ls ju¿ odwiedzonych wierzcho³ków
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
					if (temp.size()>0) // Nie dodajemy pustego zbioru, bo i tak zosta³by usuniêty na pocz¹tku pêtli
						Ls.push_front(temp); // dodajemy najbardziej "do lewej" nowy zbiór z nieodwiedzonymi s¹siadami
				}
				cout << endl;
			}

		}
		
	}
	return 0;
}
