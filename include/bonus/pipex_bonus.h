/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:01:46 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/07 16:27:44 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "get_next_line_bonus.h"

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
	int		here_doc;
	char	*here_doc_limiter;
	char	*here_doc_file;
}	t_pipex;

//exec.c
int		ft_waitpid(t_pipex *pipex_data);
void	exec(t_pipex *pipex_data);

//path.c
void	find_path(t_pipex *pipex_data);
void	get_cmd_args(t_pipex *pipex_data, char *argv[]);
void	get_env_path(t_pipex *pipex_data, char *envp[]);

//split.c
char	**ft_split(char *str, char spliter);

//utils.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	open_fd(t_pipex *pipex_data, char *argv[]);
void	check_args(t_pipex *pipex_data, int argc, char *argv[], char **envp);

//free.c
void	free_all(t_pipex *pipex_data, int exit_err, char *msg);

//here_doc.c
char	*get_file_name(void);
void	here_doc(t_pipex *pipex_data);

#endif
