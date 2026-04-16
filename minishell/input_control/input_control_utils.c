/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_control_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:54:38 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

void	j_0c_null(t_variables *vars, char **line)
{
	vars->j = 0;
	vars->c = '\0';
	(*line)++;
}

void	j_1i_0(t_variables *vars)
{
	vars->j = 1;
	vars->i = 0;
}

int	in_out_check(t_variables *vars, char *line)
{
	if ((vars->c == REDIRECT_OUT && *line == REDIRECT_IN)
		|| (vars->c == REDIRECT_IN && *line == REDIRECT_OUT))
		return (FALSE);
	return (TRUE);
}
