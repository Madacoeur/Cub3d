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

// choisit la texture selon le sens du rayon et le cote touche
// ex : un rayon qui part vers le nord (y negatif) voit la texture NO
static t_img	*pick_texture(t_game *game, t_ray *ray)
{
	// side 0 = on a touche un bord vertical -> mur est ou ouest
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->tex[TEX_EA]);
		return (&game->tex[TEX_WE]);
	}
	// side 1 = on a touche un bord horizontal -> mur nord ou sud
	if (ray->ray_dir_y > 0)
		return (&game->tex[TEX_SO]);
	return (&game->tex[TEX_NO]);
}

// trouve quelle colonne de la texture correspond a l'endroit touche
static int	get_tex_x(t_player *p, t_ray *ray, t_img *tex)
{
	double	wall_x;
	int		tex_x;

	// point exact ou le rayon touche le mur, le long de ce mur
	if (ray->side == 0)
		wall_x = p->pos_y + ray->real_wall_dist * ray->ray_dir_y;
	else
		wall_x = p->pos_x + ray->real_wall_dist * ray->ray_dir_x;
	// on garde seulement la partie apres la virgule (entre 0 et 1)
	wall_x -= floor(wall_x);
	// 0.25 -> on est au quart du mur -> colonne au quart de la texture
	tex_x = (int)(wall_x * tex->width);
	// sur ces deux faces la texture serait vue en miroir : on la retourne
	if ((ray->side == 0 && ray->ray_dir_x < 0)
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

// dessine la partie mur de la colonne x, pixel par pixel depuis la texture
static void	draw_wall(t_game *game, t_wall *w, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		end;
	int		tex_y;

	// combien de lignes de texture on avance pour 1 pixel d'ecran
	step = (double)w->tex->height / w->line_h;
	// on ne dessine que la partie visible du mur (entre 0 et WIN_HEIGHT - 1)
	y = w->start;
	if (y < 0)
		y = 0;
	end = w->end;
	if (end >= WIN_HEIGHT)
		end = WIN_HEIGHT - 1;
	// mur coupe en haut de l'ecran : on demarre plus loin dans la texture
	tex_pos = (y - WIN_HEIGHT / 2 + w->line_h / 2) * step;
	while (y <= end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= w->tex->height)
			tex_y = w->tex->height - 1;
		tex_pos += step;
		put_pixel(&game->screen, x, y,
			get_tex_pixel(w->tex, w->tex_x, tex_y));
		y++;
	}
}

// dessine la colonne x de l'ecran, de haut en bas : plafond, mur, sol
// plus le mur est loin (real_wall_dist grand), plus la bande est petite
void	draw_column(t_game *game, t_ray *ray, int x)
{
	t_wall	w;
	int		y;

	// securite : evite une division par 0 si on est colle au mur
	if (ray->real_wall_dist < 0.0001)
		ray->real_wall_dist = 0.0001;
	// hauteur du mur a l'ecran, centree verticalement
	w.line_h = (int)(WIN_HEIGHT / ray->real_wall_dist);
	w.start = WIN_HEIGHT / 2 - w.line_h / 2;
	w.end = WIN_HEIGHT / 2 + w.line_h / 2;
	w.tex = pick_texture(game, ray);
	w.tex_x = get_tex_x(&game->player, ray, w.tex);
	// plafond : du haut de l'ecran jusqu'au debut du mur
	y = 0;
	while (y < w.start && y < WIN_HEIGHT)
		put_pixel(&game->screen, x, y++, game->config.ceil_color);
	draw_wall(game, &w, x);
	// sol : de la fin du mur jusqu'en bas de l'ecran
	y = w.end + 1;
	if (y < 0)
		y = 0;
	while (y < WIN_HEIGHT)
		put_pixel(&game->screen, x, y++, game->config.floor_color);
}
