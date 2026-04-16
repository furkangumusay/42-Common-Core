/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:53:27 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

static int	is_non_alpha(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (ft_isdigit(str[0]))
	{
		print_error(str, 6);
		return (*exit_status() = 1, 1);
	}
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '_')
			i++;
		else
		{
			print_error(str, 6);
			return (*exit_status() = 1, 1);
		}
	}
	return (0);
}

static void	free_unset_env(t_env *tmp, t_env *prev, t_env **env)
{
	if (prev)
		prev->next = tmp->next;
	else
		*env = tmp->next;
	if (tmp->key)
		free(tmp->key);
	if (tmp->content)
		free(tmp->content);
	if (tmp)
		free(tmp);
}

void	unset(t_env **env, t_command *command)
{
	t_unset_vars	vars;

	vars.i = 0;
	while (command->args[vars.i])
	{
		if (is_non_alpha(command->args[(vars.i)++]))
			continue ;
		vars.tmp = *env;
		vars.prev = NULL;
		while (vars.tmp)
		{
			if (ft_strcmp(vars.tmp->key, command->args[vars.i - 1]) == 0)
			{
				vars.next = vars.tmp->next;
				free_unset_env(vars.tmp, vars.prev, env);
				vars.found = 1;
				vars.tmp = vars.next;
				break ;
			}
			vars.prev = vars.tmp;
			vars.tmp = vars.tmp->next;
		}
	}
}
