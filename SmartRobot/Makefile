all: robot

robot: main.o Lexer.o Lexem.o Common.o
	g++ main.o Lexer.o Lexem.o Common.o -Wall -o robot
	rm -rf *.o

main.o:
	g++ -c -Wall main.cpp

Lexer.o:
	g++ -c -Wall Lexer.cpp

Lexem.o:
	g++ -c -Wall Lexem.cpp

Common.o:
	g++ -c -Wall Common.cpp
