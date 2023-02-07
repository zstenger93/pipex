/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 09:54:19 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/07 18:25:11 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	here_doc(char *limiter)
{
	pid_t	pid;
	int		filedescriptor[2];
	char	*input_line;

	if (pipe(filedescriptor) == -1)
		error_type(PIPE_ERROR);
	pid = fork();
	if (pid == -1)
		error_type(FORK_ERROR);
	if (pid == 0)
	{
		close(filedescriptor[0]);
		write(2, "heredoc> ", 9);
		while (1)
		{
			input_line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(input_line, limiter, ft_strlen(limiter)) == TRUE)
				exit(EXIT_SUCCESS);
			write(filedescriptor[1], input_line, ft_strlen(input_line));
			free(input_line);
			write(2, "heredoc> ", 9);
		}
	}
	else
		close_dup_wait(filedescriptor);
}

void	here_doc_here(int argc, char **argv, int cmd_i)
{
	if (argc > 5)
	{
		cmd_i = 3;
		here_doc(argv[2]);
	}
	else
		error_type(WRONG_INPUT);
}

void	close_dup_wait(int *filedescriptor)
{
	close(filedescriptor[1]);
	dup2(filedescriptor[0], STDIN_FILENO);
	wait(NULL);
}

//check for empty and only space filled arguments
void	invalid_arg_heredoc(int argc, char **argv)
{
	int		j;
	size_t	i;
	size_t	space;

	close(1);
	j = 2;
	while (++j < argc - 1)
	{
		if (ft_strlen(argv[3]) == 0 && ft_strncmp(argv[1], "here_doc", 8) == 0)
			permission_denied(argv, argv[j], 0, argc);
		else if (ft_strlen(argv[j - 1]) == 0)
			permission_denied(argv, argv[j], 0, argc);
		i = 0;
		space = 0;
		while (i < ft_strlen(argv[j]))
		{
			if (argv[j][i] == ' ')
				space++;
			i++;
		}
		if (ft_strlen(argv[j]) == space
			&& ft_strncmp(argv[1], "here_doc", 8) == TRUE)
			permission_denied(argv, argv[j], 1, argc);
		is_argv_valid(argc, argv);
	}
}
