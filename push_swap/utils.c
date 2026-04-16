/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:27:38 by fgumusay          #+#    #+#             */
/*   Updated: 2024/07/05 11:56:55 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

int	ft_ptrsize(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

int	ft_ps_atoi(char *str, t_stack *stack)
{
	int		sign;
	long	res;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str <= 13 && *str >= 9))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (*str == '\0')
		error_exit("Error\n", stack);
	while (*str)
	{
		if (!ft_isdigit(*str))
			error_exit("Error\n", stack);
		res = (res * 10) + (*str - 48);
		str++;
		if (res * sign < -2147483648 || res * sign > 2147483647)
			error_exit("Error\n", stack);
	}
	return (res * sign);
}

void	repeated_num(t_stack *stack)
{
	int	i;
	int	j;

	i = 0;
	while (i < stack->size_a)
	{
		j = i + 1;
		while (j < stack->size_a)
		{
			if (stack->a[i] == stack->a[j] && i != j)
				error_exit("Error\n", stack);
			j++;
		}
		i++;
	}
}

int	is_sorted(int *stack, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (stack[i] > stack[i + 1])
			return (0);
		i++;
	}
	return (1);
}
