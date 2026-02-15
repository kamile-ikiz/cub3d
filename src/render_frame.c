/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:06:27 by kikiz             #+#    #+#             */
/*   Updated: 2026/02/15 21:39:40 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_game_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_color(t_game_img *texture, int tex_x, int tex_y)
{
	char	*dst;

	if (tex_x < 0 || tex_x >= texture->width
		|| tex_y < 0 || tex_y >= texture->height)
		return (0);
	dst = texture->addr + (tex_y * texture->line_length
			+ tex_x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

t_game_img	*select_texture(t_game_data *data, t_ray *ray)
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

void	calculate_texture_x(t_game_data *data, t_ray *ray,
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

int	render_frame(t_game_data *data)
{
	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}
