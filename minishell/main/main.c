/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:55:00 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

int			g_signal_status = 0;

static int	shell_init(char **env, t_mshell *shell)
{
	g_signal_status = SIGSTRT;
	shell->env = NULL;
	shell->lexer = NULL;
	shell->command = NULL;
	shell->shlvl = 1;
	shell->block = malloc_starter();
	if (get_env(env, shell) == FALSE)
		return (free_env(shell), printf(MALLOC), FALSE);
	return (TRUE);
}

int	main(int ac, char **av, char **env)
{
	t_mshell	shell;

	(void)av;
	if (ac != 1)
		return (printf(ARG), FALSE);
	if (shell_init(env, &shell) == FALSE)
		return (end_malloc(&shell), FALSE);
	init_signals();
	if (shell_cycle(&shell) == FALSE)
		return (end_malloc(&shell), FALSE);
	return (end_malloc(&shell), TRUE);
}
