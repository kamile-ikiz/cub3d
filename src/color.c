/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:05:00 by beergin           #+#    #+#             */
/*   Updated: 2026/02/10 00:38:13 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	count_commas(t_game_data *data, char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
	{
		free(str);
		print_error_exit("Invalid RGB format (Need R,G,B)", data);
	}
}

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

static void	set_color(t_game_data *data, int rgb[3], char type)
{
	if (type == 'F')
	{
		if (data->floor_rgb[0] != -1)
			print_error_exit("Duplicate Floor color", data);
		data->floor_rgb[0] = rgb[0];
		data->floor_rgb[1] = rgb[1];
		data->floor_rgb[2] = rgb[2];
		if (!is_valid_rgb(data->floor_rgb))
			print_error_exit("Floor RGB out of range", data);
	}
	else if (type == 'C')
	{
		if (data->ceiling_rgb[0] != -1)
			print_error_exit("Duplicate Ceiling color", data);
		data->ceiling_rgb[0] = rgb[0];
		data->ceiling_rgb[1] = rgb[1];
		data->ceiling_rgb[2] = rgb[2];
		if (!is_valid_rgb(data->ceiling_rgb))
			print_error_exit("Ceiling RGB out of range", data);
	}
}

static void	parse_rgb_line(t_game_data *data, char *line, int rgb[3])
{
	char	**rgb_split;
	char	*tmp_line;
	int		i;

	tmp_line = ft_strdup(jump_spaces(line + 1));
	space_to_null(tmp_line);
	count_commas(data, tmp_line);
	is_invalid_char_rgb(data, tmp_line);
	rgb_split = ft_split(tmp_line, ',');
	free(tmp_line);
	i = 0;
	while (rgb_split[i])
		i++;
	if (i != 3)
	{
		free_split(rgb_split);
		print_error_exit("Invalid RGB format (Need R,G,B)", data);
	}
	i = 0;
	while (rgb_split[i])
	{
		rgb[i] = ft_atoi(rgb_split[i]);
		i++;
	}
	free_split(rgb_split);
}

void	get_color(t_game_data *data, char *line, char type)
{
	int	rgb[3];

	parse_rgb_line(data, line, rgb);
	set_color(data, rgb, type);
}
