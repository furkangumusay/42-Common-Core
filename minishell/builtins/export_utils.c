/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:53:13 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <unistd.h>

void	if_not_exist(t_mshell *shell, char *key, char *content)
{
	t_env	*env;

	env = ft_lstnew_export_env(key, content);
	if (!env)
		return ;
	ft_lstadd_back_env(&shell->env, env);
}

int	id_validation(char *command)
{
	int	i;

	i = 0;
	if (command[0] == '_' && command[1] == '\0')
		return (FALSE);
	if (ft_isalpha(command[i]) == 0 && command[i] != '_')
		return (print_error2(3, command), *exit_status() = 1, FALSE);
	i++;
	while (command[i] && command[i] != '=')
	{
		if (ft_isalnum(command[i]) == 0 && command[i] != '_'
			&& command[i] != '=')
			return (print_error2(3, command), *exit_status() = 1, FALSE);
		i++;
	}
	return (TRUE);
}

char	*fill_content(t_command *command, int i, int j, int equal)
{
	char	*content;

	if (equal == 1 && !command->args[i][j + 1])
		content = ft_strdup("");
	else if (equal == 1 && command->args[i][j + 1])
		content = ft_substr(command->args[i], j + 1, ft_strlen(command->args[i])
				- j);
	else
		content = NULL;
	return (content);
}

t_env	*ft_lstnew_export_env(char *str, char *ptr)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (0);
	new->key = ft_strdup(str);
	if (ptr)
		new->content = ft_strdup(ptr);
	else
		new->content = NULL;
	new->next = NULL;
	return (new);
}
