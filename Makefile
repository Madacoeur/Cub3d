# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/10 13:11:48 by rzimaeva          #+#    #+#              #
#    Updated: 2026/11/25 17:04:59 by rzimaeva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d
CC		=	cc 
CFLAGS	=	-Wall -Wextra -Werror -I. -I$(LIBFT_PATH) -I$(GNL_PATH) -I$(LIBMLX_PATH)

LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a

GNL_PATH	=	./get_next_line
GNL_SRCS	=	$(GNL_PATH)/get_next_line.c \
				$(GNL_PATH)/get_next_line_utils.c
GNL_OBJS	=	$(GNL_SRCS:.c=.o)

LIBMLX_PATH	=	./minilibx-linux
LIBMLX		=	$(LIBMLX_PATH)/libmlx.a

SRCS	=	main.c \
			errors_check.c \
			floodfill_utils.c \
			floodfill.c \
			free.c \
			map_texture_utils.c \
			map_texture.c \
			parse_rgb.c \
			textures_colors.c
OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS) $(GNL_OBJS) $(LIBFT) $(LIBMLX)
			$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT) -L$(LIBMLX_PATH) -lmlx -lXext -lX11 -lm -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(LIBMLX):
	make -C $(LIBMLX_PATH)

%.o:		%.c cub3d.h
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -f $(OBJS) $(GNL_OBJS)
			make clean -C $(LIBFT_PATH)
			make clean -C $(LIBMLX_PATH)

fclean:		clean
			rm -f $(NAME)
			make fclean -C $(LIBFT_PATH)
			make clean -C $(LIBMLX_PATH)

re: 		fclean all

.PHONY: 	all clean fclean re