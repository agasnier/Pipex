/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:21:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/03 15:18:14 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_fd(t_pipex *pipex_data, char *argv[])
{
	pipex_data->fd_in = open(argv[1], O_RDONLY);
	if (pipex_data->fd_in < 0)
	{
		write(2, "Error\n", 6);
		exit(1);
	}

	pipex_data->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex_data->fd_out < 0)
	{
		write(2, "Error\n", 6);
		close(pipex_data->fd_in);
		exit(1);
	}
}

void	get_env_path(t_pipex *pipex_data, char *envp[])
{
	int	i;
	char *path;

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

	printf("%s", path); //need split
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex_data;

	if (argc != 5)
	{
		write(2, "Error\n", 6);
		//return (1);
	}

	open_fd(&pipex_data, argv);
	get_env_path(&pipex_data, envp);


	close(pipex_data.fd_in);
	close(pipex_data.fd_out);
	return (0);
}