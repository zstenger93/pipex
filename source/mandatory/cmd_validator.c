/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:16:20 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/24 12:17:19 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

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
