/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:06:27 by kikiz             #+#    #+#             */
/*   Updated: 2026/02/14 14:07:03 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	my_mlx_pixel_put(t_game_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	get_texture_color(t_game_img *texture, int tex_x, int tex_y)
{
	char	*dst;

	if (tex_x < 0 || tex_x >= texture->width
		|| tex_y < 0 || tex_y >= texture->height)
		return (0);
	dst = texture->addr + (tex_y * texture->line_length
			+ tex_x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static t_game_img	*select_texture(t_game_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->raydir_x > 0)
			return (&data->east_img);
		else
			return (&data->west_img);
	}
	else
	{
		if (ray->raydir_y > 0)
			return (&data->south_img);
		else
			return (&data->north_img);
	}
}

static void	calculate_texture_x(t_game_data *data, t_ray *ray,
		t_game_img *texture, int *tex_x)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = data->pos_y + ray->perp_wall_dist * ray->raydir_y;
	else
		wall_x = data->pos_x + ray->perp_wall_dist * ray->raydir_x;
	wall_x -= floor(wall_x);
	*tex_x = (int)(wall_x * (double)texture->width);
	if (ray->side == 0 && ray->raydir_x > 0)
		*tex_x = texture->width - *tex_x - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		*tex_x = texture->width - *tex_x - 1;
}

void	draw_vertical_line(t_game_data *data, t_ray *ray, int x)
{
	t_draw		draw;
	t_game_img	*texture;
	int			tex_x;
	int			tex_y;
	int			y;

	draw.line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	draw.draw_start = -draw.line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw.draw_start < 0)
		draw.draw_start = 0;
	draw.draw_end = draw.line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw.draw_end >= SCREEN_HEIGHT)
		draw.draw_end = SCREEN_HEIGHT - 1;
	texture = select_texture(data, ray);
	calculate_texture_x(data, ray, texture, &tex_x);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		if (y < draw.draw_start)
			my_mlx_pixel_put(data->img, x, y,
				rgb_to_int(data->ceiling_rgb[0], data->ceiling_rgb[1],
					data->ceiling_rgb[2]));
		else if (y >= draw.draw_start && y <= draw.draw_end)
		{
			tex_y = (int)((y - draw.draw_start) * texture->height
					/ draw.line_height);
			draw.color = get_texture_color(texture, tex_x, tex_y);
			my_mlx_pixel_put(data->img, x, y, draw.color);
		}
		else
			my_mlx_pixel_put(data->img, x, y,
				rgb_to_int(data->floor_rgb[0], data->floor_rgb[1],
					data->floor_rgb[2]));
		y++;
	}
}

int	render_frame(t_game_data *data)
{
	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}
