/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:22:55 by brguicho          #+#    #+#             */
/*   Updated: 2024/05/20 15:14:57 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static is_env_key_exist(t_env *env, char *str)
{
	t_env *tmp;
	
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->value, str))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static t_env	*erase_env_node(t_env *env)
{
	
}

t_env	*ft_unset(t_env *env, t_token *token)
{
	t_token *tmp;
	t_env	*new_env;

	tmp = token;
	if (!ft_strcmp(tmp->value, "unset"))
	{
		if (!tmp->next)
			return ;
		else
			tmp = tmp->next;
			while (tmp)
			{
				if (is_env_key_exist(env, tmp->value))
				{
					new_env = erase_env_node(env);
					tmp = tmp->next;
				}
				else
					tmp = tmp->next;
			}
			return;
			//check if token is valuable
			//get env node prev token
			//erase token env
			//return newenv
			
	}
}