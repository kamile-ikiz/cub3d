/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:05:00 by beergin           #+#    #+#             */
/*   Updated: 2026/02/09 01:21:34 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player(t_game_data *data, int x, int y, int *count)
{
	data->player_dir = data->map[y][x];
	data->player_x = x;
	data->player_y = y;
	(*count)++;
	printf("Player found at (%d, %d) facing %c\n", y, x, data->player_dir);
}

static void	validate_player_count(t_game_data *data, int count)
{
	if (count == 0)
		print_error_exit("No player start position found", data);
	if (count > 1)
		print_error_exit("Multiple player start positions found", data);
}

void	find_player(t_game_data *data)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < ft_strlenn(data->map[y]))
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
				set_player(data, x, y, &player_count);
			else if (!is_invalid_char(data->map[y][x]))
				print_error_exit("Invalid character in map", data);
			x++;
		}
		y++;
	}
	validate_player_count(data, player_count);
}
