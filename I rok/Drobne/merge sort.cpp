#include <iostream> 
using namespace std;

struct dane
{
	int a;
	int b;
	double wynik;
};

void merge(dane *tab,dane *tab_pom, int start, int srodek, int koniec)
{
	int i,j,k;
	i=start;
	k=0;
	j=srodek+1;
	while (i<=srodek && j<=koniec)
	{
		if (tab[j].wynik<tab[i].wynik)
		{
			tab_pom[k]=tab[j];
			j++;
		}
		else
		{
			tab_pom[k]=tab[i];
			i++;
		}
		k++;
	}
	if (i<=srodek)
	{
		while (i<=srodek)
		{
			tab_pom[k]=tab[i];
			i++;
			k++;
		}
	}
	else
	{
		while (j <= koniec)
		{
			tab_pom[k]=tab[j];
			j++;
			k++;
		}
	}
	for ( int i=0;i<=(koniec-start);i++)
	{
		tab[start+i]=tab_pom[i];	
	}
}
void merge_sort(dane *Dane,dane *tab_pom, int start, int koniec)
{
	int srodek;
	if (start!=koniec)
	{
		srodek=((start+koniec)/2);
		merge_sort(Dane,tab_pom, start,srodek);
		merge_sort(Dane,tab_pom, srodek+1,koniec);
		merge(Dane,tab_pom, start,srodek,koniec);
	}
}
int main()  {
	int k;
	cin >> k;
	dane *Dane;
	Dane=new dane[k];
	dane *tab_pom;
	tab_pom=new dane[k];
	for ( int i=0;i<k;i++)
	{
		cin >> Dane[i].a;
		char x;
		cin >> x;
		cin >> Dane[i].b;
		Dane[i].wynik=((double)Dane[i].a/(double)Dane[i].b);
	//	cout << Dane[i].wynik << endl;
	}
	merge_sort(Dane,tab_pom,0,k-1);
	for ( int i=0;i<k;i++)
	{ 
		cout << Dane[i].a << "/" << Dane[i].b << endl;
	}
	delete [] Dane;
	delete [] tab_pom;
	return 0;
}
