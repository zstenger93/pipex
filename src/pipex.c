/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:31:20 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/05 17:04:56 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
		error_type(WRONG_INPUT);
	is_argv_valid(argc, argv);
	pipex(argv, env);
	exit(0);
}

/*
check the pipe, if it returns error, either way the entire system or
the process has to many files open
input and output process
close the filedescriptors and wait for the child processes to finish
*/
void	pipex(char **argv, char **env)
{
	int		filedescriptor[2];
	char	*error;
	int		cmd_error;

	cmd_error = cmd_validator(argv[2], env);
	if (pipe(filedescriptor) == -1)
		error_type(PIPE_ERROR);
	if (open(argv[1], O_RDONLY) == -1)
	{
		error = strerror(errno);
		ft_printf("./pipex: %s: %s\n", error, argv[1]);
	}
	if (open(argv[1], O_RDONLY) != -1)
	{
		if (cmd_error == TRUE)
			input_process(filedescriptor, argv, env);
	}
	if (cmd_validator(argv[3], env) == TRUE)
		output_process(filedescriptor, argv, env, cmd_error);
	close(filedescriptor[0]);
	close(filedescriptor[1]);
	wait_for_child_process();
}

/*
doublecheck input mb not necessary
fork(), if it fails return the error and exit
if fails error


*/
void	input_process(int *fd, char **argv, char **env)
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
			close(fd[0]);
			infile_fd = open_file(0, argv[1]);
			dup2(infile_fd, STDIN_FILENO);
			close(infile_fd);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			execute_command(argv[2], env);
		}
	}
}

/*
if the 1st command is not valid and the 3rd is cat close and exit
check the command
*/
void	output_process(int *fd, char **argv, char **env, int error_id)
{
	int		outfile_fd;
	pid_t	process_id;

	if ((error_id == 1) && is_cat(argv) == 1)
		nothing_to_cat(argv);
	if (cmd_validator(argv[3], env) == FALSE)
		cmd_error(INVALID_COMMAND, argv[3]);
	else
	{
		process_id = fork();
		if (process_id == -1)
			error_type(FORK_ERROR);
		else if (process_id == 0)
		{
			close(fd[1]);
			outfile_fd = open_file(2, argv[4]);
			dup2(outfile_fd, STDOUT_FILENO);
			close(outfile_fd);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			execute_command(argv[3], env);
		}
	}	
}

void	wait_for_child_process(void)
{
	int	process_id;
	int	status;

	process_id = waitpid(0, &status, 0);
	while (process_id != -1)
		process_id = waitpid(0, &status, 0);
}
