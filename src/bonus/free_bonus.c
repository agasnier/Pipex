/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:10:30 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/07 16:33:06 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	ft_error(int exit_err, char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit (exit_err);
}

void	free_all(t_pipex *pipex_data, int exit_err, char *msg)
{
	int	i;

	free_tab(pipex_data->path);
	if (pipex_data->cmds)
	{
		i = 0;
		while (i < pipex_data->nb_cmds)
		{
			free_tab(pipex_data->cmds[i].cmd);
			free(pipex_data->cmds[i].path);
			i++;
		}
		free(pipex_data->cmds);
	}
	if (pipex_data->fd_in != -1)
		close(pipex_data->fd_in);
	if (pipex_data->fd_out != -1)
		close(pipex_data->fd_out);
	if (pipex_data->here_doc_file)
	{
		unlink(pipex_data->here_doc_file);
		free(pipex_data->here_doc_file);
	}
	if (exit_err >= 0)
		ft_error(exit_err, msg);
}
