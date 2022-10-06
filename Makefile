all:
	g++ incursion.cpp -w -lSDL2 -lSDL2_ttf -lSDL2_image -o incursion

clean:
	rm incursion
