/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikiz <kikiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:51:52 by beergin           #+#    #+#             */
/*   Updated: 2026/02/15 21:42:48 by kikiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../extras/get_next_line/get_next_line.h"
# include "../extras/minilibx-linux/mlx.h"

# define SCREEN_WIDTH 1080
# define SCREEN_HEIGHT 1020
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05

# define ESC 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

typedef struct s_game_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_game_img;

typedef struct s_draw
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
}	t_draw;

typedef struct s_ray
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_game_data
{
	char		*north_p;
	char		*south_p;
	char		*west_p;
	char		*east_p;
	int			floor_rgb[3];
	int			ceiling_rgb[3];
	int			height;
	int			width;
	char		**map;
	char		*map_dir;
	int			player_x;
	int			player_y;
	char		player_dir;
	void		*mlx;
	void		*win;
	t_game_img	*img;
	t_game_img	north_img;
	t_game_img	south_img;
	t_game_img	west_img;
	t_game_img	east_img;
	double		pos_x;
	double		pos_y;
	double		plane_x;
	double		plane_y;
	double		dir_x;
	double		dir_y;
}	t_game_data;

void		print_error_exit(char *message, t_game_data *data);
void		check_extension(char *filename, char *extension, t_game_data *data);
int			fill(t_game_data *data, char **temp_map, int x, int y);
void		get_map_width(t_game_data *data);
void		border_check(t_game_data *data);
int			ft_strlenn(const char *str);
char		*ft_strdup(const char *s);
int			get_map_width_simple(char *line);
void		find_player(t_game_data *data);
void		parsing_objects(t_game_data *data, int fd);
void		get_texture_path(t_game_data *data, char *line, char *dir);
int			ft_strncmp(const char *s1, const char *s2, size_t size);
char		*jump_spaces(char *line);
void		get_color(t_game_data *data, char *line, char type);
int			ft_atoi(const char *str);
char		**ft_split(char const *s, char c);
void		free_split(char **result);
int			is_invalid_char(char c);
void		all_free(t_game_data *data);
void		check_data_simple(t_game_data *data);
void		space_to_null(char *str);
void		start_data(t_game_data *data);
void		is_invalid_char_rgb(t_game_data *data, char *str);
void		player_direction(t_game_data *data);
void		start_mlx(t_game_data *data);
void		trim_path(char *str);
char		*join_paths(const char *dir, const char *path);
char		*try_relative_path(t_game_data *data, char *path, int *fd);
void		verify_file_exists(t_game_data *data, char *path, int fd);
void		get_map_height(t_game_data *data);
char		*get_map_dir(const char *filename);
void		get_map(t_game_data *data, char *filename);
void		map_operations(t_game_data *data);
void		cast_rays(t_game_data *data);
void		draw_vertical_line(t_game_data *data, t_ray *ray, int x);
int			render_frame(t_game_data *data);
int			key_press(int keycode, t_game_data *data);
int			close_window(t_game_data *data);
void		load_textures(t_game_data *data);
int			rgb_to_int(int r, int g, int b);
void		move_forward(t_game_data *data);
void		move_backward(t_game_data *data);
void		move_left(t_game_data *data);
void		move_right(t_game_data *data);
void		my_mlx_pixel_put(t_game_img *img, int x, int y, int color);
int			get_texture_color(t_game_img *texture, int tex_x, int tex_y);
t_game_img	*select_texture(t_game_data *data, t_ray *ray);
void		calculate_texture_x(t_game_data *data, t_ray *ray,
				t_game_img *texture, int *tex_x);

#endif