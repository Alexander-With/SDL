#OBJS specifies which files to compile as part of the project
OBJS = 08_geometry_rendering.cpp

#CC specifies which compiler we-re using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\mingw-w64\i686-w64-mingw32\include\SDL2

#LIBARY_PATHS specifies the additional libary paths we'll need
LIBARY_PATHS = -LC:\mingw-w64\i686-w64-mingw32\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
#	"-w" supresses all warnings
#	"-Wl,-subsystem,windows" gets rid of the consol windows
COMPILER_FLAGS = -w -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

#OBJ_NAME specifies the name of our execuable
OBJ_NAME = 08_geometry_rendering

#This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)