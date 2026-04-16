/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:53:50 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

void	free_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static char	*find_executable_path(t_mshell *shell, char *cmd, char **path)
{
	char	*sub;
	char	*find_executable_path;
	int		i;

	sub = ft_strjoin("/", cmd);
	if (my_malloc(shell->block, sub))
		return (perror("path"), end_malloc(shell), exit(EXIT_FAILURE), NULL);
	i = 0;
	while (path[i])
	{
		find_executable_path = ft_strjoin(path[i], sub);
		if (my_malloc(shell->block, find_executable_path))
			return (perror("path"), end_malloc(shell), exit(EXIT_FAILURE),
				NULL);
		if ((path_exists(find_executable_path) == TRUE)
			&& (is_directory(find_executable_path) == TRUE))
		{
			if (can_execute(find_executable_path) == TRUE)
				return (find_executable_path);
			else
				return (print_error(cmd, 3), NULL);
		}
		i++;
	}
	return (print_error(cmd, 5), NULL);
}

char	*find_path(t_mshell *shell, t_command *command)
{
	char	*find_path;
	char	**path;
	char	*sub;
	char	**cmd1;
	int		i;

	cmd1 = command->args;
	if (cmd1[0] == (void *)0)
		return (NULL);
	if (*cmd1 && ft_strchr(*cmd1, '/'))
	{
		if (check_path(*cmd1) == TRUE)
			return (*cmd1);
		return (NULL);
	}
	sub = find_env(shell, "PATH");
	path = ft_split(sub, ':');
	if (my_malloc(shell->block, path))
		return (NULL);
	i = -1;
	while (path[++i])
		if (my_malloc(shell->block, path[i]))
			return (NULL);
	find_path = find_executable_path(shell, *cmd1, path);
	return (find_path);
}
