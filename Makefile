#OBJS - specifies which files to compile as part of the project
OBJS = src/main.cpp 
 
#CC - specifies which compiler we're using
CC = g++

#COMPILER_FLAGS - specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -I/usr/include/SDL2

#LINKER_FLAGS - specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -Wall -Werror -Wextra -std=gnu89 -pedantic

#OBJ_NAME - specifies the name of our exectuable
OBJ_NAME = Maze_SDL

# Compile and run the exectuable
all : compile run

# Compile the executable
compile : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

# Run the executable
run : 
	./$(OBJ_NAME)
# g++ -o raycaster main.cpp -lSDL2