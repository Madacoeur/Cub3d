/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamroun <aamroun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 12:00:00 by aamroun           #+#    #+#             */
/*   Updated: 2026/11/14 12:00:00 by aamroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** TEMPORAIRE : remplit t_config comme le fera le vrai parsing.
** A supprimer quand le parsing du binome sera fusionne.
*/

static char	*copy_line(const char *src, int len)
{
	char	*line;
	int		i;

	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = src[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	fill_map(t_config *config, const char *src, int width)
{
	int	y;

	config->map = malloc(sizeof(char *) * (config->map_h + 1));
	if (!config->map)
		return (1);
	y = 0;
	while (y <= config->map_h)
		config->map[y++] = NULL;
	y = 0;
	while (y < config->map_h)
	{
		config->map[y] = copy_line(src + y * (width + 1), width);
		if (!config->map[y])
			return (1);
		y++;
	}
	return (0);
}

int	fake_parsing(t_config *config)
{
	config->map_h = 7;
	if (fill_map(config, "1111111111/1000000001/1011000101/1000N00001/"
			"1000001101/1000000001/1111111111", 10))
		return (1);
	config->tex_path[TEX_NO] = ft_strdup("./textures/north.xpm");
	config->tex_path[TEX_SO] = ft_strdup("./textures/south.xpm");
	config->tex_path[TEX_WE] = ft_strdup("./textures/west.xpm");
	config->tex_path[TEX_EA] = ft_strdup("./textures/east.xpm");
	if (!config->tex_path[TEX_NO] || !config->tex_path[TEX_SO]
		|| !config->tex_path[TEX_WE] || !config->tex_path[TEX_EA])
		return (1);
	config->floor_color = (220 << 16) | (100 << 8) | 0;
	// plafond bleu ciel : bien different du sol orange pour les tests
	config->ceil_color = (100 << 16) | (150 << 8) | 255;
	config->start_x = 4;
	config->start_y = 3;
	config->start_dir = 'N';
	return (0);
}
