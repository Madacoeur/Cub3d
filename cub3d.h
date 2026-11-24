/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 19:27:16 by aamroun           #+#    #+#             */
/*   Updated: 2026/11/24 16:43:01 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "libft.h"
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
	char 	**map;
	int		height;
	int		width;
}	t_game;
// pour initialiser les pointeurs a NULL comme ca on rempli par sur qql chose de deja rempli
// les already def c'est juste pour voir si ca a deja ete declare

// Parce que tes couleurs sont des tableaux (int[3]), elles ne sont jamais NULL (contrairement aux chaînes de caractères des textures).
// Sans flag, ton programme ne peut pas deviner si le tableau a déjà été rempli ou s'il contient juste des valeurs par défaut. Le flag sert
// juste de témoin : "C'est bon, cette couleur a déjà été définie plus haut".

/* errors_check.c */
void	double_def_tex(char *name, char *texture);
void	double_def_col(char *name, int color);
void	init_struct(t_game *game);
int		check_textures(t_game *game);
void	check_unknown_id(char *line, t_game *game, int fd);

/* floodfill_utils.c */
int		valid_map_char(char c);
int		character_pos(char c);
int		validate_map(t_game *game);
int		validate_map_lines(t_game *game);
void	free_grid(char **grid, t_game *game);

/* floodfill.c */
int		flood_fill(char **grid, t_game *game, int y, int x);
int		find_player(t_game *game, int *py, int *px);
char	**copy_grid(t_game *game);
int		map_closed_verif(t_game *game);

/* map_texture_utils.c */
void	parse_texture(char *line, int *i, char **dest, int len);
int		map_exist(int ac, char **av, int *fd);
int		is_map_line(char *line, t_game *game);
void	remove_newline(char *line);

/* map_texture.c */
int		read_map(int fd, t_game *game);

/* parse_rgb.c */
int		parse_rgb_value(char *line, int *i, int *stock);
int		rgb_separator(char *line, int *i, int j);
int		rgb_loop(char *line, t_game *game, int *i, char type);
int		parse_color(char *line, t_game *game);

/* textures_colors.c */
int		textures_p1(char *line, t_game *game);
int		textures_p2(char *line, t_game *game);
int		check_colors(char *line, t_game *game);

#endif
