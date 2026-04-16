/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:53:39 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 12:08:08 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

void	free_env(t_mshell *shell)
{
	t_env	*tmp;

	if (shell->env)
		return ;
	while (shell->env != NULL)
	{
		if (shell->env->content)
			free(shell->env->content);
		free(shell->env->key);
		tmp = shell->env;
		shell->env = shell->env->next;
		free(tmp);
	}
}

static char	*substr_from(const char *str, size_t start)
{
	return (ft_substr(str, start, ft_strlen(str + start)));
}

int	get_env(char **env, t_mshell *shell)
{
	t_get_env_vars	vars;

	while (env && *env)
	{
		vars.equal_value = ft_strchr(*env, '=');
		if (!vars.equal_value)
			return (FALSE);
		vars.char_len = vars.equal_value - *env;
		vars.name = ft_substr(*env, 0, vars.char_len);
		if (!vars.name)
			return (perror("get_env"), FALSE);
		vars.content = substr_from(*(env++), vars.char_len + 1);
		if (ft_strcmp(vars.name, "OLDPWD") == 0)
		{
			free(vars.content);
			vars.content = ft_strdup("");
		}
		if (!vars.content)
			return (perror("get_env"), free(vars.name), FALSE);
		vars.new_env = ft_lstnew_env(vars.name, vars.content);
		if (!vars.new_env)
			return (FALSE);
		ft_lstadd_back_env(&shell->env, vars.new_env);
	}
	return (TRUE);
}

void	change_env(t_mshell *shell, char *key, char *content)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->content);
			if (content)
			{
				tmp->content = ft_strdup(content);
				if (!tmp->content)
					return (perror("change_env"), end_malloc(shell),
						exit(EXIT_FAILURE));
			}
			else
				tmp->content = NULL;
		}
		tmp = tmp->next;
	}
}

void	add_export(t_mshell *shell, char *key, char *content)
{
	t_env	*new_env;

	new_env = ft_lstnew_export_env(key, content);
	ft_lstadd_back_env(&shell->env, new_env);
}
