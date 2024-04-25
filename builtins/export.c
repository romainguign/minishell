/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:01:22 by brguicho          #+#    #+#             */
/*   Updated: 2024/04/25 13:58:23 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**sort_env_tab(t_env *env)
{
	char **env_tab;
	int i;
	char *tmp;
	int size;
	int j;
	
	env_tab = lst_to_tab(env);
	size = ft_tab_len(env_tab);
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
		printf("declare -x %s\n", env_tab[i]);
		i++;
	}
}

void	ft_export(t_env *env, t_token *token)
{
	char **env_tab;

	if (!ft_strcmp(token->value , "export"))
	{
		env_tab = sort_env_tab(env);
		print_env(env_tab);
	}
}