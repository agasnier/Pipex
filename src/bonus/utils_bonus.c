/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:29:49 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/07 15:34:29 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	open_fd(t_pipex *pipex_data, char *argv[])
{
	if (pipex_data->here_doc_file)
		pipex_data->fd_in = open(pipex_data->here_doc_file, O_RDONLY);
	else
		pipex_data->fd_in = open(argv[1], O_RDONLY);
	if (pipex_data->fd_in < 0)
		perror(argv[1]);
	if (pipex_data->here_doc)
		pipex_data->fd_out = open(argv[pipex_data->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipex_data->fd_out = open(argv[pipex_data->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex_data->fd_out < 0)
	{
		if (pipex_data->fd_in > 0)
			close(pipex_data->fd_in);
		perror(argv[pipex_data->argc - 1]);
		free_all(pipex_data, 1, "");
	}
}

static void	check_args_here_doc(t_pipex *pipex_data, char *argv[])
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		pipex_data->here_doc = 2;
		pipex_data->here_doc_limiter = argv[2];
		pipex_data->here_doc_file = get_file_name();
	}
}

void	check_args(t_pipex *pipex_data, int argc, char *argv[], char **envp)
{
	int	i;

	if (argc < 5)
		free_all(pipex_data, 1, "Number of arguments must be 5 minimum.\n");
	check_args_here_doc(pipex_data, argv);
	pipex_data->argc = argc;
	pipex_data->nb_cmds = argc - 3 - pipex_data->here_doc;
	pipex_data->envp = envp;
	pipex_data->cmds = malloc(sizeof(t_cmd) * (pipex_data->nb_cmds));
	if (pipex_data->cmds == NULL)
		free_all(pipex_data, 1, "Fail: Creation tab of cmds.\n");
	i = 0;
	while (i < pipex_data->nb_cmds)
	{
		pipex_data->cmds[i].cmd = NULL;
		pipex_data->cmds[i].path = NULL;
		pipex_data->cmds[i].pid = -1;
		i++;
	}
}
