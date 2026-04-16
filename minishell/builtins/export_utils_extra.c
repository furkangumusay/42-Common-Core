/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:53:08 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

char	*fill_name(t_command *command, int i, int j, int equal)
{
	char	*name;

	name = ft_substr(command->args[i], 0, j + 1);
	if (equal == 1 && !command->args[i][j + 1] && (!ft_strncmp(name,
				command->args[i], j)) == 0)
		return (free(name), ft_substr(command->args[i], 0, j + 1));
	else
		return (free(name), ft_substr(command->args[i], 0, j));
}

void	swap_nodes(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_content;

	tmp_key = a->key;
	tmp_content = a->content;
	a->key = b->key;
	a->content = b->content;
	b->key = tmp_key;
	b->content = tmp_content;
}

void	sort_env_list(t_env *head)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	if (head == NULL)
		return ;
	swapped = 1;
	lptr = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (ft_strncmp(ptr1->key, ptr1->next->key, ft_strlen(ptr1->key)
					+ 1) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

static void	ft_put(t_env *tmp, t_command *command)
{
	ft_putstr_fd("=\"", command->output);
	ft_putstr_fd(tmp->content, command->output);
	ft_putstr_fd("\"", command->output);
}

void	only_export(t_env *env, t_command *command)
{
	t_env	*tmp;

	tmp = env;
	sort_env_list(tmp);
	while (tmp && tmp->key[0])
	{
		if (!(tmp->key[0] == '_' && tmp->key[1] == '\0'))
		{
			ft_putstr_fd("declare -x ", command->output);
			ft_putstr_fd(tmp->key, command->output);
			if (!tmp->content)
			{
				ft_putstr_fd("\n", command->output);
				tmp = tmp->next;
				continue ;
			}
			if (tmp->content && tmp->content[0] == '\0')
				ft_putstr_fd("=\"\"", command->output);
			if (tmp->content && tmp->content[0] != '\0')
				ft_put(tmp, command);
			ft_putstr_fd("\n", command->output);
		}
		tmp = tmp->next;
	}
}
