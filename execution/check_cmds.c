/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:47:40 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/11 14:09:00 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exec(char *cmd, t_minishell *infos, char **path)
{
	if (access(cmd, F_OK))
	{
		access_error(cmd, ": No such file or directory\n");
		free_close(infos);
		ft_free_env(path);
		exit(127);
	}
	if (access(cmd, X_OK))
	{
		access_error(cmd, ": Permission denied\n");
		free_close(infos);
		ft_free_env(path);
		exit(126);
	}
	return (1);
}

static int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "pwd"))
		return (0);
	return (1);
}

static int	search_cmd(char **path, char **cmd, t_minishell *infos)
{
	int		i;
	int		file;

	i = 0;
	if (!is_builtin(cmd[0]))
		return (1);
	if (*cmd[0] == '\0')
		return (0);
	if (cmd[0][0] == '.' && cmd[0][1] == '/')
		check_exec(cmd[0], infos, path);
	file = is_dir(cmd[0], 0, infos, path);
	if (!access(*cmd, X_OK) && file == 1)
		return (1);
	access_cmd(path, cmd, i, infos);
	return (1);
}

static char	**path_to_tab(t_env *env)
{
	t_env	*tmp_env;
	char	**path;

	tmp_env = env;
	while (tmp_env && ft_strcmp(tmp_env->name, "PATH"))
		tmp_env = tmp_env->next;
	if (!tmp_env)
	{
		path = ft_calloc(sizeof(char *), 2);
		if (!path)
			return (0);
		path[0] = ft_strdup("");
		if (!path[0])
		{
			free(path);
			return (0);
		}
		return (path);
	}
	path = ft_split(tmp_env->value, ':');
	if (!path)
		return (0);
	return (path);
}

int	check_cmds(t_cmd *cmds, t_env *env, t_minishell *infos)
{
	char	**path;
	t_cmd	*tmp_cmd;

	tmp_cmd = cmds;
	path = path_to_tab(env);
	if (!path)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	if (tmp_cmd->cmd[0])
	{
		search_cmd(path, &tmp_cmd->cmd[0], infos);
		if (!tmp_cmd->cmd[0])
		{
			ft_putstr_fd(MALLOC_ERROR, 2);
			return (0);
		}
	}
	ft_free_env(path);
	return (1);
}
