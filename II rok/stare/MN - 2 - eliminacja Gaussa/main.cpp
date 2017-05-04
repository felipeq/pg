#include <iostream>
#include <math.h>
#include <sys/time.h>
#include <stdio.h>

using namespace std;
int N; // rozmiar wczytanej macierzy
long double m[101][101]; // wczytana macierz
long double solution[101]; // wzorcowa odpowiedź
long double wyniki[101];
long double X[101];

using namespace std;

/* Znajdź wiersz z największą wartością w kolumnie start.
 * Zamień go miejscem z wierszem nr start.
 */
void UstawMaxWiersz(int start) {
    int max_pos = start;
    long double max_value = -100000;
    for (int i = start; i < N; i++) {
        if (max_value < m[i][start]) {
            max_value = m[i][start];
            max_pos = i;
        }

    }
    if (max_pos == start)
        return;
    long double* temp = new long double[N + 1];
    for (int i = 0; i < N + 1; i++) {
        temp[i] = m[max_pos][i];
        m[max_pos][i] = m[start][i];
        m[start][i] = temp[i];
    }
    delete temp;
}

/* Odejmij wielokrotności wiersza [start] od reszty macierzy tak,
 * aby w kolumnie [start] pojawiły się 0.
 */
void ZerujKolumne(int start) {
    for (int i = start + 1; i < N; i++) {
        long double wiel = m[i][start] / m[start][start];
        for (int ii = start; ii < N + 1; ii++) {
            if (m[start][ii] != 0) {
                m[i][ii] = m[i][ii] - wiel * m[start][ii];
            }

        }
    }
}

/* Dzieli cały wiersz przez współczynnik znajdujący się na przekątnej i otrzymujemy same jedynki na przekątnych.
 * Odejmujemy od wyniku ( ostatniej kolumny ) wartości współczynników wymnożone przez znalezioną odpowiedź z wektora X.
 */
void Rozwiaz() {
    for (int i = N - 1; i >= 0; i--) {
        long double temp = m[i][i];
        for (int q = i; q <= N; q++) {

            m[i][q] = m[i][q] / temp;
            //usleep(50);
        }
        long double wynik = m[i][N];
        for (int q = i + 1; q < N; q++) {
            wynik -= X[q] * m[i][q];
        }
        X[i] = wynik;

    }

}

int main() {

    struct timeval start, end;
    long mtime, seconds, useconds;

    int ilosc;
    cin >> ilosc;
    ilosc--;
    int old = 0;
    gettimeofday(&start, NULL);
    while (ilosc--) {
        cin >> N;
        // Zerujemy macierz
        for (int i = 0; i < 101; i++) {
            for (int q = 0; q < 101; q++)
                m[i][q] = 0;
            solution[i] = 0;
            X[i] = 1;
        }

        // Obsługujemy mierzenie czasu
        
        if (old == 0) old = N;
        if (old != N) {
            gettimeofday(&end, NULL);
            seconds = end.tv_sec - start.tv_sec;
            useconds = end.tv_usec - start.tv_usec;

            mtime = ((seconds) * 1000 + useconds / 1000.0) + 0.5;

            printf("%ld\n", mtime);
            old = N;
            gettimeofday(&start, NULL);
        }
        // Wprowadzamy dane
        for (int i = 0; i < N; i++) {
            cin >> solution[i];
        }
        int nic;
        cin >> nic;
        for (int i = 0; i < N; i++)
            for (int q = 0; q < N + 1; q++)
                cin >> m[i][q];

        // Rozpoczynamy liczenie
        for (int i = 0; i < N - 1; i++) {
            UstawMaxWiersz(i);
            ZerujKolumne(i);
        }
        Rozwiaz();
        for (int i = 0; i < N; i++)
            for (int i = 0; i < N; i++)
                wyniki[N] += solution[i] - X[i];

    }
    for (int i = 0; i < N; i++)
        printf("%.20Lf\n", (long double) fabs(wyniki[i]));

    return 0;
}