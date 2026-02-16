/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:50:35 by beergin           #+#    #+#             */
/*   Updated: 2026/02/16 18:16:39 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	border_check_fill(t_game_data *data);

void	check_filename(t_game_data *data, char *filename, int len)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	if (i < 5 || filename[i - 1] != 'b' || filename[i - 2] != 'u'
		|| filename[i - 3] != 'c' || filename[i - 4] != '.')
		print_error_exit("Invalid file extension", data);
	while (filename[len] != '/' && len > 0)
		len--;
	if (filename[len] == '/' && filename[len + 1] == '.'
		&& filename[len + 2] == 'c')
		print_error_exit("Hidden file not supported", data);
}

void	check_extension(char *filename, char *extension, t_game_data *data)
{
	int	len_filename;
	int	len_extension;
	int	i;

	len_filename = 0;
	len_extension = 0;
	while (filename[len_filename])
		len_filename++;
	check_filename(data, filename, len_filename);
	while (extension[len_extension])
		len_extension++;
	if (len_filename < len_extension)
		print_error_exit("Invalid file extension", data);
	i = 0;
	while (i < len_extension)
	{
		if (filename[len_filename - len_extension + i] != extension[i])
			print_error_exit("Invalid file extension", data);
		i++;
	}
}

static void	check_border_row(t_game_data *data, int x, int line_width)
{
	int	y;

	y = 0;
	while (data->map[x][y] != '\0' && y < line_width)
	{
		if (data->map[x][y] != '1' && data->map[x][y] != ' ')
			print_error_exit("Map is not enclosed by walls", data);
		y++;
	}
}

static void	check_middle_row(t_game_data *data, int x, int line_width)
{
	int	y;

	if (data->map[x][0] != '1' && data->map[x][0] != ' ')
		print_error_exit("Map is not enclosed by walls", data);
	y = 0;
	while (data->map[x][y] != '\0' && y < line_width)
		y++;
	if (data->map[x][y - 1] != '1' && data->map[x][y - 1] != ' ')
		print_error_exit("Map is not enclosed by walls", data);
}

void	border_check(t_game_data *data)
{
	int	x;
	int	line_width;

	x = 0;
	while (data->map[x] != NULL)
	{
		line_width = get_map_width_simple(data->map[x]);
		if (x == 0 || x == data->height - 1)
			check_border_row(data, x, line_width);
		else
			check_middle_row(data, x, line_width);
		x++;
	}
	get_map_width(data);
	border_check_fill(data);
}
