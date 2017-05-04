#include <iostream>
#include <string>
using namespace std;



int main()
{
	ios_base::sync_with_stdio(0);
	int g;
	cin >> g;
	int tab[26];
	string str1, str2;


	while(g--)
	{
		for ( int i=0;i<26;++i)
		{
			tab[i]=0;
	//		cout << tab[i];
		}
	//	cout << endl;
		//for(int i='a'; i<='z'; ++i)
		//{ tab[i] = 0; cout << tab[i]; }
	//	cout << endl;
		cin >> str1 >> str2;

		for ( string::iterator i=str2.begin();i!=str2.end();i++)
		{
		//	cout << "i: " << (int)*i << endl;
			tab[(int)*i-97]++;
		}
		for ( string::iterator i=str1.begin();i!=str1.end();i++)
		{
			if (tab[(int)*i-97]==0) cout << *i;
			if (tab[(int)*i-97]>0) tab[(int)*i-97]--;
		}
		cout << "\n";
	}

	return 0;
}