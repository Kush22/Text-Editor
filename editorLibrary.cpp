/**
 * Code By: Kushagra Gupta
 * Roll Number: 20172079
 * Subject: M17CSE531: Operating System- Assignment Sumbission
**/

#ifndef EDITORLIBRARY_H
#define EDITORLIBRARY_H
#include "editorLibrary.h"

struct terminalProperties editor;
int TERMINATE;

/** Global File Properties **/
int fileGiven;
string fileName;
int fileDirty;

/** Definitions of the global data items **/
list< string > :: iterator terminal_begin;
list< string > :: iterator temp_iterator;
list< string > :: iterator line_number;
list< string > backgroundFile;

void error(const char * s){
	perror(s);
	exit(1);
}

void disableRawMode(){
	if( tcsetattr(STDIN_FILENO, TCSAFLUSH, &editor.orig_termios) == -1)
		error("Error in disabling raw mode.");
}

void enableRawMode(){
	
	//getting the attributes of the terminal in global structure so we can restore it later
	if(tcgetattr(STDIN_FILENO, &editor.orig_termios) == -1)
		error("Error in getting default attributes of terminal.");

	//when exit from prog set the values like before
	atexit(disableRawMode);

	//assigning the new structure original values so as to change only what we need
	struct termios raw = editor.orig_termios;

	//making changes to the settings that we got(turning off echo & canonical mode)
	raw.c_iflag &= ~(ICRNL | IXON);
	
	//to disable output processing ()
	//raw.c_oflag &= ~(OPOST);

	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

	//setting the changed values to reflect on terminal
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		error("Error in setting terminal to new settings.");

}


void clearTerminalScreen(){
	write(STDOUT_FILENO, "\x1b[2J", 4);
}


void moveCursorTopLeft(){
	write(STDOUT_FILENO, "\x1b[H", 3);
}


void clearScreenCursorTop(){
	clearTerminalScreen();
	moveCursorTopLeft();
	//system("clear");
}


void clearLine(int row){
	saveCursorPos();
	moveCursorXY(row, 1);
	
	//clearing the staus bar
	string CLEAR_LINE = "\033[K";
	write(STDOUT_FILENO, CLEAR_LINE.c_str(), CLEAR_LINE.length());

	restoreCursorPos();
}




void moveCursorXY(int x, int y){
	string s = "\033[" + to_string(x) + ";" + to_string(y) + "H";
	write(STDOUT_FILENO, s.c_str(), s.length());
}

/*
Position is the number of places we want to move
In the direction, these characters specify the direction(in escape sequences)
A- UP
B- DOWN
C- Forward / Right
D- Backward / Left
*/
void moveCursor(char direction, int position){
	string s = "\033["+ to_string(position)+ direction;
	write(STDOUT_FILENO, s.c_str(), s.length());
}


void saveCursorPos(){
	string SAVE_CURSOR_POS = "\033[s";
	write(STDOUT_FILENO, SAVE_CURSOR_POS.c_str(), SAVE_CURSOR_POS.length());
}


void restoreCursorPos(){
	string RESTORE_CURSOR_POS = "\033[u";
	write(STDOUT_FILENO, RESTORE_CURSOR_POS.c_str(), RESTORE_CURSOR_POS.length());

}


void drawStatusBar(){
	clearLine(editor.terminal_rows-1);
	saveCursorPos();
	
	//moving cursor to status bar
	moveCursorXY((editor.terminal_rows - 1), 1);

	if (editor.MODE == 1)
		write(STDOUT_FILENO, "NORMAL-MODE", 11);
	else if(editor.MODE == 2)
		write(STDOUT_FILENO, "INSERT-MODE", 11);
	else
		write(STDOUT_FILENO, "COMMAND-MODE", 12);

	//Writing the dimension of terminal(in status bar)
	moveCursorXY(editor.terminal_rows - 1, editor.terminal_cols - RIGHT_MARGIN);

	string size_terminal = "ROWS: "+ to_string(editor.terminal_rows) + " COLUMNS: " + to_string(editor.terminal_cols);
	write(STDOUT_FILENO, size_terminal.c_str(), size_terminal.length());

	//restoring cursor position
	restoreCursorPos();
	//write(STDOUT_FILENO, RESTORE_CURSOR_POS.c_str(), RESTORE_CURSOR_POS.length());
}


int terminalSize(int *rows, int *cols){
	struct winsize terminal_window;

	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal_window) == -1)
		return -1;
	else{
		*cols = terminal_window.ws_col;
		*rows = terminal_window.ws_row;
		return 0;
	}
}


void initialiseScreen(){
	if(terminalSize(&editor.terminal_rows, &editor.terminal_cols) == -1)
		error("Error in Getting Window Size");
	drawStatusBar();
	//moveCursorTopLeft();
}


void handleScreenResize(int signal_number){
	clearLine(editor.terminal_rows-1);
	if(terminalSize(&editor.terminal_rows, &editor.terminal_cols) == -1)
		error("Error in Getting Window Size");
	clearScreenCursorTop();
	refreshScreen();
	moveCursorXY(editor.cursor_X, editor.cursor_Y);
	drawStatusBar();	
}


char getCharInput(){
	char c;
	while(int readVal = read(STDOUT_FILENO, &c, 1) != 1){
		if(readVal == -1)
			error(" Error in reading character");
	}
	return c;
}


void processInputChar(){
	char c = getCharInput();

	if (editor.MODE == 1 && c == ':'){
		editor.MODE = 3; 
		drawStatusBar();
	}
	else if(editor.MODE == 1 && c == 'i'){
		editor.MODE = 2; // Insert Mode
		drawStatusBar();
	}
	else if(c == 27){  //Escape is pressed
		editor.MODE = 1;
		drawStatusBar();
	}
	else{
		// add more cases here if you need
	}
	if(editor.MODE == 1)
		normalMode();
	else if(editor.MODE == 2)
		insertMode();
	else
		commandMode();
}

#endif
