NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -std=gnu17

# Chemins et flags pour ta minilibx locale
MLX_DIR     = ./minilibx-linux
MLX_LIB     = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm
MLX_INC     = -I $(MLX_DIR)

HEADER      = cub3d.h
SRCS        = main.c \
              free.c \
              utils.c \
              draw.c \
              render.c \
              player.c \
              raycast.c \
              fake_parsing.c
OBJS        = $(SRCS:.c=.o)

all: $(NAME)

# Compile les .c en .o en incluant le bon chemin pour mlx.h
# (recompile aussi si cub3d.h change)
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

# Compile la minilibx seulement si l'archive n'existe pas encore
$(MLX_LIB):
	make -C $(MLX_DIR) CC="cc -std=gnu17"

# Lie l'executable seulement si un .o ou la minilibx a change (pas de relink)
$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

bonus: all

clean:
	rm -f $(OBJS)
	-make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
