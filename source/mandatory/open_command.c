/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:36:12 by zstenger          #+#    #+#             */
/*   Updated: 2023/03/02 13:28:21 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

//open the file we need, if it fails, return the the error
int	open_file(int fd, char *file)
{
	int		file_fd;

	file_fd = -2;
	if (fd == 0)
		file_fd = open(file, O_RDONLY);
	else if (fd == 1)
		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, GIVE_PERM_WTH_RW);
	else if (fd == 2)
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW);
	if (file_fd == -1)
	{
		ft_printf("pipex: %s: %s\n", file, strerror(errno));
		exit(0);
	}
	return (file_fd);
}

//check if the files can be opened or not
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
			return (-1);
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

//does it start with ./ and ends with .sh?
int	check_for_script(char *command)
{
	int	i;

	i = 0;
	while (command[i] != '\0')
		i++;
	if (command[0] == '.' && command[1] == '/')
	{
		if (script_check_end(command, i) == TRUE)
			return (TRUE);
	}
	else if (command[i - 1] == 'h' && command[i - 2] == 's'
		&& command[i - 3] == '.')
	{
		if (ft_strrchr(command, '/') == NULL)
			return (FALSE);
		else if (access(command, X_OK) == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

//check if the .sh file has rights to execute
int	script_check_end(char *command, int i)
{
	int	error;

	if (command[i - 1] == 'h' && command[i - 2] == 's'
		&& command[i - 3] == '.')
	{
		error = access(command, X_OK);
		if (error < 0)
		{
			ft_printf("pipex: %s: %s\n", command, strerror(errno));
			exit(0);
		}
		else
			return (TRUE);
	}
	return (FALSE);
}
