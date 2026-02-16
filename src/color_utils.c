/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 00:34:14 by beergin           #+#    #+#             */
/*   Updated: 2026/02/16 18:19:52 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rgb_error(t_game_data *data, char *str, char *msg)
{
	free(str);
	print_error_exit(msg, data);
}

static void	convert_rgb_values(t_game_data *data, char **rgb_split, int rgb[3])
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

static void	remove_spaces(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

static void	validate_rgb_spacing(t_game_data *data, char *str)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	if (str[i] < '0' || str[i] > '9')
		rgb_error(data, str, "Invalid RGB format (Need R,G,B)");
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (comma_count < 2)
	{
		if (str[i++] != ',')
			rgb_error(data, str, "Invalid RGB format (Need R,G,B)");
		if (str[i] == ' ')
			i++;
		if (str[i] < '0' || str[i] > '9')
			rgb_error(data, str, "Invalid RGB format (comma spacing)");
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		comma_count++;
	}
	while (str[i] == ' ')
		i++;
	if (str[i] && str[i] != '\n')
		rgb_error(data, str, "Invalid RGB format (extra characters)");
}

void	parse_rgb_line(t_game_data *data, char *line, int rgb[3])
{
	char	**rgb_split;
	char	*tmp_line;
	int		i;

	tmp_line = ft_strdup(jump_spaces(line + 1));
	validate_rgb_spacing(data, tmp_line);
	remove_spaces(tmp_line);
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
