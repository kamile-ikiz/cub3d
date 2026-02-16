/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:50:46 by beergin           #+#    #+#             */
/*   Updated: 2026/02/16 18:17:25 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_data_simple(t_game_data *data)
{
	if (!data->map || !data->map[0])
		print_error_exit("Valid map data must be present", data);
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
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
	all_free(data);
	return (0);
}
