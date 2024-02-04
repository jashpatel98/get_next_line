/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japatel <japatel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 04:27:35 by japatel           #+#    #+#             */
/*   Updated: 2024/02/04 18:46:26 by japatel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static void	*ft_bzero(void *ptr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)ptr + i) = '\0';
		i++;
	}
	return (ptr);
}

static char	*ft_join_string(char *line, char *buffer)
{
	char	*result;
	size_t	buffersize;

	buffersize = ft_strlen(buffer);
	if (buffer == NULL)
		return (line);
	result = malloc(sizeof(char) * (ft_strlen(line) + buffersize + 1));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, line, ft_strlen(line));
	ft_memcpy(result + ft_strlen(line), buffer, buffersize);
	result[ft_strlen(line) + buffersize] = '\0';
	free(line);
	line = NULL;
	return (result);
}

static char	*read_to_line(int fd, char *line)
{
	int		bytesrd;
	char	buffer[BUFFER_SIZE + 1];

	ft_bzero(&buffer, BUFFER_SIZE + 1);
	while (1)
	{
		bytesrd = read(fd, buffer, BUFFER_SIZE);
		if (bytesrd < 1)
			break ;
		buffer[bytesrd] = '\0';
		line = ft_join_string(line, buffer);
		if (!line)
			return (free(buffer), NULL);
		if (ft_strchr(line, '\n'))
			break ;
	}
	if (bytesrd < 0)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	return (line);
}

static int	check_file_read(int fd, char *line)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) <= -1)
	{
		free(line);
		line = NULL;
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char		*line1;
	static char	*line2;

	if (!check_file_read(fd, line2))
		return (NULL);
	line2 = read_to_line(fd, line2);
	if (!line2)
	{
		return (NULL);
	}
	line1 = ft_get_one_line(line2);
	line2 = ft_get_new_line(line2);
	return (line1);
}
