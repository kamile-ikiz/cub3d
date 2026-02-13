/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:05:00 by beergin           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:51 by beergin          ###   ########.fr       */
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
		if (data->map_dir)
			free(data->map_dir);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->img)
		{
			if (data->img->img)
				mlx_destroy_image(data->mlx, data->img->img);
			free(data->img);
		}
		if (data->mlx)
			mlx_destroy_display(data->mlx);
		free_map(data->map);
		free(data);
	}
}

void	print_error_exit(char *message, t_game_data *data)
{
	printf("Error\n%s\n", message);
	all_free(data);
	exit(1);
}
