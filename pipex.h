/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:01:46 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/04 19:00:25 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct s_cmd
{
	char	**cmd;
	char	*path;

}	t_cmd;

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		argc;
	char	**path;
	// char	**cmd1;
	// char	*path_cmd1;
	// char	**cmd2;
	// char	*path_cmd2;
	t_cmd	*cmds;
}	t_pipex;



//main.c



//path.c
void	get_env_path(t_pipex *pipex_data, char *envp[]);
void	find_path(t_pipex *pipex_data);
void	get_cmd_args(t_pipex *pipex_data, char *argv[]);

//split.c
char	**ft_split(char *str, char spliter);

//utils.c
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	open_fd(t_pipex *pipex_data, char *argv[]);
void	free_all(t_pipex *pipex_data, int error);
void	check_args(t_pipex *pipex_data, int argc);

#endif