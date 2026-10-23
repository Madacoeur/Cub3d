/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 13:03:00 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/10/23 14:41:25 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_color(char *line, t_game *game)
{
    int i;
    int j;
    char type;
    
    i = 0;
    j = 0;
    while (line[i] == '\t' || line[i] == ' ')
        i++;
    if ((line[i] == 'F' || line[i] == 'C')
        && (line[i + 1] == ' ' || line[i + 1] == '\t'))
    {
        type = line[i]; // on memorise les caracteres F ou C
        i++;
    }
    else
        return (0); // sécurité si c'est pas F ou C
    return (RGB_loop(line, game, &i, type));
}
// ok donc imaginons j'ai 'F', je selectionne F et je le mets de cote
// (je le stock), puis quand je vais lire les chiffres je vais l'attribuer 
// a mon 'F' que j'avais stocke au prealable

int parse_rgb_value(char *line, int *i, int *stock) // je mets des * partout parce que sinon je peux pas appeler la fonction avec l'adresse memoire direct
{
    *stock = 0;
    if (line[*i] < '0' || line[*i] > '9') //securite
        return (0);
    while (line[*i] >= '0' && line[*i] <= '9') //tant que c'est un chiffre donc pas de virgule ou quoi pour pouvoir lire meme les gros nombres
    {
        if (*stock > 25 || (*stock == 25 && line[*i] > '5')) // en gros le max c'est 255 donc si t'as 25 le chiffre d'apres doit etre entre 0 et 5 et pas plus
            return (0);
        *stock = (*stock) * 10 + line[*i] - 48; //*
        (*i)++;
    }
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
        if (type == 'F')
            game->floor_color[j] = stock; //ici je stocke directement dans ma struct
        else if (type == 'C')
            game->ceiling_color[j] = stock; //on met [j] parce que dans la strutc on est sur [3] donc ca n'ecrase pas les 3 valeurs RGB mais les prend chacune leur tour
        if (!rgb_separator(line, i, j))
			return (0);
		j++;
    }
    return (1);
}
// on doit faire les couleurs RGB donc c'est la meme logique trois fois
// d'abord pour Red jusqu'a la virgule puis, Green et enfin, Blue

// *stock = stock * 10 + line[*i] - 48; pour cette ligne c'est comme dans atoi
// si on a 220, d'abord on lit '2' donc stock = 0 * 10 + 2 = 2, ensuite le deuxieme chiffre '2' donc stock = 2 * 10 + 2 = 22
// et enfin le dernier chiffre '0' donc stock = 22 * 10 + 0 = 220
// puis pour le - 48 c'est '0' en ascii donc si tu veux 1 tu fais 49 (1 en ascii) - 48 (0 en ascii) ca fait 1
