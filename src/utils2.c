#include "cub3d.h"

void get_texture_path(t_game_data *data, char *line, char *dir)
{
    char *path;

    path = ft_strdup(jump_spaces(line + 2));
    int i = 0;
    while (path[i])
    {
        if (path[i] == '\n')
            path[i] = '\0';
        i++;
    }
    if (ft_strncmp(dir, "NO", 2) == 0)
    {
        if (data->north_p) print_error_exit("Duplicate NO texture", data);
        data->north_p = path;
    }
    else if (ft_strncmp(dir, "SO", 2) == 0)
    {
        if (data->south_p) print_error_exit("Duplicate SO texture", data);
        data->south_p = path;
    }
    else if (ft_strncmp(dir, "WE", 2) == 0)
    {
        if (data->west_p) print_error_exit("Duplicate WE texture", data);
        data->west_p = path;
    }
    else if (ft_strncmp(dir, "EA", 2) == 0)
    {
        if (data->east_p) print_error_exit("Duplicate EA texture", data);
        data->east_p = path;
    }
}

void free_split(char **result)
{
    int i = 0;
    while (result[i])
    {
        free(result[i]);
        i++;
    }
    free(result);
}
int is_valid_rgb(int rgb[3])
{
    for (int i = 0; i < 3; i++)
    {
        if (rgb[i] < 0 || rgb[i] > 255)
            return (0);
    }
    return (1);
}

void get_color(t_game_data *data, char *line, char type)
{
    char    **rgb_split;
    char    *tmp_line;
    int     i;

    tmp_line = ft_strdup(jump_spaces(line + 1));
    i = 0;
    while (tmp_line[i])
    {
        if (tmp_line[i] == '\n')
            tmp_line[i] = '\0';
        i++;
    }
    rgb_split = ft_split(tmp_line, ',');
    free(tmp_line);
    i = 0;
    while (rgb_split[i])
        i++;
    if (i != 3)
    {
        free_split(rgb_split);
        print_error_exit("Invalid RGB format (Need R,G,B)", data);
    }
    if (type == 'F')
    {
        if (data->floor_rgb[0] != -1) print_error_exit("Duplicate Floor color", data);
        data->floor_rgb[0] = ft_atoi(rgb_split[0]);
        data->floor_rgb[1] = ft_atoi(rgb_split[1]);
        data->floor_rgb[2] = ft_atoi(rgb_split[2]);
        if (!is_valid_rgb(data->floor_rgb)) print_error_exit("Floor RGB out of range", data);
    }
    else if (type == 'C')
    {
        if (data->ceiling_rgb[0] != -1) print_error_exit("Duplicate Ceiling color", data);
        data->ceiling_rgb[0] = ft_atoi(rgb_split[0]);
        data->ceiling_rgb[1] = ft_atoi(rgb_split[1]);
        data->ceiling_rgb[2] = ft_atoi(rgb_split[2]);
        if (!is_valid_rgb(data->ceiling_rgb)) print_error_exit("Ceiling RGB out of range", data);
    }
    free_split(rgb_split);
}

int is_invalid_char(char c)
{
    if (c != '0' && c != '1' && c != ' ' &&
        c != 'N' && c != 'S' && c != 'E' && c != 'W')
        return (0);
    return (1);
}