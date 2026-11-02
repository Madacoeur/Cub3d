/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 19:27:16 by aamroun           #+#    #+#             */
/*   Updated: 2026/10/31 19:44:12 by aamroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <X11/keysym.h>
#include "mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
// #include "get_next_line.h"
// #include "libft.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef struct s_player {
	double pos_x;
	double pos_y;
	double dir_x;	//Vecteur de direction
	double dir_y;
	double plane_x;  //plan de la cam (FOV) champ de vision en anglais 
	double plane_y;
}	t_player;

typedef struct s_game {
	void	*mlx;
	void	*win;  // pour window que la win que la win
}	t_game;

typedef struct s_ray {
	double	camera_x;  // point x sur le plan de la cam ( c entre -1 et 1)
	double	ray_dir_x;
	double	ray_dir_y;
	int	map_x;	// case de la map askip ou on est en gros
	int	map_y;
	double	side_dist_x;	//distance jusqu au prochain cote X
	double	side_dist_y;	// distance jusqu au prochain cote Y
	double	delta_dist_x;	
	double	delta_dist_y;
	double	real_wall_dist;
	int	step_x;
	int	step_y;
	int	hit;
	int	side;

int	init_game(t_game *game);
int	close_game(t_game *game);
int	key_press(int keycode, t_game *game);

#endif
