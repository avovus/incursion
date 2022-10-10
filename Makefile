all: Player.o Clyn.o Car.o
	g++ incursion.cpp -w -lSDL2 -lSDL2_ttf -lSDL2_image -o incursion lib/Player.o lib/Clyn.o lib/Car.o

Player.o:
	g++ -c -o lib/Player.o lib/Player.cpp -Ilib

Clyn.o:
	g++ -c -o lib/Clyn.o lib/Clyn.cpp -Ilib

Car.o:
	g++ -c -o lib/Car.o lib/Car.cpp -Ilib

clean:
	rm incursion
