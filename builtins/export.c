/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:01:22 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/03 10:57:15 by brguicho         ###   ########.fr       */
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

static void	print_error_identifier(char *cmd)
{
	int i;
	
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
			break;
		}
		i++;
	}
}

static char	**sort_env_tab(t_env *env)
{
	char **env_tab;
	int i;
	char *tmp;
	int j;
	
	env_tab = lst_to_tab_export(env);
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
	int i;

	i = 0;
	while (env_tab[i])
	{
		if (env_tab[i][0] == '_' && env_tab[i][1] == '=')
			i++;
		else
			printf("declare -x %s\n", env_tab[i]);
		i++;
	}
}

int	ft_export(t_env *env, char **cmd)
{
	char **env_tab;
	int i;

	i = 1;
	if (ft_tab_len(cmd) == 1)
	{
		env_tab = sort_env_tab(env);
		print_env(env_tab);
		free_tab((void **)env_tab);
		return (0);
	}
	else if (ft_tab_len(cmd) > 1)
	{
		while (cmd[i])
		{
			if (is_input_correct(cmd[i]))
			{
				check_type_and_add(cmd[i], env);
				return (0);
			}
			else
			{
				print_error_identifier(cmd[i]);
				return(1);
			}
			i++;
		}
	}
	return (1);
}