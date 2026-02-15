/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:05:00 by beergin           #+#    #+#             */
/*   Updated: 2026/02/16 00:24:35 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_rgb(int rgb[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

static void	set_floor_color(t_game_data *data, int rgb[3])
{
	if (data->floor_rgb[0] != -1)
		print_error_exit("Duplicate Floor color", data);
	data->floor_rgb[0] = rgb[0];
	data->floor_rgb[1] = rgb[1];
	data->floor_rgb[2] = rgb[2];
	if (!is_valid_rgb(data->floor_rgb))
		print_error_exit("Floor RGB out of range", data);
}

static void	set_ceiling_color(t_game_data *data, int rgb[3])
{
	if (data->ceiling_rgb[0] != -1)
		print_error_exit("Duplicate Ceiling color", data);
	data->ceiling_rgb[0] = rgb[0];
	data->ceiling_rgb[1] = rgb[1];
	data->ceiling_rgb[2] = rgb[2];
	if (!is_valid_rgb(data->ceiling_rgb))
		print_error_exit("Ceiling RGB out of range", data);
}

static void	set_color(t_game_data *data, int rgb[3], char type)
{
	if (type == 'F')
		set_floor_color(data, rgb);
	else if (type == 'C')
		set_ceiling_color(data, rgb);
}

void	get_color(t_game_data *data, char *line, char type)
{
	int	rgb[3];

	parse_rgb_line(data, line, rgb);
	set_color(data, rgb, type);
}
