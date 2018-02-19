/**
 * Code By: Kushagra Gupta
 * Roll Number: 20172079
 * Subject: M17CSE531: Operating System- Assignment Sumbission
**/


#ifndef INSERTMODE_H
#define INSERTMODE_H
#include <sstream>
#include "editorLibrary.h"

void insertMode(){
	char c;
	do{
		c = getCharInput();

		switch(c){
			
			case ESCAPE:
				editor.MODE = 1; //setting to normal mode
				drawStatusBar();
				normalMode();


			case ENTER:
			{	
				string line = *terminal_begin;
				int prev = (editor.lineNo) * (editor.terminal_cols) + (editor.cursor_Y);
				string newString = line.substr(0, prev) + c + line.substr(prev+1);
				*terminal_begin = newString;
				refreshScreen();
				break;
			}

			case BACKSPACE:
			{
				int prev;
				string newString;
				string line = *terminal_begin;
				if(line.length() == 1){
					temp_iterator = terminal_begin;
					temp_iterator++;
					backgroundFile.erase(terminal_begin);
					terminal_begin = temp_iterator;
					
					editor.cursor_X = 1;
					editor.cursor_Y = 1; 
				 }
				else{
					if(editor.cursor_Y == 1 && editor.cursor_X == 1){
						//do nothing
					}
					else{
						prev = (editor.lineNo) * (editor.terminal_cols) + (editor.cursor_Y);
						newString = line.substr(0, prev-1) + line.substr(prev);
						if(editor.cursor_Y == 1){
							editor.cursor_Y = editor.terminal_cols;
							editor.cursor_X--;
							editor.lineNo--;
						}
						else
							editor.cursor_Y--;
					}
					*terminal_begin = newString;
				}
				refreshScreen();
				moveCursorXY(editor.cursor_X, editor.cursor_Y);			
			}
				break;

			default:
			{
				fileDirty = 1;
				string newString;
				string line = *terminal_begin;
				if(line != "\n"){
					int prev = (editor.lineNo) * (editor.terminal_cols) + (editor.cursor_Y);
					if(editor.cursor_Y == 1 && editor.lineNo == 0){
						newString = c + line.substr(0);
					}
					else{
						newString = line.substr(0, prev) + c + line.substr(prev);	
					}
					*terminal_begin = newString;
					refreshScreen();
					//moveCursorXY(editor.cursor_X, editor.cursor_Y);
					editor.cursor_Y++;
					if(editor.cursor_Y == editor.terminal_cols){
						editor.cursor_Y = 1;
						editor.cursor_X++;
						editor.lineNo++;
					}
				}
				else{
					string newString = c + "\n";
					*terminal_begin = newString;
					refreshScreen();
					editor.cursor_Y++;
					if(editor.cursor_Y == editor.terminal_cols){
						editor.cursor_Y = 1;
						editor.cursor_X++;
						editor.lineNo++;
					}
				}
				moveCursorXY(editor.cursor_X, editor.cursor_Y);
			}
			break;
		}
	}while(c != ESCAPE);
}

#endif
