CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: soccerStars.out

soccerStars.out:  utils.o vector2d.o dynamics.o main.o rsdl.o components.o soccerstars.o soccerstars_parameters.o soccerstars_gui.o soccerstars_components.o
	$(CC) utils.o vector2d.o dynamics.o main.o rsdl.o components.o soccerstars.o soccerstars_parameters.o soccerstars_gui.o soccerstars_components.o $(CCFLAGS) -o soccerStars.out

main.o: main.cpp
	$(CC) -c main.cpp -o main.o

soccerstars.o: soccerstars.hpp soccerstars.cpp
	$(CC) -c soccerstars.cpp -o soccerstars.o

soccerstars_gui.o: soccerstars_gui.hpp soccerstars_gui.cpp
	$(CC) -c soccerstars_gui.cpp -o soccerstars_gui.o

soccerstars_components.o: soccerstars_components.hpp soccerstars_components.cpp
	$(CC) -c soccerstars_components.cpp -o soccerstars_components.o

components.o: components.hpp components.cpp
	$(CC) -c components.cpp -o components.o

dynamics.o: dynamics.hpp dynamics.cpp
	$(CC) -c dynamics.cpp -o dynamics.o

vector2d.o: vector2d.hpp vector2d.cpp
	$(CC) -c vector2d.cpp -o vector2d.o

utils.o: utils.hpp utils.cpp
	$(CC) -c utils.cpp -o utils.o

soccerstars_parameters.o: soccerstars_parameters.hpp soccerstars_parameters.cpp
	$(CC) -c soccerstars_parameters.cpp -o soccerstars_parameters.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
	$(CC) -c src/rsdl.cpp -o rsdl.o


.PHONY: clean
clean:
	rm -r *.o