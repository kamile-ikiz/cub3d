/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 00:34:14 by beergin           #+#    #+#             */
/*   Updated: 2026/02/16 00:41:22 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_invalid_char_rgb(t_game_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ',' && (str[i] < '0' || str[i] > '9') && str[i] != '\n')
		{
			free(str);
			print_error_exit("Invalid character in RGB format", data);
		}
		i++;
	}
}

void	count_commas(t_game_data *data, char *str)
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

void	convert_rgb_values(t_game_data *data, char **rgb_split, int rgb[3])
{
	int	i;

	i = 0;
	while (rgb_split[i])
	{
		rgb[i] = ft_atoi(rgb_split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free_split(rgb_split);
			print_error_exit("RGB value must be between 0-255", data);
		}
		i++;
	}
}

static void	check_extra_chars(t_game_data *data, char *tmp_line)
{
	int	i;

	i = 0;
	while (tmp_line[i] && tmp_line[i] != ' ' && tmp_line[i] != '\t'
		&& tmp_line[i] != '\n')
		i++;
	if (tmp_line[i] == ' ' || tmp_line[i] == '\t')
	{
		free(tmp_line);
		print_error_exit("Invalid RGB format (extra characters)", data);
	}
}

void	parse_rgb_line(t_game_data *data, char *line, int rgb[3])
{
	char	**rgb_split;
	char	*tmp_line;
	int		i;

	tmp_line = ft_strdup(jump_spaces(line + 1));
	check_extra_chars(data, tmp_line);
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
	convert_rgb_values(data, rgb_split, rgb);
	free_split(rgb_split);
}
