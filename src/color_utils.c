/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 00:34:14 by beergin           #+#    #+#             */
/*   Updated: 2026/02/10 00:50:36 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_invalid_char_rgb(t_game_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ',' && (str[i] < '0' || str[i] > '9') && str[i] != '\n')
		{
			free(str);
			print_error_exit("Invalid character in RGB format1", data);
		}
		i++;
	}
}
