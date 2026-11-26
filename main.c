/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 16:36:20 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/11/26 12:12:19 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_map(t_game *game)
{
	int	y;

	printf("NO: %s\nSO: %s\nEA: %s\nWE: %s\n",
		game->no_texture, game->so_texture,
		game->ea_texture, game->we_texture);
	printf("Floor: %d,%d,%d | Ceiling: %d,%d,%d\n",
		game->floor_color[0], game->floor_color[1], game->floor_color[2],
		game->ceiling_color[0], game->ceiling_color[1], game->ceiling_color[2]);
	printf("Height: %d | Width: %d\n", game->height, game->width);
	y = 0;
	while (y < game->height)
	{
		printf("[%s]\n", game->map[y]);
		y++;
	}
}

int	main(int ac, char **av)
{
	t_game	game;
	int		fd;

	init_struct(&game);
	if (map_exist(ac, av, &fd))
		return (1);
	if (read_map(fd, &game))
	{
		free_grid(game.map, &game);
		free_textures(&game);
		return (1);
	}
	print_map(&game);
	free_grid(game.map, &game);
	free_textures(&game);
	return (0);
}