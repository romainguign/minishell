/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:46:29 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/18 15:22:56 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_prompted_path(char *new_path, int len_home, char *path)
{
	int	i;

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

int	ft_pwd(char **cmd)
{
	char	*path;

	path = NULL;
	if (!ft_strcmp(cmd[0], "pwd"))
	{
		path = getcwd(path, 0);
		if (errno == ENOENT)
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

static char	*home_path(char *home, char *path)
{
	char	*new_path;
	int		len_home;

	len_home = ft_strlen(home);
	if (len_home < ft_strlen(path))
	{
		new_path = ft_calloc(ft_strlen(path) - len_home + 3, sizeof(char));
		new_path = copy_prompted_path(new_path, len_home, path);
	}
	else
		new_path = ft_strjoinfree(path, "$ Minishell > ");
	if (!new_path)
	{
		free(path);
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	return (new_path);
}

static char	*get_cwd_fail(void)
{
	char	*path;

	if (errno == ENOENT)
	{
		perror("minishell");
		path = ft_strdup("$ Minishell >");
		if (!path)
			return (0);
		return (path);
	}
	ft_putstr_fd(MALLOC_ERROR, 2);
	return (0);
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
	if (!path)
		return (get_cwd_fail());
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
