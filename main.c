/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:21:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/04 10:27:43 by algasnie         ###   ########.fr       */
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

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex_data;
	int		pipe_fd[2];

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
	find_path(&pipex_data);
	create_pipe(pipe_fd);



	free_all(&pipex_data, 0);

	return (0);
}