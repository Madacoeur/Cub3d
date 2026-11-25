/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 16:56:41 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/11/25 17:05:48 by rzimaeva         ###   ########.fr       */
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

void	empty_gnl(int fd)
{
	char	*pipi;

	if (fd < 0)
		return ;
	pipi = get_next_line(fd);
	while (pipi)
	{
		free(pipi);
		pipi = get_next_line(fd);
	}
}

void	cleanup_parsing(t_game *game, int fd)
{
	free_textures(game);
	if (game->map)
	{
		free_grid(game->map, game);
		game->map = NULL;
	}
	empty_gnl(fd);
	if (fd >= 0)
		close(fd);
}
