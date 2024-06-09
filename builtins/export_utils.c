/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:10:25 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/07 22:05:29 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	is_wrong_identifier2(char c)
{
	if ((c >= '#' && c <= '*') || (c >= ',' && c <= '/')
		|| (c >= ':' && c <= '<') || (c >= '>' && c <= '@')
		|| (c >= '[' && c <= '^') || (c >= '{' && c <= '~'))
		return (1);
	return (0);
}

int	define_type_argument(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '+')
			return (2);
		else if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	check_type_and_add(char *cmd, t_env *env)
{
	char	*key;

	key = ft_strldup(cmd, get_len_key(cmd));
	if (!key)
		return ;
	if (define_type_argument(cmd) == 0)
	{
		if (!is_env_key_exist(env, cmd))
			new_env_element_key(cmd, env);
	}
	else if (define_type_argument(cmd) == 1)
	{
		if (!is_env_key_exist(env, key))
			ft_envadd_back(&env, ft_newenv(cmd));
		else
			update_value(&env, cmd);
	}
	else if (define_type_argument(cmd) == 2)
	{
		if (!is_env_key_exist(env, key))
			ft_envadd_back(&env, ft_newenv_export(cmd));
		else
			join_value(&env, cmd);
	}
	free(key);
}

int	is_input_correct(char *str)
{
	int	i;

	i = 1;
	if (is_wrong_identifier(str[0]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
		{
			if (str[i + 1] != '=')
				return (0);
		}
		if (str[i] == '-')
		{
			if (str[i + 1] == '=')
				return (0);
		}
		if (is_wrong_identifier2(str[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	new_env_element_key(char *cmd, t_env *env)
{
	t_env	*new_element;

	new_element = ft_calloc(1, sizeof(t_env));
	if (!new_element)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		ft_envclear(&env, free);
		return ;
	}
	new_element->name = ft_strdup(cmd);
	new_element->value = NULL;
	if (!new_element->name)
	{
		ft_envclear(&env, free);
		return ;
	}
	new_element->next = NULL;
	ft_envadd_back(&env, new_element);
}
