/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:44:30 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/10/13 18:01:28 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_exist(int ac, char **av)
{
    if (ac != 2)
    {
        write(1, "Error: Wrong arguments number.\n", 31);
        return (1);
    }
    else if (ac == 2)
    {
        int len = ft_strlen(av[1]);
        if (strncmp(&av[1][len - 4], ".cub", 4) != 0) //on verifie que c'est bien un fichier .cub en comparant la longueur des strings qu'on lui donne avec les 4 caracteres de ".cub"
        {
            write(1, "Error: Invalid file extension.\n", 31);
            return (1);
        }
        int fd = open(av[1], O_RDONLY); //on ouvre le fichier pour le lire seulement
        if (fd < 0) //securite
        {
            write(1, "Error: Fail to open file.\n", 26);
            return (1);
        }
        char **line = get_next_line(fd); //on prne dligne par ligne et on stocke dans un buffer pluis tard
        char *EOF = strchr(line, '\n'); //ici on va chercher le caractere de fin \n pour le remplacer par un caractere nulll comme ca il nous derange pas dans la lecture de la map
        if (EOF)
            *EOF = '\0';
        int i = 0;
        inf j = 0;
        while ((line[i] == '\t' || line[i] == ' ') && line[i] != '\0')
        {
            if (strncmp(&line[i], "NO", 2) == 0)
            {
                
            }
            line = 0;
        }
    }
    return (0);
}
