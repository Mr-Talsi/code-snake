// DO NOT EDIT !!!! ///////////////////////////////

#include "myLib.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>  /* for WinAPI and Sleep() */
#define _NO_OLDNAMES  /* for MinGW compatibility */
#include <conio.h>    /* for getch() and kbhit() */
#define getch _getch
#define kbhit _kbhit

RLUTIL_STRING_T ANSI_CLS                = "\033[2J\033[3J";
RLUTIL_STRING_T ANSI_CONSOLE_TITLE_PRE  = "\033]0;";
RLUTIL_STRING_T ANSI_CONSOLE_TITLE_POST = "\007";
RLUTIL_STRING_T ANSI_ATTRIBUTE_RESET    = "\033[0m";
RLUTIL_STRING_T ANSI_CURSOR_HIDE        = "\033[?25l";
RLUTIL_STRING_T ANSI_CURSOR_SHOW        = "\033[?25h";
RLUTIL_STRING_T ANSI_CURSOR_HOME        = "\033[H";
RLUTIL_STRING_T ANSI_BLACK              = "\033[22;30m";
RLUTIL_STRING_T ANSI_RED                = "\033[22;31m";
RLUTIL_STRING_T ANSI_GREEN              = "\033[22;32m";
RLUTIL_STRING_T ANSI_BROWN              = "\033[22;33m";
RLUTIL_STRING_T ANSI_BLUE               = "\033[22;34m";
RLUTIL_STRING_T ANSI_MAGENTA            = "\033[22;35m";
RLUTIL_STRING_T ANSI_CYAN               = "\033[22;36m";
RLUTIL_STRING_T ANSI_GREY               = "\033[22;37m";
RLUTIL_STRING_T ANSI_DARKGREY           = "\033[01;30m";
RLUTIL_STRING_T ANSI_LIGHTRED           = "\033[01;31m";
RLUTIL_STRING_T ANSI_LIGHTGREEN         = "\033[01;32m";
RLUTIL_STRING_T ANSI_YELLOW             = "\033[01;33m";
RLUTIL_STRING_T ANSI_LIGHTBLUE          = "\033[01;34m";
RLUTIL_STRING_T ANSI_LIGHTMAGENTA       = "\033[01;35m";
RLUTIL_STRING_T ANSI_LIGHTCYAN          = "\033[01;36m";
RLUTIL_STRING_T ANSI_WHITE              = "\033[01;37m";
RLUTIL_STRING_T ANSI_BACKGROUND_BLACK   = "\033[40m";
RLUTIL_STRING_T ANSI_BACKGROUND_RED     = "\033[41m";
RLUTIL_STRING_T ANSI_BACKGROUND_GREEN   = "\033[42m";
RLUTIL_STRING_T ANSI_BACKGROUND_YELLOW  = "\033[43m";
RLUTIL_STRING_T ANSI_BACKGROUND_BLUE    = "\033[44m";
RLUTIL_STRING_T ANSI_BACKGROUND_MAGENTA = "\033[45m";
RLUTIL_STRING_T ANSI_BACKGROUND_CYAN    = "\033[46m";
RLUTIL_STRING_T ANSI_BACKGROUND_WHITE   = "\033[47m";
/*/ Remaining colors not supported as background colors*/


/* Function: setCursorVisibility
/// Shows/hides the cursor. */
void setCursorVisibility(char visible) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	HANDLE hConsoleOutput = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo( hConsoleOutput, &structCursorInfo ); /* Get current cursor size */
	structCursorInfo.bVisible = (visible ? TRUE : FALSE);
	SetConsoleCursorInfo( hConsoleOutput, &structCursorInfo );
#else // _WIN32 || USE_ANSI
	RLUTIL_PRINT((visible ? ANSI_CURSOR_SHOW : ANSI_CURSOR_HIDE));
#endif // _WIN32 || USE_ANSI
}

/* Function: hidecursor
/// Hides the cursor. */
void hidecursor(void) {
	setCursorVisibility(0);
}

