/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:48:02 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/10 15:58:59 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_key_exist(t_env *env, char *key)
{
	t_env	*tmp_env;

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
	t_env	*tmp;
	t_env	*prev;
	t_env	*node_to_remove;

	tmp = *env;
	prev = NULL;
	node_to_remove = NULL;
	while (tmp)
	{
		if (tmp->next && !ft_strcmp(tmp->next->name, key))
		{
			node_to_remove = tmp->next;
			tmp->next = tmp->next->next;
			free(node_to_remove->name);
			free(node_to_remove->value);
			free(node_to_remove);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	if (*env && !ft_strcmp((*env)->name, key))
	{
		node_to_remove = *env;
		*env = (*env)->next;
		free(node_to_remove->name);
		free(node_to_remove->value);
		free(node_to_remove);
	}
}

int	ft_unset(t_env **env, char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[1])
		return (0);
	while (cmd[i])
	{
		if (is_env_key_exist(*env, cmd[i]))
			erase_env_node(env, cmd[i]);
		i++;
	}
	return (0);
}
