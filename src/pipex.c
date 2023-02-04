/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:31:20 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/04 09:01:13 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **env)
{
	input_check(argc, argv, env);
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
	int	filedescriptor[2];

	if (pipe(filedescriptor) == -1)
		error_type(PIPE_ERROR);
	input_process(filedescriptor, argv[1], argv[2], env);
	output_process(filedescriptor, argv[3], argv[4], env);
	close(filedescriptor[0]);
	close(filedescriptor[1]);
	wait_for_child_process();
}

/*
fork(), if it fails return the error and exit

*/
void	input_process(int *fd, char *infile, char *command, char **env)
{
	int		infile_fd;
	pid_t	process_id;

	process_id = fork();
	if (process_id == -1)
		error_type(FORK_ERROR);
	if (process_id == 0)
	{
		close(fd[0]);
		infile_fd = open_file(0, infile);
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_command(command, env);
	}
}

void	output_process(int *fd, char *command, char *outfile, char **env)
{
	int		outfile_fd;
	pid_t	process_id;

	process_id = fork();
	if (process_id == -1)
		error_type(FORK_ERROR);
	if (process_id == 0)
	{
		close(fd[1]);
		outfile_fd = open_file(2, outfile);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute_command(command, env);
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
