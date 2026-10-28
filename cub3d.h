/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 19:27:16 by aamroun           #+#    #+#             */
/*   Updated: 2026/10/28 19:13:08 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
//# include "mlx.h"
//# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef	struct s_game
{
	void	*mlx;
	void	*win;
	char	*no_texture;
	char	*so_texture;
	char	*ea_texture;
	char	*we_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	int		f_already_def;
	int		c_already_def;
}	t_game;
// pour initialiser les pointeurs a NULL comme ca on rempli par sur qql chose de deja rempli
// les already def c'est juste pour voir si ca a deja ete declare


/* --- Initialisation & Erreurs --- */
void	init(t_game *game);
void	double_def_tex(char *name, char *texture);
void	double_def_col(char *name, int color);
int		check_textures(t_game *game);
void	check_unknown_id(char *line, t_game *game, int fd);

/* --- Fichiers & Map --- */
int		map_exist(int ac, char **av, int *fd);
int		read_map(int fd, t_game *game);

/* --- Textures --- */
int		textures_p1(char *line, t_game *game);
int		textures_p2(char *line, t_game *game);
void	parse_texture(char *line, int *i, char **dest, int len);

/* --- Couleurs RGB --- */
int		colors(char *line, t_game *game);
int		parse_color(char *line, t_game *game);
int		rgb_loop(char *line, t_game *game, int *i, char type);
int		parse_rgb_value(char *line, int *i, int *stock);
int		rgb_separator(char *line, int *i, int j);

#endif
