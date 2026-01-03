/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:51:26 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/03 21:51:57 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (path == NULL) //error
	{
		free_all(pipex_data, 1);
	}
	pipex_data->path = ft_split(path, ':');
}


static char	*find_exec(char *cmd, char **path)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	if (access(cmd, X_OK) == 0)
	{
			printf("\nPath find\n");
	}
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/"); //free
		tmp2 = ft_strjoin(tmp, cmd); //free
		if (access(tmp2, X_OK) == 0)
		{
			printf("\nPath find: %s\n", tmp2);
			return (tmp2);
		}
		i++;
	}
	return (NULL);
}


void	find_path(t_pipex *pipex_data)
{
	pipex_data->path_cmd1 = find_exec(pipex_data->cmd1[0], pipex_data->path); //error
	pipex_data->path_cmd2 = find_exec(pipex_data->cmd2[0], pipex_data->path); //error
}

void	get_cmd_args(t_pipex *pipex_data, char *argv[])
{
	pipex_data->cmd1 = ft_split(argv[2], ' ');
	pipex_data->cmd2 = ft_split(argv[3], ' ');
}