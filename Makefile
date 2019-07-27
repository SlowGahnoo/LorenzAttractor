CC := g++

CFLAGS := `sdl2-config --libs --cflags` -Wall -Wextra -Wshadow

OPT := -O2

lorenz: lorenz.cpp
	${CC} lorenz.cpp ${CFLAGS} ${OPT} -o lorenz
