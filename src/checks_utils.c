/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:05:00 by beergin           #+#    #+#             */
/*   Updated: 2026/02/13 20:37:56 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_temp_map(char **temp_map, int height)
{
	int	x;

	x = 0;
	while (x < height)
	{
		free(temp_map[x]);
		x++;
	}
	free(temp_map);
}

static int	fill_start(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	check_fill_line(t_game_data *data, char **temp_map, int x)
{
	int	y;

	y = 0;
	while (y < ft_strlenn(temp_map[x]))
	{
		if (fill_start(temp_map[x][y]) && !fill(data, temp_map, y, x))
		{
			free_temp_map(temp_map, data->height);
			print_error_exit("Map is not enclosed", data);
		}
		y++;
	}
}

void	border_check_fill(t_game_data *data)
{
	char	**temp_map;
	int		x;

	temp_map = malloc(sizeof(char *) * (data->height + 1));
	if (!temp_map)
		print_error_exit("Memory allocation failed", data);
	x = 0;
	while (x < data->height)
	{
		temp_map[x] = ft_strdup(data->map[x]);
		if (!temp_map[x])
			print_error_exit("Memory allocation failed", data);
		x++;
	}
	temp_map[data->height] = NULL;
	x = 0;
	while (x < data->height)
	{
		check_fill_line(data, temp_map, x);
		x++;
	}
	free_temp_map(temp_map, data->height);
}
