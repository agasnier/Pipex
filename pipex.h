/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:01:46 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/05 17:42:11 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_cmd
{
	pid_t	pid;
	char	**cmd;
	char	*path;

}	t_cmd;

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		argc;
	char	**envp;
	char	**path;
	int		nb_cmds;
	t_cmd	*cmds;
}	t_pipex;

//exec.c
void	ft_waitpid(t_pipex *pipex_data);
void	exec(t_pipex *pipex_data);

//path.c
void	find_path(t_pipex *pipex_data);
void	get_cmd_args(t_pipex *pipex_data, char *argv[]);
void	get_env_path(t_pipex *pipex_data, char *envp[]);

//split.c
char	**ft_split(char *str, char spliter);

//utils.c
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	open_fd(t_pipex *pipex_data, char *argv[]);
void	check_args(t_pipex *pipex_data, int argc, char **envp);

//free.c
void	ft_error(t_pipex *pipex_data, char *msg);
void	free_all(t_pipex *pipex_data);

#endif