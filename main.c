/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:21:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/03 15:43:55 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"







int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex_data;

	check_args(argc);
	open_fd(&pipex_data, argv);
	get_env_path(&pipex_data, envp);

	free_all(&pipex_data, 0);

	return (0);
}