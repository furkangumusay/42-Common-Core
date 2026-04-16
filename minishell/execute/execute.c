/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:54:21 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	setup_io(t_command *command)
{
	t_command	*tmp;

	tmp = command->next;
	dup2(command->input, STDIN_FILENO);
	if (command->input != STDIN_FILENO)
		close(command->input);
	dup2(command->output, STDOUT_FILENO);
	if (command->output != STDOUT_FILENO)
		close(command->output);
	while (tmp)
	{
		if (tmp->output != STDOUT_FILENO)
			close(tmp->output);
		if (tmp->input != STDIN_FILENO)
			close(tmp->input);
		tmp = tmp->next;
	}
}

void	execve_start(t_mshell *shell, t_command *command)
{
	char	*path;
	int		pid;
	char	**env;

	g_signal_status = SIGEXEC;
	env = convert_env_to_array(shell);
	path = find_path(shell, command);
	if (!path || !env)
		return ;
	pid = create_fork(shell);
	if (pid == 0)
	{
		setup_io(command);
		execve(path, command->args, env);
		end_malloc(shell);
		exit(EXIT_FAILURE);
	}
	else
	{
		command->child_pid = pid;
		g_signal_status = 0;
	}
}

static void	single_executive(t_mshell *shell, t_command *command,
		t_lexer *lexer)
{
	while (lexer && lexer->type != T_PIPE)
	{
		if (command->control != FALSE)
			file_creation(shell, command, &lexer);
		lexer = lexer->next;
	}
	if (lexer && lexer->next && lexer->type == T_PIPE)
		shell->lexer = lexer->next;
	if ((builtin_control(command, command->args[0]) == TRUE)
		&& (command->control != FALSE))
		builtin_start(shell, command, 0);
	else
	{
		if (command->control != FALSE)
			execve_start(shell, command);
	}
}

void	close_pipe(t_command *command)
{
	if (command->input != STDIN_FILENO)
		close(command->input);
	if (command->output != STDOUT_FILENO)
		close(command->output);
}

void	execute(t_mshell *shell)
{
	t_command	*command;
	int			fd[2];

	g_signal_status = SIGSTRT;
	command = shell->command;
	while (command != NULL)
	{
		if (command->next && command->output == STDOUT_FILENO)
		{
			create_pipe(shell, fd);
			if (command->next->input == STDIN_FILENO
				&& command->next->heredoc != TRUE)
				command->next->input = fd[0];
			else
				close(fd[0]);
			command->output = fd[1];
		}
		if (command->prev || command->next)
			multiple_execute(shell, command, shell->lexer);
		else
			single_executive(shell, command, shell->lexer);
		close_pipe(command);
		command = command->next;
	}
	return (child_control(shell));
}
