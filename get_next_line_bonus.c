/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokdas <ogokdas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:47:44 by ogokdas           #+#    #+#             */
/*   Updated: 2025/07/12 16:00:33 by ogokdas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	ssize_t	rlen;

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
		if (rlen == 0)
			return (free(buf), s);
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
	free(s);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*s[2048];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s[fd] = ft_read(s[fd], fd);
	if (!s[fd])
		return (NULL);
	line = ft_getline(s[fd]);
	s[fd] = ft_getcut(s[fd]);
	return (line);
}
