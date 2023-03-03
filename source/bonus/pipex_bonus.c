/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 09:54:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/28 10:33:25 by zstenger         ###   ########.fr       */
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
		invalid_arg_heredoc(argc, argv, env);
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
			pipex_bonus(argv, argc, argv[cmd_index++], env);
		final_cmd(argv, argc, env, outfile);
	}
	too_few_arg(argc);
}

void	pipex_bonus(char **argv, int argc, char *command, char **env)
{
	pid_t	pid;
	int		filedescriptor[2];

	if (cmd_validator(command, env) == FALSE)
		cmd_error(INVALID_COMMAND, command);
	if (pipe(filedescriptor) == -1)
		error_type(PIPE_ERROR);
	pid = fork();
	if (pid == -1)
		error_type(FORK_ERROR);
	if (pid == 0)
	{
		close(filedescriptor[0]);
		dup2(filedescriptor[1], STDOUT_FILENO);
		can_we_execute(argv, argc, command, env);
		execute_command(command, env);
	}
	else
	{
		close(filedescriptor[1]);
		dup2(filedescriptor[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	final_cmd(char **argv, int argc, char **env, int filedescriptor)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		dup2(filedescriptor, STDOUT_FILENO);
		close(filedescriptor);
		can_we_execute(argv, argc, argv[argc - 2], env);
		execute_command(argv[argc - 2], env);
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

/*
	if there is a wrong command,
	checks if the rest can be executed without that one,
	if so then it executes the command
*/
void	can_we_execute(char **argv, int argc, char *command, char **env)
{
	static int	i = 2;

	while (argv[i] != command)
		i++;
	if (cmd_validator(command, env) == FALSE && command != argv[argc - 1])
	{
		while (i < argc - 1)
		{
			if (ft_strncmp(argv[i], "ls", 2) == TRUE
				|| ft_strncmp(argv[i], "pwd", 3) == TRUE
				|| ft_strncmp(argv[i], "env", 3) == TRUE
				|| ft_strncmp(argv[i], "export", 6) == TRUE
				|| ft_strncmp(argv[i], "man", 3) == TRUE
				|| ft_strncmp(argv[i], "echo", 4) == TRUE
				|| ft_strncmp(argv[i], "history", 7) == TRUE
				|| ft_strncmp(argv[i], "sleep", 5) == TRUE
				|| ft_strncmp(argv[i], "which", 5) == TRUE
				|| ft_strncmp(argv[i], "wait", 4) == TRUE
				|| ft_strncmp(argv[i], "printenv", 8) == TRUE
				|| ft_strncmp(argv[i], "exit", 4) == TRUE)
				execute_command(argv[i], env);
			i++;
		}
		cannot_execute_quit(argv, argc, command);
	}
}
