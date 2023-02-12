/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:24:58 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/12 11:28:01 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

//check for direct paths, in case of only "cmd" check if it's valid
void	execute_command(char *command, char **env)
{
	char	**commands;
	char	*cmd_path;
	char	*env_path;

	commands = ft_split(command, ' ');
	if (check_for_script(command) == TRUE)
		execve(command, commands, env);
	else if (path_check(commands[0]) == TRUE)
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
		}
		else if (access(cmd_path, X_OK) == TRUE)
			execve(cmd_path, commands, env);
	}
}
