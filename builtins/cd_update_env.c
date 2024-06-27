/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:36:34 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/27 14:42:04 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_cmd_path(char *pwd, char *path, char ***cmd)
{
	*cmd = ft_calloc(sizeof(char *), 3);
	if (!(*cmd))
	{
		free(pwd);
		free(path);
		return (0);
	}
	(*cmd)[0] = ft_strdup("export");
	(*cmd)[1] = ft_strdup(path);
	(*cmd)[2] = NULL;
	if (!((*cmd)[0]) || !((*cmd)[0]))
	{
		if ((*cmd)[0])
			free((*cmd)[0]);
		if ((*cmd)[1])
			free((*cmd)[1]);
		free(*cmd);
		free(pwd);
		free(path);
		return (0);
	}
	return (1);
}

static t_env	*export_env_pwd(char *pwd, t_minishell *infos, char *path)
{
	char	*path1;
	char	**cmd;
	t_env	*new_env;

	if (!pwd)
		return (0);
	path1 = ft_strjoin(pwd, path);
	if (!path1)
		return (0);
	cmd = NULL;
	if (!init_cmd_path(pwd, path1, &cmd))
		return (0);
	ft_export(infos->env, cmd, 1);
	free_tab((void **)cmd);
	new_env = get_env_node(infos->env, pwd);
	free(path1);
	free(pwd);
	return (new_env);
}

static int	check_if_oldpwd_set(t_env **old_pwd, t_minishell *infos, char *path)
{
	char	*pwd;

	pwd = ft_strdup("OLDPWD=");
	if (!pwd)
	{
		free(path);
		return (1);
	}
	*old_pwd = export_env_pwd(pwd, infos, path);
	return (0);
}

static int	check_if_pwd_set(t_env **pwd_env, t_minishell *infos, char *path)
{
	char	*pwd;

	pwd = ft_strdup("PWD=");
	if (!pwd)
	{
		free(path);
		return (1);
	}
	*pwd_env = export_env_pwd(pwd, infos, path);
	return (0);
}

int	update_env(t_minishell *infos, char *path)
{
	t_env	*pwd_env;
	t_env	*old_pwd;

	pwd_env = NULL;
	old_pwd = NULL;
	if (check_if_oldpwd_set(&old_pwd, infos, path))
		return (1);
	if (path)
		free(path);
	path = NULL;
	path = getcwd(path, 0);
	if (errno == ENOENT)
	{
		print_pwd_errors();
		return (1);
	}
	if (!path)
		return (1);
	if (check_if_pwd_set(&pwd_env, infos, path))
		return (1);
	if (path)
		free(path);
	return (0);
}
