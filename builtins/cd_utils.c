/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:55:51 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/18 16:44:32 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*export_env_pwd(char *pwd, t_minishell *infos, char *path)
{
	char	*path1;
	char	*cmd[3];
	int		i;
	t_env	*new_env;

	path1 = path;
	if (!pwd)
		return (0);
	path = ft_strjoin(pwd, path1);
	cmd[0] = ft_strdup("export");
	cmd[1] = path;
	cmd[2] = NULL;
	ft_export(infos->env, cmd, 1);
	i = 0;
	while (pwd[i])
		i++;
	pwd[i - 1] = '\0';
	new_env = get_env_node(infos->env, pwd);
	free(path);
	free(pwd);
	if (cmd[0])
		free(cmd[0]);
	path = path1;
	return (new_env);
}

int	update_env(t_minishell *infos, char *path)
{
	t_env	*pwd_env;
	t_env	*old_pwd;

	pwd_env = get_env_node(infos->env, "PWD");
	if (!pwd_env)
		pwd_env = export_env_pwd(ft_strdup("PWD="), infos, path);
	old_pwd = get_env_node(infos->env, "OLDPWD");
	if (!old_pwd)
		old_pwd = export_env_pwd(ft_strdup("OLDPWD="), infos, path);
	if (!old_pwd || !pwd_env)
		return (0);
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
