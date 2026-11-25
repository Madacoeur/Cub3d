/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamroun <aamroun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 12:00:00 by aamroun           #+#    #+#             */
/*   Updated: 2026/11/15 12:00:00 by aamroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// prepare le rayon de la colonne x : sa direction et sa case de depart
static void	init_ray(t_player *p, t_ray *ray, int x)
{
	// camera_x va de -1 (bord gauche de l'ecran) a +1 (bord droit)
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	// direction du rayon = regard + un morceau du plan camera
	ray->ray_dir_x = p->dir_x + p->plane_x * ray->camera_x;
	ray->ray_dir_y = p->dir_y + p->plane_y * ray->camera_x;
	// le rayon part de la case ou se trouve le joueur
	ray->map_x = (int)p->pos_x;
	ray->map_y = (int)p->pos_y;
	// distance pour traverser une case entiere en x (puis en y)
	// si le rayon ne bouge pas en x, il ne traversera jamais : valeur enorme
	ray->delta_dist_x = 1e30;
	if (ray->ray_dir_x != 0)
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = 1e30;
	if (ray->ray_dir_y != 0)
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

// choisit le sens d'avance (step) et la distance jusqu'au 1er bord de case
static void	init_step(t_player *p, t_ray *ray)
{
	// en x : vers la gauche (-1) ou vers la droite (+1)
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->pos_x) * ray->delta_dist_x;
	}
	// en y : vers le haut (-1) ou vers le bas (+1)
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->pos_y) * ray->delta_dist_y;
	}
}

// vrai si la case (x, y) est un mur, ou en dehors de la carte (securite)
static int	is_wall(t_config *config, int x, int y)
{
	if (y < 0 || y >= config->map_h || x < 0)
		return (1);
	if (x >= (int)ft_strlen(config->map[y]))
		return (1);
	return (config->map[y][x] == '1');
}

// dda : on saute de case en case jusqu'a tomber sur un mur
static void	run_dda(t_config *config, t_ray *ray)
{
	while (ray->hit == 0)
	{
		// le prochain bord vertical est plus proche : on change de colonne
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		// sinon le bord horizontal est plus proche : on change de ligne
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(config, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
	// distance perpendiculaire au mur (evite l'effet fish-eye) :
	// c'est la derniere side_dist, moins le dernier saut
	if (ray->side == 0)
		ray->real_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->real_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

// lance le rayon de la colonne x et remplit "ray" avec le resultat
void	cast_ray(t_game *game, t_ray *ray, int x)
{
	init_ray(&game->player, ray, x);
	init_step(&game->player, ray);
	run_dda(&game->config, ray);
}
