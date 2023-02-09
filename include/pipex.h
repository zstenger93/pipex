/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:28:02 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/09 15:06:22 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

# define TRUE 0
# define FALSE 1

# define GIVE_PERM_WTH_RW 0644
# define INVALID_COMMAND 127

# define WRONG_INPUT 107
# define PIPE_ERROR 108
# define PROCESS_ERROR 109
# define CHILD_ERROR 110
# define FORK_ERROR 111

//error handling
int		is_cat(char **argv);
void	error_type(int error_id);
int		is_exit_code(char **argv);
void	nothing_to_cat(char **argv);
int		input_check(char **argv, char **env);
int		path_with_bin_check(char **commands);
void	is_argv_valid(int argc, char **argv);
int		no_such_file_or_folder(char *command);
void	cmd_error(int error_id, char *command);
int		cmd_validator(char *command, char **env);
int		check_open_for_failure(char **argv, int pick);
int		is_path_null(char *cmd_path, char **commands);
void	permission_denied(char **argv, char *command, int space, int argc);

//get & check path
char	*get_env(char **env);
int		path_check(char *cmd_path);
char	*get_path(char *env_path, char *command);

//mandatory core part
int		open_file(int fd, char *file);
void	pipex(char **argv, char **env);
void	execute_command(char *command, char **env);
void	closefd_and_wait_for_child_process(int *filedescriptor);
void	input_process(int *filedescriptor, char **argv, char **env);
void	output_process(int *filedescriptor, char **argv, char **env, int e_id);

//utils
void	free_array(void **array);
void	free_25(char *path, char **paths);

//bonus extra error handling
void	too_few_arg(int argc);
int		check_for_script(char *command);
int		script_check_end(char *command, int i);
void	invalid_arg_heredoc(int argc, char **argv);

//bonus core part
void	here_doc(char *limiter);
void	close_dup_wait(int *filedescriptor);
void	child_process(char *argv, char **env);
void	pipex_bonus(int argc, char **argv, char **env);
void	here_doc_here(int argc, char **argv, int cmd_i);
void	final_cmd(char *command, char **env, int filedescriptor);

#endif