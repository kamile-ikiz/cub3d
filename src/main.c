/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:50:46 by beergin           #+#    #+#             */
/*   Updated: 2026/02/09 01:43:03 by beergin          ###   ########.fr       */
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

void	get_map(t_game_data *data, char *filename)
{
	int	fd;

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

int	main(int ac, char **av)
{
	t_game_data	*data;

	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
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
	printf("Map loaded successfully. width: %d\n", data->width);
	all_free(data);
	return (0);
}
