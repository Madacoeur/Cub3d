/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamroun <aamroun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 19:48:41 by aamroun           #+#    #+#             */
/*   Updated: 2026/10/09 20:02:36 by aamroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, 800, 600, "cub3D");
	if (!game->win)
	{
		//ajouter la liberation de la fenetre si ca echoue
		return (1);
	}
	return (0);
}

int	close_game(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (gme->mlx)
	{
		mlx_destroy_display(game_mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}

int	key_press(int key_code, t_game *game)
{
	if (keycode == 65307)
		close_game(game);
	return (0);
}

int	main(void)
{
	t_game game;
	if (init_game(&game) != 0)
		return (1);

}
