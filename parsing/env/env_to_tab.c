/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:43:27 by brguicho          #+#    #+#             */
/*   Updated: 2024/06/18 10:18:14 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_to_tab(t_env *env)
{
	t_env	*tmp;
	char	**tab_env;
	int		i;

	tmp = env;
	i = 0;
	tab_env = ft_calloc(ft_lst_size_env(env) + 1, sizeof(char *));
	if (!tab_env)
		return (NULL);
	while (tmp)
	{
		tab_env[i] = ft_strjoin_env(tmp->name, tmp->value);
		if (!tab_env[i])
		{
			ft_putstr_fd(MALLOC_ERROR, 2);
			ft_free_env(tab_env);
			return (0);
		}
		i++;
		tmp = tmp->next;
	}
	return (tab_env);
}

char	**lst_to_tab_export(t_env *env)
{
	t_env	*tmp;
	char	**tab_env;
	int		i;

	tmp = env;
	i = 0;
	tab_env = ft_calloc(ft_lst_size_env(env) + 1, sizeof(char *));
	if (!tab_env)
		return (NULL);
	while (tmp)
	{
		tab_env[i] = ft_strjoin_export(tmp->name, tmp->value);
		if (!tab_env[i])
		{
			free_tab((void **)tab_env);
			ft_putstr_fd(MALLOC_ERROR, 2);
			return (0);
		}
		i++;
		tmp = tmp->next;
	}
	return (tab_env);
}
