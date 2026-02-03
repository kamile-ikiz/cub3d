#include "cub3d.h"

static void get_map_height(t_game_data *data)
{
    int i;    
    i = 0;
    while (data->map[i] != NULL)
        i++;
    data->height = i;
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	leng;
	size_t	i;

	leng = ft_strlenn(s);
	str = (char *)malloc(sizeof(char) * (leng + 1));
	if (!(str))
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void get_map(t_game_data *data, char *filename)
{
    int   fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        print_error_exit("Could not open file", data);
    parsing_objects(data, fd);
    get_map_height(data);
    close(fd);
}

//get_map fonksiyonu düzenlenicek

void map_operations(t_game_data *data)
{
    border_check(data);
    find_player(data);
    
}

static void	init_data(t_game_data *data)
{
    data->north_p = NULL;
    data->south_p = NULL;
    data->west_p = NULL;
    data->east_p = NULL;
    data->map = NULL;
    data->height = 0;
    data->width = 0;
    data->player_x = 0;
    data->player_y = 0;
    data->player_dir = '\0';
    data->floor_rgb[0] = -1;
    data->floor_rgb[1] = -1;
    data->floor_rgb[2] = -1;
    data->ceiling_rgb[0] = -1;
    data->ceiling_rgb[1] = -1;
    data->ceiling_rgb[2] = -1;
}

int main(int ac, char **av)
{
    t_game_data *data;
    
    if(ac != 2)
    {
        printf("Error\nInvalid number of arguments\n");
        return (1);
    }
    data = malloc(sizeof(t_game_data));
    if(!data)
    {
        printf("Error\nMemory allocation failed\n");
        return (1);
    }
    init_data(data);
    check_extension(av[1], ".cub", data);
    get_map(data, av[1]);
    map_operations(data);
    printf("Map loaded successfully. width: %d\n", data->width);
    all_free(data);
    return 0;
}