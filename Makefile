CXX = clang++
CXXFLAGS = -std=c++17 -Wall

debug: CXXFLAGS += -DBANANA_LOG -g
debug: all

release: CXXFLAGS += -O3
release: all

SDL_PREFIX := $(shell brew --prefix sdl2)
SDL_TTF_PREFIX := $(shell brew --prefix sdl2_ttf)
SDL_INC = -I$(SDL_PREFIX)/include -I$(SDL_TTF_PREFIX)/include/SDL2
SDL_LIB = -L$(SDL_PREFIX)/lib -L$(SDL_TTF_PREFIX)/lib 

ASSIMP_PREFIX := $(shell brew --prefix assimp)
ASSIMP_INC = -I$(ASSIMP_PREFIX)/include
ASSIMP_LIB = -L$(ASSIMP_PREFIX)/lib

LIBS = -lSDL2 -lSDL2_ttf -lassimp -framework OpenGL

TARGET = main

OBJ = \
	main.o \
	BananaEngine/Window.o \
	BananaEngine/GameController.o \
	BananaEngine/Input.o \

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Linking [$@]"
	@$(CXX) $^ $(LIBS) $(SDL_LIB) $(ASSIMP_LIB) -o $(TARGET)

%.o: %.cpp
	@echo "Compiling [$<]"
	@$(CXX) -c $< $(CXXFLAGS) $(SDL_INC) $(ASSIMP_INC) -o $@

clean:
	@rm -f $(TARGET)
	@rm -f $(OBJ)
