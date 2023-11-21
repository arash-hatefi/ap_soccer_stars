CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
BUILD_DIR := build

all: soccerStars.out

soccerStars.out: $(BUILD_DIR)/utils.o $(BUILD_DIR)/vector2d.o $(BUILD_DIR)/dynamics.o $(BUILD_DIR)/main.o $(BUILD_DIR)/rsdl.o $(BUILD_DIR)/components.o $(BUILD_DIR)/soccerstars.o $(BUILD_DIR)/soccerstars_parameters.o $(BUILD_DIR)/soccerstars_gui.o $(BUILD_DIR)/soccerstars_components.o
	$(CC) $(BUILD_DIR)/utils.o $(BUILD_DIR)/vector2d.o $(BUILD_DIR)/dynamics.o $(BUILD_DIR)/main.o $(BUILD_DIR)/rsdl.o $(BUILD_DIR)/components.o $(BUILD_DIR)/soccerstars.o $(BUILD_DIR)/soccerstars_parameters.o $(BUILD_DIR)/soccerstars_gui.o $(BUILD_DIR)/soccerstars_components.o $(CCFLAGS) -o soccerStars.out

$(BUILD_DIR)/main.o: src/main.cpp | $(BUILD_DIR)
	$(CC) -c src/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/soccerstars.o: include/soccerstars.hpp src/soccerstars.cpp | $(BUILD_DIR)
	$(CC) -c src/soccerstars.cpp -o $(BUILD_DIR)/soccerstars.o

$(BUILD_DIR)/soccerstars_gui.o: include/soccerstars_gui.hpp src/soccerstars_gui.cpp | $(BUILD_DIR)
	$(CC) -c src/soccerstars_gui.cpp -o $(BUILD_DIR)/soccerstars_gui.o

$(BUILD_DIR)/soccerstars_components.o: include/soccerstars_components.hpp src/soccerstars_components.cpp | $(BUILD_DIR)
	$(CC) -c src/soccerstars_components.cpp -o $(BUILD_DIR)/soccerstars_components.o

$(BUILD_DIR)/components.o: include/components.hpp src/components.cpp | $(BUILD_DIR)
	$(CC) -c src/components.cpp -o $(BUILD_DIR)/components.o

$(BUILD_DIR)/dynamics.o: include/dynamics.hpp src/dynamics.cpp | $(BUILD_DIR)
	$(CC) -c src/dynamics.cpp -o $(BUILD_DIR)/dynamics.o

$(BUILD_DIR)/vector2d.o: include/vector2d.hpp src/vector2d.cpp | $(BUILD_DIR)
	$(CC) -c src/vector2d.cpp -o $(BUILD_DIR)/vector2d.o

$(BUILD_DIR)/utils.o: include/utils.hpp src/utils.cpp | $(BUILD_DIR)
	$(CC) -c src/utils.cpp -o $(BUILD_DIR)/utils.o

$(BUILD_DIR)/soccerstars_parameters.o: include/soccerstars_parameters.hpp src/soccerstars_parameters.cpp | $(BUILD_DIR)
	$(CC) -c src/soccerstars_parameters.cpp -o $(BUILD_DIR)/soccerstars_parameters.o

$(BUILD_DIR)/rsdl.o: lib/rsdl.hpp lib/rsdl.cpp | $(BUILD_DIR)
	$(CC) -c lib/rsdl.cpp -o $(BUILD_DIR)/rsdl.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)/*.o soccerStars.out
