/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:52:58 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

int	env_controller(t_command *command)
{
	if (command->args[1])
	{
		*exit_status() = 127;
		printf("env: %s: No such file or directory\n", command->args[1]);
		return (0);
	}
	return (1);
}

void	env(t_env *env, t_command *command)
{
	*exit_status() = 0;
	if (!env)
		return ;
	if (!env_controller(command))
		return ;
	while (env && env->key)
	{
		if (env->key && env->content == NULL)
			env = env->next;
		else if (env->key && env->content)
		{
			ft_putstr_fd(env->key, command->output);
			ft_putstr_fd("=", command->output);
			ft_putendl_fd(env->content, command->output);
			env = env->next;
		}
		else
			env = env->next;
	}
	return ;
}
