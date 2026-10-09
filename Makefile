NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

MLX_FLAGS   = -lmlx -lXext -lX11 -lm

SRCS        = main.c \

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
