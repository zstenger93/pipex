/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:31:20 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/13 19:07:06 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	main(int argc, char **argv, char **env)
{
	does_the_path_exist(argv, env, 'm');
	if (argc != 5)
	{
		usage('m');
		error_type(WRONG_INPUT);
	}
	is_argv_valid(argc, argv);
	pipex(argv, env);
	exit(EXIT_SUCCESS);
}

//check if the system or process has to many files open
void	pipex(char **argv, char **env)
{
	int		filedescriptor[2];
	int		cmd_error_nb;

	cmd_error_nb = cmd_validator(argv[2], env);
	if (pipe(filedescriptor) == -1)
		error_type(PIPE_ERROR);
	check_open_for_failure(argv, 1);
	if (open(argv[1], O_RDONLY) != -1)
	{
		if (cmd_error_nb == TRUE)
			input_process(filedescriptor, argv, env);
		else
			cmd_error(INVALID_COMMAND, argv[2]);
	}
	if (check_open_for_failure(argv, 2) == 0 && is_exit_code(argv) == FALSE)
	{
		if (cmd_validator(argv[3], env) == FALSE)
		{
			cmd_error(INVALID_COMMAND, argv[3]);
			exit(INVALID_COMMAND);
		}
		else if (cmd_validator(argv[3], env) == TRUE)
			output_process(filedescriptor, argv, env, cmd_error_nb);
	}
	closefd_and_wait_for_child_process(filedescriptor);
}

/*
if we are in the child process (pid 0)
close(0) open infile and make it as stdin
make fd 1 as stdout
*/
void	input_process(int *filedescriptor, char **argv, char **env)
{
	int		infile;
	pid_t	pid;

	if (input_check(argv, env) == FALSE)
		cmd_error(INVALID_COMMAND, argv[2]);
	else
	{
		pid = fork();
		if (pid == -1)
			error_type(FORK_ERROR);
		else if (pid == 0)
		{
			close(filedescriptor[0]);
			infile = open_file(0, argv[1]);
			dup2(infile, STDIN_FILENO);
			close(infile);
			dup2(filedescriptor[1], STDOUT_FILENO);
			close(filedescriptor[1]);
			execute_command(argv[2], env);
		}
	}
}

/*
if child process (pid 0) close(1) open the outfile and set it as stdout
close outfile, make fd[0] as stdin, close(0), execute command
*/
void	output_process(int *filedescriptor, char **argv, char **env, int e_id)
{
	int		outfile;
	pid_t	pid;

	if ((e_id == 1) && is_cat(argv) == 1)
		nothing_to_cat(argv);
	else
	{
		pid = fork();
		if (pid == -1)
			error_type(FORK_ERROR);
		else if (pid == 0)
		{
			close(filedescriptor[1]);
			outfile = open_file(2, argv[4]);
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
			dup2(filedescriptor[0], STDIN_FILENO);
			close(filedescriptor[0]);
			execute_command(argv[3], env);
		}
	}	
}

/*
close and wait for all child processes
status sores the exit status of the child proc.
if the return is -1, there is no more process to wait for
*/
void	closefd_and_wait_for_child_process(int *filedescriptor)
{
	int	pid;
	int	status;

	close(filedescriptor[0]);
	close(filedescriptor[1]);
	pid = waitpid(0, &status, 0);
	while (pid != -1)
		pid = waitpid(0, &status, 0);
}
