/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 06:55:18 by fgumusay          #+#    #+#             */
/*   Updated: 2024/08/27 11:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/stat.h>
#include <unistd.h>

int	is_directory(const char *path)
{
	struct stat	stats;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
		return (FALSE);
	return (TRUE);
}

int	path_exists(const char *path)
{
	if (access(path, F_OK) == 0)
		return (TRUE);
	return (FALSE);
}

int	can_execute(const char *path)
{
	if (access(path, X_OK) == 0)
		return (TRUE);
	return (FALSE);
}

int	check_path(char *path)
{
	if (path_exists(path) == FALSE)
	{
		print_error(path, 1);
		return (FALSE);
	}
	if (is_directory(path) == FALSE)
	{
		print_error(path, 2);
		return (FALSE);
	}
	if (can_execute(path) == FALSE)
	{
		print_error(path, 3);
		return (FALSE);
	}
	return (TRUE);
}
