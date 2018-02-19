/**
 * Code By: Kushagra Gupta
 * Roll Number: 20172079
 * Subject: M17CSE531: Operating System- Assignment Sumbission
**/

#ifndef ED_LIB
#define ED_LIB

/** Includes **/
#include <iostream>
#include <ctype.h> //for iscntrl() to check that input character is a control character or not
#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include <string>
#include <errno.h>
#include <cstdio>
#include <signal.h>
#include <sys/ioctl.h>
#include <fstream>
#include <list>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std;

/*** defines ***/
#define UP 'A'
#define DOWN 'B'
#define RIGHT 'C'
#define LEFT 'D'
#define CTRL_KEY(k) ((k) & 0x1f)
#define ENTER 13
#define BACKSPACE 127
#define ESCAPE 27
#define RIGHT_MARGIN 20

struct terminalProperties{
	struct termios orig_termios;
	int terminal_rows;
	int terminal_cols;
	int MODE = 1;
	//int rightFlag = 1;
	//int cursor_pos = 1;
	int lineNo = 0;
	int cursor_X = 1;
	int cursor_Y = 1;
};

extern int fileGiven;
extern string fileName;

/** List Data-Structure to hold the background file data **/
extern list< string > backgroundFile;
extern list< string > :: iterator terminal_begin;
extern list< string > :: iterator temp_iterator;
extern list< string > :: iterator line_number;

/** Termial Properties while the editor is running **/
extern struct terminalProperties editor;
extern int TERMINATE;
extern int fileDirty;


void error(const char * s);

void disableRawMode();

void enableRawMode();

void clearTerminalScreen();

void moveCursorTopLeft();

void clearScreenCursorTop();

void drawTildes();

void moveCursorXY(int x, int y);

void moveCursor(char direction, int position);

void saveCursorPos();

void restoreCursorPos();

void clearStatusBar();

void drawStatusBar();

int terminalSize(int *rows, int *cols);

void initialiseScreen();

void handleScreenResize(int signal_number);

char getCharInput();

void processInputChar();

void clearLine(int row);

void normalMode();

void insertMode();

void commandMode();

void initialiseScreenWithFile(string file_name);

void refreshScreen();

void moveCursorLEFT();

void moveCursorRIGHT();

void moveCursorUP();

void moveCursorDOWN();

#endif
