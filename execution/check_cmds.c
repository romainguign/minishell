/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:47:40 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/22 10:48:33 by brguicho         ###   ########.fr       */
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

static	void access_error(char *cmd, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(error, 2);
}

static int	search_directory(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static int	access_cmd(char **path, char **cmd, int j)
{
	char	*command_path;
	
	while (path[j])
	{
		command_path = ft_concatenate_dir(path[j], *cmd);
		if (!command_path)
			return (1);
		if (!access(command_path, F_OK))
		{
			free(*cmd);
			*cmd = ft_strdup(command_path);
			free(command_path);
			break ;
		}
		free(command_path);
		j++;
	}
	if (!path[j])
	{
		ft_free_env(path);
		access_error(cmd[0], ": command not found\n");
		exit (127);
	}
	return (0);
}

void	is_dir(char *cmd)
{
	struct stat st;
    
    if (stat(cmd, &st) == 0) 
	{
		if (S_ISDIR(st.st_mode) && search_directory(cmd)) 
		{
            access_error(cmd, ": Is a Directory\n");
			exit (126);
        }
    } 
	else
	{
        perror("stat");
        return ;
	}
}

static int	search_cmd(char **path, char **cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (*cmd[0] == '\0')
		return (0);
	is_dir(cmd[0]);
	if (!access(*cmd, X_OK))
		return (1);
	while (cmd[i])
		i++;
	access_cmd(path, cmd, i);
	if (!access(*cmd, F_OK) && access(*cmd, X_OK) == -1)
	{
		access_error(cmd[0], ": Permission denied\n");
		exit (126);
	}
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
	if (tmp_cmd->cmd[0])
	{
		search_cmd(path, &tmp_cmd->cmd[0]);
		if (!tmp_cmd->cmd[0])
		{
			ft_putstr_fd(MALLOC_ERROR, 2);
			return (0);
		}
	}
	ft_free_env(path);
	return (1);
}
