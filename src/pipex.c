/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:31:20 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/03 18:25:37 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
		error_type(WRONG_INPUT);
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

	if ((process_id = fork()) == -1)
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

	if ((process_id = fork()) == -1)
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

/*
open R only, if doesnt exist open it with read and write permissions
open WR only, created if doesnt exist and new data should be appended to the
end of file open WR only, created if doesnt exist and its content should be
removed if open return -1 print the error specified in errno
*/
int	open_file(int fd, char *file)
{
	int	file_fd;

	file_fd = -2;
	if (fd == 0)
		file_fd = open(file, O_RDONLY, GIVE_PERM_WTH_RW);
	else if (fd == 1)
		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, GIVE_PERM_WTH_RW);
	else if (fd == 2)
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, GIVE_PERM_WTH_RW);
	if (file_fd == -1)
		perror("open failed");
	return (file_fd);
}
