DEPS = editorLibrary.h
OBJ = vi_editor.o editorLibrary.o insertMode.o normalMode.o commandMode.o file_handling.o
CC = g++
CFLAGS = -I -Wall -std=c++11

%.o: %.cpp $(DEPS)
	g++ -c -std=c++11 editorLibrary.h
	$(CC) -c -o $@ $< $(CFLAGS)

vi_editor: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)