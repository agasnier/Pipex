/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:21:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/05 12:18:59 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

void	child_exec(t_pipex *pipex_data)
{
	int	i;
	int pipe[2];
	int fd_in;

	i = 0;
	fd_in = pipex_data->fd_in;
	while (i < pipex_data->nb_cmds)
	{
		if (i < pipex_data->nb_cmds)
			create_pipe(pipe);

		pipex_data->cmds[i].pid = fork();
		if (pipex_data->cmds[i].pid == 0)
		{
			dup2(fd_in, STDIN_FILENO);
			
			if (i == pipex_data->nb_cmds - 1)
				dup2(pipex_data->fd_out, STDOUT_FILENO);
			else
				dup2(pipe[1], STDOUT_FILENO);
			if (i < pipex_data->nb_cmds - 1)
				close(pipe[0]);
			close(fd_in);
			execve(pipex_data->cmds[i].path, pipex_data->cmds[i].cmd, pipex_data->envp);
			exit(1);			
		}
		else
		{
			if (fd_in != pipex_data->fd_in)
				close(fd_in);
			if (i < pipex_data->nb_cmds - 1)
			{
				close(pipe[1]);
				fd_in = pipe[0];
			}
		}
		i++;	
	}		
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex_data;

	check_args(&pipex_data, argc, envp);
	open_fd(&pipex_data, argv);

	get_cmd_args(&pipex_data, argv);
	printf("cmd1: %s cmd2: %s\n", pipex_data.cmds[0].cmd[0], pipex_data.cmds[1].cmd[0]);

	get_env_path(&pipex_data, envp);
	find_path(&pipex_data);

	printf("path: %s\n\n", pipex_data.cmds[0].path);


	child_exec(&pipex_data);

	int	j = 0;
	while(j < pipex_data.nb_cmds)
	{
		waitpid(pipex_data.cmds[j].pid, NULL, 0);
		j++;
	}

	free_all(&pipex_data, 0);

	return (0);
}