/*/ Function: msleep
/// Waits given number of milliseconds before continuing.*/
void msleep(unsigned int ms) {
#ifdef _WIN32
	Sleep(ms);
#else
	/* usleep argument must be under 1 000 000 */
	if (ms > 1000) sleep(ms/1000000);
	usleep((ms % 1000000) * 1000);
#endif
}

/*/ Function: getkey
/// Reads a key press (blocking) and returns a key code.
///
/// See <Key codes for keyhit()>
///
/// Note:
/// Only Arrows, Esc, Enter and Space are currently working properly.*/
int getkey(void) {
	#ifndef _WIN32
	int cnt = kbhit(); /* for ANSI escapes processing */
	#endif
	int k = getch();
	switch(k) {
		case 0: {
			int kk;
			switch (kk = getch()) {
				case 71: return KEY_NUMPAD7;
				case 72: return KEY_NUMPAD8;
				case 73: return KEY_NUMPAD9;
				case 75: return KEY_NUMPAD4;
				case 77: return KEY_NUMPAD6;
				case 79: return KEY_NUMPAD1;
				case 80: return KEY_NUMPAD2;
				case 81: return KEY_NUMPAD3;
				case 82: return KEY_NUMPAD0;
				case 83: return KEY_NUMDEL;
				default: return kk-59+KEY_F1; /* Function keys */
			}}
		case 224: {
			int kk;
			switch (kk = getch()) {
				case 71: return KEY_HOME;
				case 72: return KEY_UP;
				case 73: return KEY_PGUP;
				case 75: return KEY_LEFT;
				case 77: return KEY_RIGHT;
				case 79: return KEY_END;
				case 80: return KEY_DOWN;
				case 81: return KEY_PGDOWN;
				case 82: return KEY_INSERT;
				case 83: return KEY_DELETE;
				default: return kk-123+KEY_F1; /* Function keys */
			}}
		case 13: return KEY_ENTER;
#ifdef _WIN32
		case 27: return KEY_ESCAPE;
#else // _WIN32
		case 155: /* single-character CSI*/
		case 27: {
			/* Process ANSI escape sequences*/
			if (cnt >= 3 && getch() == '[') {
				switch (k = getch()) {
					case 'A': return KEY_UP;
					case 'B': return KEY_DOWN;
					case 'C': return KEY_RIGHT;
					case 'D': return KEY_LEFT;
				}
			} else return KEY_ESCAPE;
		}
#endif /* _WIN32*/
		default: return k;
	}
}

/*/ Function: locate
/// Sets the cursor position to 1-based x,y.*/
void locate(int x, int y) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	COORD coord;
	/* TODO: clamping/assert for x/y <= 0?*/
	coord.X = (SHORT)(x - 1);
	coord.Y = (SHORT)(y - 1);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else /* _WIN32 || USE_ANSI*/
	#ifdef __cplusplus
		RLUTIL_PRINT("\033[" << y << ";" << x << "H");
	#else
		char buf[32];
		sprintf(buf, "\033[%d;%df", y, x);
		RLUTIL_PRINT(buf);
	#endif
#endif
}


/*/ Function: gotoxy
/// Same as <rlutil.locate>.*/
void gotoxy(int x, int y) {

	locate(x,y);
}

char* NomCouleur(const int c) {
	switch (c) {
		case BLACK       : return (char*)"noir";
		case BLUE        : return (char*)"bleu"; /* non-ANSI*/
		case GREEN       : return (char*)"vert";
		case CYAN        : return (char*)"cyan"; /* non-ANSI*/
		case RED         : return (char*)"rouge"; /* non-ANSI*/
		case MAGENTA     : return (char*)"magenta";
		case BROWN       : return (char*)"marron";
		case GREY        : return (char*)"gris";
		case DARKGREY    : return (char*)"gris sombre";
		case LIGHTBLUE   : return (char*)"bleu clair"; /* non-ANSI*/
		case LIGHTGREEN  : return (char*)"vert clair";
		case LIGHTCYAN   : return (char*)"cyan clair"; /* non-ANSI;*/
		case LIGHTRED    : return (char*)"rouge clair"; /* non-ANSI;*/
		case LIGHTMAGENTA: return (char*)"magenta clair";
		case YELLOW      : return (char*)"jaune"; /* non-ANSI*/
		case WHITE       : return (char*)"blanc";
		default: return "";
	}
}


