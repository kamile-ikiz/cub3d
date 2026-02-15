/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:05:00 by beergin           #+#    #+#             */
/*   Updated: 2026/02/16 00:23:19 by beergin          ###   ########.fr       */
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

static void	free_paths(t_game_data *data)
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
}

static void	free_textures(t_game_data *data)
{
	if (!data->mlx)
		return ;
	if (data->north_img.img)
		mlx_destroy_image(data->mlx, data->north_img.img);
	if (data->south_img.img)
		mlx_destroy_image(data->mlx, data->south_img.img);
	if (data->west_img.img)
		mlx_destroy_image(data->mlx, data->west_img.img);
	if (data->east_img.img)
		mlx_destroy_image(data->mlx, data->east_img.img);
}

static void	free_mlx_resources(t_game_data *data)
{
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
}

void	all_free(t_game_data *data)
{
	if (data)
	{
		free_paths(data);
		free_textures(data);
		free_mlx_resources(data);
		free_map(data->map);
		free(data);
	}
}
