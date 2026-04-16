/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:28:06 by fgumusay          #+#    #+#             */
/*   Updated: 2024/07/05 11:58:45 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include <stdlib.h>

static void	create_stack(char **tmp, t_stack *stack)
{
	int	i;

	i = -1;
	stack->size_a = ft_ptrsize(tmp);
	if (stack->size_a < 1)
		error_exit("Error\n", stack);
	stack->size_b = 0;
	stack->a = (int *)malloc(sizeof(int) * stack->size_a);
	if (!stack->a)
		error_exit("Error\n", stack);
	stack->b = (int *)malloc(sizeof(int) * stack->size_a);
	if (!stack->b)
		error_exit("Error\n", stack);
	while (tmp[++i])
	{
		stack->num = ft_strtrim(tmp[i], " ");
		if (!stack->num)
			error_exit("Error\n", stack);
		stack->a[i] = ft_ps_atoi(stack->num, stack);
		free(stack->num);
	}
	stack->num = NULL;
	repeated_num(stack);
}

static	void	init_data(t_stack *stack)
{
	stack->a = NULL;
	stack->b = NULL;
	stack->tmp = NULL;
	stack->num = NULL;
	stack->size_a = 0;
	stack->size_b = 0;
}

static	void	sort_stack(t_stack *stack, int size)
{
	if (is_sorted(stack->a, stack->size_a) == 0)
	{
		if (size == 2)
			sa(stack);
		else if (size == 3)
			sort_three(stack);
		else if (stack->size_a <= 32)
			selection_sort(stack);
		else
		{
			index_stack(stack->a, stack->size_a, stack);
			radix_sort(stack);
		}
	}
}

int	main(int argc, char *argv[])
{
	t_stack	stack;

	argv++;
	if (argc == 1)
		return (0);
	init_data(&stack);
	if (argc == 2)
	{
		stack.tmp = ft_split(*argv, ' ');
		if (!stack.tmp)
			error_exit("Error\n", &stack);
		create_stack(stack.tmp, &stack);
	}
	else
		create_stack(argv, &stack);
	if (stack.tmp)
		free_strings(stack.tmp);
	sort_stack(&stack, stack.size_a);
	free(stack.a);
	free(stack.b);
}
