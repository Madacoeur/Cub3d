/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamroun <aamroun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 12:00:00 by aamroun           #+#    #+#             */
/*   Updated: 2026/11/15 12:00:00 by aamroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ecrit un pixel de couleur "color" en (x, y) dans l'image "img"
// (en memoire seulement : rien ne s'affiche avant mlx_put_image_to_window)
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	// securite : on ne fait rien si le pixel est en dehors de l'image
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	// on saute y lignes entieres, puis x pixels de 4 octets
	dst = img->addr + y * img->line_len + x * (img->bpp / 8);
	// on ecrit les 4 octets de la couleur d'un seul coup
	*(unsigned int *)dst = color;
}

// dessine la colonne x de l'ecran, de haut en bas : plafond, mur, sol
// plus le mur est loin (real_wall_dist grand), plus la bande est petite
void	draw_column(t_game *game, t_ray *ray, int x)
{
	int	line_h;
	int	start;
	int	end;
	int	y;
	int	color;

	// securite : evite une division par 0 si on est colle au mur
	if (ray->real_wall_dist < 0.0001)
		ray->real_wall_dist = 0.0001;
	// hauteur du mur a l'ecran, centree verticalement
	line_h = (int)(WIN_HEIGHT / ray->real_wall_dist);
	start = WIN_HEIGHT / 2 - line_h / 2;
	end = WIN_HEIGHT / 2 + line_h / 2;
	// couleur unie : plus sombre sur les cotes nord/sud pour voir le relief
	color = WALL_COLOR_X;
	if (ray->side == 1)
		color = WALL_COLOR_Y;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < start)
			put_pixel(&game->screen, x, y, game->config.ceil_color);
		else if (y <= end)
			put_pixel(&game->screen, x, y, color);
		else
			put_pixel(&game->screen, x, y, game->config.floor_color);
		y++;
	}
}
