/*
Zadanie jest nastêpuj¹ce: nale¿y policzyæ n!! = [n (n - 2) (n - 4) ...] mod 225 - iloczyn wszystkich liczb tej samej parzystoœci co n (0 < n < 100000), brany modulo 225.

Wskazówka: prawie po³owa przypadków jest trywialna i nie wymaga ¿adnych obliczeñ. Ale dlaczego?

Input

W pierwszej linii liczba k. W nastêpnych k liniach pojedyncze liczby n.

Output

W k liniach po jednej liczbie: liczba n!! mod 225

Example

Input:
3
5
6
151

Output:
15
48
22197881
*/
#include <iostream.h>
#include <math.h>
using namespace std;
int main()
{
    int k;
    unsigned long long int x=pow(2,25);
    cin >> k;
	unsigned long long int input=0;
	unsigned long long int output=0;
 
	for ( int i=0;i<k;i++)
	{
		cin >> input;
		output=input;
		unsigned long long int control=output;
		for ( unsigned long long int ii=0;ii<control;ii++)
		{
            if (input==1) break;
            input=input-2;
			if (input>1)
			   output=output*(input);
            if (output>=x)
               output=output%x;
			if (input<=1)
			   break;
		}
		cout << output << endl;
	}
return 0;
}