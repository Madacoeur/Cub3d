/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 19:27:16 by aamroun           #+#    #+#             */
/*   Updated: 2026/10/20 13:59:24 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef struct s_game
{
	void	*mlx;
	void	*win;
}			t_game;

int			init_game(t_game *game);
int			close_game(t_game *game);
int			key_press(int keycode, t_game *game);

typedef	struct s_game
{
		char	*no_texture;
		char	*so_texture;
		char	*ea_texture;
		char	*we_texture;
		char	*floor_color;
		char	*ceiling_color;
}	t_game

//map_texture

void	parsing(*line, int *i, char **dest, int len);
int	map_exist(int ac, char **av, int *fd);
int	read_map(int fd, t_game *game);


//textures_colors

int	textures_p1(char *line, t_game *game);
int	textures_p2(char *line, t_game *game);
int	colors(char *line, t_game *game);
void check_unknown_id(char *line, t_game *game, int fd);


//error_check

void	double_def(char *name, char *element);
int	check_textures(t_game *game);

#endif
