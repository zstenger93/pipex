/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:32:12 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/05 17:09:05 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	input_check(char **argv, char **env)
{
	int		infile_fd;
	int		outfile_fd;
	char	*error;

	infile_fd = open(argv[1], O_RDONLY);
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW);
	if (infile_fd < 0)
	{
		error = strerror(errno);
		ft_printf("%s: %s: %s\n", argv[0], error, argv[4]);
	}
	close(infile_fd);
	close(outfile_fd);
	if (cmd_validator(argv[2], env) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	nothing_to_cat(char **argv)
{
	open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW);
	exit(0);
}

void	is_argv_valid(int argc, char **argv)
{
	int		j;
	size_t	i;
	size_t	space;

	j = 1;
	while (++j < argc - 1)
	{
		if (ft_strlen(argv[j]) == 0)
			permission_denied(argv);
		i = 0;
		space = 0;
		while (i < ft_strlen(argv[j]))
		{
			if (argv[j][i] == ' ')
				space++;
			i++;
		}
		if (ft_strlen(argv[j]) == space)
			permission_denied(argv);
	}
}

void	permission_denied(char **argv)
{
	ft_printf("./pipex: %s:\n", strerror(EACCES));
	open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW);
	exit(0);
}
