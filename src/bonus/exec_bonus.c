/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:10:34 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/07 15:36:00 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_waitpid(t_pipex *pipex_data)
{
	int	i;
	int	status;
	int	return_code;

	i = 0;
	return_code = 0;
	while (i < pipex_data->nb_cmds)
	{
		if (pipex_data->cmds[i].pid > 0)
		{
			waitpid(pipex_data->cmds[i].pid, &status, 0);
			if (WIFEXITED(status))
				return_code = WEXITSTATUS(status);
		}
		i++;
	}
	return (return_code);
}

static void	child_dup(t_pipex *pipex_data, int *pipe, int *fd_in, int i)
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
}

static void	child_process(t_pipex *pipex_data, int *pipe, int *fd_in, int i)
{
	if (*fd_in == -1)
	{
		if (i < pipex_data->nb_cmds - 1)
		{
			close(pipe[0]);
			close(pipe[1]);
		}
		free_all(pipex_data, 1, "");
	}
	child_dup(pipex_data, pipe, fd_in, i);
	if (pipex_data->fd_in != -1)
		close(pipex_data->fd_in);
	if (pipex_data->fd_out != -1)
		close(pipex_data->fd_out);
	if (!pipex_data->cmds[i].path)
	{
		if (pipex_data->cmds[i].cmd[0])
			write(2, pipex_data->cmds[i].cmd[0],
				ft_strlen(pipex_data->cmds[i].cmd[0]));
		free_all(pipex_data, 127, ": command not found\n");
	}
	execve(pipex_data->cmds[i].path, pipex_data->cmds[i].cmd, pipex_data->envp);
	perror(pipex_data->cmds[i].cmd[0]);
	free_all(pipex_data, 126, "");
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
