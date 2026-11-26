/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:44:30 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/11/26 16:24:00 by rzimaeva         ###   ########.fr       */
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

//static void	handle_texcol_line(char *line, t_game *game, int fd)
//{
	//if (!textures_p1(line, game, fd) && !textures_p2(line, game, fd)
		//&& !check_colors(line, game, fd))
		//check_unknown_id(line, game, fd);
	//free(line);
//}

int handle_texcol_line(char *line, t_game *game, int fd)
{
    int ret;

    ret = textures_p1(line, game, fd);
    if (ret == -1)
        return (-1);
    if (ret == 0)
    {
        ret = textures_p2(line, game, fd);
        if (ret == -1)
            return (-1);
    }
    if (ret == 0)
    {
        ret = check_colors(line, game, fd);
        if (ret == -1)
            return (-1);
    }
    if (ret == 0)
        check_unknown_id(line, game, fd);
    return (1);
}

static int	read_map_lines(int fd, t_game *game)
{
	char	*line;
	int		i;
	int     ret;

	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (game->height > 0 && !line[i])
			return (write(2, "Error: Empty line in map.\n", 26),
				free(line), cleanup_parsing(game, fd), 1);
		if (is_map_line(line))
		{
			if (!add_map_line(game, line))
				return (free(line), cleanup_parsing(game, fd), 1);
		}
		else
		{
            ret = handle_texcol_line(line, game, fd);
            if (ret == -1)
                return (free(line), cleanup_parsing(game, fd), 1);
        }
		line = get_next_line(fd);
	}
	return (0);
}

int	read_map(int fd, t_game *game)
{
	if (read_map_lines(fd, game))
		return (1);
	close(fd);
	if (check_textures(game) || !game->map || !game->height)
		return (cleanup_parsing(game, -1), 1);
	if (!validate_map(game) || !map_closed_verif(game))
		return (cleanup_parsing(game, -1), 1);
	return (0);
}
