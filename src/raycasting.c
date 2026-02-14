/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:03:57 by kikiz             #+#    #+#             */
/*   Updated: 2026/02/14 14:05:50 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_game_data *data, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->raydir_x = data->dir_x + data->plane_x * ray->camera_x;
	ray->raydir_y = data->dir_y + data->plane_y * ray->camera_x;
	ray->map_x = (int)data->pos_x;
	ray->map_y = (int)data->pos_y;
	if (ray->raydir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->raydir_y);
	ray->hit = 0;
}

static void	calculate_step(t_game_data *data, t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->pos_x) * ray->delta_dist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->pos_y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_game_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= data->width
			|| ray->map_y < 0 || ray->map_y >= data->height)
			ray->hit = 1;
		else if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calculate_wall_distance(t_game_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->pos_x
				+ (1 - ray->step_x) / 2) / ray->raydir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->pos_y
				+ (1 - ray->step_y) / 2) / ray->raydir_y;
}

void	cast_rays(t_game_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(data, &ray, x);
		calculate_step(data, &ray);
		perform_dda(data, &ray);
		calculate_wall_distance(data, &ray);
		draw_vertical_line(data, &ray, x);
		x++;
	}
}
