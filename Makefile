all: Player.o Clyn.o Car.o Copter.o TicTacToe.o Menu.o
	g++ incursion.cpp -w -lSDL2 -lSDL2_image -o incursion lib/Player.o lib/Clyn.o lib/Car.o lib/Copter.o lib/Menu.o lib/TicTacToe.o -lSDL2_ttf

TicTacToe.o:
	g++ -c -o lib/TicTacToe.o lib/TicTacToe.cpp -Ilib

Menu.o:
	g++ -c -o lib/Menu.o lib/Menu.cpp -Ilib

Player.o:
	g++ -c -o lib/Player.o lib/Player.cpp -Ilib

Clyn.o:
	g++ -c -o lib/Clyn.o lib/Clyn.cpp -Ilib

Car.o:
	g++ -c -o lib/Car.o lib/Car.cpp -Ilib

Copter.o:
	g++ -c -o lib/Copter.o lib/Copter.cpp -Ilib

clean:
	rm incursion
