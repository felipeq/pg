/*Nale¿y policzyæ liczby Fibonacciego F(n) mod 70001 dla ujemnych n. Nale¿y skorzystaæ z faktu, ze F(-2k) = -F(2k) i F(-2k + 1) = F(2k - 1).

Oczywiœcie F(0) = 0, F(1) = 1 i F(n) = F(n - 1) + F(n - 2) dla n > 1.

Przydatne moga byæ równie¿ zale¿noœci:
F(2n) = F(n) (F(n) + 2 F(n - 1))
F(2n + 1) = F(n + 1)2 + F(n - 1)2

Kolejne testy zawieraj¹ wartoœci n > -104

Input

W pierwszej linii liczba k. W nastêpnych k liniach pojedyncze ujemne liczby n.

Output

W k liniach po jednej liczbie: n-ta liczba Fibonacciego F(n)

Example

Input:
5
-3
-25
-187
-1000
-9998

Output:
2
5024
34789
31219
10430
*/
#include <iostream.h>
using namespace std;
const int x=70001;
int main()
{
    int k;
    cin >> k;
    for ( int i=0;i<k;i++)
    {
        long long int n;
        cin >> n;
        n=-n;
        unsigned long int wynik=0;
        if (n==0) wynik=0;
         if (n==1) wynik=1;
         unsigned long int pom1=0;
         unsigned long int pom2=1;
         for ( int i=0;i<n-1;i++)
         {
             wynik=pom1+pom2;
             if (wynik>=x) wynik=wynik%x;
             pom1=pom2;
             pom2=wynik; 
         }
         if (n%2==0)    wynik=x-wynik;
         if (n%2==1)     wynik=wynik;
        cout << wynik << endl;
    }
    return 0;
}
