/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:30:04 by mailinci          #+#    #+#             */
/*   Updated: 2024/10/17 16:02:08 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void set_objects(t_objects *object)
{
    object->P = 0;
    object->E = 0;
    object->C = 0;
}

t_parsing set_dimentions(char **map_copy, t_dimensions d)
{
    t_parsing check;

    check.map = map_copy;
    check.exit_found = 0;
    check.height = d.height;
    check.width = d.width;
    return (check);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	count_rows(char **map)
{
	int	i;

	i = 0;
    if(!map)
    {
        return (0);
    }
	while(map[i])
		i++;
	return (i);
}

void flood_fill(int x, int y, t_parsing *check)
{
    if (check->map[y][x] == '1' || check->map[y][x] == '2')
        return;

    if (check->map[y][x] == 'E')
    {
        check->map[y][x] = '2';   
        check->exit_found = 1;
        return;
    }
    check->map[y][x] = '2';
    flood_fill(x + 1, y, check);
    flood_fill(x - 1, y, check);
    flood_fill(x, y + 1, check);
    flood_fill(x, y - 1, check);
}
