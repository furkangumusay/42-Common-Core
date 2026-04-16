/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:27:51 by fgumusay          #+#    #+#             */
/*   Updated: 2024/07/05 11:58:45 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_stack *s)
{
	if (s->a[0] > s->a[1] && s->a[0] < s->a[2] && s->a[1] < s->a[2])
		sa(s);
	if (s->a[0] > s->a[1] && s->a[0] > s->a[2] && s->a[1] > s->a[2])
	{
		sa(s);
		rra(s);
	}
	if (s->a[0] > s->a[1] && s->a[0] > s->a[2] && s->a[1] < s->a[2])
		ra(s);
	if (s->a[0] < s->a[1] && s->a[0] < s->a[2] && s->a[1] > s->a[2])
	{
		sa(s);
		ra(s);
	}
	if (s->a[0] < s->a[1] && s->a[0] > s->a[2] && s->a[1] > s->a[2])
		rra(s);
}

static	int	find_min_index(int *arr, int size)
{
	int	i;
	int	min;
	int	index;

	i = 0;
	min = arr[0];
	index = 0;
	while (i < size)
	{
		if (arr[i] < min)
		{
			min = arr[i];
			index = i;
		}
		i++;
	}
	return (index);
}

static	void	r_or_rr(t_stack *stack, int min_value, int min_index)
{
	if (min_index >= stack->size_a / 2 + stack->size_a % 2)
		while (stack->a[0] != min_value && is_sorted(stack->a,
				stack->size_a) == 0)
			rra(stack);
	else
		while (stack->a[0] != min_value && is_sorted(stack->a,
				stack->size_a) == 0)
			ra(stack);
}

void	selection_sort(t_stack *stack)
{
	int	i;
	int	min_index;
	int	temp;
	int	size;

	i = 0;
	size = stack->size_a;
	while (i < size && is_sorted(stack->a, stack->size_a) == 0)
	{
		min_index = find_min_index(stack->a, stack->size_a);
		temp = stack->a[min_index];
		if (stack->a[0] != temp && stack->size_a > 1)
			r_or_rr(stack, temp, min_index);
		if (is_sorted(stack->a, stack->size_a) == 0)
			pb(stack);
		i++;
	}
	while (stack->size_b > 0)
		pa(stack);
}
