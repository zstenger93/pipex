/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:32:00 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/07 10:03:24 by zstenger         ###   ########.fr       */
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

/*
if the first arg invalid, and the second one is cat, dont run cat
*/
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

int	no_such_file_or_folder(char *command)
{
	ft_printf("./pipex: %s: %s\n", strerror(ENOENT), command);
	return (FALSE);
}

void	closefd_and_wait_for_child_process(int *filedescriptor)
{
	int	process_id;
	int	status;

	close(filedescriptor[0]);
	close(filedescriptor[1]);
	process_id = waitpid(0, &status, 0);
	while (process_id != -1)
		process_id = waitpid(0, &status, 0);
}
