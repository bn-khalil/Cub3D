NAME = cub3d

SRC = src/main.c \
		src/libft_tools_0.c \
		src/libft_tools_1.c \
		src/parsing/map_getting.c \
		src/parsing/map_parsing.c \
		src/parsing/conf_parsing.c \
		src/parsing/texture_parsing.c \
		src/parsing/color_parsing.c \
		src/parsing/map_utils.c \
		

OBJ = $(SRC:.c=.o)

MFLAGS = -lmlx -framework OpenGL -framework Appkit
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

all: $(NAME)

$(NAME):$(OBJ) inc/cub3d.h
	cc $(CFLAGS) $(MFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
