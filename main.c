/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:21:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/05 17:08:08 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex_data;

	pipex_data.fd_in = -1;
	pipex_data.fd_out = -1;
	pipex_data.path = NULL;
	pipex_data.cmds = NULL;
	pipex_data.nb_cmds = 0;
	
	check_args(&pipex_data, argc, envp); //erreur ok
	open_fd(&pipex_data, argv); //erreur ok
	get_env_path(&pipex_data, envp); //erreur ok
	get_cmd_args(&pipex_data, argv);
	find_path(&pipex_data); //erreur ok
	exec(&pipex_data);
	ft_waitpid(&pipex_data); //erreur ok
	free_all(&pipex_data, 0);
	return (0);
}
