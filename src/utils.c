/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:50:49 by beergin           #+#    #+#             */
/*   Updated: 2026/02/16 18:42:40 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	start_data_img(t_game_data *data)
{
	data->north_img.img = NULL;
	data->north_img.addr = NULL;
	data->south_img.img = NULL;
	data->south_img.addr = NULL;
	data->west_img.img = NULL;
	data->west_img.addr = NULL;
	data->east_img.img = NULL;
	data->east_img.addr = NULL;
}

void	start_data(t_game_data *data)
{
	data->north_p = NULL;
	data->south_p = NULL;
	data->west_p = NULL;
	data->east_p = NULL;
	data->map = NULL;
	data->map_dir = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->height = 0;
	data->width = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->player_dir = '\0';
	data->floor_rgb[0] = -1;
	data->floor_rgb[1] = -1;
	data->floor_rgb[2] = -1;
	data->ceiling_rgb[0] = -1;
	data->ceiling_rgb[1] = -1;
	data->ceiling_rgb[2] = -1;
	start_data_img(data);
}

void	print_error_exit(char *message, t_game_data *data)
{
	printf("Error\n%s\n", message);
	all_free(data);
	exit(1);
}
