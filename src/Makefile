TARGET = rpi_nexa_controller
CC = g++

HEADERS  := $(wildcard *.h)
CPPFLAGS := -I. -MMD -MP -std=c++14
CFLAGS = -I.  -Wall -O2 -falign-functions=1 -falign-jumps=1 -falign-loops=1 -falign-labels=1 
LDLIBS   := -lwiringPi -lwiringPiDev -lcrypt



BUILD_DIR := build
SRC_DIR := .
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := .

EXE := $(BIN_DIR)/$(TARGET)
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))



.PHONY: all clean run

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

#.PRECIOUS: $(TARGET) $(OBJ)


$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@


clean:
	@$(RM) -rv $(BUILD_DIR) $(OBJ_DIR)
	@$(RM)  $(EXE)

run:
	./$(EXE)