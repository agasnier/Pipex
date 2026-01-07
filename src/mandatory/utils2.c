/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:17:21 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/06 14:18:35 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	length;
	size_t	i;

	length = ft_strlen(src);
	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (length);
}

char	*ft_strdup(const char *s)
{
	char	*t;

	t = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!t)
		return (NULL);
	ft_strlcpy(t, s, ft_strlen(s) + 1);
	return (t);
}
