/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamroun <aamroun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 12:00:00 by aamroun           #+#    #+#             */
/*   Updated: 2026/11/15 12:00:00 by aamroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// donne au joueur sa direction (dir) et calcule son plan camera (plane)
// le plan est toujours perpendiculaire a dir, vers la droite du joueur
static void	set_direction(t_player *player, double dir_x, double dir_y)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
	// tourner (x, y) d'un quart de tour vers la droite donne (-y, x)
	player->plane_x = -dir_y * FOV_PLANE;
	player->plane_y = dir_x * FOV_PLANE;
}

// place le joueur au centre de sa case de depart et l'oriente selon N/S/E/W
// rappel : l'axe y descend, donc le nord c'est y = -1
void	init_player(t_game *game)
{
	char	dir;

	// + 0.5 : on se met au milieu de la case, pas dans un coin
	game->player.pos_x = game->config.start_x + 0.5;
	game->player.pos_y = game->config.start_y + 0.5;
	dir = game->config.start_dir;
	if (dir == 'N')
		set_direction(&game->player, 0, -1);
	else if (dir == 'S')
		set_direction(&game->player, 0, 1);
	else if (dir == 'E')
		set_direction(&game->player, 1, 0);
	else
		set_direction(&game->player, -1, 0);
}
