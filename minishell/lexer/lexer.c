/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:54:50 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

static int	skip_quotes(const char *input, int i)
{
	char	quote;

	quote = input[i++];
	while (input[i] && input[i] != quote)
		i++;
	return (i);
}

static int	get_token_length(char *input)
{
	int	i;

	i = 0;
	if ((input[i] == '<' && input[i + 1] == '<') || (input[i] == '>' && input[i
				+ 1] == '>'))
		return (2);
	if (input[i] && (input[i] == '>' || input[i] == '<' || input[i] == '|'))
		return (1);
	while (input[i] && input[i] != '>' && input[i] != '<' && input[i] != '|'
		&& input[i] != ' ')
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			i = skip_quotes(input, i) + 1;
			if (!input[i])
				break ;
		}
		else
			i++;
	}
	return (i);
}

static t_token_type	get_token_type(char *token)
{
	if (ft_strncmp(token, "<<", 2) == 0)
		return (T_HEREDOC);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (T_REDIR_APPEND);
	if (ft_strncmp(token, "<", 1) == 0)
		return (T_REDIR_IN);
	if (ft_strncmp(token, ">", 1) == 0)
		return (T_REDIR_OUT);
	if (ft_strcmp(token, "|") == 0)
		return (T_PIPE);
	return (T_WORD);
}

static void	extract_tokens(char *input, t_mshell *shell)
{
	int				len;
	char			*content;
	t_token_type	type;
	char			*next_input_tmp;

	while (input && *input)
	{
		len = get_token_length(input);
		if (len == 0)
			break ;
		content = ft_substr(input, 0, len);
		if (my_malloc(shell->block, content))
			return (end_malloc(shell), exit(EXIT_FAILURE));
		type = get_token_type(content);
		ft_lstadd_back_lexer(&shell->lexer, ft_lstnew_lexer(shell, content,
				type));
		next_input_tmp = ft_strtrim(input + len, " ");
		if (my_malloc(shell->block, next_input_tmp))
			return (perror("next_input_tmp"), end_malloc(shell),
				exit(EXIT_FAILURE));
		input = next_input_tmp;
	}
}

void	tokenize_input(t_mshell *shell)
{
	char	*input_tmp;

	input_tmp = ft_strtrim(shell->input, " ");
	if (my_malloc(shell->block, input_tmp))
		return (perror("input_tmp"), end_malloc(shell), exit(EXIT_FAILURE));
	extract_tokens(input_tmp, shell);
}
