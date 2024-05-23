/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:21:38 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/23 15:11:53 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(char **cmd, t_minishell *infos)
{
	if (!ft_strcmp(cmd[0], "cd"))
		exit(ft_cd(infos, cmd));
	else if (!ft_strcmp(cmd[0], "echo"))
		exit(ft_echo(cmd));
	else if (!ft_strcmp(cmd[0], "env"))
		exit(ft_env(infos->env));
	else if (!ft_strcmp(cmd[0], "exit"))
		exit(ft_exit(cmd));
	else if (!ft_strcmp(cmd[0], "export"))
		exit(ft_export(infos->env, cmd));
	else if (!ft_strcmp(cmd[0], "pwd"))
		exit(ft_pwd(cmd));
	else if (!ft_strcmp(cmd[0], "unset"))
		exit(ft_unset(infos->env, cmd));
	else
		return ;
	exit(EXIT_FAILURE);
}

static int	execute_only_builtin(t_minishell *infos, char **cmd)
{
	// int i = 0;
	// while (cmd[i])
	// {
	// 	printf("cmd : %s\n", cmd[i]);
	// 	i++;
	// }
	// printf("%s %s\n", cmd[0], cmd[1]);
	if (!ft_strcmp(cmd[0], "cd"))
		infos->exit_code = ft_cd(infos, cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		infos->exit_code = ft_exit(cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		infos->exit_code = ft_export(infos->env, cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		infos->exit_code = ft_unset(infos->env, cmd);
	else
		return (1);
	return (0);
}

static char	**builtin_cmd(t_minishell *infos, int len)
{
	t_token	*tmp;
	char	**cmd;
	int		i;

	tmp = infos->token;
	i = 0;
	cmd = ft_calloc(len + 1, sizeof(char *));
	if (!cmd)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	while (tmp)
	{
		cmd[i] = ft_strdup(tmp->value);
		if (!cmd[i])
		{
			ft_putstr_fd(MALLOC_ERROR, 2);
			free_tab((void **)cmd);
			return (0);
		}
		tmp = tmp->next;
		i++;
	}
	return (cmd);
}

int	only_builtin(t_minishell *infos)
{
	t_token	*tmp;
	char	**cmd;
	int		len;

	tmp = infos->token;
	len = 0;
	while (tmp)
	{
		if (tmp->token_type == PIPE)
			return (1);
		tmp = tmp->next;
		len++;
	}
	cmd = builtin_cmd(infos, len);
	if (!cmd)
		return (0);
	if (!execute_only_builtin(infos, cmd))
	{
		free_tab((void **)cmd);
		return (0);
	}
	free_tab((void **)cmd);
	return (1);
}
