/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokdas <ogokdas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 00:37:51 by ogokdas           #+#    #+#             */
/*   Updated: 2025/07/07 00:37:51 by ogokdas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	newline(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_read(char *s, int fd)
{
	char	*buf;
	int		rlen;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	rlen = 1;
	while (!newline(s) && rlen != 0)
	{
		rlen = read(fd, buf, BUFFER_SIZE);
		if (rlen == -1)
		{
			if (s)
				free(s);
			free(buf);
			return (NULL);
		}
		buf[rlen] = '\0';
		s = ft_strjoin(s, buf);
	}
	free(buf);
	return (s);
}

char	*ft_getline(char *s)
{
	int		i;
	char	*line;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = ft_substr(s, 0, i);
	return (line);
}

char	*ft_getcut(char *s)
{
	char	*line_end;
	char	*res;

	line_end = ft_strchr(s, '\n');
	if (!line_end || *(line_end + 1) == '\0')
	{
		free(s);
		return (NULL);
	}
	res = ft_strdup(line_end + 1);
	free (s);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s = ft_read(s, fd);
	if (!s)
		return (NULL);
	line = ft_getline(s);
	s = ft_getcut(s);
	return (line);
}
