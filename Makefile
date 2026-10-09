NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

# Chemins et flags pour ta minilibx locale
MLX_DIR     = ./minilibx-linux
MLX_FLAGS   = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm
MLX_INC     = -I $(MLX_DIR)

SRCS        = main.c
OBJS        = $(SRCS:.c=.o)

all: $(NAME)

# Compile les .c en .o en incluant le bon chemin pour mlx.h
%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

# Compile d'abord la minilibx, puis ton exécutable
$(NAME): $(OBJS)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)
	-make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
