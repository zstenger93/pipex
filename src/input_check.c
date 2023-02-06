/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:32:12 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/06 16:50:05 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	input_check(char **argv, char **env)
{
	int		infile_fd;
	int		outfile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW);
	if (infile_fd < 0)
		ft_printf("%s: %s: %s\n", argv[0], strerror(errno), argv[4]);
	if (outfile_fd < 0)
		ft_printf("%s: %s: %s\n", argv[0], strerror(errno), argv[4]);
	close(infile_fd);
	close(outfile_fd);
	if (cmd_validator(argv[2], env) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	nothing_to_cat(char **argv)
{
	if (open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW) < 0)
		ft_printf("%s: %s: %s\n", argv[0], strerror(errno), argv[4]);
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
			permission_denied(argv, argv[j], 0);
		i = 0;
		space = 0;
		while (i < ft_strlen(argv[j]))
		{
			if (argv[j][i] == ' ')
				space++;
			i++;
		}
		if (ft_strlen(argv[j]) == space && argv[j])
			permission_denied(argv, argv[j], 1);
	}
}

//when the argument is empty or have only space
void	permission_denied(char **argv, char *command, int space)
{
	if (open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW) < 0)
		ft_printf("%s: %s: %s\n", argv[0], strerror(errno), argv[4]);
	if (space == 0)
	{
		ft_printf("./pipex: %s:\n", strerror(EACCES));
		exit(0);
	}
	else if (space == 1)
	{
		ft_printf("./pipex: command not found: %s\n", command);
		exit(INVALID_COMMAND);
	}
	exit(0);
}

/*
if the given command is exit -> exit with the correct code. check with: echo $?
*/
int	is_exit_code(char **argv)
{
	char	*str;
	int		len;
	int		i;
	char	*codestr;
	int		code;

	str = "exit ";
	if (ft_strcmp(argv[3], "exit") == 1 && ft_strncmp(argv[3], "exit ", 5) != 0)
	{
		cmd_error(INVALID_COMMAND, "exit");
		exit(INVALID_COMMAND);
	}
	else if (ft_strncmp(argv[3], str, 5) == 0)
	{
		i = 5;
		len = ft_strlen(argv[3] + i);
		codestr = (char *)malloc((len + 1) * sizeof(char));
		strcpy(codestr, argv[3] + i);
		code = ft_atoi(codestr);
		free(codestr);
		exit(code);
	}
	else
		return (FALSE);
}
