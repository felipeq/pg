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
long double gauss[N];
/*
double m[N][N + 1] = {
    {4.0, -1.0, -0.2, 2.0, 30.0},
    {-1, 5, 0, -2, 0},
    {0.2, 1, 10, -1, -10},
    {0, -2, -1, 4, 5},
};*/
long double m[N][N + 1] = {
    {2.0, 1.0, 5.0},
    {4.0, 1.0, 9.0},
};

void OdwrocD() {
    for (int i = 0; i < N; i++)
        m[i][i] = 1.0 / m[i][i];
}

void Db() {
    for (int i = 0; i < N; i++) {
        m[i][N] = m[i][N] * m[i][i];
    }
}

void DL() {
    for (int i = 0; i < N; i++)
        for (int ii = 0; ii < N; ii++) {
            if (ii < i)
                m[i][ii] *= m[i][i];
        }
}

void DU() {
    for (int i = 0; i < N; i++)
        for (int ii = 0; ii < N; ii++) {
            if (ii > i)
                m[i][ii] *= m[i][i];
        }
}

int main() {
    OdwrocD();
    Db();
    DL();
    DU();
    for (int i = 0; i < N; i++) {
        for (int ii = 0; ii <= N; ii++) {
            cout << m[i][ii] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < ITERACJE; i++) {

    }
    return 0;
}

