/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 17:23:40 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/11/26 11:49:51 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	character_pos(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_map(t_game *game)
{
	int	y;
	int	x;
	int	players;

	if (!validate_map_lines(game))
		return (0);
	y = 0;
	players = 0;
	while (y < game->height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (!valid_map_char(game->map[y][x]))
				return (0);
			if (character_pos(game->map[y][x]))
				players++;
			x++;
		}
		y++;
	}
	if (players != 1) // si c'est pas un seul player donc le booleen est incorrect ca renvoie direct 0
		return (write(2, "Error: Wrong number of player.\n", 32), 0);
	return (players == 1); // si c'est bien un seul player donc le booleen est correct ca renvoie direct 1
}
// sert a verifier que la map est valide en verifiant que toutes les lignes existent,
// que tous les caracteres sont valides et qu'il y a exactement un joueur

int	validate_map_lines(t_game *game)
{
	int	y;
	
	if (!game->map || game->height <= 0)
	return (0);
	y = 0;
	while (y < game->height)
	{
		if (!game->map[y])
		return (0);
		y++;
	}
	return (1);
}
