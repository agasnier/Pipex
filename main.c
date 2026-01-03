/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:21:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/01/03 14:43:39 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>

int	main(int argc, char *argv[])
{
	if (argc != 5)
	{
		write(1, "Error\n", 6);
		//return (1);
	}

	int	fd_in;
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
	{
		write(1, "Error\n", 6);
		//return (1);
	}

	int	fd_out;
	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_in < 0)
	{
		write(1, "Error\n", 6);
		//return (1);
	}




	

	return (0);
}