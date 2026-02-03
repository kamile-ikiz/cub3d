NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
#MINIDIR = ./extras/minilibx-linux
SRCS = src/main.c src/utils.c src/utils2.c src/ft_atoi.c src/ft_split.c extras/get_next_line/get_next_line.c extras/get_next_line/get_next_line_utils.c src/checks.c

#MINILIBNAME = ./extras/minilibx-linux/libmlx.a


OBJ = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
#		make -C ${MINIDIR}
		ar rcs ${NAME} ${OBJ}
		${CC} ${CFLAGS} ${SRCS} -o ${NAME} -lX11 -lXext -lm
		
clean:
#		make clean -C ${MINIDIR}
		${RM} ${OBJ}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re