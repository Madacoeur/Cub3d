/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamroun <aamroun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 19:48:41 by aamroun           #+#    #+#             */
/*   Updated: 2026/11/14 12:00:00 by aamroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (1);
	// cree une image vide de la taille de la fenetre (on dessinera dedans)
	game->screen.ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->screen.ptr)
		return (1);
	// recupere l'adresse des pixels + remplit bpp, line_len et endian
	game->screen.addr = mlx_get_data_addr(game->screen.ptr,
			&game->screen.bpp, &game->screen.line_len, &game->screen.endian);
	if (!game->screen.addr)
		return (1);
	// on note la taille nous-memes (la mlx ne le fait pas)
	game->screen.width = WIN_WIDTH;
	game->screen.height = WIN_HEIGHT;
	return (0);
}

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		close_game(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		exit_error(&game, "usage: ./cub3D <map.cub>");
	(void)argv;
	if (fake_parsing(&game.config))
		exit_error(&game, "parsing failed");
	if (init_game(&game))
		exit_error(&game, "mlx initialisation failed");
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	// la mlx appellera render() en boucle, des qu'elle n'a rien a faire
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	return (0);
}
