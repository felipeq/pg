#include "console.h"
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define MOD(x,y) x%=y;


int const corner_X=20; // Wspolrzedna X lewego gornego rogu obszaru rysowania
int const corner_Y=20; // Wspolrzedna Y lewego gornego rogu obszaru rysowania
int const size_X=40;   // Dlugosc na osi X obszaru do rysowania
int const size_Y=20;   // Dlugosc na osi Y obszaru do rysowania


int cursor_pos_X;
int cursor_pos_Y;
int SelectedColor=7;
int field[size_X][size_Y]={0};
int TempLinePos[size_X][size_Y]={0};


vector <int> pixele;
string IntToStr(int n)
{
     string tmp, ret;
     if(n < 0) {
          ret = "-";
          n = -n;
     }
     do {
          tmp += n % 10 + 48;
          n -= n % 10;
     }
     while(n /= 10);
     for(int i = tmp.size()-1; i >= 0; i--)
          ret += tmp[i];
     return ret;
}
void CountFulfilledX()
{
	setTextAttributes(7);
	for ( int ii=0;ii<size_Y;ii++)
	{

		gotoXY(0,corner_Y+ii);
		for ( int i=0;i<corner_X-1;i++)
		write(" ");

	}

	for ( int y=0;y<size_Y;y++)
	{

		pixele.clear();
		for ( int x=0;x<size_X;x++)
		{
			if (field[x][y]!=0)
			{ 
				int counter;
			
				for ( counter=1;counter<=size_X;counter++)
				{
					if (counter+x>size_X)
						break;
					if ( field[x+counter][y]!=0) continue;
					if (field[x+counter][y]==0) break;
					
				}
				pixele.push_back(counter);
				x=x+counter;
			}		
		}

		string str;
		bool TooLongString=false;

		for ( int i=pixele.size()-1;i>=0;i--)
		{	

			str=IntToStr(pixele[i])+" "+str;

			if (str.size()>corner_X-5)
			{
				str="< "+str;
				break;
			}
		}
		gotoXY(corner_X-str.size()-1,20+y);
		for ( int c=0;c<str.size();c++)
		{
			char tempchar=str[c];
			write(tempchar);
		}
	}
}
void MoveCursor(char key)
{
		switch ( key )
		{
		case VK_UP:			if (cursor_pos_Y-1>=corner_Y)			cursor_pos_Y--; break;
		case VK_DOWN:		if (cursor_pos_Y+1<size_Y+corner_Y)		cursor_pos_Y++; break;
		case VK_LEFT:		if (cursor_pos_X-1>=corner_X)			cursor_pos_X--; break;
		case VK_RIGHT:		if (cursor_pos_X+1<size_X+corner_X)		cursor_pos_X++; break;
		}

	gotoXY(cursor_pos_X,cursor_pos_Y);

}
void linia(int x0, int y0, int x1, int y1, char c)
{
   
	int dx = abs(x1-x0);
	int dy = abs(y1-y0);

	int sx,sy;

	if (x0 < x1) 
		sx = 1;
	else 
		sx = -1;

	if (y0 < y1) 
		sy = 1;
	else 
		sy = -1;

	int err = dx-dy;

	while(1)
	{
		gotoXY(x0,y0);
		TempLinePos[whereX()-corner_X][whereY()-corner_Y]=1;
		if (x0 == x1 && y0 == y1) 
			break;

		int e2 = 2*err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}	
	}
}
bool CheckFile (const string& nazwa)
{
        fstream plik;
        plik.open(nazwa.c_str(), ios::in);
        if ( plik.is_open() )
        {
            plik.close();
            return true;
        }
        plik.close();
        return false;
}
void Save()
{
	ofstream out;

  out.open ("obrazek.txt");
	for ( int y=0;y<size_Y;y++)
	{
		for ( int x=0;x<size_X;x++)
		{
		if (field[x][y]/16==48)
			out << 0;
			else
			out << field[x][y]/16;
		}
		out << "\n";
}
	out.close();
}
void ShowColorCube()
{
	for ( int x=0;x<4;x++)
	{
		for ( int y=0;y<3;y++)
		{
			gotoXY(45+x,16+y);
			write((char)219);
		}
	}
	gotoXY(cursor_pos_X,cursor_pos_Y);
}
void SetBorder()
{
	line(corner_X+size_X,	corner_Y,			corner_X+size_X,	corner_Y+size_Y-1,	'|'); 
	line(corner_X-1,		corner_Y,			corner_X-1,			corner_Y+size_Y-1,	'|');
	line(corner_X+size_X-1, corner_Y-1,			corner_X,			corner_Y-1,			'-');
	line(corner_X+size_X-1, corner_Y+size_Y,	corner_X,			corner_Y+size_Y,	'-');
}
void DoStartBasis()
{
{
		write( "137248 Biedrzycki Filip gr.5: Praktyki programowania projekt 1.\n\n\n     Czesc B\n     Obsluga:\n       Strzalki - poruszanie kursorem\n       SPACJA  - zmiana znaku\n           R    - wyczyszczenie obrazka\n");
		write( "           W    - wczytaj obrazek.txt\n");
		write( "           Z    - zapisz obrazek.txt\n");
		write( "          1..8  - zmiana koloru\n");
		write( "           L    - zacznij rysowanie linii (spacja zatwierdza, drugie L anuluje )");
		write( "           F    - wypelnianie obszaru\n");
	gotoXY(38,17);
		write( "KOLOR: ");
}
	ShowColorCube();
	setTextAttributes(7);
	SetBorder();
	gotoXY(corner_X-1+size_X/2,corner_Y-1+size_Y/2);
}

