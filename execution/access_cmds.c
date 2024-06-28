/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:21:57 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/28 19:50:13 by roguigna         ###   ########.fr       */
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
	if (!s1)
		return (0);
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

void	access_error(char *cmd, char *error)
{
	char	*error_msg;

	if (cmd[0] == '\0')
	{
		error_msg = ft_strjoin("minishell: '", cmd);
		if (!error_msg)
			return ;
		error_msg = ft_strjoinfree(error_msg, "'");
	}
	else
		error_msg = ft_strjoin("minishell: ", cmd);
	if (!error_msg)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return ;
	}
	error_msg = ft_strjoinfree(error_msg, error);
	if (!error_msg)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return ;
	}
	ft_putstr_fd(error_msg, 2);
	free (error_msg);
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

int	is_dir(char *cmd, int i, t_minishell *infos, char **path)
{
	struct stat	st;

	if (stat(cmd, &st) != 0)
		return (1);
	if (S_ISDIR(st.st_mode))
	{
		if (i == 0 && search_directory(cmd))
		{
			access_error(cmd, ": Is a directory\n");
			free_close(infos);
			free_tab((void **)path);
			exit(126);
		}
		else
			return (0);
	}
	return (1);
}

int	access_cmd(char **path, char **cmd, int j, t_minishell *infos)
{
	char	*command_path;

	while (path[j])
	{
		command_path = ft_concatenate_dir(path[j], *cmd);
		if (!command_path)
			return (1);
		if (!access(command_path, F_OK) && is_dir(command_path, 1, infos, path))
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
		access_error(cmd[0], ": command not found\n");
		ft_free_env(path);
		free_close(infos);
		exit (127);
	}
	return (0);
}
