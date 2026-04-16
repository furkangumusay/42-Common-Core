/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:27:43 by fgumusay          #+#    #+#             */
/*   Updated: 2024/07/04 14:16:45 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

void	pb(t_stack *stack)
{
	int	i;

	if (stack->size_a > 0)
	{
		i = stack->size_b;
		while (i > 0)
		{
			stack->b[i] = stack->b[i - 1];
			i--;
		}
		stack->b[0] = stack->a[0];
		i = 0;
		while (i < stack->size_a - 1)
		{
			stack->a[i] = stack->a[i + 1];
			i++;
		}
		stack->size_b++;
		stack->size_a--;
		write(1, "pb\n", 3);
	}
}

void	rb(t_stack *stack)
{
	int	tmp;
	int	i;

	if (stack->size_b > 1)
	{
		tmp = stack->b[0];
		i = -1;
		while (++i < stack->size_b - 1)
			stack->b[i] = stack->b[i + 1];
		stack->b[i] = tmp;
		write(1, "rb\n", 3);
	}
}
