/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:05:00 by beergin           #+#    #+#             */
/*   Updated: 2026/02/09 01:22:35 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	print_error_exit(char *message, t_game_data *data)
{
	printf("Error\n%s\n", message);
	if (data)
	{
		if (data->north_p)
			free(data->north_p);
		if (data->south_p)
			free(data->south_p);
		if (data->west_p)
			free(data->west_p);
		if (data->east_p)
			free(data->east_p);
		free_map(data->map);
		free(data);
	}
	exit(1);
}

void	all_free(t_game_data *data)
{
	if (data)
	{
		if (data->north_p)
			free(data->north_p);
		if (data->south_p)
			free(data->south_p);
		if (data->west_p)
			free(data->west_p);
		if (data->east_p)
			free(data->east_p);
		free_map(data->map);
		free(data);
	}
}
