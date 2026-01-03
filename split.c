/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:37:55 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/03 19:51:19 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	**ft_split(char *str, char spliter)
{
	char	**result;
	int		nb_tokens;
	int		i;
	int		j;
	int		k;
	int		token_len;

	if (!str)
		return (NULL);

	nb_tokens = count_split(str, spliter);
	result = malloc(sizeof(char *) * (nb_tokens + 1));
	if (!result)
		return (NULL);
	result[nb_tokens] = NULL;

	i = 0;
	k = 0;
	while (i < nb_tokens)
	{
		j = 0;
		token_len = get_len_split(&str[k], spliter);
		result[i] = malloc(sizeof(char) * (token_len + 1)); //error
		while (str[k] != '\0' && str[k] != spliter)
		{
			result[i][j] = str[k];
			j++;
			k++;
		}
		result[i][j] = '\0';
		if (str[k] == spliter)
			k++;
		i++;
	}
	return (result);
}
