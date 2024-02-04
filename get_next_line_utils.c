/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japatel <japatel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 04:26:56 by japatel           #+#    #+#             */
/*   Updated: 2024/01/13 14:19:12 by japatel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	char	character;

	character = (char)c;
	if (!s)
		return (0);
	if (character == '\0')
		return ((char *)s);
	while (*s != '\0')
	{
		if (*s == character)
			return ((char *)s);
		s++;
	}
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s = src;
	size_t		i;

	if (dst == NULL && src == NULL)
		return (0);
	d = dst;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*ft_get_one_line(char *line)
{
	char	*result;
	size_t	linesize;
	size_t	i;

	i = 0;
	linesize = ft_strlen(line);
	if (linesize == 0)
		return (NULL);
	result = malloc(sizeof(char) * (linesize + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, line, linesize);
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			result[i + 1] = '\0';
		else
			result[linesize] = '\0';
		i++;
	}
	return (result);
}

char	*ft_get_new_line(char *line)
{
	size_t	i;
	char	*result;
	char	*newline;

	newline = ft_strchr(line, '\n');
	if (newline == NULL)
		i = ft_strlen(line);
	else
		i = newline - line;
	if (!*line)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	result = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, ft_strchr(line, '\n') + 1, ft_strlen(line) - i);
	result[ft_strlen(line) - i] = '\0';
	free(line);
	line = NULL;
	return (result);
}
