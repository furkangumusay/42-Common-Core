/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:54:26 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	create_pipe(t_mshell *shell, int *fd)
{
	if (pipe(fd) == -1)
	{
		print_err_pipe_and_fork(T_PIPE);
		end_malloc(shell);
		exit(EXIT_FAILURE);
	}
}

pid_t	create_fork(t_mshell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_err_pipe_and_fork(T_FORK);
		end_malloc(shell);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
