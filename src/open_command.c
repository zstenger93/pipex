/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:36:12 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/07 18:23:50 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
open R only, if doesnt exist open it with read and write permissions
open WR only, created if doesnt exist and new data should be appended to the
end of file open WR only, created if doesnt exist and its content should be
removed if open return -1 print the error specified in errno
*/
int	open_file(int fd, char *file)
{
	int		file_fd;

	file_fd = -2;
	if (fd == 0)
		file_fd = open(file, O_RDONLY, GIVE_PERM_WTH_RW);
	else if (fd == 1)
		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, GIVE_PERM_WTH_RW);
	else if (fd == 2)
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW);
	if (file_fd == -1)
	{
		ft_printf("pipex: %s: %s\n", file, strerror(errno));
		exit(errno);
	}
	return (file_fd);
}

/*
infile check
outfile check
*/
int	check_open_for_failure(char **argv, int pick)
{
	int	stdout_copy;

	if (pick == 1)
	{
		if (open(argv[1], O_RDONLY) == -1)
		{
			stdout_copy = dup(1);
			dup2(2, 1);
			ft_printf("pipex: %s: %s\n", argv[1], strerror(errno));
			close(1);
			dup(stdout_copy);
			close(stdout_copy);
		}
		return (0);
	}
	else if (pick == 2)
	{
		if (open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW) < 0)
		{
			ft_printf("pipex: %s: %s\n", argv[4], strerror(errno));
			exit(errno);
		}
	}
	return (0);
}
