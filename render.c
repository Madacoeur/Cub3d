/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamroun <aamroun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 12:00:00 by aamroun           #+#    #+#             */
/*   Updated: 2026/11/15 12:00:00 by aamroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// dessine une image complete puis l'affiche dans la fenetre
// appelee en boucle par la mlx (mlx_loop_hook dans main.c)
int	render(t_game *game)
{
	// 1. on dessine dans l'image en memoire
	draw_floor_ceiling(game);
	// 2. on envoie toute l'image a la fenetre, coin haut gauche en (0, 0)
	mlx_put_image_to_window(game->mlx, game->win, game->screen.ptr, 0, 0);
	return (0);
}
