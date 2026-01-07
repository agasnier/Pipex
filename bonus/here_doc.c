/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 09:51:57 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/07 12:59:52 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}


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


void here_doc(t_pipex *pipex_data, char *limiter)
{
	int		fd;
	char	*line;
	char	*name;

	name = get_file_name();
	
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		free_all(pipex_data, 1, "Heredoc error");
	
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strcmp(line, "STOP\n") == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}

	close(fd);
	get_next_line(fd);
	unlink(name);
	free(name);

	return (0);
}