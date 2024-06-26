/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:41:06 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/28 18:02:44 by roguigna         ###   ########.fr       */
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

void	free_all_here_doc(t_minishell *infos)
{
	if (infos->env)
		ft_envclear(&infos->env, free);
	if (infos->token)
		ft_tokenclear(&infos->token, free);
	if (infos->cmd)
		ft_cmds_heredoc_clear(&infos->cmd, free);
	if (infos->line)
		free(infos->line);
	free(infos);
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

void	close_std(void)
{
	close(0);
	close(0);
	close(0);
}

void	free_close(t_minishell *infos)
{
	if (infos->env_tab)
	{
		ft_free_env(infos->env_tab);
		infos->env_tab = NULL;
	}
	close_pipes(infos->pipes);
	close_fds(infos->cmd);
	free_all_here_doc(infos);
}
