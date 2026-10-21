/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:44:04 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/10/20 13:47:27 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	double_def(char *name, char *element)
{
	if (element)
	{
		write(1, "Error: Double definition of ", 28);
		write(1, name, ft_strlen(name));
		write(1, ".\n", 2);
		exit(1);
	}
}
// ici a la place de name je mets "NO" et pareil avec element pour les text
// le . pour le kiff
// on arrete le programme direct parce qu'avec return la fonction
// s'arrete mais le programme continue

int	check_textures(t_game *game)
{
	if (!game->no_texture || !game->so_texture || !game->ea_texture
		|| !game->we_texture || !game->floor_color || !game->ceiling_color)
	{
		write(1, "Error: Missing texture or color.\n", 33);
		return (1);
	}
	return (0);
}
// return (1) ou exit(1) si on arrete le programme net