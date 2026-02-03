
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beergin <beergin@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:25:25 by beergin           #+#    #+#             */
/*   Updated: 2024/11/03 17:31:48 by beergin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_line(char *next_line)
{
	char	*new_str;
	int		i;

	i = 0;
	if (!*next_line)
		return (NULL);
	while (next_line[i] && next_line[i] != '\n')
		i++;
	new_str = malloc(sizeof(char) * (i + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (next_line[i] && next_line[i] != '\n')
	{
		new_str[i] = next_line[i];
		i++;
	}
	if (next_line[i] == '\n')
	{
		new_str[i] = next_line[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static char	*ft_to_next_line(char *next_line)
{
	int		i;
	int		j;
	char	*new_line;

	if (!next_line)
		return (NULL);
	i = 0;
	j = 0;
	while (next_line[i] && next_line[i] != '\n')
		i++;
	if (!next_line[i])
	{
		free(next_line);
		return (NULL);
	}
	new_line = malloc(sizeof(char) * (ft_strlen(next_line) - i + 1));
	if (!new_line)
		return (NULL);
	i++;
	while (next_line[i])
		new_line[j++] = next_line[i++];
	new_line[j] = '\0';
	free(next_line);
	return (new_line);
}

static char	*ft_get_str(int fd, char *next_line)
{
	int		r_bytes;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	r_bytes = 1;
	while (!ft_find_nl(next_line, '\n') && r_bytes != 0)
	{
		r_bytes = read(fd, buffer, BUFFER_SIZE);
		if (r_bytes == -1)
		{
			free(buffer);
			free(next_line);
			return (NULL);
		}
		buffer[r_bytes] = '\0';
		next_line = ft_strjoin(next_line, buffer);
		if (!next_line)
			return (NULL);
	}
	free(buffer);
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*next_line;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	next_line = ft_get_str(fd, next_line);
	if (!next_line)
		return (NULL);
	line = ft_get_line(next_line);
	next_line = ft_to_next_line(next_line);
	return (line);
}
