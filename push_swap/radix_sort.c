/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:28:00 by fgumusay          #+#    #+#             */
/*   Updated: 2024/07/05 13:34:48 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

static int	get_next_min_index(int *stack, int size, int *visited)
{
	int	min_index;
	int	min_value;
	int	i;

	min_index = -1;
	min_value = 0;
	i = 0;
	while (i < size)
	{
		if (!visited[i] && (min_index == -1 || stack[i] < min_value))
		{
			min_index = i;
			min_value = stack[i];
		}
		i++;
	}
	return (min_index);
}

void	index_stack(int *stack, int size, t_stack *s)
{
	int	*visited;
	int	index;
	int	min_index;

	index = 0;
	visited = ft_calloc(size, sizeof(int));
	if (!visited)
		error_exit("Error\n", s);
	min_index = get_next_min_index(stack, size, visited);
	while (min_index != -1)
	{
		stack[min_index] = index++;
		visited[min_index] = 1;
		min_index = get_next_min_index(stack, size, visited);
	}
	free(visited);
}

static int	get_max_bit(t_stack *stack)
{
	int	i;
	int	max_bit;
	int	max;

	max = stack->a[0];
	i = 1;
	while (i < stack->size_a)
	{
		if (stack->a[i] > max)
			max = stack->a[i];
		i++;
	}
	max_bit = 0;
	while ((max >> max_bit) != 0)
		max_bit++;
	return (max_bit);
}

static void	radix_sort_b(t_stack *stack, int i)
{
	int	j;
	int	size;

	size = stack->size_b;
	j = 0;
	while (j < size)
	{
		if (((stack->b[0] >> i) & 1) == 1)
			pa(stack);
		else
			rb(stack);
		j++;
	}
}

void	radix_sort(t_stack *stack)
{
	int	i;
	int	j;
	int	max_bits;
	int	size;

	max_bits = get_max_bit(stack);
	i = -1;
	while (++i < max_bits && is_sorted(stack->a, stack->size_a) == 0)
	{
		size = stack->size_a;
		j = -1;
		while (++j < size && is_sorted(stack->a, stack->size_a) == 0)
		{
			if (((stack->a[0] >> i) & 1) == 1)
				ra(stack);
			else
				pb(stack);
		}
		if (i + 1 < max_bits)
			radix_sort_b(stack, i + 1);
	}
	while (stack->size_b > 0)
		pa(stack);
}
