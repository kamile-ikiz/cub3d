/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:06:00 by beergin           #+#    #+#             */
/*   Updated: 2026/02/13 19:04:43 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

void	trim_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
}

char	*join_paths(const char *dir, const char *path)
{
	int		len1;
	int		len2;
	int		i;
	char	*full;

	if (!dir || !path)
		return (NULL);
	len1 = ft_strlenn(dir);
	len2 = ft_strlenn(path);
	full = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!full)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		full[i] = dir[i];
		i++;
	}
	len1 = 0;
	while (len1 < len2)
	{
		full[i++] = path[len1++];
	}
	full[i] = '\0';
	return (full);
}

char	*try_relative_path(t_game_data *data, char *path, int *fd)
{
	char	*full_path;

	if (path[0] != '/' && data->map_dir && data->map_dir[0] != '\0')
	{
		full_path = join_paths(data->map_dir, path);
		if (!full_path)
		{
			free(path);
			print_error_exit("Memory allocation failed", data);
		}
		*fd = open(full_path, O_RDONLY);
		if (*fd >= 0)
		{
			close(*fd);
			free(path);
			return (full_path);
		}
		free(full_path);
	}
	return (path);
}

void	verify_file_exists(t_game_data *data, char *path, int fd)
{
	if (fd < 0)
	{
		fd = open(path, O_RDONLY);
		if (fd < 0)
		{
			free(path);
			print_error_exit("Texture file not found", data);
		}
		close(fd);
	}
}
