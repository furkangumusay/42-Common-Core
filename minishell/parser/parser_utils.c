/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:55:44 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:02:08 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	clear_quotes(char *new_content, char *content,
		char double_quote, char single_quote)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == double_quote)
		{
			while (content[i] && content[++i] != double_quote)
				new_content[j++] = content[i];
			i++;
		}
		else if (content[i] == single_quote)
		{
			while (content[i] && content[++i] != single_quote)
				new_content[j++] = content[i];
			i++;
		}
		else if (content[i] != double_quote && content[i] != single_quote)
			new_content[j++] = content[i++];
		else
			i++;
	}
	new_content[j] = '\0';
}

void	unquote_lexer_content(t_mshell *shell, t_lexer *lexer)
{
	char	*content_trim;

	content_trim = malloc(sizeof(char) * (ft_strlen(lexer->content) + 1));
	if (my_malloc(shell->block, content_trim))
		return (perror("content_trim"), end_malloc(shell), exit(EXIT_FAILURE));
	clear_quotes(content_trim, lexer->content, '\"', '\'');
	lexer->content = content_trim;
}

static void	ft_lstadd_parser(t_command **lst, t_command *new)
{
	t_command	*ptr;

	if (*lst == NULL)
	{
		*lst = new;
		new->prev = NULL;
	}
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
	new->next = NULL;
}

static void	count_args_until_pipe(t_lexer **lexer, int *arg_count)
{
	while ((*lexer)->next != NULL && (*lexer)->type != T_PIPE)
	{
		if ((*lexer)->type == T_WORD)
			*arg_count += 1;
		(*lexer) = (*lexer)->next;
	}
	if ((*lexer) && (*lexer)->type != T_PIPE)
	{
		if ((*lexer)->type == T_WORD)
			*arg_count += 1;
	}
}

void	parser_init(t_mshell *shell, t_lexer **lexer)
{
	t_command	*command;
	int			arg_count;

	arg_count = 0;
	count_args_until_pipe(&(*lexer), &arg_count);
	command = ft_calloc(1, sizeof(t_command));
	if (my_malloc(shell->block, command))
		return (perror("command"), end_malloc(shell), exit(EXIT_FAILURE));
	command->args = ft_calloc(arg_count + 1, sizeof(char *));
	if (my_malloc(shell->block, command->args))
		return (perror("command->args"), end_malloc(shell), exit(EXIT_FAILURE));
	command->input = STDIN_FILENO;
	command->output = STDOUT_FILENO;
	command->control = TRUE;
	command->heredoc = FALSE;
	ft_lstadd_parser(&shell->command, command);
}
