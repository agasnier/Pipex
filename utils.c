/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:29:49 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/05 17:10:55 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

//erreur ok
void	open_fd(t_pipex *pipex_data, char *argv[])
{
	pipex_data->fd_in = open(argv[1], O_RDONLY);
	if (pipex_data->fd_in < 0)
		ft_error(pipex_data, "Fail: Open(Infile).\n");
	pipex_data->fd_out = open(argv[pipex_data->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex_data->fd_out < 0)
	{
		close(pipex_data->fd_in);
		ft_error(pipex_data, "Fail: Open(Outfile).\n");
	}
}

//erreur ok
void	check_args(t_pipex *pipex_data, int argc, char **envp)
{
	int	i;
	if (argc != 5)
		ft_error(pipex_data, "Number of arguments must be 5.\n");
	pipex_data->argc = argc;
	pipex_data->nb_cmds = argc - 3;
	pipex_data->envp = envp;
	pipex_data->cmds = malloc(sizeof(t_cmd) * (pipex_data->nb_cmds));
	if (pipex_data->cmds == NULL)
		ft_error(pipex_data, "Fail: Creation tab of cmds.\n");
	i = 0;
	while(i < pipex_data->nb_cmds)
	{
		pipex_data->cmds[i].cmd = NULL;
		pipex_data->cmds[i].path = NULL;
		pipex_data->cmds[i].pid = -1;
		i++;
	}

}
