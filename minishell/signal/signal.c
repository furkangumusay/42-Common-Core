/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:55:53 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:01:57 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../libft/libft.h"
#include <signal.h>

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (g_signal_status == SIGHEREDOC)
		{
			ft_putstr_fd("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			exit(1);
		}
		else if (g_signal_status == SIGEXEC)
		{
			ft_putstr_fd("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
		}
		else if (g_signal_status == SIGPROMT)
		{
			ft_putstr_fd("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			*exit_status() = 1;
		}
	}
}

void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
