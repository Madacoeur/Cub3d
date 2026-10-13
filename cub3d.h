/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 19:27:16 by aamroun           #+#    #+#             */
/*   Updated: 2026/10/13 18:08:28 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <X11/keysym.h>
# include "mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"
#include "libft.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef struct s_game {
	void	*mlx;
	void	*win;
}	t_game;

int	init_game(t_game *game);
int	close_game(t_game *game);
int	key_press(int keycode, t_game *game);

#endif
