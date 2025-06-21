NAME = cub3d

SRC = src/main.c \
			src/utils/memset.c \
			src/utils/memory_managemnt.c \
			src/utils/libft_tools_0.c \
			src/utils/libft_tools_1.c \
			src/utils/ray.utils.c\
			src/utils/horizantal_calcule.c \
			src/utils/vertical_calcul.c \
			src/parsing/map_getting.c \
			src/parsing/map_parsing.c \
			src/parsing/conf_parsing.c \
			src/parsing/texture_parsing.c \
			src/parsing/color_parsing.c \
			src/parsing/map_utils.c \
			src/engine/map_drawing.c \
			src/engine/raycasting.c \
			src/engine/draw_tools.c \
			src/engine/player_drawing.c \
			src/engine/texture_drawing.c \
			src/engine/intial_game.c \
			src/engine/key_event_handle.c \
			src/engine/minimap.c \
			src/engine/plr_moving.c \
			src/engine/mouse_dete.c \

OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)


CC = cc
INCLUDES = -Iinc
CFLAGS = -g -Wno-incompatible-pointer-types #-fsanitize=address
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    INCLUDES += -I${HOME}/.local/include
    LIBS = -L${HOME}/.local/lib -lmlx -lXext -lX11 -lm
else ifeq ($(UNAME_S),Darwin)
    LIBS = -lmlx -framework OpenGL -framework AppKit
else
    $(error OS not supported: $(UNAME_S))
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
