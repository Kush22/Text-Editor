/**
 * Code By: Kushagra Gupta
 * Roll Number: 20172079
 * Subject: M17CSE531: Operating System- Assignment Sumbission
**/

#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H
#include "editorLibrary.h"
#include <cmath>

// list< string > backgroundFile;
list< string > :: iterator it;

//list< string > :: iterator terminal_begin;
list< string > :: iterator terminal_end;

list< string > buffer;

int beginningPosition = 0;

void refreshScreen(){
	clearTerminalScreen();
	moveCursorXY(1,1);
	int i = 1;
	int j = 0;
	moveCursorXY(1,1);
	for(it = terminal_begin; it != backgroundFile.end() && i <= editor.terminal_rows-2; i++){
		string line = (*it).substr(j*editor.terminal_cols, editor.terminal_cols);
		j++;
		cout << line;
		cout.flush();

		if(line[line.length()-1] == '\n'){
			it++;
			j = 0;
		}
	}
	//moveCursorXY(1,1);
	drawStatusBar();
}

void initialiseScreenWithFile(string file_name){
	if(terminalSize(&editor.terminal_rows, &editor.terminal_cols) == -1)
		error("Error in Getting Window Size");
	string line;

	ifstream inputFile(file_name);

	drawStatusBar();

	//initialise the data structure with the contents of the file
	if(inputFile.is_open()){
		while(getline(inputFile, line)){
			line = line + "\n";
			backgroundFile.push_back(line);	
		}
		
		/*if(backgroundFile.size() == 0){
			backgroundFile.push_back("");
		}*/
		
		terminal_begin = backgroundFile.begin();
		
		line_number = terminal_begin;
		refreshScreen();
		inputFile.close();
		moveCursorXY(1,1);
	}
	else{
		cout << "Unable to open file!";
		cout.flush();	
		char ch = getCharInput();
		system("tput rmcup");
		disableRawMode();
		exit(0);
	}
}



#endif
