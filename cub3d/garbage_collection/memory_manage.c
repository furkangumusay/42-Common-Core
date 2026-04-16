/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:42:12 by ndogan            #+#    #+#             */
/*   Updated: 2025/01/09 16:38:36 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	add_garbage_c(void *ptr)
{
	t_malloc	*garbage_c;

	if (!ptr)
		safe_exit("Memory allocation failed");
	garbage_c = get_garbage_c();
	while (garbage_c->next)
	{
		if (garbage_c->next->ptr == ptr)
			return ;
		garbage_c = garbage_c->next;
	}
	garbage_c->next = ft_calloc(1, sizeof(t_malloc));
	if (!garbage_c->next)
	{
		free(ptr);
		safe_exit("Memory allocation failed");
	}
	*garbage_c->next = (t_malloc){.ptr = ptr, .next = NULL};
}

void	garbage_collecter(void *ptr)
{
	t_malloc	*garbage_c;
	t_malloc	*tmp;

	if (!ptr)
		return ;
	tmp = NULL;
	garbage_c = get_garbage_c();
	while (garbage_c)
	{
		if (garbage_c->ptr == ptr)
		{
			tmp->next = garbage_c->next;
			free(garbage_c);
			return ;
		}
		tmp = garbage_c;
		garbage_c = garbage_c->next;
	}
}

void	gc_free(void)
{
	t_malloc	*tmp;
	t_malloc	*garbage_c;

	tmp = NULL;
	garbage_c = get_garbage_c()->next;
	while (garbage_c)
	{
		tmp = garbage_c;
		garbage_c = garbage_c->next;
		if (tmp->ptr)
		{
			free(tmp->ptr);
			tmp->ptr = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}
