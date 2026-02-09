/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:51:52 by beergin           #+#    #+#             */
/*   Updated: 2026/02/10 00:51:02 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../extras/get_next_line/get_next_line.h"

typedef struct s_game_data
{
	char	*north_p;
	char	*south_p;
	char	*west_p;
	char	*east_p;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	int		height;
	int		width;
	char	**map;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_game_data;

void	print_error_exit(char *message, t_game_data *data);
void	check_extension(char *filename, char *extension, t_game_data *data);
int		fill(t_game_data *data, char **temp_map, int x, int y);
void	get_map_width(t_game_data *data);
void	border_check(t_game_data *data);
int		ft_strlenn(const char *str);
char	*ft_strdup(const char *s);
int		get_map_width_simple(char *line);
void	find_player(t_game_data *data);
void	parsing_objects(t_game_data *data, int fd);
void	get_texture_path(t_game_data *data, char *line, char *dir);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
char	*jump_spaces(char *line);
void	get_color(t_game_data *data, char *line, char type);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
void	free_split(char **result);
int		is_invalid_char(char c);
void	all_free(t_game_data *data);
void	check_data_simple(t_game_data *data);
void	space_to_null(char *str);
void	start_data(t_game_data *data);
void	is_invalid_char_rgb(t_game_data *data, char *str);
#endif