/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:46:29 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/27 15:14:39 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **cmd)
{
	char	*path;

	path = NULL;
	if (!ft_strcmp(cmd[0], "pwd"))
	{
		path = getcwd(path, 0);
		if (!path && errno == ENOENT)
		{
			print_pwd_errors();
			return (1);
		}
		if (!path)
			return (1);
		printf("%s\n", path);
		free(path);
	}
	return (0);
}

char	*get_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (!path && errno == ENOENT)
	{
		perror("minishell");
		path = ft_strdup("$ Minishell >");
		if (!path)
			return (0);
		return (path);
	}
	if (!path)
		return (0);
	path = ft_strjoinfree(path, "$ Minishell > ");
	if (!path)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	return (path);
}
