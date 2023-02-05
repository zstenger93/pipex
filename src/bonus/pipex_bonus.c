/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 09:54:05 by zstenger          #+#    #+#             */
/*   Updated: 2023/02/05 13:46:28 by zstenger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc < 5)
		error_type(WRONG_INPUT);
	pipex_bonus(argc, argv, env);
	exit(0);
}

void	pipex_bonus(int argc, char **argv, char **env)
{
	int		filedescriptor[2];
	char	*error;
	int		cmd_error;
}

void	child_process_bonus(char **argv, char **env)
{
}
