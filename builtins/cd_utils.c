/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:55:51 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/11 12:56:48 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env(t_minishell *infos, char *path)
{
	t_env	*pwd_env;
	t_env	*old_pwd;

	pwd_env = get_env_node(infos->env, "PWD");
	old_pwd = get_env_node(infos->env, "OLDPWD");
	old_pwd->value = ft_realloc((void *)old_pwd->value, ft_strlen(path));
	old_pwd->value = ft_memcpy(old_pwd->value, path, ft_strlen(path));
	if (path)
		free(path);
	path = NULL;
	path = getcwd(path, 0);
	if (!path)
		return (1);
	pwd_env->value = ft_realloc((void *)pwd_env->value, ft_strlen(path));
	pwd_env->value = ft_memcpy(pwd_env->value, path, ft_strlen(path));
	free(path);
	return (0);
}

int	cd_no_args(t_minishell *infos, int fork, char *path)
{
	t_env	*home_env;

	if (!check_env_home(infos->env))
	{
		if (fork == 1)
			ft_putstr_fd(CD_ENV_HOME_ERROR, 2);
		free(path);
		return (1);
	}
	home_env = get_env_node(infos->env, "HOME");
	if (chdir(home_env->value) != 0)
	{
		if (fork == 1)
			print_cd_errors(home_env->value);
		free(path);
		return (1);
	}
	if (update_env(infos, path))
		return (1);
	return (0);
}

int	cd_one_args(t_minishell *infos, int fork, char *path)
{
	if (chdir(infos->token->next->value) != 0)
	{
		if (fork == 1)
			print_cd_errors(infos->token->next->value);
		free(path);
		return (1);
	}
	if (update_env(infos, path))
		return (1);
	return (0);
}
