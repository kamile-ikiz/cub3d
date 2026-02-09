/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:05:00 by beergin           #+#    #+#             */
/*   Updated: 2026/02/10 00:10:47 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	space_to_null(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = '\0';
		i++;
	}
}

static void	to_compare(t_game_data *data, char *dir, char *path)
{
	if (ft_strncmp(dir, "NO", 2) == 0)
	{
		if (data->north_p)
			print_error_exit("Duplicate NO texture", data);
		data->north_p = path;
	}
	else if (ft_strncmp(dir, "SO", 2) == 0)
	{
		if (data->south_p)
			print_error_exit("Duplicate SO texture", data);
		data->south_p = path;
	}
	else if (ft_strncmp(dir, "WE", 2) == 0)
	{
		if (data->west_p)
			print_error_exit("Duplicate WE texture", data);
		data->west_p = path;
	}
	else if (ft_strncmp(dir, "EA", 2) == 0)
	{
		if (data->east_p)
			print_error_exit("Duplicate EA texture", data);
		data->east_p = path;
	}
}

void	get_texture_path(t_game_data *data, char *line, char *dir)
{
	char	*path;

	path = ft_strdup(jump_spaces(line + 2));
	space_to_null(path);
	if (path[0] == '\n' || path[0] == '\t')
		print_error_exit("Texture path is empty", data);
	to_compare(data, dir, path);
}
