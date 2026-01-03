/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:21:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/03 21:51:45 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	find_path(&pipex_data);
	



	free_all(&pipex_data, 0);

	return (0);
}