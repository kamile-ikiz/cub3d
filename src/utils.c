/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:50:49 by beergin           #+#    #+#             */
/*   Updated: 2026/02/16 00:23:19 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

void	print_error_exit(char *message, t_game_data *data)
{
	printf("Error\n%s\n", message);
	all_free(data);
	exit(1);
}
