/**
 * Code By: Kushagra Gupta
 * Roll Number: 20172079
 * Subject: M17CSE531: Operating System- Assignment Sumbission
**/

#ifndef NORMALMODE_H
#define NORMALMODE_H
#include "editorLibrary.h"

/** Cursor Functions **/
void moveCursorUP(){
	if(terminal_begin != backgroundFile.begin()){
		terminal_begin--;
		editor.cursor_X = 1;
		editor.cursor_Y = 1;
		editor.lineNo = 0;
		refreshScreen();
		moveCursorXY(editor.cursor_X, editor.cursor_Y);
	}
}

void moveCursorDOWN(){
	if(terminal_begin != backgroundFile.end()){
		terminal_begin++;
		editor.cursor_X = 1;
		editor.cursor_Y = 1;
		editor.lineNo = 0;
		refreshScreen();
		moveCursorXY(editor.cursor_X, editor.cursor_Y);
	}
}

void moveCursorLEFT(){

	if(editor.cursor_Y == 1 && editor.cursor_X == 1){
	}
	else if(editor.cursor_Y == 1){
		editor.cursor_Y = editor.terminal_cols;
		editor.cursor_X--;
		editor.lineNo--;
	}
	else{
		editor.cursor_Y--;
	}
	moveCursorXY(editor.cursor_X, editor.cursor_Y);
}


void moveCursorRIGHT(){
	string line = (*terminal_begin).substr(editor.lineNo*editor.terminal_cols, editor.terminal_cols);
	
	if(line.find("\n") != string::npos){
		int pos = line.find("\n");
		if(editor.cursor_Y == pos+1){
			//do nothing
		}
		else
			editor.cursor_Y++;
	}
	else if(line.length() == 0){
		//cout << line.length();
	}

	else if(editor.cursor_X == editor.terminal_rows-2 && editor.cursor_Y == editor.terminal_cols){
		terminal_begin++;
		editor.lineNo = 0;
		refreshScreen();
		editor.cursor_X = 1;
		editor.cursor_Y = 1;
		moveCursorXY(editor.cursor_X, editor.cursor_Y);
		//editor.lineNo++;
	}
	else{
		if(editor.cursor_Y == editor.terminal_cols){
			editor.cursor_X++;
			editor.cursor_Y = 1;
			editor.lineNo++;
		}
		else{
			editor.cursor_Y++;
		}
	}

	moveCursorXY(editor.cursor_X, editor.cursor_Y);
}



void normalMode(){
	char c;

	do{
		c = getCharInput();

		gotoTopLabel:
		
		switch(c){
			case 'i':
				editor.MODE = 2;
				drawStatusBar();
				insertMode();
				break;

			case ':':
				editor.MODE = 3;
				drawStatusBar();
				commandMode();
				break;

			case 'h':
				moveCursorLEFT();
				// moveCursor(LEFT, 1);
				break;
				
			case 'j':
				moveCursorDOWN();
				break;

			case 'k':
				moveCursorUP();
				break;

			case 'l':
				moveCursorRIGHT();
				// moveCursor(RIGHT, 1);
				break;

			case 'g':
			{
				c = getCharInput();
				if(c == 'g'){
					terminal_begin = backgroundFile.begin();
					refreshScreen();
					editor.cursor_X = 1;
					editor.cursor_Y = 1;
					moveCursorXY(editor.cursor_X, editor.cursor_Y);
				}
				else
					goto gotoTopLabel;
				
				break;
			}

			case 'G':
				terminal_begin = backgroundFile.end();
				refreshScreen();
				editor.cursor_X = 1;
				editor.cursor_Y = 1;
				moveCursorXY(editor.cursor_X, editor.cursor_Y);
				break;

			case 'r':
			{	
				char newChar = getchar();
				string line = *terminal_begin;
				int prev = (editor.lineNo) * (editor.terminal_cols) + (editor.cursor_Y);
				string newString = line.substr(0, prev-1) + newChar + line.substr(prev);
				*terminal_begin = newString;
				refreshScreen();
				moveCursorXY(editor.cursor_X, editor.cursor_Y);
				break;
			}
			case ESCAPE:
			{
				char ch = getCharInput();
				if(ch == '['){
					ch = getCharInput();
					if (ch == UP)
						moveCursorUP();
					else if(ch == DOWN)
						moveCursorDOWN();
					else if(ch == LEFT)
						moveCursorLEFT();
					else if(ch == RIGHT)
						moveCursorRIGHT();
					}
				break;
			}

			default:
				break;
		}
	}while(c != 'i' || c != ':');
}

#endif
