/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:32:07 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/27 11:58:40 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	error_type(int error_id)
{
	if (error_id == WRONG_INPUT)
		ft_putstr_fd("          \033[1;4;91mWrong number of arguments!\n", 2);
	else if (error_id == PIPE_ERROR)
		perror("pipe failed");
	else if (error_id == FORK_ERROR)
		perror("fork failed");
	exit(EXIT_FAILURE);
}

//used if a command is invalid, redirect stdout to stderr and restore stdout
void	cmd_error(int error_id, char *command)
{
	int	stdout_copy;

	if (error_id == INVALID_COMMAND)
	{
		stdout_copy = dup(1);
		dup2(2, 1);
		ft_printf("pipex: %s: command not found\n", command);
		close(1);
		dup(stdout_copy);
		close(stdout_copy);
		close(0);
	}
}

void	cannot_execute_quit(char **argv, int argc, char *command)
{
	int	i;

	i = argc - 1;
	if (ft_strncmp(argv[0], "./pipex_bonus", 13) == TRUE)
	{
		if (open(argv[i], O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW) < 0)
			ft_printf("pipex: %s: %s\n", argv[i], strerror(errno));
		cmd_error(INVALID_COMMAND, command);
		exit(INVALID_COMMAND);
	}
}

int	no_such_file_or_folder(char *command)
{
	ft_printf("./pipex: %s: %s\n", strerror(ENOENT), command);
	return (FALSE);
}
