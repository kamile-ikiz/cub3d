#include "cub3d.h"

void check_extension(char *filename, char *extension, t_game_data *data)
{
    int len_filename = 0;
    int len_extension = 0;

    while (filename[len_filename])
        len_filename++;
    while (extension[len_extension])
        len_extension++;
    if (len_filename < len_extension)
        print_error_exit("Invalid file extension", data);
    for (int i = 0; i < len_extension; i++)
    {
        if (filename[len_filename - len_extension + i] != extension[i])
            print_error_exit("Invalid file extension", data);
    }
}

static void border_check2(t_game_data *data)
{
    int x;
    int y;
    char **temp_map;

    temp_map = malloc(sizeof(char *) * (data->height + 1));
    if (!temp_map)
        print_error_exit("Memory allocation failed", data);
    for (x = 0; x < data->height; x++)
    {
        temp_map[x] = ft_strdup(data->map[x]);
        if (!temp_map[x])
            print_error_exit("Memory allocation failed", data);
    }
    temp_map[data->height] = NULL;

    for (x = 0; x < data->height; x++)
    {
        for (y = 0; y < ft_strlenn(temp_map[x]); y++)
        {
            if (temp_map[x][y] == '0')
            {
                if (!fill(data, temp_map, y, x))
                {
                    for (int i = 0; i < data->height; i++)
                        free(temp_map[i]);
                    free(temp_map);
                    print_error_exit("Map is not enclosed", data);
                }
            }
        }
    }

    for (x = 0; x < data->height; x++)
        free(temp_map[x]);
    free(temp_map);
}

void border_check(t_game_data *data)
{
    int x;
    int y;
    int line_width;


    x = 0;
    while(data->map[x] != NULL)
    {
        line_width = get_map_width_simple(data->map[x]);
        y = 0;
        if(x == 0 || x == data->height - 1)
        {
            while(data->map[x][y] != '\0' && y < line_width)
            {
                if(data->map[x][y] != '1' && data->map[x][y] != ' ')
                    print_error_exit("Map is not enclosed1 by walls", data);
                y++;
            }
        }
        else
        {
            if(data->map[x][0] != '1' && data->map[x][0] != ' ')
                print_error_exit("Map is not enclosed2 by walls", data);
            y = 0;
            while(data->map[x][y] != '\0' && y < line_width)
                y++;
            if(data->map[x][y - 1] != '1' && data->map[x][y - 1] != ' ')
                print_error_exit("Map is not enclosed3 by walls", data);
        }
        x++;
    }
    get_map_width(data);
    border_check2(data);
}

/*
yapılacaklar:
karakterin pozisyonunu bul
gezinme algoritması ile haritanın dışına çıkabiliyor mu kontrol et



*/

