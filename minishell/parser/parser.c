/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:55:48 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:02:01 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

void	fill_command(t_mshell *shell, t_command *command, t_lexer *lexer)
{
	int	index;

	index = 0;
	while (lexer != NULL && command != NULL)
	{
		if (lexer->type == T_WORD)
		{
			expander(shell, lexer);
			unquote_lexer_content(shell, lexer);
			command->args[index] = lexer->content;
			index++;
		}
		if (lexer->type == T_PIPE)
		{
			index = 0;
			command = command->next;
		}
		if (lexer->type != T_WORD && lexer->type != T_PIPE
			&& lexer->next)
			lexer = lexer->next;
		lexer = lexer->next;
	}
}

void	parser(t_mshell *shell)
{
	t_lexer		*lexer;
	t_command	*command;

	lexer = shell->lexer;
	while (lexer != NULL)
	{
		parser_init(shell, &lexer);
		lexer = lexer->next;
	}
	fill_command(shell, shell->command, shell->lexer);
	command = shell->command;
	while (command)
	{
		while (*command->args && command->args[0][0] == 0)
			command->args = &command->args[1];
		command = command->next;
	}
	check_heredoc_status(shell, shell->command, shell->lexer);
}
