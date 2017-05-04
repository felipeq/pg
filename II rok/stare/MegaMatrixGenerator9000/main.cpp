/* 
 * File:   main.cpp
 * Author: filip
 *
 * Created on 21 maj 2013, 21:03
 */

#include <cstdlib>
#include <stdio.h>
#include <fstream>   /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;
#define MIN -100
#define MAX 100
#define PREC 20
long double m[101][101];

int main() {
    cout.precision(PREC);
    srand(time(NULL));

    fstream plik;
    plik.open("macierze.txt", ios::out);

    printf("Podaj ilość macierzy i ich maksymalny rozmiar: ");
    int ilosc, rozmiar;

    scanf("%d %d", &ilosc, &rozmiar);
    plik << ilosc * rozmiar << endl;
    for (int roz = 3; roz <= rozmiar + 1; roz++) {

        for (int il = 0; il < ilosc; il++) {
            plik << roz - 1 << endl;
            for (int i = 0; i < roz; i++) {
                for (int q = 0; q < roz - 1; q++) {
                    long double liczba = (MIN + rand() % (MAX - MIN)) * (long double) rand() / (long double) RAND_MAX;
                    m[i][q] = liczba;
                    long double temp = 123.0;
                    if (i > 0) {
                        temp = m[i][roz - 1];
                        m[i][roz - 1] += m[i][q] * m[0][q];
                    }
                }

            }
            for (int i = 0; i < roz; i++) {
                for (int q = 0; q < roz; q++) {
                    //printf("%.15Lf ", m[i][q]);

                    plik << setprecision(PREC) << m[i][q] << " ";
                }
                plik << "\n";
            }
            for (int i = 0; i <= 100; i++)
                for (int ii = 0; ii <= 100; ii++)
                    m[i][ii] = 0;
        }
    }
    return 0;
}

