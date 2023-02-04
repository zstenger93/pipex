/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:32:12 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/04 09:35:49 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	input_check(int argc, char **argv, char **env)
{
	int	infile_fd;
	int	outfile_fd;
	char	*error;

	if (argc != 5)
		error_type(WRONG_INPUT);
	infile_fd = open(argv[1], O_RDONLY);
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW);
	if (infile_fd < 0 || outfile_fd < 0)
	{
		if (infile_fd < 0)
		{
			error = strerror(errno);
			ft_printf("%s: %s: %s\n", argv[0], error, argv[1]);
			close_and_exit_with_error(infile_fd, outfile_fd);
		}
		else
		{
			error = strerror(errno);
			ft_printf("%s: %s: %s\n", argv[0], error, argv[4]);
			close_and_exit_with_error(infile_fd, outfile_fd);
		}
	}
	close(infile_fd);
	close(outfile_fd);
}

void	close_and_exit_with_error(int infile_fd, int outfile_fd)
{
	close(infile_fd);
	close(outfile_fd);
	exit(1);
}
