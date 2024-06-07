/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:21:38 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/07 19:48:14 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(char **cmd, t_minishell *infos)
{
	long long int	exit_code;
	
	if (!ft_strcmp(cmd[0], "cd"))
		exit_code = ft_cd(infos, cmd, 0);
	else if (!ft_strcmp(cmd[0], "echo"))
		exit_code = ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		exit_code = ft_env(infos->env);
	else if (!ft_strcmp(cmd[0], "exit"))
		exit_code = ft_exit(cmd, infos, 0);
	else if (!ft_strcmp(cmd[0], "export"))
		exit_code = ft_export(infos->env, cmd, 0);
	else if (!ft_strcmp(cmd[0], "pwd"))
		exit_code = ft_pwd(cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		exit_code = ft_unset(infos->env, cmd);
	else
		return ;
	free_close(infos);
	exit(exit_code);
}

static int	execute_only_builtin(t_minishell *infos, char **cmd)
{
	if (!ft_strcmp(cmd[0], "cd"))
		infos->exit_code = ft_cd(infos, cmd, 1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (ft_exit(cmd, infos, 1));
	else if (!ft_strcmp(cmd[0], "export"))
		infos->exit_code = ft_export(infos->env, cmd, 1);
	else if (!ft_strcmp(cmd[0], "unset"))
		infos->exit_code = ft_unset(infos->env, cmd);
	else
		return (0);
	return (infos->exit_code);
}

long long int	only_builtin(t_minishell *infos)
{
	int	exec;

	if (infos->cmd->next)
		return (0);
	exec = execute_only_builtin(infos, infos->cmd->cmd);
	if (!exec)
		return (0);
	return (exec);
}
