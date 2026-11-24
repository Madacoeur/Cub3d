/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:44:30 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/11/24 16:25:39 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_map_width(t_game *game, char *line)
{
	int	len;

	len = (int)ft_strlen(line);
	if (len > game->width)
		game->width = len; //si la longueur de la ligne ajoutee est superieur a la lngr totale de la map alors ca remplace
}

static int	add_map_line(t_game *game, char *line)
{
	char		**new_map;
	int					i;

	new_map = malloc(sizeof(char *) * (game->height + 2));
	if (!new_map)
		//free_grid(game->map, game);
		//game->map = NULL; // on remet a NULL pour bien nettoyer
		return (0);
	i = 0;
	while (i < game->height)
	{
		new_map[i] = game->map[i]; // recopie l'ancien tab d'adresses dans la nouvelle map
		i++;
	}
	new_map[i] = line; // place la nvlle ligne a la fin 
	new_map[i + 1] = NULL; // apres la nvlle ligne on s'arrete la
	free(game->map);
	game->map = new_map; // remplace l'ancien tab d'adresses apres s'en etre debarrasse avec le free
	game->height++;
	update_map_width(game, line);
	return (1);
}
// on aggrandi le tableau petit a petit avec ca parce qu'on a pas une taille decise du tableau

static void	handle_config_line(char *line, t_game *game, int fd)
{
	if (!textures_p1(line, game) && !textures_p2(line, game)
		&& !check_colors(line, game))
		check_unknown_id(line, game, fd);
	free(line);
}

int	read_map(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		if (is_map_line(line, game))
		{
			if (!add_map_line(game, line))
				return (free(line), close(fd), 1);
		}
		else
			handle_config_line(line, game, fd);
		line = get_next_line(fd);
	}
	close(fd);
	if (check_textures(game))
		return (free_grid(game->map, game), game->map = NULL, 1);
	if (!game->map || game->height == 0)
		return (1);
	if (!validate_map(game))
		return (free_grid(game->map, game), game->map = NULL, 1);
	if (!map_closed_verif(game))
		return (free_grid(game->map, game), game->map = NULL, 1);
	return (0);
}
