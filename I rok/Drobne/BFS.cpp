#include <iostream> 
#include <list>
#include <string>
#include <queue>
#include <math.h>
using namespace std;
int main()
{
	int IloscGrafow;
//	cout << "Ilosc grafow: ";
	cin >> IloscGrafow;

	for ( int i=0;i<IloscGrafow;i++)
	{
		vector<list<int> > GlobalV;
		int IloscWierzcholkow;
	//	cout <<"Podaj ilosc wierzcholkow: ";
		string temps;		
		cin >> IloscWierzcholkow;
		int *tabs = new int[IloscWierzcholkow];
	//	cout << endl;
		for ( int ii=0;ii<IloscWierzcholkow;ii++)
		{
			int IloscS;
			cin >> IloscS;
			list<int> temp;
			for ( int si=0;si<IloscS;si++)
			{
				int x;
				cin >> x;
				temp.push_back(x-1);
			}
			tabs[ii]=0;
			GlobalV.push_back(temp);
		}
		int IloscTestow;
		cin >> IloscTestow;
		for ( int it=0;it<IloscTestow;it++)
		{
			int TypTestu;
			cin >> TypTestu;
			if (TypTestu==1)
			{
				int start;
				cin >> start;
				list<int> kolejka;
				vector<list<int> > GlobalC;
				GlobalC=GlobalV;
				int *tabc = new int[IloscWierzcholkow];
				for ( int i=0;i<IloscWierzcholkow;i++)
					tabc[i]=tabs[i];
				kolejka.push_back(start-1);
				cout <<"-------------------------------------OUTPUT: ";
				while(kolejka.size()>0)
				{
				/*	cout <<"Stan kolejki:\n";
					for ( list<int>::iterator iter=kolejka.begin();iter!=kolejka.end();iter++)
						cout << *iter <<" ";
					cout<< "\nStan sasiadow: \n";
					for ( int i=0;i<IloscWierzcholkow;i++)
					{
						cout << i <<": ";
						for ( list<int>::iterator iter=GlobalC[i].begin();iter!=GlobalC[i].end();iter++)
						{}
							cout << *iter <<" ";
						cout<< ". Odwiedzonych: " << tabc[i] << endl;
					}
					cout <<"WYRZUCAM NA EKRAN: " << kolejka.front() << " \n";*/
					cout << kolejka.front()+1<< " ";
					for ( int i=0;i<GlobalC.size();i++)
					{
						for ( list<int>::iterator iter=GlobalC[i].begin();iter!=GlobalC[i].end();iter++)
						{
							if (*iter==kolejka.front())
								tabc[i]++;
						}
						GlobalC[i].remove(kolejka.front());
					}
					int ss=-1;	// ilosc s¹siadów do porównania
					int w=-1;	// kto ma tyle s¹siadów
				//	cout <<"wyb " << wybrany << endl;
					for (list<int>::iterator iter=GlobalC[kolejka.front()].begin();iter!=GlobalC[kolejka.front()].end();iter++)
					{
						if (ss==(-1))
						{
							ss=tabc[*iter];
							w=*iter;
							continue;
						}
						else
						{
							if (tabc[*iter]>ss)
							{
								ss=tabc[*iter];
								w=*iter;
							}
						}
					}
					if (w!=(-1))
					kolejka.push_back(w);
			//	cout <<"Wybrany: " << w <<". ";
					for (list<int>::iterator iter=GlobalC[kolejka.front()].begin();iter!=GlobalC[kolejka.front()].end();iter++)// posortowaæ mo¿e?
						if (*iter!=w)
							kolejka.push_back(*iter);
					kolejka.remove(kolejka.front());
			//		cout << "tutej" << endl;
				}
				cout << endl;
			}
		}
	}

	return 0;
}
