/**
 * Code By: Kushagra Gupta
 * Roll Number: 20172079
 * Subject: M17CSE531: Operating System- Assignment Sumbission
**/

#ifndef commandMode_H
#define commandMode_H

#include "editorLibrary.h"



void commandMode(){
	pid_t x;
	
	int tempCursorX = editor.cursor_X;
	int tempCursorY = editor.cursor_Y;

	clearLine(editor.terminal_rows);

	moveCursorXY(editor.terminal_rows, 1);
	write(STDOUT_FILENO, ":", 1);
	
	string command = "";

	char ch;

	while(ch != ENTER){
		ch = getCharInput();

		if(ch == BACKSPACE && command.length() > 0){
			cout << "\b \b";
			cout.flush();
			command = command.substr(0, command.length()-1);
		}

		else if(ch == ESCAPE){
			clearLine(editor.terminal_rows);
			moveCursorXY(tempCursorX, tempCursorY);
			normalMode();
			break;
		}

		else if(!iscntrl(ch)){
			cout << ch;
			cout.flush();
			command += ch;
		}
	}

	if(command[0] == '!'){
		//fork and exec commands
		disableRawMode();
		//system("tput rmcup");
		command = command.substr(1, command.length());
		
		x = fork();
		if(x == 0){
			//inside child
			system("tput rmcup");
			string message = "\n\nOutput of " + command + " -\n\n";
			write(STDOUT_FILENO, message.c_str(), message.length());
			execl("/bin/bash", "bash", "-c", command.c_str(), (char*)NULL);
		}
		else{
			wait(&x);
			
			string message = "\n\nPress Enter to Continue";
			write(STDOUT_FILENO, message.c_str(), message.length());
			
			ch = getCharInput();
			system("tput smcup");
			enableRawMode();
			editor.MODE = 1;
			refreshScreen();
			moveCursorXY(editor.cursor_X, editor.cursor_Y);
			//restoreCursorPos();
			drawStatusBar();
			normalMode();

		}
	}
	else{
		if(command == "q!"){
			system("tput rmcup");
			exit(0);
		}
		else if(command == "q"){
			//add to check whether the file is edited or not
			if(fileDirty == 1){
				moveCursorXY(editor.terminal_rows, 1);
				string message = "File is Not Saved. Save or use q! to quit";
				write(STDOUT_FILENO, message.c_str(), message.length());
				moveCursorXY(tempCursorX, tempCursorY);
				normalMode();
			}
			else{ 
				system("tput rmcup");
				exit(0);
			}
		}
		else if(command == "w"){
			if(fileGiven == 1){
				std::ofstream oStream(fileName);
				//oStream.open(fileName, std::ofstream::out | std::ofstream::trunc);
				for(temp_iterator = backgroundFile.begin(); temp_iterator != backgroundFile.end(); temp_iterator++){
					oStream << *temp_iterator;
				}
				oStream.close();
			}
			moveCursorXY(editor.terminal_rows, 1);
			clearLine(editor.terminal_rows);
			write(STDOUT_FILENO, "Data Written To File",20);
			moveCursorXY(tempCursorX, tempCursorY);
			normalMode();

		}

		else{
			clearLine(editor.terminal_rows);
			string MESSAGE = "Invalid Editor Command";
			write(STDOUT_FILENO, MESSAGE.c_str(), MESSAGE.length());

			ch = getCharInput();
			clearLine(editor.terminal_rows);
			if(ch == ':')
				commandMode();
			else if (ch == ESCAPE){
				restoreCursorPos();
				normalMode();
			}
			else{

			}
		}
	}
}

#endif
