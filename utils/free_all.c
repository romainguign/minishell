/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:41:06 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/07 10:49:00 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(void **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_all(t_minishell *infos)
{
	if (infos->env)
		ft_envclear(&infos->env, free);
	if (infos->token)
		ft_tokenclear(&infos->token, free);
	if (infos->cmd)
		ft_cmdsclear(&infos->cmd, free);
	if (infos->line)
		free(infos->line);
	free(infos);
}
