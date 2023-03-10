/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:23:59 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/27 12:18:37 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

//get the full path splitted at : and command with /
char	*get_path(char *env_path, char *command)
{
	int		i;
	char	*path;
	char	**paths;
	char	*slash_cmd;

	i = 0;
	paths = ft_split(env_path, ':');
	while (paths != NULL)
	{
		slash_cmd = ft_nm_strjoin("/", command);
		path = ft_nm_strjoin(paths[i], slash_cmd);
		free(slash_cmd);
		if (path == NULL)
			return (free_25(path, paths), NULL);
		else if (access(path, X_OK) == TRUE)
		{
			free_array(paths);
			return (path);
		}
		i++;
		free(path);
	}
	free_array(paths);
	return (NULL);
}

//get the start of path from env
char	*get_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == TRUE)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
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

void	does_the_path_exist(char **argv, char **env, char type)
{
	if (type == 'm')
	{
		if (get_env(env) == NULL && check_for_script(argv[2]) == FALSE
			&& check_for_script(argv[3]) == FALSE)
		{
			ft_printf("\033[1;91mThe PATH environmental "
				"variable is not set.\n\033[0;39m");
			exit(EXIT_FAILURE);
		}
	}
	else if (type == 'b')
	{
		if (get_env(env) == NULL)
		{
			ft_printf("\033[1;91mThe PATH environmental "
				"variable is not set.\n\033[0;39m");
			exit(EXIT_FAILURE);
		}
	}
}

int	path_check(char *cmd_path)
{
	if (cmd_path[0] == '/' && access(cmd_path, X_OK) == TRUE)
		return (TRUE);
	return (FALSE);
}
