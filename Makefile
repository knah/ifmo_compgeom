C_FLAGS = -std=c++11 -Wall -Wextra -g -O3 `pkg-config --cflags sdl2`

OBJS = SDLVisualizer.o Point2D.o

all: loc

clean:
	rm -f loc
	rm -f *.o

loc: main.cpp $(OBJS) $(ASM_OBJS)
	clang++ $(C_FLAGS) -o loc main.cpp $(OBJS) $(ASM_OBJS) -lm -lSDL2 -lgmpxx -lgmp

%.o: %.cpp
	clang++ -c -o $@ $(C_FLAGS) $^


