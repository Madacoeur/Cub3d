/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:44:30 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/10/21 13:43:36 by rzimaeva         ###   ########.fr       */
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
	if (len < 4 || strncmp(&av[1][len - 4], ".cub", 4) != 0)
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

int	read_map(int fd, t_game *game)
{
	char	*line;
	char	*eof;

	line = get_next_line(fd);
	while (line)
	{
		eof = strchr(line, '\n');
		if (eof)
			*eof = '\0';
		if (!textures_p1(line, game) && !textures_p2(line, game)
			&& !colors(line, game))
			check_unknown_id(line, game, fd);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (check_textures(game))
		return (1);
	return (0);
}

