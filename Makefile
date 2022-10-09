all: Player.o
	g++ incursion.cpp -w -lSDL2 -lSDL2_ttf -lSDL2_image -o incursion

Player.o:
	g++ -c -o lib/Player.o lib/Player.cpp -Ilib

clean:
	rm incursion
