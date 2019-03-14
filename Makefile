PLATFORM = $(shell uname)

TARGET = a.out

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	LIBS = -L/usr/local/lib -lglfw -lGLEW -lGL -lSOIL
endif

ifeq ($(findstring Darwin,$(PLATFORM)),Darwin)
	LIBS = -L/usr/local/lib -lglfw -lGLEW -lSOIL -framework OpenGL -framework CoreFoundation
endif
 
FLAGS = -O3 -Wall

SRC = src/*.cpp src/**/*.cpp

OBJ = obj/

INC = -I include

CC = g++ -std=gnu++11

DBG = -g1 -rdynamic

SOURCE=$(wildcard src/*.cpp src/**/*cpp)
OBJS=$(patsubst %.cpp,$(OBJ)%.o,$(SOURCE))

all: compare move link

compare:
	$(CC) $(FLAGS) $(SRC) $(INC) -c

scene: src/modules/Scene.cpp
	$(CC) $(FLAGS) $(INC) $< -c && make move && make link

app: src/core/App.cpp
	$(CC) $(FLAGS) $(INC) $< -c && make move && make link

camera: src/modules/Camera.cpp
	$(CC) $(FLAGS) $(INC) $< -c && make move && make link

ter: src/geometry/Terrain.cpp
	$(CC) $(FLAGS) $(INC) $< -c && make move && make link

poly: src/modules/Poly.cpp
	$(CC) $(FLAGS) $(INC) $< -c && make move && make link

move:
	mv ./*.o $(OBJ)

link:
	$(CC) $(OBJ)*.o $(LIBS) $(INC) -o $(TARGET)

clean:
	rm -rf $(OBJ)*.o ./*.o 
