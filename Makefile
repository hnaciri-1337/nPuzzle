SRCS = *.cpp
OBJS = *.o
INCLUDE = *.hpp
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++17
NAME = nPuzzle

all: ${NAME}

${NAME}: ${SRCS} ${INCLUDE}
	${CC} ${CFLAGS} -c ${SRCS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
clean:
	rm -f ${OBJS}
fclean: clean
	rm -f ${NAME}
run: all clean
	clear && ./${NAME}
re : fclean all
