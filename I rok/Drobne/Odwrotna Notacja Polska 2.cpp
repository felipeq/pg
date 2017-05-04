/*Nale¿y obliczyæ wartoœæ wyra¿enia w postaci prefiksowej (NP). Wykorzystano 3 operatory: N (negacja), K (koniunkcja) oraz A (alternatywa) i dwie wartoœci logiczne t (prawda) i f (fa³sz).

Input

t - liczba przypadków wejœciowych
W kolejnych t liniach wyra¿enia prefiksowe, bez spacji

Output

Kolejne wartoœci wyra¿eñ w osobnych liniach

Example

Input:
2
KtKtKtf
NAtf

Output:
f
f
*/
#include <iostream.h>
#include <stack>
#include <string>
using namespace std;

int main()
{
    stack<char> s;
    int t;
	char var1=0;
	char var2=0;
	cin >> t;
	for ( int i=0;i<t;i++)
	{
		string s;
		cin >> s;
		for ( int q=s.length()-1;q>=0;q--)
		{	
            if (s[q-2]=='K')
            {
               if (s[q-1]=='t' && s[q]=='t') 
                   s[q-2]='t';
               else
                   s[q-2]='f';
                   q=q-1;       
            }
            if (s[q-1]=='N')
            {
               if (s[q]=='t') s[q-1]='f';
               else           s[q-1]='t';             
            }
            if (s[q-2]=='A')
            {
                            if (s[q-1]=='t' || s[q]=='t')
                            s[q-2]='t';
                            else
                            s[q-2]='f';
                            q=q-1;
                            }
		}
		cout << s[0] << endl;
	}
	return 0;
}
