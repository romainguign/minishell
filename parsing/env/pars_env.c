/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:30:21 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/12 18:55:00 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **envp)
{
	int		lines;
	char	**env;

	lines = 0;
	while (envp[lines])
		lines++;
	env = ft_calloc(lines + 1, sizeof(char *));
	if (!env)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	lines = 0;
	while (envp[lines])
	{
		env[lines] = ft_strdup(envp[lines]);
		if (!env[lines])
		{
			free_tab((void **)env);
			ft_putstr_fd(MALLOC_ERROR, 2);
			return (0);
		}
		lines++;
	}
	return (env);
}
