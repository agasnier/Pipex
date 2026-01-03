/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:01:46 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/03 15:42:29 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	char	**path;
}	t_pipex;


//main.c



//utils.c
void	get_env_path(t_pipex *pipex_data, char *envp[]);
void	open_fd(t_pipex *pipex_data, char *argv[]);
void	free_all(t_pipex *pipex_data, int error);
void	check_args(int argc);

#endif