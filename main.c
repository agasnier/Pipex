/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:21:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/03 17:33:48 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"







int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex_data;

	check_args(argc);
	open_fd(&pipex_data, argv);

	pipex_data.cmd1 = argv[2];
	pipex_data.cmd2 = argv[3];

	printf("cmd 1: %s || cmd 2: %s\n\n", pipex_data.cmd1, pipex_data.cmd2);
	
	get_env_path(&pipex_data, envp);



	int i = 0;
	while (pipex_data.path[i])
	{
		printf("%s\n\n", pipex_data.path[i]);
		i++;
	}

	free_all(&pipex_data, 0);

	return (0);
}