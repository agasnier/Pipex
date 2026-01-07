/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:37:55 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/07 15:34:50 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	get_len_split(char *str, char spliter)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != spliter)
		i++;
	return (i);
}

static int	count_split(char *str, char spliter)
{
	int	i;
	int	count;

	if (!str || !*str)
		return (0);
	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == spliter)
			count++;
		i++;
	}
	return (count);
}

static int	write_split_helper(char **result, int i)
{
	while (--i >= 0)
		free(result[i]);
	return (1);
}

static int	write_split(char **result, int nb_split, char *str, char spliter)
{
	int		i;
	int		j;
	int		k;
	int		len_split;

	i = 0;
	k = 0;
	while (i < nb_split)
	{
		j = 0;
		len_split = get_len_split(&str[k], spliter);
		result[i] = malloc(sizeof(char) * (len_split + 1));
		if (!result[i])
			return (write_split_helper(result, i));
		while (str[k] != '\0' && str[k] != spliter)
			result[i][j++] = str[k++];
		result[i][j] = '\0';
		if (str[k] == spliter)
			k++;
		i++;
	}
	return (0);
}

char	**ft_split(char *str, char spliter)
{
	char	**result;
	int		nb_split;

	if (!str)
		return (NULL);
	nb_split = count_split(str, spliter);
	result = malloc(sizeof(char *) * (nb_split + 1));
	if (!result)
		return (NULL);
	result[nb_split] = NULL;
	if (write_split(result, nb_split, str, spliter))
	{
		free (result);
		return (NULL);
	}
	return (result);
}
