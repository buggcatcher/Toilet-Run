/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:27:42 by mailinci          #+#    #+#             */
/*   Updated: 2024/10/14 22:57:27 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_usage_and_file_type(int argc, char *map_file)
{
	int filename_length;

	if (argc != 2)
	{
		ft_printf("Usage: ./so_long [map.ber]\n");
		return (1);
	}
	filename_length = ft_strlen(map_file);
	if (filename_length < 4 || ft_strncmp(map_file + filename_length - 4, ".ber", 4))
	{
		ft_printf("Error: Invalid file type\n");
		return (1);
	}
	return (0);
}

static int validate_file(char *map_file, int *fd)
{
    *fd = open(map_file, O_RDONLY | __O_DIRECTORY);
    if (*fd >= 0)
    {
        close(*fd);
        ft_printf("Error: The map must be a file\n");
        return (1);
    }

    *fd = open(map_file, O_RDONLY);
    if (*fd < 0)
    {
        ft_printf("Error: Unable to open the map file\n");
        return (1);
    }

    return (0);
}

int check_map_line_lengths(int fd)
{
    char *line;
    size_t current_length;
    size_t line_length;

    line = ft_get_next_line(fd);
    if (!line)
        return (1);
    line_length = ft_strlen(line);
    if (line[line_length - 1] == '\n')
        line_length--;
    free(line);

    while ((line = ft_get_next_line(fd)) != NULL)
    {
        current_length = ft_strlen(line);
        if (line[current_length - 1] == '\n')
            current_length--;
        if (current_length != line_length)
        {
            free(line);
            return (1);
        }
        free(line);
    }
    return(0);
}

int check_map_objects(char *map_file)
{
    t_objects	object;
	int			i;

    set_objects(&object);
	object.fd = open(map_file, O_RDONLY);
    while ((object.line = ft_get_next_line(object.fd)) != NULL)
    {
        i = 0;
        while (object.line[i] != '\0')
        {
            if (object.line[i] == POOPIE)
                object.P++;
            else if (object.line[i] == EXIT)
                object.E++;
            else if (object.line[i] == COLLECTABLE)
                object.C++;
            i++;
        }
        free(object.line);
    }
    close(object.fd);
    if (object.P == 1 && object.E == 1 && object.C >= 1)
        return (0);
	else
		return (1);
}

int validate_map_file(char *map_file)
{
    t_objects	o;
    if (validate_file(map_file, &o.fd))
        exit(1);
    if (check_map_line_lengths(o.fd))
    {
        ft_printf("Error: Invalid map\n");
        close(o.fd);
        exit(1);
    }
    if (check_map_objects(map_file))
    {
        ft_printf("Error: Invalid objects\n");
        close(o.fd);
        exit(1);
    }
    return (0);
}

 


