/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:21:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/05 14:58:39 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex_data;

	check_args(&pipex_data, argc, envp);
	open_fd(&pipex_data, argv);
	get_cmd_args(&pipex_data, argv);
	get_env_path(&pipex_data, envp);
	find_path(&pipex_data);
	exec(&pipex_data);
	ft_waitpid(&pipex_data);
	free_all(&pipex_data, 0);
	return (0);
}
