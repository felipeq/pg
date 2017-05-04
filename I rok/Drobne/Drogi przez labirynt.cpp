#include <iostream>
#include <string>
using namespace std;
int main()
{
	unsigned long long int width, height;
	cin >> width>>height;

	bool **blocked = new bool *[width]; // tablica, czy pole jest przechodne
	for ( int i = 0; i < width; ++i )
		blocked[i] = new bool [height];
	
	unsigned long long int **ways = new unsigned long long int *[width]; // ilosc drog do danego pola
	for ( unsigned long long int i = 0; i < width; ++i )
	{
		ways[i] = new unsigned long long int [height];
		for ( unsigned long long int ii=0;ii<height;++ii)
			ways[i][ii]=0;
	}
	ways[0][0]=1;

	char symbol;
	for ( unsigned long long int i = 0; i < height; ++i )
		for ( unsigned long long int ii = 0; ii < width; ++ii )
		{
			cin >> symbol;
			if (symbol=='#') blocked[i][ii]=true;
			if (symbol=='.') blocked[i][ii]=false;
		}
	for (unsigned long long int h=0;h<height;h++)
	{
		for (unsigned long long int w=0;w<width;w++)
		{
			if (blocked[h][w]==false)
			{
				if (h+1<height)
					ways[h+1][w]+=ways[h][w];
				if (w+1<width)
					ways[h][w+1]+=ways[h][w];
			}
		}
	}
	cout << ways[height-1][width-1];
}