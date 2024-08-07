/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:01:22 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/28 19:26:22 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wrong_identifier(char c)
{
	if ((c >= '#' && c <= '@') || (c >= '[' && c <= '^')
		|| (c >= '{' && c <= '~'))
		return (1);
	return (0);
}

void	print_error_identifier(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (is_wrong_identifier(cmd[i]))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd("<< ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(" >> ", 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("not a valid identifier", 2);
			ft_putstr_fd("\n", 2);
			break ;
		}
		i++;
	}
}

static char	**sort_env_tab(t_env *env)
{
	char	**env_tab;
	int		i;
	char	*tmp;
	int		j;

	env_tab = lst_to_tab_export(env);
	if (!env_tab)
		return (NULL);
	i = 0;
	while (env_tab[i])
	{
		j = i + 1;
		while (env_tab[j])
		{
			if (ft_strcmp(env_tab[i], env_tab[j]) > 0)
			{
				tmp = env_tab[i];
				env_tab[i] = env_tab[j];
				env_tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env_tab);
}

static void	print_env(char **env_tab)
{
	int	i;

	i = 0;
	while (env_tab[i])
	{
		if (env_tab[i][0] == '_' && env_tab[i][1] == '=')
			i++;
		else
		{
			if (env_tab[i][0] != '\0')
				printf("declare -x %s\n", env_tab[i]);
			i++;
		}
	}
}

int	ft_export(t_env *env, char **cmd, int fork)
{
	char	**env_tab;
	int		exit_code;

	exit_code = 0;
	if (ft_tab_len(cmd) == 1 || (ft_tab_len(cmd) == 2 && cmd[1][0] == '\0'))
	{
		env_tab = sort_env_tab(env);
		if (!env_tab)
			return (1);
		if (fork == 0)
			print_env(env_tab);
		free_tab((void **)env_tab);
		return (0);
	}
	else if (ft_tab_len(cmd) > 1)
		exit_code = export_with_args(env, cmd, fork);
	return (exit_code);
}
