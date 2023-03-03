/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:28:02 by zstenger          #+#    #+#             */
/*   Updated: 2023/03/02 10:55:08 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>

# define GIVE_PERM_WTH_RW 0644
# define INVALID_COMMAND 127
# define PROCESS_ERROR 109
# define CHILD_ERROR 110
# define WRONG_INPUT 107
# define PIPE_ERROR 108
# define FORK_ERROR 111
# define FALSE 1
# define TRUE 0

//error handling
int		is_cat(char **argv);
void	too_few_arg(int argc);
void	error_type(int error_id);
int		is_exit_code(char **argv);
void	nothing_to_cat(char **argv);
int		check_for_script(char *command);
void	is_argv_valid(int argc, char **argv);
int		input_check(char **argv, char **env);
int		path_with_bin_check(char **commands);
int		no_such_file_or_folder(char *command);
int		script_check_end(char *command, int i);
void	cmd_error(int error_id, char *command);
int		cmd_validator(char *command, char **env);
int		check_open_for_failure(char **argv, int pick);
int		is_path_null(char *cmd_path, char **commands);
void	invalid_arg_heredoc(int argc, char **argv, char **env);
void	does_the_path_exist(char **argv, char **env, char type);
void	cannot_execute_quit(char **argv, int argc, char *command);
void	can_we_execute(char **argv, int argc, char *command, char **env);
void	permission_denied(char **argv, char *command, int space, int argc);

//get & check path
char	*get_env(char **env);
int		path_check(char *cmd_path);
char	*get_path(char *env_path, char *command);

//mandatory core part
int		open_file(int fd, char *file);
void	pipex(char **argv, char **env);
void	execute_command(char *command, char **env);
void	closefd_and_wait_for_process(int *filedescriptor);
void	input_process(int *filedescriptor, char **argv, char **env);
void	output_process(int *filedescriptor, char **argv, char **env, int e_id);

//utils
void	usage(char part);
void	free_array(char **array);
void	free_25(char *path, char **paths);

//bonus core part
void	here_doc(char *limiter, int argc);
void	close_dup_wait(int *filedescriptor);
void	heredoc_process(char *limiter, int *filedescriptor);
void	pipex_bonus(char **argv, int argc, char *command, char **env);
void	final_cmd(char **argv, int argc, char **env, int filedescriptor);

#endif