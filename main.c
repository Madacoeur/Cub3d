/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamroun <aamroun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 19:48:41 by aamroun           #+#    #+#             */
/*   Updated: 2026/10/09 21:03:40 by aamroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, 800, 600, "cub3D");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (1);
	}
	return (0);
}

int	close_game(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}

int	key_press(int key_code, t_game *game)
{
	if (key_code == 65307)
		close_game(game);
	return (0);
}

int	main(void)
{
	t_game game;
	if (init_game(&game) != 0)
		return (1);
	mlx_hook(game.win, 2, 1L<<0, (int (*)())(void (*)(void))key_press, &game);
	//hook pour la croix rouge (evenement 17)
	mlx_hook(game.win, 17, 1L<<17, (int (*)())(void (*)(void))close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
