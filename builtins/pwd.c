/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:46:29 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/09 15:34:46 by brguicho         ###   ########.fr       */
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
		// si errno == ENOENT alors pas de fail malloc
		// et donc pas arreter minishell
		printf("%s\n", path);
		free(path);
	}
	return (0);
}

static char	*home_path(char *home, char *path)
{
	char	*new_path;
	int		len_home;
	int		i;

	len_home = ft_strlen(home);
	new_path = ft_calloc(ft_strlen(path) - len_home + 3, sizeof(char));
	if (!new_path)
	{
		free(path);
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	i = 1;
	new_path[0] = '~';
	while (path[len_home])
	{
		new_path[i] = path[len_home];
		len_home++;
		i++;
	}
	free(path);
	new_path = ft_strjoinfree(new_path, "$ Minishell > ");
	if (!new_path)
		ft_putstr_fd(MALLOC_ERROR, 2);
	return (new_path);
}

char	*get_pwd(t_env *env)
{
	char	*path;
	t_env	*tmp;

	path = NULL;
	tmp = env;
	while (tmp && strcmp(tmp->name, "HOME"))
		tmp = tmp->next;
	path = getcwd(path, 0);
	if (!tmp)
	{
		path = ft_strjoinfree(path, "$ Minishell > ");
		if (!path)
		{
			ft_putstr_fd(MALLOC_ERROR, 2);
			return (0);
		}
		return (path);
	}
	path = home_path(tmp->value, path);
	if (!path)
		return (0);
	return (path);
}
