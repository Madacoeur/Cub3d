/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamroun <aamroun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 19:27:16 by aamroun           #+#    #+#             */
/*   Updated: 2026/11/14 12:00:00 by aamroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>
# include "mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_config
{
	char	*tex_path[4];
	int		floor_color;
	int		ceil_color;
	char	**map;
	int		map_h;
	int		start_x;
	int		start_y;
	char	start_dir;
}	t_config;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	real_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_img		tex[4];
	t_config	config;
	t_player	player;
	t_keys		keys;
}	t_game;

/* main.c */
int		init_game(t_game *game);
int		close_game(t_game *game);
int		key_press(int keycode, t_game *game);

/* free.c */
void	free_config(t_config *config);
void	free_game(t_game *game);
void	exit_error(t_game *game, char *msg);

/* utils.c */
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

/* draw.c */
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_floor_ceiling(t_game *game);

/* render.c */
int		render(t_game *game);

/* fake_parsing.c (temporaire, remplace par le parsing du binome) */
int		fake_parsing(t_config *config);

#endif
