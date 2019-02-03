LIBS = -L/usr/local/lib -lglfw -lGLEW -lGL
 
FLAGS = -O3 -ffast-math -Wall

SRC = source/*.cpp source/**/*.cpp

INC = -I headers

CC = g++ -std=gnu++11

all:
	$(CC) $(FLAGS) $(SRC) $(INC) -c && make build

scene: source/modules/Scene.cpp
	$(CC) $(FLAGS) $(INC) $< -c && make build

camera: source/modules/Camera.cpp
	$(CC) $(FLAGS) $(INC) $< -c && make build

build:
	$(CC) ./*.o $(LIBS) $(INC) -o a.out

clean:
	rm -rf ./*.o