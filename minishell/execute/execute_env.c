/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:34:45 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/26 17:36:07 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include "../minishell.h"

char	*env_join(t_mshell *shell, t_env *env)
{
	char	*path;
	char	*tmp;

	if (!env->key || !env->content)
		return (NULL);
	tmp = ft_strjoin(env->key, "=");
	if (my_malloc(shell->block, tmp))
		return (perror("env_join"), end_malloc(shell), exit(EXIT_FAILURE),
			NULL);
	path = ft_strjoin(tmp, env->content);
	if (my_malloc(shell->block, path))
		return (perror("env_join"), end_malloc(shell), exit(EXIT_FAILURE),
			NULL);
	return (path);
}

int	ft_lstsize_env(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**convert_env_to_array(t_mshell *shell)
{
	char	**env;
	int		lst_size;
	t_env	*clone_env;
	int		i;

	i = 0;
	env = NULL;
	clone_env = shell->env;
	lst_size = ft_lstsize_env(clone_env);
	env = malloc(sizeof(char *) * (lst_size + 1));
	if (my_malloc(shell->block, env))
		return (perror("execute_env"), end_malloc(shell), exit(EXIT_FAILURE),
			NULL);
	while ((i < lst_size) && (clone_env != NULL))
	{
		env[i] = env_join(shell, clone_env);
		clone_env = clone_env->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
