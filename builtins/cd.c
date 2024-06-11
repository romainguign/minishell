/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:28:25 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/11 12:54:46 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_home(t_env *env)
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

t_env	*get_env_node(t_env *env, char *node)
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

void	print_cd_errors(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

int	ft_cd(t_minishell *infos, char **cmd, int fork)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (!path)
		return (1);
	if (ft_tab_len(cmd) > 2)
	{
		if (fork == 1)
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		free(path);
		return (1);
	}
	if (!cmd[1])
	{
		if (cd_no_args(infos, fork, path))
			return (1);
	}
	if (cmd[1])
	{
		if (cd_one_args(infos, fork, path))
			return (1);
	}
	return (0);
}
