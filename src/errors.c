/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:32:07 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/08 11:15:46 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error_type(int error_id)
{
	if (error_id == WRONG_INPUT)
		ft_putstr_fd("Wrong number of arguments!\n", 2);
	else if (error_id == PIPE_ERROR)
		perror("pipe failed");
	else if (error_id == FORK_ERROR)
		perror("fork failed");
	exit(EXIT_FAILURE);
}

//return if a command is invalid
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
	else if (error_id == 42)
		ft_printf("pipex: command not found: %s\n", command);
}

//check for valid commands with direct path else looking thru the folders
int	cmd_validator(char *command, char **env)
{
	char	**commands;
	char	*cmd_path;
	char	*env_path;

	commands = ft_split(command, ' ');
	if (check_for_script(command) == TRUE)
		return (TRUE);
	else if (path_with_bin_check(commands) == TRUE)
	{
		if (path_check(commands[0]) == TRUE)
			free_array((void **)commands);
		else
		{
			env_path = get_env(env);
			cmd_path = get_path(env_path, commands[0]);
			if (is_path_null(cmd_path, commands) == TRUE)
				return (FALSE);
			else if (access(cmd_path, X_OK) == TRUE)
				free_array((void **)commands);
			free(cmd_path);
		}
		return (TRUE);
	}
	free_array((void **)commands);
	return (FALSE);
}

//direct path check for commands
int	path_with_bin_check(char **commands)
{
	if (*commands[0] == '/')
	{
		if (ft_strncmp(*commands, "/bin", 4) == 0)
		{
			if (path_check(commands[0]) == TRUE)
				return (TRUE);
			else if (no_such_file_or_folder(*commands) == FALSE)
				return (FALSE);
		}
		if (ft_strncmp(*commands, "/usr/bin", 8) == 0)
		{
			if (path_check(commands[0]) == TRUE)
				return (TRUE);
			else if (no_such_file_or_folder(*commands) == FALSE)
				return (FALSE);
		}
		else if (no_such_file_or_folder(*commands) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

//check if there is no path
int	is_path_null(char *cmd_path, char **commands)
{
	if (cmd_path == NULL)
	{
		free_array((void **)commands);
		free(cmd_path);
		return (TRUE);
	}
	return (FALSE);
}
