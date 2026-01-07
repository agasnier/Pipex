/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:21:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/06 18:42:52 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pipex_struct_init(t_pipex *pipex_data)
{
	pipex_data->fd_in = -1;
	pipex_data->fd_out = -1;
	pipex_data->path = NULL;
	pipex_data->cmds = NULL;
	pipex_data->nb_cmds = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex_data;
	int		return_code;

	pipex_struct_init(&pipex_data);
	check_args(&pipex_data, argc, envp);
	open_fd(&pipex_data, argv);
	get_env_path(&pipex_data, envp);
	get_cmd_args(&pipex_data, argv);
	find_path(&pipex_data);
	exec(&pipex_data);
	return_code = ft_waitpid(&pipex_data);
	free_all(&pipex_data, -1, "");
	return (return_code);
}