void ExterminateField()
{
	for ( int x=0;x<size_X;x++)
			memset( field[x], 0, size_X*2);

}
void BringThatField(int cx, int cy) // drukujemy tablice na pole wyznaczone granicami
{
	for ( int y=0;y<size_Y;y++)
	{
		gotoXY(corner_X,corner_Y+y); // przesuwamy kursor w dol

		for ( int x=0;x<size_X;x++)
		{
			setTextAttributes(field[x][y]);
			write(" ");
		}
	}
	
	gotoXY(cx,cy);
	setTextAttributes(field[cx-corner_X][cy-corner_Y]+SelectedColor);
	write("X");
	gotoXY(whereX()-1,whereY());
	setTextAttributes(SelectedColor);
	
}
void Load()
{
	if ( CheckFile("obrazek.txt")==true )
{
	ExterminateField();
	ifstream in;
	in.exceptions ( ifstream::failbit | ifstream::badbit );
		try 
		{
   			in.open("obrazek.txt");
			char s[size_X];
			ExterminateField();
			gotoXY(corner_X,corner_Y);
				for ( int y=0;y<size_Y;y++)
				{
					for ( int x=0;x<size_X;x++)
					{	
						in >> s[x];
						if (s[x]==NULL)
							break;
						else field[x][y]=(s[x]-48)*16;
					}
				}
			BringThatField(corner_X-1+size_X/2,corner_Y-1+size_Y/2); 
		}
	catch (ifstream::failure e) { }


		in.close();
		   }
		   else {gotoXY(corner_X-1+cursor_pos_X,corner_Y-1+cursor_pos_Y);}
}
void ChangeColorTo(char key)
	{
		switch ( key )
		{
			case '1': setTextAttributes(0); break;
			case '2': setTextAttributes(1); break;
			case '3': setTextAttributes(2); break;
			case '4': setTextAttributes(3); break;
			case '5': setTextAttributes(4); break;
			case '6': setTextAttributes(5); break;
			case '7': setTextAttributes(6); break;
			case '8': setTextAttributes(7); break;
			default:{}
				break;
		}
		SelectedColor=getTextAttributes();
		ShowColorCube();
	}
