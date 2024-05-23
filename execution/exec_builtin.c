/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:21:38 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/23 11:11:52 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(char **cmd, t_minishell *infos)
{
	if (!ft_strcmp(cmd[0], "cd"))
	{
		exit(ft_cd(infos));
	}
	else if (!ft_strcmp(cmd[0], "echo"))
		exit(ft_echo(cmd));
	else if (!ft_strcmp(cmd[0], "env"))
		exit(ft_env(infos->env));
	else if (!ft_strcmp(cmd[0], "exit"))
		exit(ft_exit(infos->token));
	else if (!ft_strcmp(cmd[0], "export"))
		exit(ft_export(infos->env, infos->token));
	else if (!ft_strcmp(cmd[0], "pwd"))
		exit(ft_pwd(infos));
	else if (!ft_strcmp(cmd[0], "unset"))
		exit(ft_unset(infos->env, infos->token));
	else
		return ;
	exit(EXIT_FAILURE);
}
