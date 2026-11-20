/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 17:23:40 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/11/20 18:02:23 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_map_chars(char **map, int height)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			if (!valid_map_char(map[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	character_pos(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	free_grid(char **grid, int height)
{
	int	y;

	if (!grid)
		return ;
	y = 0;
	while (y < height)
	{
		free(grid[y]);
		y++;
	}
	free(grid);
}