/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:50:46 by beergin           #+#    #+#             */
/*   Updated: 2026/02/14 20:11:47 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_map_height(t_game_data *data)
{
	int	i;

	i = 0;
	while (data->map[i] != NULL)
		i++;
	data->height = i;
}

static char	*get_map_dir(const char *filename)
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

int	game_loop(t_game_data *data)
{
	render_frame(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_game_data	*data;

	if (ac != 2)
		return (printf("Error\nInvalid number of arguments\n"), 1);
	data = malloc(sizeof(t_game_data));
	if (!data)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	start_data(data);
	check_extension(av[1], ".cub", data);
	get_map(data, av[1]);
	map_operations(data);
	start_mlx(data);
	player_direction(data);
	render_frame(data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
	all_free(data);
	return (0);
}
