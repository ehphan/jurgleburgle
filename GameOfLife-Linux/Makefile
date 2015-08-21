OBJS = game_of_life.cpp element.cpp world.cpp

CC = g++

# -w suppresses all warnings
COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = game_of_life

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 

clean:
	rm $(OBJ_NAME)
