/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 14:20:44 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/11/24 16:24:20 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//*i car on modifie l'original
void	parse_texture(char *line, int *i, char **dest, int len)
{
	int	start;

	*i += len;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (!line[*i])
		return ;
	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
		(*i)++;
	*dest = ft_substr(line, start, *i - start);
	while (line[*i] == ' ' || line[*i] == '\t')
        (*i)++;
	if (line[*i])
	{
		write(2, "Error: Extra argument.\n", 23);
    	exit(1);
	}
}
// dans cette focntion on recupere uniquement une chaine et si y'a
// plus d'une chaine c'est un arg en trop
// le i - start = si ton i avance avec i++ t'auras par ex i = 4 
// et start = 0 et ta string totale fait 7, ca's'arrete a 4 
// de longueur (dest = destination)
// ligne 29 je reregarde s'il reste pas des tab ou espaces APRES que
// j'ai recupere mes textures puis les caracteres aussi avec
// if (line) donc si ca continue 

int	map_exist(int ac, char **av, int *fd)
{
	int	len;

	if (ac != 2)
	{
		write(2, "Error: Wrong arguments number.\n", 31);
		return (1);
	}
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4) != 0)
	{
		write(2, "Error: Invalid file extension.\n", 31);
		return (1);
	}
	*fd = open(av[1], O_RDONLY);
	if (*fd < 0)
	{
		write(2, "Error: Fail to open file.\n", 26);
		return (1);
	}
	return (0);
}
// on verifie que c'est bien un fichier .cub en comparant la
// longueur des strings qu'on lui donne avec les 4 caracteres de ".cub"
// on ouvre le fichier pour le lire seulement

int	is_map_line(char *line, t_game *game)
{
	int	i;

	if (!game->no_texture || !game->so_texture || !game->ea_texture
		|| !game->we_texture || !game->f_already_def || !game->c_already_def)
		return (0);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i])
	{
		if (game->height > 0)
		{
			write(2, "Error: Empty line in map.\n", 26);
			exit(1);
		}
		return (0);
	}
	if ((!ft_strncmp(&line[i], "NO", 2)
			|| !ft_strncmp(&line[i], "SO", 2)
			|| !ft_strncmp(&line[i], "EA", 2)
			|| !ft_strncmp(&line[i], "WE", 2))
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (0);
	if ((line[i] == 'F' || line[i] == 'C')
		&& (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (0);
	return (1);
}
// on regarde juste si c'est une ligne de map genre 1 ou 0

void remove_newline(char *line)
{
    char *eof;

    if (!line)
        return ;
    eof = ft_strchr(line, '\n');
	if (eof)
			*eof = '\0';
}
