/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:08:43 by kikiz             #+#    #+#             */
/*   Updated: 2026/02/16 16:20:07 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture_image(t_game_data *data, t_game_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path,
			&img->width, &img->height);
	if (!img->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		all_free(data);
		exit(1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	load_textures(t_game_data *data)
{
	load_texture_image(data, &data->north_img, data->north_p);
	load_texture_image(data, &data->south_img, data->south_p);
	load_texture_image(data, &data->west_img, data->west_p);
	load_texture_image(data, &data->east_img, data->east_p);
}

int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
