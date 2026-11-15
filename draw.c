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

// moitie haute de l'ecran = plafond, moitie basse = sol
void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		// au-dessus du milieu : plafond, en dessous : sol
		color = game->config.ceil_color;
		if (y >= WIN_HEIGHT / 2)
			color = game->config.floor_color;
		// on colorie toute la ligne y, de gauche a droite
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(&game->screen, x, y, color);
			x++;
		}
		y++;
	}
}
