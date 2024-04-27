/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:43:27 by brguicho          #+#    #+#             */
/*   Updated: 2024/04/27 17:35:55 by roguigna         ###   ########.fr       */
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
	while (tmp->next)
	{
		tab_env[i] = ft_strjoin_env(tmp->name, tmp->value);
		i++;
		tmp = tmp->next;
	}
	return (tab_env);
}
