#include "cub3d.h"

int ft_strlenn(const char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

void print_error_exit(char *message, t_game_data *data)
{
    int i;
    printf("Error\n%s\n", message);
    if (data)
    {
        if (data->north_p) free(data->north_p);
        if (data->south_p) free(data->south_p);
        if (data->west_p) free(data->west_p);
        if (data->east_p) free(data->east_p);

        if (data->map)
        {
            i = 0;
            while (data->map[i])
            {
                free(data->map[i]);
                i++;
            }
            free(data->map);
        }        
        free(data);
    }
    exit(1);
}

void all_free(t_game_data *data)
{
    int i;

    if (data)
    {
        if (data->north_p) free(data->north_p);
        if (data->south_p) free(data->south_p);
        if (data->west_p) free(data->west_p);
        if (data->east_p) free(data->east_p);

        if (data->map)
        {
            i = 0;
            while (data->map[i])
            {
                free(data->map[i]);
                i++;
            }
            free(data->map);
        }
        free(data);
    }
}

int fill(t_game_data *data, char **temp_map, int x, int y)
{
    if (y < 0 || y >= data->height || x < 0 || x >= ft_strlenn(temp_map[y]))
        return (0);
    if (temp_map[y][x] == ' ')
        return (0);
    if (temp_map[y][x] == '1' || temp_map[y][x] == 'B')
        return (1);
    temp_map[y][x] = 'B';
    if (!fill(data, temp_map, x + 1, y) || !fill(data, temp_map, x - 1, y) ||
        !fill(data, temp_map, x, y + 1) || !fill(data, temp_map, x, y - 1))
        return (0);
    return (1);
}

void get_map_width(t_game_data *data)
{
    int len;
    int max_width;
    int i;

    i = 0;
    max_width = 0;
    while(data->map[i] != NULL)
    {
        len = 0;
        while(data->map[i][len] != '\0')
            len++;
        if(len > max_width)
            max_width = len;
        i++;
    }
    data->width = max_width;
}

int get_map_width_simple(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0' && line[i] != '\n')
        i++;
    return (i);    
}

void find_player(t_game_data *data)
{
    int x;
    int y;
    int player_count = 0;

    for (y = 0; y < data->height; y++)
    {
        for (x = 0; x < ft_strlenn(data->map[y]); x++)
        {
            if (data->map[y][x] == 'N' || data->map[y][x] == 'S' ||
                data->map[y][x] == 'E' || data->map[y][x] == 'W')
            {
                data->player_dir = data->map[y][x];
                data->player_x = x;
                data->player_y = y;
                player_count++;
                printf("Player found at (%d, %d) facing %c\n", y, x, data->player_dir);
            }
            else if(!is_invalid_char(data->map[y][x]))
                print_error_exit("Invalid character in map", data);
        }
    }
    if (player_count == 0)
        print_error_exit("No player start position found", data);
    if (player_count > 1)
        print_error_exit("Multiple player start positions found", data);
}

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char *jump_spaces(char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    return (line);
}

int all_elements_filled(t_game_data *data)
{
    if (data->north_p && data->south_p && data->west_p && data->east_p &&
        data->floor_rgb[0] != -1 && data->ceiling_rgb[0] != -1)
        return (1);
    return (0);
}

void parse_elements(t_game_data *data, char *line)
{
    char *tmp_line;

    tmp_line = jump_spaces(line);
    if(ft_strncmp(tmp_line, "NO ", 3) == 0)
        get_texture_path(data, tmp_line, "NO");
    else if(ft_strncmp(tmp_line, "SO ", 3) == 0)
        get_texture_path(data, tmp_line, "SO");
    else if(ft_strncmp(tmp_line, "WE ", 3) == 0)
        get_texture_path(data, tmp_line, "WE");
    else if(ft_strncmp(tmp_line, "EA ", 3) == 0)
        get_texture_path(data, tmp_line, "EA");
    else if(ft_strncmp(tmp_line, "F ", 2) == 0)
        get_color(data, tmp_line, 'F');
    else if(ft_strncmp(tmp_line, "C ", 2) == 0)
        get_color(data, tmp_line, 'C');
}

static char *ft_strjoin_nofree(char *s1, const char *s2)
{
    size_t i;
    size_t j;
    char *str;

    if (!s1 || !s2)
        return (NULL);
    str = malloc(sizeof(char) * ((ft_strlenn(s1) + ft_strlenn(s2)) + 1));
    if (!str)
        return (NULL);
    i = 0;
    j = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    while (s2[j])
        str[i++] = s2[j++];
    str[i] = '\0';
    return (str);
}

void parsing_objects(t_game_data *data, int fd)
{
    char *line;
    char *map_codes;
    char *temp_map;

    line = get_next_line(fd);
    map_codes = ft_strdup("");
    while (line != NULL)
    {
        if(!all_elements_filled(data))
            parse_elements(data, line);
        else
        {
            temp_map = map_codes;
            map_codes = ft_strjoin_nofree(map_codes, line);
            free(temp_map);
        }
        free(line);
        line = get_next_line(fd);
    }
    if (map_codes && *map_codes)
        data->map = ft_split(map_codes, '\n');
    free(map_codes);
    if (data->map && data->map[0])
        printf("%s", data->map[0]);
}


