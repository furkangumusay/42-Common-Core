/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:54:00 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

void	builtin_start(t_mshell *shell, t_command *command, int flag)
{
	if ((ft_strcmp(command->args[0], "echo") == 0)
		|| (ft_strcmp(command->args[0], "ECHO") == 0))
		echo(command);
	else if ((ft_strcmp(command->args[0], "env") == 0)
		|| (ft_strcmp(command->args[0], "ENV") == 0))
		env(shell->env, command);
	else if ((ft_strcmp(command->args[0], "pwd") == 0)
		|| (ft_strcmp(command->args[0], "PWD") == 0))
		pwd(command);
	else if (ft_strcmp(command->args[0], "cd") == 0)
		cd(command, shell);
	else if (ft_strcmp(command->args[0], "unset") == 0)
		unset(&shell->env, command);
	else if (ft_strcmp(command->args[0], "export") == 0)
		export(shell, command);
	else if (ft_strcmp(command->args[0], "exit") == 0)
		ft_exit(shell, command);
	if (flag == 1)
		end_malloc(shell);
}

int	builtin_control(t_command *cmd, char *command)
{
	if (cmd->control == FALSE)
		return (FALSE);
	if ((ft_strcmp(command, "echo") == 0) || (ft_strcmp(command, "ECHO") == 0))
		return (TRUE);
	else if ((ft_strcmp(command, "pwd") == 0) || (ft_strcmp(command,
				"PWD") == 0))
		return (TRUE);
	else if ((ft_strcmp(command, "env") == 0) || (ft_strcmp(command,
				"ENV") == 0))
		return (TRUE);
	else if (ft_strcmp(command, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(command, "exit") == 0)
		return (TRUE);
	else if (ft_strcmp(command, "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(command, "export") == 0)
		return (TRUE);
	return (FALSE);
}

void	print_err_pipe_and_fork(int flag)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (flag == T_PIPE)
		ft_putstr_fd("pipe error", STDERR_FILENO);
	else
		ft_putstr_fd("fork error", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	perror_write(char *content, char *perror)
{
	if (content)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(content, STDERR_FILENO);
		ft_putstr_fd(":", STDERR_FILENO);
		ft_putstr_fd(perror, STDERR_FILENO);
		*exit_status() = 127;
	}
}
