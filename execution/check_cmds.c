/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:47:40 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/08 14:57:15 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_concatenate_dir(char *s1, char *s2)
{
	int			i;
	int			str_len;
	char		*str;

	i = 0;
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	str_len = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = malloc(sizeof(char) * (str_len));
	if (str == 0)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '/';
	str[i + 1] = '\0';
	ft_strlcat(str, s2, str_len);
	return (str);
}

static int	search_cmd(char **path, char **cmd, int command_finded)
{
	char	*command_path;
	int		j;

	j = 0;
	if (*cmd[0] == '\0')
		return (0);
	if (!access(*cmd, X_OK))
		return (1);
	while (path[j])
	{
		command_path = ft_concatenate_dir(path[j], *cmd);
		if (!command_path)
			return (1);
		command_finded = access(command_path, X_OK);
		if (command_finded == 0)
		{
			free(*cmd);
			*cmd = ft_strdup(command_path);
			free(command_path);
			break ;
		}
		free(command_path);
		j++;
	}
	return (command_finded);
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

int	check_cmds(t_cmd *cmds, t_env *env)
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
	while (tmp_cmd)
	{
		if (tmp_cmd->cmd[0])
		{
			search_cmd(path, &tmp_cmd->cmd[0], 0);
			if (!tmp_cmd->cmd[0])
			{
				ft_putstr_fd(MALLOC_ERROR, 2);
				return (0);
			}
		}
		tmp_cmd = tmp_cmd->next;
	}
	ft_free_env(path);
	return (1);
}
