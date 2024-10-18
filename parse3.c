/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mailinci <mailinci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:17:21 by mailinci          #+#    #+#             */
/*   Updated: 2024/10/17 15:52:34 by mailinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game setup_game(char *map_file, t_dimensions *d)
{
    t_game game;
	
    *d = get_map_dimensions(map_file);
    game.map = create_map(map_file);
    return (game);
}


int check_playability(t_game game, t_dimensions d)
{
    t_coord c;
    t_parsing check;
	char **map_dup;

    if (check_map_walls(game, d))
    {
        ft_printf("Error: Invalid map\n");
        return (0);
    }
    map_dup = map_copy(game.map);
    if(!map_dup)
        return (0);
    check = set_dimentions(map_dup, d);
    c = player_position(game.map);
    flood_fill(c.x, c.y, &check);
    if (!is_it_filled(&check))
    {
        ft_printf("Error: Unplayable map1\n");
        free_map(map_dup);
        return (0);
    }
    check_collectibles(check.map, d);
	free_map(game.map);
    free_map(map_dup);
    return (1);
}

int char_check(char **map, t_dimensions d)
{
    size_t i;
    size_t j;
    
    i = 0;
    while (i < d.height)
    {
        j = 0;
        while (j < d.width)
        {
            if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'P' && map[i][j] != 'E' && map[i][j] != 'C')
            {
                return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
}

int is_playable(char *map_file)
{
    t_game game;
    t_dimensions d;

    game = setup_game(map_file, &d);
    if (!game.map)
        return (0);
    if (char_check(game.map, d))
    {
        ft_printf("Error: Invalid map\n");
        return (0);
    }
    return (check_playability(game, d));
}
