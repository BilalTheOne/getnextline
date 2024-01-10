/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:21:09 by bel-barb          #+#    #+#             */
/*   Updated: 2024/01/10 15:12:05 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_free_s2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*returrn;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	returrn = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!returrn)
		return (free(s1), free(s2), NULL);
	while (s1[i] != '\0')
		returrn[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		returrn[j++] = s2[i++];
	returrn[j] = 0;
	return (free(s1), free(s2), returrn);
}

char	*read_file(int fd, char **line)
{
	char	*buf;
	int		bytes;

	bytes = 1;
	buf = ft_calloc((size_t)BUFFER_SIZE + 1, 1);
	if (!buf)
		return (free(*line), *line = NULL, NULL);
	while (buf != NULL && bytes != 0 && !ft_strchr(buf, '\n'))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (free(*line), *line = NULL, free(buf), NULL);
		if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		*line = ft_strjoin(line, buf);
		if (!*line)
			return (free(buf), buf = NULL, NULL);
	}
	return (free(buf), buf = NULL, *line);
}

char	*before_nl(char **buf)
{
	char	*line;
	int		i;

	i = 0;
	if (!*buf || !**buf)
		return (NULL);
	while (*buf && (*buf)[i] != '\n' && (*buf)[i] != '\0')
		i++;
	if (ft_strchr(*buf, '\n'))
		i++;
	line = ft_calloc(i + 1, 1);
	if (!line)
		return (free(*buf), *buf = NULL, NULL);
	if ((*buf)[0] == '\n')
		return (line[0] = '\n', line[1] = '\0', line);
	i = 0;
	while ((*buf)[i] != '\n' && (*buf)[i] != '\0')
	{
		line[i] = (*buf)[i];
		i++;
		if ((*buf)[i] == '\n')
			line[i] = '\n';
	}
	return (line);
}

char	*after_nl(char **buf)
{
	char	*rest;
	int		i;
	int		j;

	if (!buf || !*buf)
		return (free(*buf), *buf = NULL, NULL);
	i = 0;
	while ((*buf)[i] && (*buf)[i] != '\n')
		i++;
	if ((*buf)[i] == '\n')
		i++;
	rest = (char *)ft_calloc(ft_strlen(*buf + i) + 1, sizeof(char));
	if (!rest)
		return (free(*buf), *buf = NULL, NULL);
	j = 0;
	while ((*buf)[i])
		rest[j++] = (*buf)[i++];
	rest[j] = '\0';
	(free(*buf), *buf = NULL);
	if (rest[0] == '\0')
		return (free(rest), rest = NULL, NULL);
	return (free(*buf), rest);
}

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	char		*buf;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX || read(fd, 0, 0) < 0)
		return (free(rest), rest = NULL, NULL);
	line = NULL;
	if (rest != NULL)
	{
		line = before_nl(&rest);
		if (ft_strchr(rest, '\n'))
			return (rest = after_nl(&rest), line);
	}
	buf = ft_calloc((size_t)BUFFER_SIZE + 1, 1);
	if (!buf)
		return (free(line), free(rest), rest = NULL, NULL);
	buf = read_file(fd, &buf);
	if (!buf)
		return (free(line), free(rest), rest = NULL, NULL);
	line = ft_strjoin_free_s2(line, (tmp = before_nl(&buf)));
	(free(rest), rest = NULL);
	if (!line)
		return (free(buf), NULL);
	return (rest = after_nl(&buf), free(buf), buf = NULL, line);
}
