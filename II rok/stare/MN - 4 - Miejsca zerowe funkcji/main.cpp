/* 
 * File:   main.cpp
 * Author: filip
 *
 * Created on 31 maj 2013, 15:44
 */

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <math.h>

#define E 0.001 // Jeśli KROK = E, to mamy błąd
#define KROK 0.1
#define NMAX 1000
using namespace std;
int fx;
int iter;

long double f(long double x) {
    switch (fx) {
        case 1: return sin(x);
            break;
        case 2: return cos(x);
            break;
        case 3: return x * x - 2 * x - 2;
            break;
        case 4: return -5 * x * x * x + 4 * x * x + 3 * x - 2;
            break;
        default: return -1;
            break;
    }

}

long double pochodna(long double x, int st) {
    switch (fx) {
        case 1:
        {
            if (st == 1)
                return cos(x);
            if (st == 2)
                return -sin(x);
            break;
        }
        case 2:
        {
            if (st == 1)
                return -sin(x);
            if (st == 2)
                return -cos(x);
            break;
        }
        case 3:
        {
            if (st == 1)
                return 2 * x - 2;
            if (st == 2)
                return 2;
            break;
        }
        case 4:
        {
            if (st == 1)
                return -15 * x * x + 8 * x + 3;
            if (st == 2)
                return 8 - 30 * x;
            break;
        }
        default: return -1;
            break;
    }
}

void bisekcja(long double a, long double b) {

    if (iter + 1 >= NMAX) {
        cout << "Bisekcja: MAX ITER ERROR!\n";
        return;
    }
    iter++;

    long double x1 = (a + b) / 2.0;

    if (fabs(a - b) < E) {
        cout << "Miejsce zerowe w " << (a + b) / 2.0 << endl;
        return;
    } else {
        if (f(a) * f(x1) < 0) {
            bisekcja(a, x1);
        }
        if (f(b) * f(x1) < 0) {
            bisekcja(x1, b);
        }
    }
}

void styczne(long double x0) {
    if (iter + 1 >= NMAX) {
        //cout << "Newton: MAX ITER ERROR!\n";
        return;
    }
    iter++;
    long double df = pochodna(x0, 1);

    x0 = x0 - f(x0) / df;
    if (fabs(f(x0)) < E) {
        cout << "Miejsce zerowe w " << x0 << endl; 
        return;
    } else
        styczne(x0);
    
}

/*
 * 
 */
int main() {
    long double a, b;
    cout << "Wybierz funkcję: \n"
            << "[1] sin(x)\n"
            << "[2] cos(x)\n"
            << "[3] x^2-2x-2\n"
            << "[4] -5x^3 + 4x^2 + 3x - 2\n";
    cin >> fx;
    cout << "Podaj a i b:\n";
    cin >> a >> b;
    double i;
    cout << "BISEKCJA:\n";
    for (i = a; i < b; i += KROK) {
        if (i + KROK <= b)
            bisekcja(i, i + KROK);
        else if (fabs(i - b) > E)
            bisekcja(i, b);
    }
    //cout << pochodna(5,1) << endl;
    iter = 0;
    cout << "STYCZNYCH:\n";
    for (i = a; i < b; i += KROK) {
        if (f(i) * pochodna(i, 2) > 0) {
            //printf("f(%.1LF): %0.5LF, %.5LF\n", i, f(i), pochodna(i, 2));
            styczne(i);
        }
        else
            styczne(i+KROK);

    }
    return 0;
}

