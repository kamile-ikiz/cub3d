/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:50:46 by beergin           #+#    #+#             */
/*   Updated: 2026/02/14 20:10:00 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_mlx(t_game_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		print_error_exit("Error initializing MLX", data);
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	if (data->win == NULL)
		print_error_exit("Error creating window", data);
	data->img = malloc(sizeof(t_game_img));
	if (data->img == NULL)
		print_error_exit("Error allocating memory for image", data);
	data->img->img = mlx_new_image(data->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (data->img->img == NULL)
		print_error_exit("Error creating image", data);
	data->img->addr = mlx_get_data_addr(data->img->img,
			&data->img->bits_per_pixel, &data->img->line_length,
			&data->img->endian);
	data->img->width = SCREEN_WIDTH;
	data->img->height = SCREEN_HEIGHT;
	load_textures(data);
}

static void	set_north_south(t_game_data *data)
{
	if (data->player_dir == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = 0.66;
		data->plane_y = 0;
	}
	else if (data->player_dir == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = -0.66;
		data->plane_y = 0;
	}
}

static void	set_west_east(t_game_data *data)
{
	if (data->player_dir == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -0.66;
	}
	else if (data->player_dir == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
}

void	player_direction(t_game_data *data)
{
	data->pos_x = data->player_x + 0.5;
	data->pos_y = data->player_y + 0.5;
	if (data->player_dir == 'N' || data->player_dir == 'S')
		set_north_south(data);
	else if (data->player_dir == 'W' || data->player_dir == 'E')
		set_west_east(data);
}
