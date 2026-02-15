/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:42:22 by kikiz             #+#    #+#             */
/*   Updated: 2026/02/15 18:44:07 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_height(t_game_data *data)
{
	int	i;

	i = 0;
	while (data->map[i] != NULL)
		i++;
	data->height = i;
}

char	*get_map_dir(const char *filename)
{
	int		len;
	int		i;
	char	*dir;

	len = ft_strlenn(filename);
	i = len;
	while (i > 0 && filename[i - 1] != '/')
		i--;
	if (i == 0)
		return (ft_strdup(""));
	dir = (char *)malloc(sizeof(char) * (i + 1));
	if (!dir)
		return (NULL);
	len = 0;
	while (len < i)
	{
		dir[len] = filename[len];
		len++;
	}
	dir[len] = '\0';
	return (dir);
}

void	get_map(t_game_data *data, char *filename)
{
	int	fd;

	if (data->map_dir)
		free(data->map_dir);
	data->map_dir = get_map_dir(filename);
	if (!data->map_dir)
		print_error_exit("Memory allocation failed", data);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error_exit("Could not open file", data);
	parsing_objects(data, fd);
	get_map_height(data);
	close(fd);
}

void	map_operations(t_game_data *data)
{
	border_check(data);
	find_player(data);
}
