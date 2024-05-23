/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:22:55 by brguicho          #+#    #+#             */
/*   Updated: 2024/05/23 10:35:23 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_env_key_exist(t_env *env, char *key)
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

int	ft_unset(t_env *env, t_token *token)
{
	t_token *tmp_token;

	tmp_token = token;
	if (!tmp_token->next)
		return (0);
	else
	{
		tmp_token = tmp_token->next;
		while (tmp_token)
		{
			if (is_env_key_exist(env, tmp_token->value))
			{
				erase_env_node(&env, tmp_token->value);
				tmp_token = tmp_token->next;
			}
			else
				tmp_token = tmp_token->next;
		}
		return (0);
	}
	return (1);
}