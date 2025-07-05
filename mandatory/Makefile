# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kben-tou <kben-tou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 20:22:14 by kben-tou          #+#    #+#              #
#    Updated: 2025/07/05 20:22:43 by kben-tou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = src/main.c \
			src/utils/memset.c \
			src/utils/memory_managemnt.c \
			src/utils/libft_tools_0.c \
			src/utils/libft_tools_1.c \
			src/utils/libft_tools_2.c \
			src/utils/libft_tools_3.c \
			src/utils/ray_utils.c\
			src/utils/horizantal_calcule.c \
			src/utils/vertical_calcul.c \
			src/utils/plr_moving_utils.c \
			src/parsing/map_getting.c \
			src/parsing/map_parsing.c \
			src/parsing/conf_parsing.c \
			src/parsing/texture_parsing.c \
			src/parsing/color_parsing.c \
			src/parsing/map_utils.c \
			src/parsing/map_components.c \
			src/engine/raycasting.c \
			src/engine/texture_drawing.c \
			src/engine/intial_game.c \
			src/engine/key_event_handle.c \
			src/engine/plr_moving.c \
			src/engine/sprite_handler.c \
			src/engine/mouse_dete.c 

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all