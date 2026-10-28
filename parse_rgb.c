/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 13:03:00 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/10/28 18:40:34 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_rgb_value(char *line, int *i, int *stock) // je mets des * partout parce que sinon je peux pas appeler la fonction avec l'adresse memoire direct
{
    *stock = 0;
    if (line[*i] < '0' || line[*i] > '9') //securite
        return (0);
    while (line[*i] >= '0' && line[*i] <= '9') //tant que c'est un chiffre donc pas de virgule ou quoi pour pouvoir lire meme les gros nombres
    {
        if (*stock * 10 + line[*i] - '0' > 255)
            return (0);
        *stock = (*stock) * 10 + line[*i] - 48; //*
        (*i)++;
    }
    return (1);
}

int	rgb_separator(char *line, int *i, int j)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (j < 2)
	{
		if (line[*i] != ',')
			return (0);
		(*i)++; //on saute la virgule
	}
	else if (line[*i] != '\0')
		return (0);
	return (1);
}

int rgb_loop(char *line, t_game *game, int *i, char type)
{
    int stock;
    int j;
    
    j = 0;
    while (j < 3)
    {
        while (line[*i] == '\t' || line[*i] == ' ')
            (*i)++;
        if (!parse_rgb_value(line, i, &stock))
            return (0);
        if (type == 'F')
            game->floor_color[j] = stock; //ici je stocke directement dans ma struct
        else
            game->ceiling_color[j] = stock; //on met [j] parce que dans la strutc on est sur [3] donc ca n'ecrase pas les 3 valeurs RGB mais les prend chacune leur tour
        if (!rgb_separator(line, i, j))
			return (0);
		j++;
    }
    if (type == 'F')
        game->f_already_def = 1;
    else
        game->c_already_def = 1;
    return (1);
}
// on doit faire les couleurs RGB donc c'est la meme logique trois fois
// d'abord pour Red jusqu'a la virgule puis, Green et enfin, Blue


int	check_colors(char *line, t_game *game)
{
    int		i;
    
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
    i++;
	if (!line[i])
    return (1);
	if ((line[i] == 'F' || line[i] == 'C')
    && (line[i + 1] == ' ' || line[i + 1] == '\t'))
	{
        if (line[i] == 'F')
        double_def_col("F", game->f_already_def);
		else
        double_def_col("C", game->c_already_def);
		if (!parse_color(line, game))
		{
            write(2, "Error: Invalid color.\n", 22);
			exit(1);
		}
		return (1);
	}
	return (0);
}
// colors : repere si la ligne correspond a F ou C,
// verifie les doublons et lance le parsing de la couleur

int parse_color(char *line, t_game *game)
{
    int i;
    int j;
    char type;
    
    i = 0;
    j = 0;
    while (line[i] == '\t' || line[i] == ' ')
    i++;
    type = line[i]; // on memorise les caracteres F ou C
    i++;
    return (rgb_loop(line, game, &i, type));
}
// ok donc imaginons j'ai 'F', je selectionne F et je le mets de cote
// (je le stock), puis quand je vais lire les chiffres donc valeurs RGB
// je vais attribuer a la couleur correspondante


//* *stock = stock * 10 + line[*i] - 48; pour cette ligne c'est comme dans atoi
// si on a 220, d'abord on lit '2' donc stock = 0 * 10 + 2 = 2, ensuite le deuxieme chiffre '2' donc stock = 2 * 10 + 2 = 22
// et enfin le dernier chiffre '0' donc stock = 22 * 10 + 0 = 220
// puis pour le - 48 c'est '0' en ascii donc si tu veux 1 tu fais 49 (1 en ascii) - 48 (0 en ascii) ca fait 1