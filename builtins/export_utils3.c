/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:01:29 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/11 10:20:12 by brguicho         ###   ########.fr       */
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

int	export_with_args(t_env *env, char **cmd, int fork)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	while (cmd[i])
	{
		if (is_input_correct(cmd[i]))
			check_type_and_add(cmd[i], env);
		else
		{
			exit_code = 1;
			if (fork == 0)
				print_error_identifier(cmd[i]);
		}
		i++;
	}
	return (exit_code);
}
