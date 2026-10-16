/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:42:02 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/10/16 13:57:05 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	textures_p1(char *line, t_game *game)
{
	int	i;

	i = 0;
	while ((line[i] == '\t' || line[i] == ' ') && line[i])
		i++;
	if ((strncmp(&line[i], "NO", 2) == 0) && (line[i + 2] == '\t' || line[i
				+ 2] == ' '))
	{
		double_def("NO", game->no_texture);
		parse_texture(line, &i, &game->no_texture, 2);
	}
	else if ((strncmp(&line[i], "SO", 2) == 0) && (line[i + 2] == '\t' || line[i
				+ 2] == ' '))
	{
		double_def("SO", game->so_texture);
		parse_texture(line, &i, &game->so_texture, 2);
	}
	return (0);
}

int	textures_p2(char *line, t_game *game)
{
	int	i;

	i = 0;
	while ((line[i] == '\t' || line[i] == ' ') && line[i])
		i++;
	if ((strncmp(&line[i], "EA", 2) == 0) && (line[i + 2] == '\t' || line[i
				+ 2] == ' '))
	{
		double_def("EA", game->ea_texture);
		parse_texture(line, &i, &game->ea_texture, 2);
	}
	else if ((strncmp(&line[i], "WE", 2) == 0) && (line[i + 2] == '\t' || line[i
				+ 2] == ' '))
	{
		double_def("WE", game->we_texture);
		parse_texture(line, &i, &game->we_texture, 2);
	}
	return (0);
}

int	colors(char *line, t_game *game)
{
	int	i;

	i = 0;
	while ((line[i] == '\t' || line[i] == ' ') && line[i])
		i++;
	if ((strncmp(&line[i], "F", 1) == 0) && (line[i + 1] == '\t' || line[i
				+ 1] == ' '))
	{
		double_def("F", game->floor_color);
		parse_texture(line, &i, &game->floor_color, 1);
	}
	else if ((strncmp(&line[i], "C", 1) == 0) && (line[i + 1] == '\t' || line[i
				+ 1] == ' '))
	{
		double_def("C", game->ceiling_color);
		parse_texture(line, &i, &game->ceiling_color, 1);
	}
	return (0);
}
