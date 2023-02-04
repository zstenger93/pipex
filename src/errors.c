/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:32:07 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/04 12:01:55 by zstenger         ###   ########.fr       */
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
	exit(1);
}

void	cmd_error(int error_id, char *command)
{
	if (error_id == INVALID_COMMAND)
		ft_printf("./pipex: command not found: %s\n", command);
}

int	cmd_validator(char *command, char **env)
{
	char	**commands;
	char	*cmd_path;
	char	*env_path;

	commands = ft_split(command, ' ');
	if (path_check(commands[0]))
		 return (0);
	else
	{
		env_path = get_env(env);
		cmd_path = get_path(env_path, commands[0]);
		if (cmd_path == NULL)
			return (1);
		else if (access(cmd_path, X_OK) != 0)
			return (1);
	}
	return (0);
}