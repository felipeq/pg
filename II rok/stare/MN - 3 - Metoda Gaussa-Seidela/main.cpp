/* 
 * File:   main.cpp
 * Author: filip
 *
 * Created on 9 maj 2013, 20:52
 */
#include <iostream>
#include <string>
#include <math.h>
#include <stdio.h>
using namespace std;


#define ITERACJE 10
const int N = 2;

/*
double m[N][N + 1] = {
    {4.0, -1.0, -0.2, 2.0, 30.0},
    {-1, 5, 0, -2, 0},
    {0.2, 1, 10, -1, -10},
    {0, -2, -1, 4, 5},
};*/
double m[N][N + 1] = {
    {2.0, 1.0, 5.0},
    {4.0, 1.0, 9.0},
};
/*
double m[N][N + 1] = {
    {8.00000, 2.00000, 7.00000, 95.00000},
    {7.00000, 2.00000, 4.00000, 69.00000},
    {5.00000, 1.00000, 1.00000, 35.00000},
};*/
//double solution[N] = {5.00000, 3.00000, 7.00000};
double b[N];
double Gauss_X[2][N];
double Jacob_X[ITERACJE][N];

void PokazMacierz(string tytul) {
    cout << tytul << endl;
    for (int i = 0; i < N; i++) {
        for (int ii = 0; ii < N; ii++)
            printf("%.5f ", m[i][ii]);
        printf("\n");
    }
    cout << "Odpowiedź:\n";
    for (int i = 0; i < N; i++) {
        printf("%.5f ", b[i]);
    }
    printf("\n");
}

void OdwrocD() {
    for (int i = 0; i < N; i++)
        m[i][i] = (double) (1.0 / m[i][i]);
}

void PomnozPrzezD() {
    for (int i = 0; i < N; i++) {
        b[i] = (double) (b[i] * m[i][i]);
        for (int ii = 0; ii < N; ii++) {
            if (i != ii)
                m[i][ii] = (double) (m[i][ii] * m[i][i]);
        }
    }
}

void PokazX() {
    cout << "--GAUSS--";
    for (int ii = 0; ii < ITERACJE; ii++) {
        cout << "\nITERACJA NR " << ii + 1 << endl;
        for (int i = 0; i < N; i++)
            cout << "\n" << Gauss_X[ii][i] << "; ";
        cout << endl;
    }
}

void Gauss() {
    OdwrocD(); // ok!
    PokazMacierz("Odwrócone D: ");
    PomnozPrzezD(); //ok!
    PokazMacierz("Wymnożone all przez D:");
    for (int i = 1; i < ITERACJE; i++) { //wszystkie iteracje
        for (int w = 0; w < N; w++) { // kolejne X-y 
            Gauss_X[1][w] += b[w];
            printf("[%d][%d]=%.1lf", i, w, b[w]);
            for (int k = 0; k < N; k++) { // kolejne elementy wiersza
                if (w == k) {
                    //printf(" !Przekątna! ");
                    continue;
                }
                // wiersz mniejszy niż kolumna
                if (w < k) {
                    Gauss_X[1][w] -= m[w][k] * Gauss_X[0][k];
                    if (m[w][k] >= 0)
                        printf("-%.3lf*%.3lf ", m[w][k], Gauss_X[0][k]);
                    else
                        printf("+%.3lf*%.3lf ", -m[w][k], Gauss_X[0][k]);
                }
                if (w > k) {
                    Gauss_X[1][w] -= m[w][k] * Gauss_X[1][k];
                    if (m[w][k] >= 0)
                        printf("-%.3lf*%.3lf ", m[w][k], Gauss_X[1][k]);
                    else
                        printf("+%.3lf*%.3lf ", -m[w][k], Gauss_X[1][k]);
                }
            }
            printf(",czyli %0.3lf\n", Gauss_X[1][w]);
        }
    }
}

void Jacob() {
    for (int i = 0; i < N; i++) {
        for (int ii = 0; ii < N; ii++) {
            if (i == ii) {
                m[i][ii] = 0;
                continue;
            } else
                m[i][ii] -= m[i][ii]*2;


        }
    }
    for (int i = 0; i < ITERACJE; i++) { //wszystkie iteracje
        for (int w = 0; w < N; w++) { // kolejne X-y 
            Jacob_X[i][w] += b[w];
            if (i == 0) continue;
            for (int q = 0; q < N; q++) {
                Jacob_X[i][w] += m[w][q] * Jacob_X[i - 1][q];
                //printf("[%d][%d][%d]: Dodaję %f*%f, mam %f\n",i,w,q, m[w][q], Jacob_X[i - 1][w],Jacob_X[i][w]);
            }
        }
    }
}

void AnalizujWyniki() {
    cout << "\nRóżnica metod Gaussa i Jacoba: \n";
    for (int q = 0; q < N; q++) {
        cout << "Dla zmiennej x[" << q << "], iteracje od 1 do " << ITERACJE << endl;
        for (int i = 0; i < ITERACJE; i++) {
            printf("Jacob: %.5lf\n", Jacob_X[i][q]);
            printf("Gauss: %.5lf\n", Gauss_X[i][q]);
            //printf("%.5lf\n", i + 1, fabs(Gauss_X[i][q] - solution[q]));
        }
    }
}

int main() {
    for (int i = 0; i < N; i++)
        b[i] = m[i][N];
    PokazMacierz("Macierz do rozwiązania: ");
    Gauss();
    //Jacob();
    //AnalizujWyniki();
    return 0;
}

