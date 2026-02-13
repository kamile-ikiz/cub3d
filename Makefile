NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MINIDIR = ./extras/minilibx-linux
SRCS = src/main.c src/ft_atoi.c src/ft_split.c src/checks.c \
	src/checks_utils.c src/parsing.c src/utils_string.c \
	src/utils_memory.c src/utils_map.c src/player.c \
	src/texture.c src/texture_utils.c src/color.c src/char_utils.c \
	extras/get_next_line/get_next_line.c \
	extras/get_next_line/get_next_line_utils.c \
	src/utils.c src/color_utils.c src/mlx_init.c
MINILIBNAME = ./extras/minilibx-linux/libmlx.a


OBJ = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
		make -C ${MINIDIR}
		ar rcs ${NAME} ${OBJ}
		${CC} ${CFLAGS} ${SRCS} ${MINILIBNAME} -o ${NAME} -lX11 -lXext -lm
		
clean:
		make clean -C ${MINIDIR}
		${RM} ${OBJ}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re