/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:05:00 by beergin           #+#    #+#             */
/*   Updated: 2026/02/13 20:31:36 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill(t_game_data *data, char **temp_map, int x, int y)
{
	if (y < 0 || y >= data->height || x < 0
		|| x >= ft_strlenn(temp_map[y]))
		return (0);
	if (temp_map[y][x] == ' ')
		return (0);
	if (temp_map[y][x] == '1' || temp_map[y][x] == 'B')
		return (1);
	temp_map[y][x] = 'B';
	if (!fill(data, temp_map, x + 1, y)
		|| !fill(data, temp_map, x - 1, y)
		|| !fill(data, temp_map, x, y + 1)
		|| !fill(data, temp_map, x, y - 1))
		return (0);
	return (1);
}

void	get_map_width(t_game_data *data)
{
	int	len;
	int	max_width;
	int	i;

	i = 0;
	max_width = 0;
	while (data->map[i] != NULL)
	{
		len = 0;
		while (data->map[i][len] != '\0')
			len++;
		if (len > max_width)
			max_width = len;
		i++;
	}
	data->width = max_width;
}

int	get_map_width_simple(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	return (i);
}
