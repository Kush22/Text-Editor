/**
 * Code By: Kushagra Gupta
 * Roll Number: 20172079
 * Subject: M17CSE531: Operating System- Assignment Sumbission
**/ 

#ifndef MAIN_H
#define MAIN_H

#include "editorLibrary.h"

int main(int argc, char *argv[]){
	
	//Switching the terminal to alternate mode
	system("tput smcup");
	
	//Establishing signal to handle window resizing
	signal(SIGWINCH, handleScreenResize);
	
	clearScreenCursorTop();
	enableRawMode();
	
	if(argc < 2){
		fileGiven = 0;
		initialiseScreen();
	}
	else{
		fileGiven = 1;
		fileName = argv[1];

		ifstream iStream(fileName);
		
		//if the given file exists
		if(iStream.is_open()){
			iStream.close();
			initialiseScreenWithFile(fileName);
		}
		
		//if the file does not exist
		else{
			string createFile = "touch " + fileName;
			cout << createFile;
			system(createFile.c_str());
			initialiseScreenWithFile(fileName);
		}
	}

	while(1){
		processInputChar();
		if(TERMINATE)
			break;
	}

	system("tput rmcup");
	return 0;
}

#endif
