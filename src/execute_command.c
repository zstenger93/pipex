/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:24:58 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/05 11:17:02 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_command(char *command, char **env)
{
	char	**commands;
	char	*cmd_path;
	char	*env_path;

	commands = ft_split(command, ' ');
	if (path_check(commands[0]) == 0)
	{
		cmd_path = commands[0];
		execve(cmd_path, commands, env);
	}
	else
	{
		env_path = get_env(env);
		cmd_path = get_path(env_path, commands[0]);
		if (cmd_path == NULL)
		{
			free_array((void **)commands);
			free(cmd_path);
			// cmd_error(INVALID_COMMAND, command);
		}
		else if (access(cmd_path, X_OK) == 0)
			execve(cmd_path, commands, env);
	}
	// free_array((void **)commands);
}

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
