/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:21:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/04 11:35:56 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child_exec(t_pipex *pipex_data, char *path_cmd, char **cmd, int fd_in, int fd_out, int unused_fd, char **envp)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{	
		write(2, "Error\n", 6); //error
		exit(1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		write(2, "Error\n", 6); //error
		exit(1);
	}
	close(fd_in);
	close(fd_out);
	close(unused_fd);

	(void)pipex_data;

	execve(path_cmd, cmd, envp);
	write(2, "Error\n", 6); //error
	exit(1);	
}

void	create_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex_data;
	int		pipe_fd[2];

	check_args(argc);
	open_fd(&pipex_data, argv);

	get_cmd_args(&pipex_data, argv);
	printf("cmd1: %s cmd2: %s\n\n", pipex_data.cmd1[0], pipex_data.cmd2[1]);

	get_env_path(&pipex_data, envp);
	find_path(&pipex_data);

	printf("%s\n", pipex_data.path_cmd1);




	create_pipe(pipe_fd);



	pid_t pid1 = fork();
	if (pid1 == -1)
	{
		write(2, "Error\n", 6); //error
		exit(1);
	}
	if (pid1 == 0)
	{
		child_exec(&pipex_data, pipex_data.path_cmd1, pipex_data.cmd1, pipex_data.fd_in, pipe_fd[1], pipe_fd[0], envp);

	}
	pid_t pid2 = fork();
	if (pid2 == -1)
	{
		write(2, "Error\n", 6); //error
		exit(1);
	}
	if (pid2 == 0)
	{
		child_exec(&pipex_data, pipex_data.path_cmd2, pipex_data.cmd2, pipe_fd[0], pipex_data.fd_out, pipe_fd[1], envp);

	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);	






	free_all(&pipex_data, 0);

	return (0);
}