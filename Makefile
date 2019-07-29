CC := g++

CFLAGS := `sdl2-config --libs --cflags` -Werror -Wall -Wextra -Wshadow -Wsign-conversion -pedantic-errors

OPT := -O2

lorenz: lorenz.cpp
	${CC} lorenz.cpp ${CFLAGS} ${OPT} -o lorenz
