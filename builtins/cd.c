/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:28:25 by brguicho          #+#    #+#             */
/*   Updated: 2024/04/22 10:34:09 by brguicho         ###   ########.fr       */
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

static t_env	*get_home_node(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "HOME"))
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

void	ft_cd(t_minishell *infos)
{
	t_env	*tmp_env;
	t_env	*home_env;

	tmp_env = infos->env;
	if (!ft_strcmp(infos->token->value, "cd"))
	{
		if (!infos->token->next)
		{
			if (!check_env_home(infos->env))
			{
				ft_putstr_fd(CD_ENV_HOME_ERROR, 2);
				return ;
			}
			home_env = get_home_node(infos->env);
			if (chdir(home_env->value) != 0)
			{
				print_cd_errors(home_env->value);
				return ;
			}
		}
		else if (chdir(infos->token->next->value) != 0)
			print_cd_errors(infos->token->next->value);
	}
}
