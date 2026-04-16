/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:27:30 by fgumusay          #+#    #+#             */
/*   Updated: 2024/07/05 11:58:45 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_stack
{
	int		size_a;
	int		size_b;
	char	**tmp;
	char	*num;
	int		*a;
	int		*b;
}			t_stack;

void		free_strings(char **str);
void		sort_three(t_stack *s);
void		radix_sort(t_stack *stack);
void		repeated_num(t_stack *stack);
void		selection_sort(t_stack *stack);
void		error_exit(char *str, t_stack *stack);
void		index_stack(int *stack, int size, t_stack *s);
int			is_sorted(int *stack, int size);
int			ft_ps_atoi(char *str, t_stack *stack);
int			ft_ptrsize(char **ptr);

void		sa(t_stack *stack);
void		ra(t_stack *stack);
void		rra(t_stack *stack);
void		pa(t_stack *stack);
void		pb(t_stack *stack);
void		rb(t_stack *stack);

#endif
