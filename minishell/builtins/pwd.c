/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:53:22 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <limits.h>
#include <unistd.h>

int	arg_order(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	pwd(t_command *command)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != 0)
	{
		ft_putendl_fd(cwd, command->output);
		*exit_status() = 0;
		return ;
	}
	else
	{
		ft_putstr_fd("ERROR\ncwd", STDERR_FILENO);
		*exit_status() = 1;
		return ;
	}
}
