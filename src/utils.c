/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:32:00 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/05 14:21:53 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_array(void **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	is_cat(char **argv)
{
	if ((ft_strcmp(argv[3], "cat")
		|| ft_strcmp(argv[3], "/cat")
		|| ft_strcmp(argv[3], "bin/cat")
		|| ft_strcmp(argv[3], "/bin/cat")) == 1)
		return (1);
	else
		return (0);
}

void	free_25(char *path, char **paths)
{
	free(path);
	free_array((void **)paths);
}
