/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:29:27 by bel-barb          #+#    #+#             */
/*   Updated: 2024/01/09 20:36:14 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char **s1, char *s2)
{
	int		i;
	int		j;
	char	*returrn;

	i = 0;
	j = 0;
	if (!*s1 && !s2)
		return (NULL);
	if (!*s1)
		return (s2);
	if (!s2)
		return (*s1);
	returrn = (char *)malloc((ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (!returrn)
		return (free(*s1), *s1 = NULL, NULL);
	while ((*s1)[i] != '\0')
		returrn[j++] = (*s1)[i++];
	i = 0;
	while (s2[i] != '\0')
		returrn[j++] = s2[i++];
	returrn[j] = 0;
	return (free(*s1), *s1 = NULL, returrn);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	_c;

	if (s == NULL)
		return (NULL);
	_c = (char)c;
	i = 0;
	while (s[i] != '\0' || (_c == '\0' && s[i] == '\0'))
	{
		if (s[i] == _c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(b + i) = (unsigned char)c;
		i++;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, '\0', count * size);
	return (ptr);
}
