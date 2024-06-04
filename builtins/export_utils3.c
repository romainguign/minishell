/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:01:29 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/04 14:26:22 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_envname_export(char *envp, int *i)
{
	char	*name;
	int		j;

	while (envp[*i] && envp[*i] != '+')
		(*i)++;
	name = ft_calloc(sizeof(char), *i + 1);
	if (!name)
		return (NULL);
	j = 0;
	while (j < *i)
	{
		name[j] = envp[j];
		j++;
	}
	return (name);
}

t_env	*ft_newenv_export(char *envp)
{
	t_env	*env;
	int		i;

	i = 0;
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		ft_envclear(&env, free);
		return (0);
	}
	env->name = dup_envname_export(envp, &i);
	env->value = ft_strdup(&envp[i + 2]);
	if (!env->value || !env->name)
	{
		ft_envclear(&env, free);
		return (0);
	}
	env->next = NULL;
	return (env);
}