void ColorSwitch(char key)
	{
		switch ( SelectedColor )
		{
			case '1': setTextAttributes(16); break;
			case '2': setTextAttributes(32); break;
			case '3': setTextAttributes(48); break;
			case '4': setTextAttributes(64); break;
			case '5': setTextAttributes(80); break;
			case '6': setTextAttributes(96); break;
			case '7': setTextAttributes(112); break;
			case '8': setTextAttributes(128); break; // - 7
			case '9': setTextAttributes(0); break;
			default:{}
				break;
		}
	}
void CombineLineAndField()
{
	for ( int x=0;x<size_X;x++)
	{
		for ( int y=0;y<size_Y;y++)
		{
			if (TempLinePos[x][y]==1)
			{
				field[x][y]=SelectedColor*16;
			}
		}
	}
}
void DrawLine()
{
	for ( int x=0;x<size_X;x++)
			memset( TempLinePos[x], 0, size_X*2);
	int LineFromX=cursor_pos_X;
	int LineFromY=cursor_pos_Y;
	char key;
	do
	{
		key=getVKey();
		MoveCursor(key);
		linia(LineFromX,LineFromY,cursor_pos_X,cursor_pos_Y,'X');

			if (key==VK_SPACE)
			{
				CombineLineAndField();
				break;
			}

		BringThatField(cursor_pos_X,cursor_pos_Y);

			for ( int y=0;y<size_Y;y++)
			{
				gotoXY(corner_X,corner_Y+y);

				for ( int x=0;x<size_X;x++)
				{
					if (TempLinePos[x][y]==1)
					{
						setTextAttributes(field[x][y]+SelectedColor);
						write("X");
					}
					if (TempLinePos[x][y]==0)
						gotoXY(whereX()+1,whereY());
				}
			}
				for ( int x=0;x<size_X;x++)
		for ( int y=0;y<size_Y;y++)
			TempLinePos[x][y]=0;
	
gotoXY(cursor_pos_X,cursor_pos_Y);
	}
	while (key!='L');
CountFulfilledX();
}


int ColorFulfill(int x, int y, int StartBGColor)
{
	int a=field[x][y];

	if ((a==StartBGColor) && (a!=SelectedColor) && ((x<size_X && x>=0) && (y>=0 && y<size_Y)))
	{
		field[x][y]=SelectedColor*16;
		ColorFulfill(x,y+1, StartBGColor);
		ColorFulfill(x,y-1, StartBGColor);
		ColorFulfill(x-1,y, StartBGColor);
		ColorFulfill(x+1,y, StartBGColor);
		return 0;
	}

}
int main()
{
	initConsole();
	setCursorSize(100,false);
	char key;
	DoStartBasis();

	cursor_pos_X=whereX();
	cursor_pos_Y=whereY();

	do 
	{

		key=getVKey();
		ChangeColorTo(key);

		switch ( key )
		{
			case VK_UP:		MoveCursor(VK_UP);		break;
			case VK_DOWN:	MoveCursor(VK_DOWN);	break;
			case VK_LEFT:	MoveCursor(VK_LEFT);	break;
			case VK_RIGHT:	MoveCursor(VK_RIGHT);	break;


			case VK_SPACE: field[cursor_pos_X-corner_X][cursor_pos_Y-corner_Y]=SelectedColor*16;	break;


			case 'L': DrawLine();					break;
			case 'R': ExterminateField();			break;
			case 'Z': Save();						break;
			case 'W': Load();						break;

			case 'F': 
				{
					if (SelectedColor*16!=field[cursor_pos_X-corner_X][cursor_pos_Y-corner_Y])
				ColorFulfill(cursor_pos_X-corner_X, cursor_pos_Y-corner_Y, field[cursor_pos_X-corner_X][cursor_pos_Y-corner_Y]); 
				}
				break;

		}	
		if ( key=='W' || key=='R' || key==VK_SPACE || key=='F')
		CountFulfilledX();
		BringThatField(cursor_pos_X,cursor_pos_Y);

	}
	while(key!=VK_ESCAPE);
	return 0;
}