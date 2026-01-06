/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:10:34 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/06 15:45:03 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_waitpid(t_pipex *pipex_data)
{
	int	i;

	i = 0;
	while (i < pipex_data->nb_cmds)
	{
		if (pipex_data->cmds[i].pid > 0)
			waitpid(pipex_data->cmds[i].pid, NULL, 0);
		i++;
	}
}

static void	child_process(t_pipex *pipex_data, int *pipe, int *fd_in, int i)
{
	if (dup2(*fd_in, STDIN_FILENO) == -1)
		free_all(pipex_data, 1, strerror(errno));
	close(*fd_in);
	if (i < pipex_data->nb_cmds - 1)
	{
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
		{
			close(pipe[0]);
			close(pipe[1]);
			free_all(pipex_data, 1, strerror(errno));
		}
		close(pipe[0]);
		close(pipe[1]);
	}
	else
		if (dup2(pipex_data->fd_out, STDOUT_FILENO) == -1)
			free_all(pipex_data, 1, strerror(errno));
	close(pipex_data->fd_in);
	close(pipex_data->fd_out);
	execve(pipex_data->cmds[i].path, pipex_data->cmds[i].cmd, pipex_data->envp);
	perror("child_process");
	free_all(pipex_data, 127, "");
}

static void	parent_process(t_pipex *pipex_data, int *pipe, int *fd_in, int i)
{
	if (*fd_in != pipex_data->fd_in)
		close(*fd_in);
	if (i < pipex_data->nb_cmds - 1)
	{
		close(pipe[1]);
		*fd_in = pipe[0];
	}
}

void	exec(t_pipex *pipex_data)
{
	int	i;
	int	pipe_fd[2];
	int	fd_in;

	i = 0;
	fd_in = pipex_data->fd_in;
	while (i < pipex_data->nb_cmds)
	{
		if (i < pipex_data->nb_cmds - 1)
			if (pipe(pipe_fd) == -1)
				free_all(pipex_data, 1, strerror(errno));
		pipex_data->cmds[i].pid = fork();
		if (pipex_data->cmds[i].pid == -1)
			free_all(pipex_data, 1, strerror(errno));
		if (pipex_data->cmds[i].pid == 0)
			child_process(pipex_data, pipe_fd, &fd_in, i);
		else
			parent_process(pipex_data, pipe_fd, &fd_in, i);
		i++;
	}
}
