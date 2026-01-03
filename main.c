/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:21:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/03 20:57:13 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


// void	find_path(t_pipex *pipex_data)
// {
// 	if (access(pipex_data->cmd1, X_OK) == 0)
// 	{
		
// 	}



// }

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

void	get_cmd_args(t_pipex *pipex_data, char *argv[])
{
	pipex_data->cmd1 = ft_split(argv[2], ' ');
	pipex_data->cmd2 = ft_split(argv[3], ' ');
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex_data;

	check_args(argc);
	open_fd(&pipex_data, argv);

	get_cmd_args(&pipex_data, argv);
	printf("cmd1: %s cmd2: %s\n\n", pipex_data.cmd1[0], pipex_data.cmd2[1]);

	get_env_path(&pipex_data, envp);
	int i = 0;
	while (pipex_data.path[i])
	{
		printf("%s\n", pipex_data.path[i]);
		i++;
	}
	//find_path(&pipex_data);
	



	free_all(&pipex_data, 0);

	return (0);
}