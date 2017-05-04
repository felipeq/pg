// Prosta biblioteka konsolowa - win32
// Autor: Jacek Dabrowski, jacek.dabrowski@eti.pg.gda.pl
// Udzielam licencji na wykorzystanie tej biblioteki oraz jej modyfikacje przez studentow pierwszego 
// roku Informatyki Politechniki Gdanskiej w ramach przedmiotu Praktyka Programowania

#include "console.h"
#include "windows.h"

HANDLE hStdout, hStdin; 

// the key record is kept between calls to getKey/getVKey to handle
// multiple same characters in a single event
KEY_EVENT_RECORD ker;

// Initialize the console and set it to full screen mode
BOOL initConsole()
{
	hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    if (hStdin == INVALID_HANDLE_VALUE || 
        hStdout == INVALID_HANDLE_VALUE) 
    {
        MessageBox(NULL, TEXT("GetStdHandle"),
            TEXT("Console Error"), MB_OK);
        return false;
    }

	ker.wRepeatCount = 0;

	SMALL_RECT windowSize = {0, 0, 79, 49};
    
    // Change the console window size:
    SetConsoleWindowInfo(hStdout, TRUE, &windowSize);

	COORD c = { 80, 50};

    //Change the internal buffer size:
    SetConsoleScreenBufferSize(hStdout, c);

	
	SetConsoleDisplayMode(hStdout,CONSOLE_FULLSCREEN_MODE, &c);

	return true;
}

// return the current column
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hStdout, &info);
	return info.dwCursorPosition.X;
}

// return the current row
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hStdout, &info);
	return info.dwCursorPosition.Y;
}

// return the width of the screen
int sizeX()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hStdout, &info);
	return info.dwSize.X;
}

// return the height of the screen
int sizeY()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hStdout, &info);
	return info.dwSize.Y;
}

// move the cursor to this position
void gotoXY(int x, int y)
{
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(hStdout,c);

}

// set the text attributes to the specified value 
// (check documentation for SetConsoleTextAttribute for details)
void setTextAttributes(int attr)
{
	SetConsoleTextAttribute(hStdout, (WORD) attr);
}

// return the current text attributes
int getTextAttributes()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hStdout, &info);
	return info.wAttributes;
}

// write a single character to screen
void write(char c)
{
	DWORD charsWritten;
	WriteConsole(hStdout, &c, 1, &charsWritten, NULL);
}

// write a null-terminated string to screen
void write(char *str)
{
	DWORD charsWritten;
	WriteConsole(hStdout, str, strlen(str), &charsWritten, NULL);
}


// fill the screen using current attributes
void fillScreen()
{
	DWORD charsWritten;
	COORD c;					//upper left corner
	c.X=0;
	c.Y=0;

	int size = sizeX()*sizeY(); //number of characters in the screen

	//fill the screen with spaces
	FillConsoleOutputCharacter(hStdout, ' ', size, c, &charsWritten);

	//set the attribute to current attribute 
	int attr = getTextAttributes();
	FillConsoleOutputAttribute(hStdout, attr, size, c, &charsWritten);

	//put the cursor in the upper left corner
	gotoXY(0,0);
}



// clear the screen using default attributes (reset to defaults as well)
void clearScreen()
{
	setTextAttributes(FOREGROUND_BLUE |FOREGROUND_GREEN |FOREGROUND_RED );

	fillScreen();
}


// return the ASCII code for the key pressed
char getKey()
{
	// if there are some characters left in the last keyboard event
	if (ker.wRepeatCount > 0)
	{
		ker.wRepeatCount --;
		return ker.uChar.AsciiChar;
	}

	INPUT_RECORD inputInfo;
	while(1)
	{
		DWORD count;
		BOOL result = ReadConsoleInput(hStdin, &inputInfo, 1, &count);

		if (count==1)
		{
			if (inputInfo.EventType == KEY_EVENT)
			{
				ker = inputInfo.Event.KeyEvent;
				if (ker.bKeyDown)
				{
					ker.wRepeatCount --;
					return ker.uChar.AsciiChar;
				}
			}
		}
		else
			Sleep(25);
	}
}

// return the Keyboard code for the key pressed (Virtual-Key Codes)
int getVKey()
{
	if (ker.wRepeatCount > 0)
	{
		ker.wRepeatCount --;
		return ker.wVirtualKeyCode;
	}

	// if there are some characters left in the last keyboard event
	INPUT_RECORD inputInfo;
	while(1)
	{
		DWORD count;
		BOOL result = ReadConsoleInput(hStdin, &inputInfo, 1, &count);

		if (count==1)
		{
			if (inputInfo.EventType == KEY_EVENT)
			{
				ker = inputInfo.Event.KeyEvent;
				if (ker.bKeyDown)
				{
					ker.wRepeatCount --;
					return ker.wVirtualKeyCode;
				}
			}
		}
		else
			Sleep(25);
	}
}



// set the cursor size: 0 - no cursor; 100 - full cursor
void setCursorSize(DWORD size, bool visible)
{
	_CONSOLE_CURSOR_INFO cursorInfo;
	
	cursorInfo.dwSize = size;
	cursorInfo.bVisible = visible;

	SetConsoleCursorInfo(hStdout, &cursorInfo);

}


// draw a line between (x0,y0) and (x1,y1) using char c
void line(int x0, int y0, int x1, int y1, char c)
{
	/* Funkcja stworzona na podstawie pseudokodu ze strony 
	   http://en.wikipedia.org/wiki/Bresenham's_line_algorithm */
   
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
		write(c);
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
