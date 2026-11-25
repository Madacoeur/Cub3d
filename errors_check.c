/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:44:04 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/11/25 17:09:46 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	double_def_tex(char *name, char *texture, t_game *game, int fd)
{
	if (texture != NULL)
	{
		write(2, "Error: Double definition of ", 28);
		write(2, name, ft_strlen(name));
		write(2, ".\n", 2);
		cleanup_parsing(game, fd);
		exit(1);
	}
}
// on regarde si element est NULL, s'il l'est pas apres qu'on ait deja rempli
// un de nos pointeurs (par ex avec "NO" dans int *no_texture) alors on enclenche le cas d'erreur
// ici a la place de name je mets "NO" et pareil avec element pour les text
// le . pour le kiff
// on arrete le programme direct parce qu'avec return la fonction
// s'arrete mais le programme continue

void	double_def_col(char *name, int color, t_game *game, int fd)
{
	if (color == 1)
	{
		write(2, "Error: Double definition of ", 28);
		write(2, name, ft_strlen(name));
		write(2, ".\n", 2);
		cleanup_parsing(game, fd);
		exit(1);
	}
}
// color == 1 genre y'a deja un element de defini

void init_struct(t_game *game)
{
	*game = (t_game){0};
}

int	check_textures(t_game *game)
{
	if (!game->no_texture || !game->so_texture || !game->ea_texture
		|| !game->we_texture || !game->f_already_def || !game->c_already_def)
	{
		write(2, "Error: Missing texture or color.\n", 33);
		return (1);
	}
	return (0);
}
// return (1) ou exit(1) si on arrete le programme net

void check_unknown_id(char *line, t_game *game, int fd)
{
    int i;

    i = 0;
    while ((line[i] == ' ' || line[i] == '\t') && line[i])
        i++;
    if (line[i] && (!game->no_texture || !game->so_texture
        || !game->ea_texture || !game->we_texture
        || !game->f_already_def || !game->c_already_def))
    {
        write(2, "Error: Unknown identifier.\n", 27);
        free(line);
        cleanup_parsing(game, fd);
        exit(1);
    }
}
// on regarde simplement si on a marque le bon nom ex NO SO etc 
// on free et on close encore parce que y'a un exit qui arrete net
// le programme donc fuites de donnees, si j'avais return j'aurai pas eu besoin
// car seulement la fonction se serait arrete