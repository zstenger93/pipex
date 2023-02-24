/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:32:00 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/24 12:19:41 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

//to free the splitted command before exit
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

//if the first arg invalid, and the second one is cat, dont run cat
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

//love norm
void	free_25(char *path, char **paths)
{
	free(path);
	free_array((void **)paths);
}

//in case of wrong input, return how to use pipex
void	usage(char part)
{
	if (part == 'm')
	{
		ft_printf("\n\033[4;92mHow to use: ./pipex infile "
			"\"cmd\" \"cmd1\" outfile\033[0;39m\n");
		ft_printf("\n   \033[4;92mExample: ./pipex Makefile "
			"\"cat\" \"cat\" out\033[0;39m\n\n");
	}
	if (part == 'b')
	{
		ft_printf("\n\033[4;92mHow to use: ./pipex_bonus infile "
			"\"cmd\" \"cmd1\" \"cmd2\" \"cmd3\" outfile\033[0;39m\n");
		ft_printf("\n    \033[4;92mExample: ./pipex_bonus Makefile "
			"\"cat\" \"cat\" \"cat\" \"cat\" out\033[0;39m\n\n");
	}
	if (part == 'h')
	{
		ft_printf("\n\033[4;92mHow to use: ./pipex_bonus here_doc limiter "
			"\"cmd\" \"cmd1\" outfile\033[0;39m\n");
		ft_printf("\n     \033[4;92mExample: ./pipex_bonus here_doc stop "
			"\"cat\" \"cat\" out\033[0;39m\n\n");
	}
}
