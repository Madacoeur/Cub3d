/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzimaeva <rzimaeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 12:44:30 by rzimaeva          #+#    #+#             */
/*   Updated: 2026/10/13 19:12:50 by rzimaeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_exist(int ac, char **av, t_game *game)
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
        char *line = get_next_line(fd); //on prend ligne par ligne et on stocke dans un buffer pluis tard
        while (line)
        {
            char *eof = strchr(line, '\n'); //ici on va chercher le caractere de fin \n pour le remplacer par un caractere nulll comme ca il nous derange pas dans la lecture de la map
            int i = 0;
            if (eof)
                *eof = '\0';
            while ((line[i] == '\t' || line[i] == ' ') && line[i])
                i++;
            if (strncmp(&line[i], "NO", 2) == 0) //texture de mur
            {
                i += 2;
                while (line[i] == '\t' || line[i] == ' ')
                    i++;
                int start = i; //commence directement apres avoir saute 
                while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
                    i++;
                game->no_texture = ft_substr(line, start, i - start); //le i - start = si ton i avance avec i++ t'auras par ex i = 4 et start = 0 et ta string totale fait 7, ca's'arrete a 4 de longueur
            }
            else if (strncmp(&line[i], "SO", 2) == 0) //texture de mur
            {
                i += 2;
                while (line[i] == '\t' || line[i] == ' ')
                    i++;
                int start = i; //commence directement apres avoir saute 
                while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
                    i++;
                game->so_texture = ft_substr(line, start, i - start); //le i - start = si ton i avance avec i++ t'auras par ex i = 4 et start = 0 et ta string totale fait 7, ca's'arrete a 4 de longueur
            }
            else if (strncmp(&line[i], "EA", 2) == 0) //texture de mur
            {
                i += 2;
                while (line[i] == '\t' || line[i] == ' ')
                    i++;
                int start = i; //commence directement apres avoir saute 
                while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
                    i++;
                game->ea_texture = ft_substr(line, start, i - start); //le i - start = si ton i avance avec i++ t'auras par ex i = 4 et start = 0 et ta string totale fait 7, ca's'arrete a 4 de longueur
            }
            else if (strncmp(&line[i], "WE", 2) == 0) //texture de mur
            {
                i += 2;
                while (line[i] == '\t' || line[i] == ' ')
                    i++;
                int start = i; //commence directement apres avoir saute 
                while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
                    i++;
                game->we_texture = ft_substr(line, start, i - start); //le i - start = si ton i avance avec i++ t'auras par ex i = 4 et start = 0 et ta string totale fait 7, ca's'arrete a 4 de longueur
            }
            else if (strncmp(&line[i], 'F', 1) == 0) //texture de mur
            {
                i += 2;
                while (line[i] == '\t' || line[i] == ' ')
                    i++;
                int start = i; //commence directement apres avoir saute 
                while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
                    i++;
                game->f_texture = ft_substr(line, start, i - start); //le i - start = si ton i avance avec i++ t'auras par ex i = 4 et start = 0 et ta string totale fait 7, ca's'arrete a 4 de longueur
            }
            else if (strncmp(&line[i], 'C', 1) == 0) //texture de mur
            {
                i += 2;
                while (line[i] == '\t' || line[i] == ' ')
                    i++;
                int start = i; //commence directement apres avoir saute 
                while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
                    i++;
                game->c_texture = ft_substr(line, start, i - start); //le i - start = si ton i avance avec i++ t'auras par ex i = 4 et start = 0 et ta string totale fait 7, ca's'arrete a 4 de longueur
            }
            free(line);
            line = get_next_line(fd);
            i = 0;
        }
        close (fd);
    }
    return (0);
}
