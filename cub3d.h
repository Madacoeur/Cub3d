/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamroun <aamroun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 19:27:16 by aamroun           #+#    #+#             */
/*   Updated: 2026/10/09 19:32:16 by aamroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3d_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <X11/keysym.h>
# include "mlx.h"

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
