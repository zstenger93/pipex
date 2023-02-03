/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:28:02 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/03 19:09:23 by zstenger         ###   ########.fr       */
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
# define INVALID_COMMAND 112

void	error_type(int error_id);
void	pipex(char **argv, char **env);
void	input_process(int *fd, char *infile, char *command, char **env);
void	output_process(int *fd, char *command, char *outfile, char **env);
void	wait_for_child_process(void);

char	*get_env(char **env);
char	*get_path(char *env_path, char *command);
int		path_check(char *cmd_path);
void	execute_command(char *command, char **env);

int		open_file(int fd, char *file);
void	input_check(int argc, char **argv, char **env);

#endif