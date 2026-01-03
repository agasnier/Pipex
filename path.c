/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:45:52 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/03 17:37:34 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_len_path(char *path)
{
	int	i;

	i = 0;
	while (path[i] != '\0' && path[i] != ':')
		i++;
	return (i);
}

static int count_path(char *path)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (path[i])
	{
		if (path[i] == ':')
			count++;
		i++;
	}
	return (count);
	
}

static void split_env_path(t_pipex *pipex_data, char *path)
{
	char **env_path;
	int	nb_path;
	int	i;
	int	j;
	int	k;
	int	len_path;

	nb_path = count_path(path);

	env_path = malloc(sizeof(char *) * (nb_path + 1));
	if (env_path == NULL)
	{
		free_all(pipex_data, 1);
	}
	env_path[nb_path] = NULL;


	i = 0;
	k = 0;
	while (i < nb_path)
	{
		j = 0;
		len_path = get_len_path(&path[k]);
		env_path[i] = malloc(sizeof(char) * ( len_path + 2)); //gerer erreur
		while (path[k] != '\0' && path[k] != ':')
		{
			env_path[i][j] = path[k];
			j++;
			k++;
		}
		env_path[i][j] = '\0';
		if (path[k] == ':')
			k++;
		i++;
	}

	pipex_data->path = env_path;
}

void	get_env_path(t_pipex *pipex_data, char *envp[])
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' &&
			envp[i][2] == 'T' && envp[i][3] == 'H')
		{
			path = &envp[i][5];
		}
		i++;
	}
	if (path == NULL)
	{
		free_all(pipex_data, 1);
	}
	split_env_path(pipex_data, path);
}