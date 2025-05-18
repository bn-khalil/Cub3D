NAME = cub3d

SRC = src/main.c \
		src/libft_tools.c \

OBJ = $(SRC:.c=.o)

MFLAGS = -lmlx -framework OpenGL -framework Appkit
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):$(OBJ) inc/cub3d.h
	cc $(CFLAGS) $(MFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
