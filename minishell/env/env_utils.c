/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:53:31 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include "../minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_env	*ft_lstnew_env(char *str, char *ptr)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (perror("lstnew_env"), free(str), free(ptr), NULL);
	new->key = str;
	new->content = ptr;
	new->next = NULL;
	return (new);
}