/*#include "myConstant.h"*/

/**
 * Defs: Internal typedefs and macros
 * RLUTIL_STRING_T - String type depending on which one of C or C++ is used
 * RLUTIL_PRINT(str) - Printing macro independent of C/C++
 */




/*/ Function: getANSIColor
/// Return ANSI color escape sequence for specified number 0-15.
///
/// See <Color Codes>*/
RLUTIL_STRING_T getANSIColor(const int c) {
	switch (c) {
		case BLACK       : return (char*)ANSI_BLACK;
		case BLUE        : return (char*)ANSI_BLUE; /* non-ANSI*/
		case GREEN       : return (char*)ANSI_GREEN;
		case CYAN        : return (char*)ANSI_CYAN; /* non-ANSI*/
		case RED         : return (char*)ANSI_RED; /* non-ANSI*/
		case MAGENTA     : return (char*)ANSI_MAGENTA;
		case BROWN       : return (char*)ANSI_BROWN;
		case GREY        : return (char*)ANSI_GREY;
		case DARKGREY    : return (char*)ANSI_DARKGREY;
		case LIGHTBLUE   : return (char*)ANSI_LIGHTBLUE; /* non-ANSI*/
		case LIGHTGREEN  : return (char*)(char*)ANSI_LIGHTGREEN;
		case LIGHTCYAN   : return (char*)ANSI_LIGHTCYAN; /* non-ANSI;*/
		case LIGHTRED    : return (char*)ANSI_LIGHTRED; /* non-ANSI;*/
		case LIGHTMAGENTA: return (char*)ANSI_LIGHTMAGENTA;
		case YELLOW      : return (char*)ANSI_YELLOW; /* non-ANSI*/
		case WHITE       : return (char*)ANSI_WHITE;
		default: return "";
	}
}

/*/ Function: setColor
/// Change color specified by number (Windows / QBasic colors).
/// Don't change the background color
///
/// See <Color Codes>*/
 void setColor(int c) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFFF0) | (WORD)c); /* Foreground colors take up the least significant byte**/
#else
	RLUTIL_PRINT(getANSIColor(c));
#endif
}

/*/ Function: setBackgroundColor
/// Change background color specified by number (Windows / QBasic colors).
/// Don't change the foreground color
///
/// See <Color Codes>*/
void setBackgroundColor(int c) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFF0F) | (((WORD)c) << 4)); /* Background colors take up the second-least significant byte*/
#else
	RLUTIL_PRINT(getANSIBackgroundColor(c));
#endif
}

/*/ Function: cls
/// Clears screen, resets all attributes and moves cursor home.*/
 void cls(void) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)

	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const COORD coordScreen = {0, 0};
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	const DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

	SetConsoleCursorPosition(hConsole, coordScreen);
#else
	RLUTIL_PRINT(ANSI_CLS);
	RLUTIL_PRINT(ANSI_CURSOR_HOME);
#endif
}



/* fonction renvoie nombre aleatoire */
int random(){
    static int k=0;
    if (k==0){
            srand(time(NULL));
            k=1;}

    return rand();
}

/* Affiche une pomme */
void printPomme(int x, int y, int color){
    gotoxy(x,y);
    setColor(color);
    printf("%c",FORME_POMME);
}

/* Affiche la tete du SNAKE */
void printSnakeHead(int x, int y, int color){
    gotoxy(x,y);
    setColor(color);
    printf("%c",FORME_TETE);
}

/* Affiche un élément du corps du serpent*/
void printSnakeBody(int x, int y, int color){
    gotoxy(x,y);
    setColor(color);
    printf("%c",FORME_CORPS);
}

/* Affiche un élément du stade */
void printStadeElement(int x, int y, int color){
    gotoxy(x,y);
    setColor(color);
    printf("%c",FORME_STADE);
}
