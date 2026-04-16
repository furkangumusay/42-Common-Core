/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:40:47 by fgumusay          #+#    #+#             */
/*   Updated: 2024/07/04 16:41:01 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include <stdlib.h>

void	free_strings(char **str)
{
	size_t	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	error_exit(char *str, t_stack *stack)
{
	if (stack->tmp)
		free_strings(stack->tmp);
	if (stack->a)
		free(stack->a);
	if (stack->b)
		free(stack->b);
	if (stack->num)
		free(stack->num);
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
