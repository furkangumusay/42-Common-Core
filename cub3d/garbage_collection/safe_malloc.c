/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:42:45 by ndogan            #+#    #+#             */
/*   Updated: 2025/01/07 22:18:30 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdlib.h>

t_malloc	*get_garbage_c(void)
{
	static t_malloc	garbage_c = {NULL, NULL};

	return (&garbage_c);
}

void	*gc_malloc(unsigned int size)
{
	void		*ptr;
	t_malloc	*garbage_c;

	garbage_c = get_garbage_c();
	while (garbage_c->next)
		garbage_c = garbage_c->next;
	if (garbage_c->next == NULL)
		garbage_c->next = ft_calloc(1, sizeof(t_malloc));
	if (!garbage_c->next)
		safe_exit("Memory allocation failed");
	ptr = ft_calloc(1, size);
	if (!ptr)
		safe_exit("Memory allocation failed");
	*garbage_c->next = (t_malloc){.ptr = ptr, .next = NULL};
	return (ptr);
}

void	safe_free(void *ptr)
{
	if (!ptr)
		return ;
	garbage_collecter(ptr);
	free(ptr);
}

void	safe_exit(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	gc_free();
	exit(0);
}
