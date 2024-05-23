/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:28:25 by brguicho          #+#    #+#             */
/*   Updated: 2024/05/23 12:51:55 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_env_home(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "HOME"))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static t_env	*get_env_node(t_env *env, char *node)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, node))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

static void	print_cd_errors(char *str)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

int		ft_cd(t_minishell *infos, char **cmd)
{
	t_env	*tmp_env;
	t_env	*home_env;
	t_env	*pwd_env;
	t_env 	*old_pwd;
	char	*path;

	//erreur too many arg a gerer
	path = NULL;
	path = getcwd(path, 0);
	tmp_env = infos->env;
	if (ft_tab_len(cmd) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return(1);
	}
	if (!cmd[2])
	{
		if (!check_env_home(infos->env))
		{
			ft_putstr_fd(CD_ENV_HOME_ERROR, 2);
			return (1);
		}
		home_env = get_env_node(infos->env, "HOME");
		if (chdir(home_env->value) != 0)
		{
			print_cd_errors(home_env->value);
			return (1);
		}
		pwd_env = get_env_node(infos->env, "PWD");
		old_pwd = get_env_node(infos->env, "OLDPWD");
		old_pwd->value = ft_realloc((void *)old_pwd->value, ft_strlen(path));
		old_pwd->value = ft_memcpy(old_pwd->value, path, ft_strlen(path));
		path = NULL;
		path = getcwd(path, 0);
		pwd_env->value = ft_realloc((void *)pwd_env->value, ft_strlen(path));
		pwd_env->value = ft_memcpy(pwd_env->value, path, ft_strlen(path));
		
	}
	if (cmd[2])
	{
		if (chdir(infos->token->next->value) != 0)
		{
			print_cd_errors(infos->token->next->value);
			return (1);
		}
		pwd_env = get_env_node(infos->env, "PWD");
		old_pwd = get_env_node(infos->env, "OLDPWD");
		old_pwd->value = ft_realloc((void *)old_pwd->value, ft_strlen(path));
		old_pwd->value = ft_memcpy(old_pwd->value, path, ft_strlen(path));
		path = NULL;
		path = getcwd(path, 0);
		pwd_env->value = ft_realloc((void *)pwd_env->value, ft_strlen(path));
		pwd_env->value = ft_memcpy(pwd_env->value, path, ft_strlen(path));
	}
	return (0);
}
