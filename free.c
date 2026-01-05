/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:10:30 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/05 17:11:28 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	ft_error(t_pipex *pipex_data, char *msg)
{
	(void)pipex_data;
	write(2, msg, ft_strlen(msg));
	exit (1);
}

void static	free_tab(char **tab)
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

void	free_all(t_pipex *pipex_data, int error)
{
	int i;

	if (error)
		write(2, "error\n", 6);
	if (pipex_data->path)
	{
		free_tab(pipex_data->path);
		pipex_data->path = NULL;
	}
	if (pipex_data->cmds)
	{
		i = 0;
		while (i < pipex_data->nb_cmds)
		{
			if (pipex_data->cmds[i].cmd)
				free_tab(pipex_data->cmds[i].cmd);
			if (pipex_data->cmds[i].path)
				free(pipex_data->cmds[i].path);
			i++;
		}
		free(pipex_data->cmds);
		pipex_data->cmds = NULL;
	}
	if (pipex_data->fd_in != -1)
		close(pipex_data->fd_in);
	if (pipex_data->fd_out != -1)
		close(pipex_data->fd_out);
}