#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED

/*// Define: RLUTIL_USE_ANSI
/// Define this to use ANSI escape sequences also on Windows
/// (defaults to using WinAPI instead).*/


/*/// Define: RLUTIL_STRING_T
/// Define/typedef this to your preference to override rlutil's string type.
///
/// Defaults to std::string with C++ and char* with C.*/

// DO NOT EDIT !!!! ///////////////////////////////

#define RLUTIL_STRING_T char*
#define RLUTIL_INLINE static __inline__

#include <stdio.h>
#include <string.h>

#include <windows.h>  /* for WinAPI and Sleep() */
#define _NO_OLDNAMES  /* for MinGW compatibility */
#include <conio.h>    /* for getch() and kbhit() */
#define getch _getch
#define kbhit _kbhit

#ifndef RLUTIL_STRING_T
		typedef const char* RLUTIL_STRING_T;
#endif /* RLUTIL_STRING_T */

#define RLUTIL_PRINT(st) printf("%s", st)

#define FORME_TETE 79
#define FORME_CORPS 42
#define FORME_STADE 178
#define FORME_POMME 153

/*#define HD 187
#define BD 188
#define HG 201
#define BG 200
#define HB 205
#define VB 186*/

void locate(int , int ) ;
void gotoxy(int , int );
RLUTIL_STRING_T getANSIColor(const int ) ;
void setColor(int ) ;
void cls(void) ;
void setBackgroundColor(int ) ;
int getkey(void) ;
void msleep(unsigned int ) ;
void setCursorVisibility(char );
void hidecursor(void) ;
int random();
void printPomme(int, int, int);
void printSnakeHead(int, int, int);
void printSnakeBody(int, int, int);
void printStadeElement(int, int, int);
char* NomCouleur(const int c);



#endif /* MYLIB_H*/

/*/==================================================*/


/**
 * Enums: Color codes
 *
 * BLACK - Black
 * BLUE - Blue
 * GREEN - Green
 * CYAN - Cyan
 * RED - Red
 * MAGENTA - Magenta / purple
 * BROWN - Brown / dark yellow
 * GREY - Grey / dark white
 * DARKGREY - Dark grey / light black
 * LIGHTBLUE - Light blue
 * LIGHTGREEN - Light green
 * LIGHTCYAN - Light cyan
 * LIGHTRED - Light red
 * LIGHTMAGENTA - Light magenta / light purple
 * YELLOW - Yellow (bright)
 * WHITE - White (bright)
 */
enum {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	GREY,
	DARKGREY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};

enum{DROITE,GAUCHE,BAS,HAUT,ENTREE};


/**
 * Consts: ANSI escape strings
 *
 * ANSI_CLS                - Clears screen
 * ANSI_CONSOLE_TITLE_PRE  - Prefix for changing the window title, print the window title in between
 * ANSI_CONSOLE_TITLE_POST - Suffix for changing the window title, print the window title in between
 * ANSI_ATTRIBUTE_RESET    - Resets all attributes
 * ANSI_CURSOR_HIDE        - Hides the cursor
 * ANSI_CURSOR_SHOW        - Shows the cursor
 * ANSI_CURSOR_HOME        - Moves the cursor home (0,0)
 * ANSI_BLACK              - Black
 * ANSI_RED                - Red
 * ANSI_GREEN              - Green
 * ANSI_BROWN              - Brown / dark yellow
 * ANSI_BLUE               - Blue
 * ANSI_MAGENTA            - Magenta / purple
 * ANSI_CYAN               - Cyan
 * ANSI_GREY               - Grey / dark white
 * ANSI_DARKGREY           - Dark grey / light black
 * ANSI_LIGHTRED           - Light red
 * ANSI_LIGHTGREEN         - Light green
 * ANSI_YELLOW             - Yellow (bright)
 * ANSI_LIGHTBLUE          - Light blue
 * ANSI_LIGHTMAGENTA       - Light magenta / light purple
 * ANSI_LIGHTCYAN          - Light cyan
 * ANSI_WHITE              - White (bright)
 * ANSI_BACKGROUND_BLACK   - Black background
 * ANSI_BACKGROUND_RED     - Red background
 * ANSI_BACKGROUND_GREEN   - Green background
 * ANSI_BACKGROUND_YELLOW  - Yellow background
 * ANSI_BACKGROUND_BLUE    - Blue background
 * ANSI_BACKGROUND_MAGENTA - Magenta / purple background
 * ANSI_BACKGROUND_CYAN    - Cyan background
 * ANSI_BACKGROUND_WHITE   - White background
 */

/**
 * Enums: Key codes for keyhit()
 *
 * KEY_ESCAPE  - Escape
 * KEY_ENTER   - Enter
 * KEY_SPACE   - Space
 * KEY_INSERT  - Insert
 * KEY_HOME    - Home
 * KEY_END     - End
 * KEY_DELETE  - Delete
 * KEY_PGUP    - PageUp
 * KEY_PGDOWN  - PageDown
 * KEY_UP      - Up arrow
 * KEY_DOWN    - Down arrow
 * KEY_LEFT    - Left arrow
 * KEY_RIGHT   - Right arrow
 * KEY_F1      - F1
 * KEY_F2      - F2
 * KEY_F3      - F3
 * KEY_F4      - F4
 * KEY_F5      - F5
 * KEY_F6      - F6
 * KEY_F7      - F7
 * KEY_F8      - F8
 * KEY_F9      - F9
 * KEY_F10     - F10
 * KEY_F11     - F11
 * KEY_F12     - F12
 * KEY_NUMDEL  - Numpad del
 * KEY_NUMPAD0 - Numpad 0
 * KEY_NUMPAD1 - Numpad 1
 * KEY_NUMPAD2 - Numpad 2
 * KEY_NUMPAD3 - Numpad 3
 * KEY_NUMPAD4 - Numpad 4
 * KEY_NUMPAD5 - Numpad 5
 * KEY_NUMPAD6 - Numpad 6
 * KEY_NUMPAD7 - Numpad 7
 * KEY_NUMPAD8 - Numpad 8
 * KEY_NUMPAD9 - Numpad 9
 */
enum {
	KEY_ESCAPE  = 0,
	KEY_ENTER   = 1,
	KEY_SPACE   = 32,

	KEY_INSERT  = 2,
	KEY_HOME    = 3,
	KEY_PGUP    = 4,
	KEY_DELETE  = 5,
	KEY_END     = 6,
	KEY_PGDOWN  = 7,

	KEY_UP      = 14,
	KEY_DOWN    = 15,
	KEY_LEFT    = 16,
	KEY_RIGHT   = 17,

	KEY_F1      = 18,
	KEY_F2      = 19,
	KEY_F3      = 20,
	KEY_F4      = 21,
	KEY_F5      = 22,
	KEY_F6      = 23,
	KEY_F7      = 24,
	KEY_F8      = 25,
	KEY_F9      = 26,
	KEY_F10     = 27,
	KEY_F11     = 28,
	KEY_F12     = 29,

	KEY_NUMDEL  = 30,
	KEY_NUMPAD0 = 31,
	KEY_NUMPAD1 = 127,
	KEY_NUMPAD2 = 128,
	KEY_NUMPAD3 = 129,
	KEY_NUMPAD4 = 130,
	KEY_NUMPAD5 = 131,
	KEY_NUMPAD6 = 132,
	KEY_NUMPAD7 = 133,
	KEY_NUMPAD8 = 134,
	KEY_NUMPAD9 = 135
};

