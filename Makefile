# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/10 13:11:48 by rzimaeva          #+#    #+#              #
#    Updated: 2026/11/26 12:57:05 by rzimaeva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME	=	cub3d
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g -I. -I$(LIBFT_PATH) -I$(GNL_PATH) -I$(LIBMLX_PATH)

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

PINK	=	\033[38;5;213m
PURPLE	=	\033[38;5;141m
RESET	=	\033[0m

all: $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS) $(LIBFT) $(LIBMLX)
	@$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT) -L$(LIBMLX_PATH) -lmlx -lXext -lX11 -lm -o $(NAME)
	@printf "$(PINK)♡ Compilation réussie ! ✧$(RESET)\n"

$(LIBFT):
	@make --no-print-directory -s -C $(LIBFT_PATH) > /dev/null 2>&1

$(LIBMLX):
	@make --no-print-directory -s -C $(LIBMLX_PATH) > /dev/null 2>&1

%.o: %.c cub3d.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(GNL_OBJS)
	@make --no-print-directory -s clean -C $(LIBFT_PATH) > /dev/null 2>&1
	@make --no-print-directory -s clean -C $(LIBMLX_PATH) > /dev/null 2>&1
	@printf "$(PURPLE)✧ Fichiers objets supprimés avec succès ♡$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@make --no-print-directory -s fclean -C $(LIBFT_PATH) > /dev/null 2>&1
	@make --no-print-directory -s clean -C $(LIBMLX_PATH) > /dev/null 2>&1
	@printf "$(PINK)♡ Nettoyage complet effectué ! ✧$(RESET)\n"

re: fclean all
	@printf "$(PURPLE)✧ Recompilation terminée avec succès ♡$(RESET)\n"

.PHONY: all clean fclean re


