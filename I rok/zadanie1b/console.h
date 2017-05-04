#undef UNICODE

#include "windows.h"


// Initialize the console and set it to full screen mode
int initConsole();
// return the current column
int whereX();
// return the current row
int whereY();
// return the width of the screen
int sizeX();
// return the height of the screen
int sizeY();


// move the cursor to this position
void gotoXY(int x, int y);

// set the text attributes to the specified value 
// (check documentation for SetConsoleTextAttribute for details)
void setTextAttributes(int attr);

// return the current text attributes
// (check documentation for SetConsoleTextAttribute for details)
int getTextAttributes();


// write a single character to screen
void write(char c);
// write a null-terminated string to screen
void write(char *string);

// clear the screen using default attributes (reset to defaults as well)
void clearScreen();

// fill the screen using current attributes
void fillScreen();


// return the ASCII code for the key pressed
char getKey();

// return the Keyboard code for the key pressed (Virtual-Key Codes)
int getVKey();

// set the cursor size: 0 - no cursor; 100 - full cursor
void setCursorSize(DWORD size, bool visible);

// draw a line between (x0,y0) and (x1,y1) using char c
void line(int x0, int y0, int x1, int y1, char c);