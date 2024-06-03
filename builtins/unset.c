/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:22:55 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/03 10:50:29 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_key_exist(t_env *env, char *key)
{
	t_env *tmp_env;
	
	tmp_env = env;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->name, key))
			return (1);
		tmp_env = tmp_env->next;
	}
	return (0);
}

static void	erase_env_node(t_env **env, char *key)
{
	t_env *tmp;

	tmp = (*env);
	while (tmp)
	{
		if(tmp->next != NULL)
		{
			if (!ft_strcmp(tmp->next->name, key))
			{
				free(tmp->next->name);
				free(tmp->next->value);
				free(tmp->next);
				tmp->next = tmp->next->next;
			}
		}
		tmp = tmp->next;
	}
}

int	ft_unset(t_env *env, char **cmd)
{
	int i;
	
	i = 1;
	if (!cmd[2])
		return (0);
	else
	{
		i++;
		while (cmd[i])
		{
			if (is_env_key_exist(env, cmd[i]))
			{
				erase_env_node(&env, cmd[i]);
				i++;
			}
			else
				i++;
		}
		return (0);
	}
	return (1);
}