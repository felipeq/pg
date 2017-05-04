/*
Nale�y przepisa� wyra�enie w postaci infiksowej na postfiksow� (ONP). Wykorzystano 3 operatory: N (negacja), K (koniunkcja) oraz A (alternatywa) i dwie warto�ci logiczne t (prawda) i f (fa�sz).

Wszystkie wyra�enia s� dok�adnie onawiasowane, nie ma potrzeby rozpoznawania pierwsze�stwa operator�w.

Input

t - liczba przypadk�w wej�ciowych
W kolejnych t liniach wyra�enia infiksowe, bez spacji

Output

Kolejne wyra�enia w Odwrotnej Notacji Polskiej w osobnych liniach
*/
#include <iostream.h>
#include <stack>
#include <string>
using namespace std;
int main()
{
    int t;
	
	cin >> t;
	stack<char> a;
	stack<char> w;
	string s;
	for ( int i=0;i<t;i++)
	{
	//	cin >> s;
	cin >> s;
		for ( int q=0;q<s.length();q++)
		{
		//	cout << "sprawdzam " << s[q] << endl;
			if (s[q]=='f') cout << 'f';
			if (s[q]=='t') cout << 't';
			if (s[q]=='(') a.push('(');
			if (s[q]=='N') a.push('N');
			if (s[q]=='K') a.push('K');
			if (s[q]=='A') a.push('A');
			if (s[q]==')')
			{
				if (a.top()!='(')
				{
				cout << a.top();
				a.pop();
				}
			//	char temp=a.top();
		//		cout << "usuwam " << temp << endl;
				a.pop();	
			//	cout << "usunalem, mam teraz "<< a.top() << endl;		
			}
		}
        cout << endl;
	}
	return 0;
}
