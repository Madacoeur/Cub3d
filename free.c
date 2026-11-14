/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamroun <aamroun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 12:00:00 by aamroun           #+#    #+#             */
/*   Updated: 2026/11/14 12:00:00 by aamroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(config->tex_path[i]);
		config->tex_path[i] = NULL;
		i++;
	}
	if (config->map)
	{
		i = 0;
		while (i < config->map_h)
			free(config->map[i++]);
		free(config->map);
		config->map = NULL;
	}
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].ptr)
			mlx_destroy_image(game->mlx, game->tex[i].ptr);
		game->tex[i].ptr = NULL;
		i++;
	}
	if (game->screen.ptr)
		mlx_destroy_image(game->mlx, game->screen.ptr);
	game->screen.ptr = NULL;
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	free_config(&game->config);
}

void	exit_error(t_game *game, char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free_game(game);
	exit(1);
}
