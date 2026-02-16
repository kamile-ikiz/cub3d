/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:00:00 by beergin           #+#    #+#             */
/*   Updated: 2026/02/16 16:43:16 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_elements(t_game_data *data, char *line)
{
	char	*tmp_line;

	tmp_line = jump_spaces(line);
	if (ft_strncmp(tmp_line, "NO ", 3) == 0)
		get_texture_path(data, tmp_line, "NO");
	else if (ft_strncmp(tmp_line, "SO ", 3) == 0)
		get_texture_path(data, tmp_line, "SO");
	else if (ft_strncmp(tmp_line, "WE ", 3) == 0)
		get_texture_path(data, tmp_line, "WE");
	else if (ft_strncmp(tmp_line, "EA ", 3) == 0)
		get_texture_path(data, tmp_line, "EA");
	else if (ft_strncmp(tmp_line, "F ", 2) == 0)
		get_color(data, tmp_line, 'F');
	else if (ft_strncmp(tmp_line, "C ", 2) == 0)
		get_color(data, tmp_line, 'C');
	else if (*tmp_line && *tmp_line != '\n')
		print_error_exit("Invalid configuration line in file", data);
}

static char	*ft_strjoin_nofree(char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlenn(s1) + ft_strlenn(s2)) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

void	check_line(char *line, t_game_data *data)
{
	int	i;
	int flag;

	i = 0;
	flag = 0;
	while (line[i] && line[i] != '\n')
	{
		while(!flag && (line[i] == ' ' || line[i] == '\t' || line[i] == '\r'))
			i++;
		if (flag && (line[i] != ' ' && line[i] != '\t' && line[i] != '\r'))
			print_error_exit("Invalid line!", data);
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
			flag = 1;
		i++;
	}
}

static char	*process_map_line(t_game_data *data, char *map_codes,
		char *line, int *map_started)
{
	char	*temp_map;

	temp_map = map_codes;
	if (*map_started && (*jump_spaces(line) == '\0'
			|| *jump_spaces(line) == '\n'))
	{
		free(map_codes);
		free(line);
		print_error_exit("Empty lines are not allowed in the map", data);
	}
	if (*jump_spaces(line) && *jump_spaces(line) != '\n')
		*map_started = 1;
	map_codes = ft_strjoin_nofree(map_codes, line);
	check_line(line, data);
	free(temp_map);
	return (map_codes);
}

void	parsing_objects(t_game_data *data, int fd)
{
	char	*line;
	char	*map_codes;
	int		map_started;

	map_codes = ft_strdup("");
	map_started = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!all_elements_filled(data))
		{
			if (*jump_spaces(line) && *jump_spaces(line) != '\n')
				parse_elements(data, line);
		}
		else
			map_codes = process_map_line(data, map_codes, line, &map_started);
		free(line);
	}
	if (!map_started)
		print_error_exit("Map data was not found in the file", data);
	data->map = ft_split(map_codes, '\n');
	free(map_codes);
	check_data_simple(data);
}
