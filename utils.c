/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:29:49 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/06 14:17:35 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*t;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	t = malloc(sizeof(char) * (len + 1));
	if (!t)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		t[i++] = s1[j++];
	j = 0;
	while (s2[j])
		t[i++] = s2[j++];
	t[i] = '\0';
	return (t);
}

void	open_fd(t_pipex *pipex_data, char *argv[])
{
	pipex_data->fd_in = open(argv[1], O_RDONLY);
	if (pipex_data->fd_in < 0)
		free_all(pipex_data, 1, strerror(errno));
	pipex_data->fd_out = open(argv[pipex_data->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex_data->fd_out < 0)
	{
		close(pipex_data->fd_in);
		free_all(pipex_data, 1, strerror(errno));
	}
}

void	check_args(t_pipex *pipex_data, int argc, char **envp)
{
	int	i;

	if (argc != 5)
		free_all(pipex_data, 1, "Number of arguments must be 5.\n");
	pipex_data->argc = argc;
	pipex_data->nb_cmds = argc - 3;
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
