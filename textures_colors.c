/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:42:02 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/11/20 18:06:14 by rzimaeva         ###   ########.fr       */
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
	if ((ft_strncmp(&line[i], "NO", 2) == 0) && (line[i + 2] == '\t' || line[i
				+ 2] == ' '))
	{
		double_def_tex("NO", game->no_texture);
		parse_texture(line, &i, &game->no_texture, 2);
		return (1);
	}
	else if ((ft_strncmp(&line[i], "SO", 2) == 0) && (line[i + 2] == '\t' || line[i
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
	if ((ft_strncmp(&line[i], "EA", 2) == 0) && (line[i + 2] == '\t' || line[i
				+ 2] == ' '))
	{
		double_def_tex("EA", game->ea_texture);
		parse_texture(line, &i, &game->ea_texture, 2);
		return (1);
	}
	else if ((ft_strncmp(&line[i], "WE", 2) == 0) && (line[i + 2] == '\t' || line[i
				+ 2] == ' '))
	{
		double_def_tex("WE", game->we_texture);
		parse_texture(line, &i, &game->we_texture, 2);
		return (1);
	}
	return (0);
}

int	check_colors(char *line, t_game *game)
{
    int		i;
    
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
    i++;
	if (!line[i])
    return (1);
	if ((line[i] == 'F' || line[i] == 'C')
    && (line[i + 1] == ' ' || line[i + 1] == '\t'))
	{
        if (line[i] == 'F')
            double_def_col("F", game->f_already_def);
		else
            double_def_col("C", game->c_already_def);
		if (!parse_color(line, game))
		{
            write(2, "Error: Invalid color format.\n", 29);
			exit(1);
		}
		return (1);
	}
	return (0);
}
// colors : repere si la ligne correspond a F ou C,
// verifie les doublons et lance le parsing de la couleur