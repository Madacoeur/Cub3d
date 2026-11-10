/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:42:02 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/11/10 18:18:59 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	textures_p1(char *line, t_game *game)
{
	int	i;

	i = 0;
	while ((line[i] == '\t' || line[i] == ' ') && line[i])
		i++;
	if (!line[i])
		return (1);
	if ((strncmp(&line[i], "NO", 2) == 0) && (line[i + 2] == '\t' || line[i
				+ 2] == ' '))
	{
		double_def_tex("NO", game->no_texture);
		parse_texture(line, &i, &game->no_texture, 2);
		return (1);
	}
	else if ((strncmp(&line[i], "SO", 2) == 0) && (line[i + 2] == '\t' || line[i
				+ 2] == ' '))
	{
		double_def_tex("SO", game->so_texture);
		parse_texture(line, &i, &game->so_texture, 2);
		return (1);
	}
	return (0);
}
// if (!line[i]) si c'est une ligne vide, avec uniquement des espaces
// ou des caracteres autre que NO SO etc

int	textures_p2(char *line, t_game *game)
{
	int	i;

	i = 0;
	while ((line[i] == '\t' || line[i] == ' ') && line[i])
		i++;
	if (!line[i])
		return (1);
	if ((strncmp(&line[i], "EA", 2) == 0) && (line[i + 2] == '\t' || line[i
				+ 2] == ' '))
	{
		double_def_tex("EA", game->ea_texture);
		parse_texture(line, &i, &game->ea_texture, 2);
		return (1);
	}
	else if ((strncmp(&line[i], "WE", 2) == 0) && (line[i + 2] == '\t' || line[i
				+ 2] == ' '))
	{
		double_def_tex("WE", game->we_texture);
		parse_texture(line, &i, &game->we_texture, 2);
		return (1);
	}
	return (0);
}

int	color_f(char *line, t_game *game)
{
	int	i;

	i = 0;
	if ((strncmp(&line[i], "F", 1) == 0) && (line[i + 1] == '\t' || line[i
				+ 1] == ' '))
	{
		double_def_col("F", game->f_already_def);
		if (!parse_color(line, game))
		{
			write(2, "Error: Invalid color format.\n", 30);
			exit(1);
		}
		return (1);
	}
	return (0);
}

int	color_c(char *line, t_game *game)
{
	int	i;

	i = 0;
	if ((strncmp(&line[i], "C", 1) == 0) && (line[i + 1] == '\t' || line[i
				+ 1] == ' '))
	{
		double_def_col("C", game->c_already_def);
		if (!parse_color(line, game))
		{
			write(2, "Error: Invalid color format.\n", 30);
			exit(1);
		}
		return (1);
	}
	return (0);
}

int	colors(char *line, t_game *game)
{
	int	i;

	i = 0;
	while ((line[i] == '\t' || line[i] == ' ') && line[i])
		i++;
	if (!line[i])
		return (1);
	if (color_f(&line[i], game))
		return (1);
	if (color_c(&line[i], game))
		return (1);
	return (0);
}
// on pointe nos tableaux sur 0 parce que c'est la premiere case donc le 'R' du RGB
