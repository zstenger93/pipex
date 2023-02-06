/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:36:12 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/06 15:02:54 by zstenger         ###   ########.fr       */
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
	char	*error;

	file_fd = -2;
	if (fd == 0)
		file_fd = open(file, O_RDONLY);
	else if (fd == 1)
		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, GIVE_PERM_WTH_RW);
	else if (fd == 2)
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW);
	if (file_fd == -1)
	{
		error = strerror(errno);
		ft_printf("./pipex: %s: %s\n", error, file);
		exit(1);
	}
	return (file_fd);
}

/*
infile check
outfile check
*/
int	check_open_for_failure(char **argv, int pick)
{
	if (pick == 1)
	{
		if (open(argv[1], O_RDONLY) == -1)
			ft_printf("./pipex: %s: %s\n", strerror(errno), argv[1]);
		return (0);
	}
	else if (pick == 2)
	{
		if (open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW) < 0)
		{
			ft_printf("%s: %s: %s\n", argv[0], strerror(errno), argv[4]);
			exit(errno);
		}
		else
			return (0);
	}
	return (0);
}
