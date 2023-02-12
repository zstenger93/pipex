/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 09:54:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/11 17:48:13 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	cmd_index;
	int	infile;
	int	outfile;

	if (argc >= 5)
	{
		cmd_index = 2;
		invalid_arg_heredoc(argc, argv);
		if (ft_strncmp(argv[1], "here_doc", 8) == TRUE)
		{
			cmd_index = 3;
			outfile = open_file(1, argv[argc - 1]);
			here_doc(argv[2], argc);
		}
		else
		{
			outfile = open_file(2, argv[argc - 1]);
			infile = open_file(0, argv[1]);
			dup2(infile, STDIN_FILENO);
		}
		while (cmd_index < argc - 2)
			child_process(argv[cmd_index++], env);
		final_cmd(argv[argc - 2], env, outfile);
	}
	too_few_arg(argc);
}

void	child_process(char *argv, char **env)
{
	pid_t	pid;
	int		filedescriptor[2];

	if (pipe(filedescriptor) == -1)
		error_type(PIPE_ERROR);
	pid = fork();
	if (pid == -1)
		error_type(FORK_ERROR);
	if (pid == 0)
	{
		close(filedescriptor[0]);
		dup2(filedescriptor[1], STDOUT_FILENO);
		execute_command(argv, env);
	}
	else
	{
		close(filedescriptor[1]);
		dup2(filedescriptor[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	final_cmd(char *command, char **env, int filedescriptor)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		dup2(filedescriptor, STDOUT_FILENO);
		close(filedescriptor);
		execute_command(command, env);
	}
	else
	{
		close(STDIN_FILENO);
		close(filedescriptor);
	}
}

void	too_few_arg(int argc)
{
	if (argc < 5)
	{
		usage('b');
		error_type(WRONG_INPUT);
	}
	else
		exit(EXIT_SUCCESS);
}
