#include "cub3d.h"


int main(void)
{
    t_game game;
    init(&game);
    int fd = open("text.txt", O_RDONLY);
    read_map(fd, &game);

    printf("%s", game.we_texture);
}


