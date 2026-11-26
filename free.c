/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 16:56:41 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/11/26 12:25:07 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_grid(char **grid, t_game *game)
{
	int	y;

	if (!grid)
		return ;
	y = 0;
	while (y < game->height)
	{
		free(grid[y]);
		y++;
	}
	free(grid);
}

void	free_textures(t_game *game)
{
	free(game->no_texture);
	game->no_texture = NULL;
	free(game->so_texture);
	game->so_texture = NULL;
	free(game->ea_texture);
	game->ea_texture = NULL;
	free(game->we_texture);
	game->we_texture = NULL;
}

void	cleanup_parsing(t_game *game, int fd)
{
	if (game)
	{
		free_textures(game);
		if (game->map)
		{
			free_grid(game->map, game);
			game->map = NULL;
		}
	}
	get_next_line(-1);
	if (fd >= 0)
		close(fd);
}
//gnl -1 parce que quand on fd < 0 ca compte le -1 donc on free comme dans la fonction