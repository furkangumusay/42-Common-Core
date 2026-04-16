/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:54:55 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>
#include <./readline/history.h>
#include <./readline/readline.h>
#include <limits.h>
#include <unistd.h>

static int	shell_start(t_mshell *shell)
{
	shell->lexer = NULL;
	shell->command = NULL;
	shell->block = malloc_starter();
	return (TRUE);
}

static void	handle_input(t_mshell *shell)
{
	shell->input = readline(PROMT);
	if (!shell->input)
	{
		ft_putstr_fd("exit\n", 1);
		end_malloc(shell);
		rl_clear_history();
		exit(EXIT_SUCCESS);
	}
	if (my_malloc(shell->block, shell->input))
		return (perror("read_loop"), end_malloc(shell), exit(EXIT_FAILURE));
	if (!ft_isspace(shell->input))
	{
		handle_input(shell);
		return ;
	}
	if (syntax_check(shell->input) == FALSE)
	{
		add_history(shell->input);
		print_error2(1, NULL);
		handle_input(shell);
		return ;
	}
	add_history(shell->input);
}

static void	end_malloc_loop(t_mshell *shell)
{
	ft_lstclear_memory(&shell->block, free);
}

int	shell_cycle(t_mshell *shell)
{
	t_mshell	*shell_clone;

	shell_clone = shell;
	while (1)
	{
		g_signal_status = SIGPROMT;
		handle_input(shell);
		tokenize_input(shell);
		parser(shell);
		execute(shell);
		shell_clone = shell;
		end_malloc_loop(shell_clone);
		if (shell_start(shell) == FALSE)
			return (end_malloc(shell), FALSE);
	}
	return (TRUE);
}
