/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 13:29:31 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/11/25 16:50:56 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(char **grid, t_game *game, int y, int x)
{
	if (y < 0 || y >= game->height || x < 0 || x >= game->width)
		return (0);
    if (x >= (int)ft_strlen(grid[y])) // verifie si x depasse la fin de la ligne grid[y] ou tombe sur '\0'
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'V') // 1 c'est un mur V c'est pour une case deja visitee/ utilisee
		return (1); // map fermee donc on revient a la partie juste avant et on continue les verifications jusqu'a qu'on ait une case valide
	if (grid[y][x] == ' ')                     
		// y'a pas eu de 1 pour fermer donc map ouverte alors soucis
		return (0);
	grid[y][x] = 'V';
	if (!flood_fill(grid, game, y - 1, x))
		return (0);
	if (!flood_fill(grid, game, y + 1, x))
		return (0);
	if (!flood_fill(grid, game, y, x - 1))
		return (0);
	if (!flood_fill(grid, game, y, x + 1))
		return (0);
	return (1);
}
// y - 1 : la case au-dessus (ligne précédente).
// y + 1 : la case en dessous (ligne suivante).
// x - 1 : la case à gauche.
// x + 1 : la case à droite.
// donc si c'est aucune de ces possibilites dans le code, la map est ouverte quelque part
// floodfill sert a regarder si la map est fermee en verifiant bien de passer sur les cases jouables une seule fois

int	find_player(t_game *game, int *py, int *px)
{
	int	y;
	int	x;

	*py = -1;
	*px = -1;
	y = 0;
	while (y < game->height && *py == -1)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (character_pos(game->map[y][x]))
			{
				*py = y;
				*px = x;
				break ; // si on a trouve la position du joueur, on sort de la boucle
			}
			x++;
		}
		y++;
	}
	if (*py == -1 || *px == -1) // on a toujours pas trouve la pos du joueur
		return (0);
	return (1);
}

char	**copy_grid(t_game	*game)
{
	char	**grid;
	int		y;

	grid = malloc(sizeof(char *) * (game->height + 1));
	if (!grid)
		return (NULL);
	y = 0;
	while (y < game->height)
	{
		grid[y] = ft_strdup(game->map[y]);
		if (!grid[y]) //si strdup a echoue
		{
			while (--y >= 0) //on part de la fin pour garder les lignes deja alouees avant le crash comme ca on peut les free
				free(grid[y]); //libere cahque ligne avant de liberer le tableau entier
			free(grid);
			return (NULL);
		}
		y++;
	}
	grid[game->height] = NULL; //terminer le tableau de lignes par un pointeur NULL pour eviter les erreurs de lecture
	return (grid);
}

static int	check_isolated_zeros(char **grid, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == '0' && !flood_fill(grid, game, y, x))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	map_closed_verif(t_game *game)
{
	char	**grid;
	int		py;
	int		px;
	int		is_closed;

	if (!find_player(game, &py, &px))
		return (ft_putstr_fd("Error: Invalid map\n", 2), 0);
	grid = copy_grid(game);
	if (!grid)
		return (0);
	is_closed = flood_fill(grid, game, py, px);
	if (is_closed)
		is_closed = check_isolated_zeros(grid, game);
	free_grid(grid, game);
	if (!is_closed)
		ft_putstr_fd("Error: Map is not closed\n", 2);
	return (is_closed);
}

// (53./54./59./60.) py/px = player y/x puis quand on fait -1 c'est pour dire qu'on a pas encore trouve la position du joueur
// (55./56.) y/x = position de la case qu'on verifie, pas necessairement la position du joueur
// y c'est colonne par colonne tandis que x c'est case par case, on commence par fouiller les colonnes/lignes puis dans la boucle on fouille case par case
// (85.) on refait un malloc avec tout ce qu'on a copie avec le strdup pour l'envoyer a floodfill et qu'il puisse check