CC = g++
CFLAGS = -std=c++11 -I/opt/homebrew/include -I/opt/homebrew/include/SDL2
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf

ifeq ($(OS),Windows_NT)
    CC = x86_64-w64-mingw32-g++

    CFLAGS += -I/c/mingw64/include/SDL2 -I/c/mingw64/include/SDL2_image -I/c/mingw64/include/SDL2_ttf
    LDFLAGS = -L/c/mingw64/lib -lSDL2 -lSDL2_image -lSDL2_ttf
    LDFLAGS += -static-libgcc -static-libstdc++

    EXT = .exe
    BIN_DIR = bin
    OBJ_DIR = obj
else
    EXT = 
    BIN_DIR = bin
    OBJ_DIR = obj
endif

SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TARGET = $(BIN_DIR)/compilado$(EXT)

all: $(TARGET)

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)


run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/*
