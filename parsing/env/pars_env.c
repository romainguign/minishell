/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:30:21 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/28 14:51:36 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_envname(char *envp, int *i)
{
	char	*name;
	int		j;

	while (envp[*i] && envp[*i] != '=')
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

t_env	*ft_newenv(char *envp)
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
	env->name = dup_envname(envp, &i);
	env->value = ft_strdup(&envp[i + 1]);
	if (!env->value || !env->name)
	{
		ft_envclear(&env, free);
		return (0);
	}
	env->next = NULL;
	return (env);
}

int	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*e_last;

	if (!new)
		return (0);
	if (!(*env))
	{
		*env = new;
		return (1);
	}
	e_last = *env;
	while (e_last->next)
		e_last = e_last->next;
	e_last->next = new;
	return (1);
}

t_env	*init_env(void)
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
	env->name = NULL;
	env->value = NULL;
	env->next = NULL;
	return (env);
}

int	get_env(char **envp, t_minishell *infos)
{
	int		i;

	i = 0;
	if (!ft_envadd_back(&infos->env, init_env()))
		return (0);
	while (envp[i])
	{
		if (i == 0)
		{
			free(infos->env);
			infos->env = NULL;
		}
		if (!ft_envadd_back(&infos->env, ft_newenv(envp[i])))
			return (0);
		i++;
	}
	return (1);
}
