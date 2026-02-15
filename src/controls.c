/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:08:06 by kikiz             #+#    #+#             */
/*   Updated: 2026/02/15 21:39:56 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_left(t_game_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(-ROT_SPEED)
		- data->dir_y * sin(-ROT_SPEED);
	data->dir_y = old_dir_x * sin(-ROT_SPEED)
		+ data->dir_y * cos(-ROT_SPEED);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(-ROT_SPEED)
		- data->plane_y * sin(-ROT_SPEED);
	data->plane_y = old_plane_x * sin(-ROT_SPEED)
		+ data->plane_y * cos(-ROT_SPEED);
}

static void	rotate_right(t_game_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(ROT_SPEED)
		- data->dir_y * sin(ROT_SPEED);
	data->dir_y = old_dir_x * sin(ROT_SPEED)
		+ data->dir_y * cos(ROT_SPEED);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(ROT_SPEED)
		- data->plane_y * sin(ROT_SPEED);
	data->plane_y = old_plane_x * sin(ROT_SPEED)
		+ data->plane_y * cos(ROT_SPEED);
}

int	key_press(int keycode, t_game_data *data)
{
	if (keycode == ESC)
	{
		all_free(data);
		exit(0);
	}
	else if (keycode == W_KEY)
		move_forward(data);
	else if (keycode == S_KEY)
		move_backward(data);
	else if (keycode == A_KEY)
		move_left(data);
	else if (keycode == D_KEY)
		move_right(data);
	else if (keycode == LEFT_ARROW)
		rotate_left(data);
	else if (keycode == RIGHT_ARROW)
		rotate_right(data);
	render_frame(data);
	return (0);
}

int	close_window(t_game_data *data)
{
	all_free(data);
	exit(0);
	return (0);
}
