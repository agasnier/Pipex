/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:59:13 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/06 12:09:15 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*t;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	t = malloc(sizeof(char) * (len + 1));
	if (!t)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		t[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		t[i++] = s2[j++];
	t[i] = '\0';
	return (t);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*t;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		t = ft_strdup("");
		return (t);
	}
	if ((ft_strlen(s) - start) < len)
		t = malloc(sizeof(char) * (ft_strlen(s) - start) + 1);
	else
		t = malloc(sizeof(char) * (len + 1));
	if (!t)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		t[i] = s[start + i];
		i++;
	}
	t[i] = '\0';
	return (t);
}

char	*ft_strdup(const char *s)
{
	char	*t;
	int		size;
	int		i;

	size = ft_strlen(s);
	t = malloc(sizeof(char) * (size + 1));
	i = 0;
	if (!t)
		return (NULL);
	while (i < size)
	{
		t[i] = s[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
