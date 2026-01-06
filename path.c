/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:51:26 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/06 11:25:56 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_exec(char *cmd, char **path) //error ok
{
	int		i;
	char	*tmp;
	char	*tmp2;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	while (path && path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(tmp2, X_OK) == 0)
			return (tmp2);
		free(tmp2);
		i++;
	}
	return (NULL);
}

void	find_path(t_pipex *pipex_data)
{
	int	arg;
	int	cmds;

	arg = 2;
	cmds = 0;
	while (arg < pipex_data->argc - 1)
	{
		pipex_data->cmds[cmds].path = find_exec(pipex_data->cmds[cmds].cmd[0],
				pipex_data->path);
		cmds++;
		arg++;
	}
}

void	get_cmd_args(t_pipex *pipex_data, char *argv[])
{
	int	arg;
	int	cmds;

	arg = 2;
	cmds = 0;
	while (arg < pipex_data->argc - 1)
	{
		pipex_data->cmds[cmds].cmd = ft_split(argv[arg], ' ');
		if (!pipex_data->cmds[cmds].cmd)
			free_all(pipex_data, 1, "Erreur parsing commands.\n");
		cmds++;
		arg++;
	}
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
		free_all(pipex_data, 1, "Envpath not found.\n");
	pipex_data->path = ft_split(path, ':');
}
