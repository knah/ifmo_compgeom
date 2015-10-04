# this actually requires c++14; clang doesn't support it, but does support the required extensions
C_FLAGS = -std=c++11 -Wall -Wextra -g -O0 `pkg-config --cflags sdl2`
OBJS = SDLVisualizer.o Point2D.o
EXTRA_DEPENDS = IVisualizer.hpp Point2D.hpp SDLVisualizer.hpp DummyVisualizer.hpp

all: loc

clean:
	rm -f loc
	rm -f *.o

loc: main.cpp $(OBJS)
	clang++ $(C_FLAGS) -o loc main.cpp $(OBJS) -lm -lSDL2 -lgmpxx -lgmp

%.o: %.cpp
	clang++ $(C_FLAGS) -c -o $@ $^


