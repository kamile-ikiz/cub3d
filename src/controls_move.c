/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:04:16 by kikiz             #+#    #+#             */
/*   Updated: 2026/02/15 21:39:49 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + data->dir_x * MOVE_SPEED;
	new_y = data->pos_y + data->dir_y * MOVE_SPEED;
	if (data->map[(int)data->pos_y][(int)new_x] != '1')
		data->pos_x = new_x;
	if (data->map[(int)new_y][(int)data->pos_x] != '1')
		data->pos_y = new_y;
}

void	move_backward(t_game_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x - data->dir_x * MOVE_SPEED;
	new_y = data->pos_y - data->dir_y * MOVE_SPEED;
	if (data->map[(int)data->pos_y][(int)new_x] != '1')
		data->pos_x = new_x;
	if (data->map[(int)new_y][(int)data->pos_x] != '1')
		data->pos_y = new_y;
}

void	move_left(t_game_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x - data->plane_x * MOVE_SPEED;
	new_y = data->pos_y - data->plane_y * MOVE_SPEED;
	if (data->map[(int)data->pos_y][(int)new_x] != '1')
		data->pos_x = new_x;
	if (data->map[(int)new_y][(int)data->pos_x] != '1')
		data->pos_y = new_y;
}

void	move_right(t_game_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + data->plane_x * MOVE_SPEED;
	new_y = data->pos_y + data->plane_y * MOVE_SPEED;
	if (data->map[(int)data->pos_y][(int)new_x] != '1')
		data->pos_x = new_x;
	if (data->map[(int)new_y][(int)data->pos_x] != '1')
		data->pos_y = new_y;
}
