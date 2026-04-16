/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:55:39 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:02:12 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <./readline/history.h>
#include <./readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static void	manage_exit(t_command *command, int exit_value, int pid, int *fd)
{
	waitpid(pid, &exit_value, 0);
	*exit_status() = WEXITSTATUS(exit_value);
	if (*exit_status() != 0)
	{
		command->control = FALSE;
		close(fd[0]);
	}
	else
	{
		if (command->input != STDIN_FILENO)
			close(command->input);
		command->input = fd[0];
		command->heredoc = TRUE;
	}
}

void	execute_heredoc(t_mshell *shell, char *delimiter, t_command *command)
{
	int		exit_value;
	pid_t	pid;
	int		fd[2];

	exit_value = 0;
	create_pipe(shell, fd);
	pid = create_fork(shell);
	g_signal_status = SIGHEREDOC;
	if (pid == 0)
	{
		close(fd[0]);
		write_to_pipe(shell, delimiter, fd[1]);
		close(fd[1]);
		end_malloc(shell);
		exit(EXIT_SUCCESS);
	}
	else
	{
		g_signal_status = SIGSTRT;
		close(fd[1]);
		manage_exit(command, exit_value, pid, fd);
	}
}

void	check_heredoc_status(t_mshell *shell, t_command *command,
		t_lexer *lexer)
{
	while (lexer != NULL && command != NULL)
	{
		if (lexer->type == T_HEREDOC && lexer->next != NULL)
		{
			if (lexer->next->type == T_WORD)
			{
				lexer = lexer->next;
				execute_heredoc(shell, lexer->content, command);
			}
			else
				command->control = FALSE;
		}
		if (lexer->type == T_HEREDOC && lexer->next == NULL)
		{
			print_error2(1, NULL);
			command->control = FALSE;
		}
		if (lexer->type == T_PIPE)
			command = command->next;
		lexer = lexer->next;
	}
}
