/* 
 * 
 * Filip Biedrzycki
 * Metody Numeryczne - Projekt 1
 * Sumowanie szeregów potęgowych
 * 
 * f(x)=ln(x^2)
 *
 * ln(x^2)=(-1)^k[(-1+x^2)^k]/k
 */

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>
#include <stdio.h>
using namespace std;

int main(int argc, char** argv) 
{
    
    int e,ee;      // dokładność obliczeń
    double x=0;     // zmienna funkcji x, obliczony od przodu wynik, zmienna pomocniczna 
    vector<double> reverse;        // wektor na obliczone składniki sumy, potrzebny do sumowania od tyłu
    
    while (x==0 || fabs(x)>=sqrt(2))
    {
        cout << "Z dziedziny: ln(x^2) x!=0 AND |x|<sqrt(2)!\n";
        cout << "Podaj x: ";
        cin >> x;
    }
    cout << "Podaj dokładność: ";
    cin >> ee;

    for ( e=1;e<=ee;e++)
    {
            double wynik=0.0,temp=1;     // zmienna funkcji x, obliczony od przodu wynik, zmienna pomocniczna 
            reverse.clear();
    int k=0;
    while(fabs(temp) > pow(10,-e)) // Kończymy działanie, gdy osiągniemy podaną precyzję
    {
        k++;
        temp=pow(-1.0,k)*pow((-1+pow(x,2.0)),k)/k; // obliczamy składnik do sumy
        wynik+=temp;
        reverse.push_back(temp);        // dodajemy składnik do wektora, aby na końcu zsumować to od tyłu
    }
    
    double r_wynik=0; // wynik obliczany od tyłu
    
    for ( int i=reverse.size();i>=0;i--) // przeglądanie wektora od tyłu i sumowanie w r_wynik
    {

        r_wynik+=reverse[i];
    }
    
    wynik=-wynik;
    r_wynik=-r_wynik;
   // cout << "\ne: " << e;
    //cout << "\nWZORCOWY WYNIK:   "   << log(pow(x,2.0));   // wzorcowy wynik z zewnętrznej biblioteki
    printf("%.20lf",wynik-r_wynik);
    cout << "\n";             // wynik obliczany od przodu
   // cout << "\nREVERSE WYNIK:    " << r_wynik;           // wynik obliczany od tyłu
   // cout << "\nRÓŻNICA REV/NORM: " << wynik-r_wynik;     // różnica między obliczonymi wynikami
    }
    return 0;
}

