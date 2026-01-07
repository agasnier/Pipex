/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:51:57 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/07 15:35:07 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "get_next_line_bonus.h"

char *get_file_name(void)
{
	int		i;
	char	*name;
	char	*tmp;

	i = 0;
	name = ft_strdup(".here_doc");
	if (!name)
		return (NULL);
	while (access(name, F_OK) == 0 && i < 2147483647)
	{
		tmp = ft_strjoin(name, "x");
		free(name);
		name = tmp;
		if (!name)
			return (NULL);
		i++;
	}
	
	return (name);
}

void here_doc(t_pipex *pipex_data)
{
	int		fd;
	char	*line;
	
	fd = open(pipex_data->here_doc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		free_all(pipex_data, 1, "Heredoc error");
	
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, pipex_data->here_doc_limiter, ft_strlen(pipex_data->here_doc_limiter)) == 0 && line[ft_strlen(pipex_data->here_doc_limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	get_next_line(fd);
}