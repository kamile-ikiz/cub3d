/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:30:47 by kikiz             #+#    #+#             */
/*   Updated: 2026/02/15 21:39:46 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_draw_values(t_draw *draw, t_ray *ray)
{
	draw->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw->draw_end >= SCREEN_HEIGHT)
		draw->draw_end = SCREEN_HEIGHT - 1;
}

static void	draw_ceiling(t_game_data *data, int x, int y)
{
	my_mlx_pixel_put(data->img, x, y,
		rgb_to_int(data->ceiling_rgb[0],
			data->ceiling_rgb[1],
			data->ceiling_rgb[2]));
}

static void	draw_floor(t_game_data *data, int x, int y)
{
	my_mlx_pixel_put(data->img, x, y,
		rgb_to_int(data->floor_rgb[0],
			data->floor_rgb[1],
			data->floor_rgb[2]));
}

static void	draw_wall_pixel(t_game_data *data, t_draw *draw,
				t_game_img *texture, int coords[3])
{
	int	tex_y;

	tex_y = (int)((coords[1] - draw->draw_start)
			* texture->height / draw->line_height);
	draw->color = get_texture_color(texture, coords[2], tex_y);
	my_mlx_pixel_put(data->img, coords[0], coords[1], draw->color);
}

void	draw_vertical_line(t_game_data *data, t_ray *ray, int x)
{
	t_draw		draw;
	t_game_img	*texture;
	int			tex_x;
	int			y;
	int			coords[3];

	init_draw_values(&draw, ray);
	texture = select_texture(data, ray);
	calculate_texture_x(data, ray, texture, &tex_x);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		if (y < draw.draw_start)
			draw_ceiling(data, x, y);
		else if (y <= draw.draw_end)
		{
			coords[0] = x;
			coords[1] = y;
			coords[2] = tex_x;
			draw_wall_pixel(data, &draw, texture, coords);
		}
		else
			draw_floor(data, x, y);
		y++;
	}
}
