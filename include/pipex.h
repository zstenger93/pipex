/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:28:02 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/04 15:28:53 by zstenger         ###   ########.fr       */
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

# define GIVE_PERM_WTH_RW 0644

# define WRONG_INPUT 107
# define PIPE_ERROR 108
# define PROCESS_ERROR 109
# define CHILD_ERROR 110
# define FORK_ERROR 111
# define INVALID_COMMAND 127

void	error_type(int error_id);
void	cmd_error(int error_id, char *command);
int		cmd_validator(char *command, char **env);
void	input_check(char **argv, char **env);

void	pipex(char **argv, char **env);
void	input_process(int *fd, char **argv, char **env);
void	output_process(int *fd, char **argv, char **env);
void	wait_for_child_process(void);

char	*get_env(char **env);
char	*get_path(char *env_path, char *command);
int		path_check(char *cmd_path);
void	execute_command(char *command, char **env);

int		open_file(int fd, char *file);
void	close_and_exit_with_error(int infile_fd, int outfile_fd);
void	free_array(void **array);

#endif