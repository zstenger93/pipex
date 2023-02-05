/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:23:59 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/05 14:45:56 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
			free_array((void **)paths);
			return (path);
		}
		i++;
		free(path);
	}
	free_array((void **)paths);
	return (NULL);
}

int	path_check(char *cmd_path)
{
	if (cmd_path[0] == '/' && access(cmd_path, X_OK) == TRUE)
		return (TRUE);
	return (FALSE);
}
