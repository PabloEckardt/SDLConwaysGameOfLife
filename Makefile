CC = g++

OBJS = conway.cpp

OBJ_NAME = main 

LINKER_FLAGS = -lSDL2

COMPILER_FLAGS = 

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $ -o $(OBJ_NAME)
