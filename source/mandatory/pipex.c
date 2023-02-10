/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:31:20 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/10 18:18:14 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/*
return a message about usage and error if the arg count is wrong
check the args for empty and only space arguments
*/
int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		usage('m');
		error_type(WRONG_INPUT);
	}
	is_argv_valid(argc, argv);
	pipex(argv, env);
	exit(EXIT_SUCCESS);
}

/*
check the pipe, if it returns error, either way the entire system or
the process has to many files open
if the file is correct and the command is valid -> input process
if if the files are good and the command is not exit then
check if the command is valid, if so execute
close the filedescriptors and wait for the child proceso to finish
*/
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
doublecheck input mb not necessary
fork(), if it fails return the error and exit
if we are in the child process (pid 0)
close(0) open infile and make it as stdin
make fd 1 as stdout
execve the command
*/
void	input_process(int *filedescriptor, char **argv, char **env)
{
	int		infile_fd;
	pid_t	process_id;

	if (input_check(argv, env) == FALSE)
		cmd_error(INVALID_COMMAND, argv[2]);
	else
	{
		process_id = fork();
		if (process_id == -1)
			error_type(FORK_ERROR);
		else if (process_id == 0)
		{
			close(filedescriptor[0]);
			infile_fd = open_file(0, argv[1]);
			dup2(infile_fd, STDIN_FILENO);
			close(infile_fd);
			dup2(filedescriptor[1], STDOUT_FILENO);
			close(filedescriptor[1]);
			execute_command(argv[2], env);
		}
	}
}

/*
if the 1st command is not valid and the 3rd is cat close and exit
if child process (pid 0) close(1) open the outfile and set it as stdout
close outfile, make fd[0] as stdin, close(0), execute command
*/
void	output_process(int *filedescriptor, char **argv, char **env, int e_id)
{
	int		outfile_fd;
	pid_t	process_id;

	if ((e_id == 1) && is_cat(argv) == 1)
		nothing_to_cat(argv);
	else
	{
		process_id = fork();
		if (process_id == -1)
			error_type(FORK_ERROR);
		else if (process_id == 0)
		{
			close(filedescriptor[1]);
			outfile_fd = open_file(2, argv[4]);
			dup2(outfile_fd, STDOUT_FILENO);
			close(outfile_fd);
			dup2(filedescriptor[0], STDIN_FILENO);
			close(filedescriptor[0]);
			execute_command(argv[3], env);
		}
	}	
}

//close fd's and wait for the child process to finish using -1
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
