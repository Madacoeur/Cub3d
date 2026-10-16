/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 19:27:16 by aamroun           #+#    #+#             */
/*   Updated: 2026/10/16 13:52:27 by rzimaeva         ###   ########.fr       */
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

// typedef	struct s_game
//{
//		char	*no_texture;
//		char	*so_texture;
//		char	*ea_texture;
//		char	*we_texture;
//		char	*floor_color;
//		char	*ceiling_color;
//}	t_game

#endif
