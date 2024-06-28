/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:53:42 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/28 19:14:14 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cmddelone(t_cmd *lst, void (*del)(void *))
{
	int	i;

	i = 0;
	if (!lst || !del)
		return ;
	if (lst->tmp_file)
	{
		if (access(lst->tmp_file, F_OK | R_OK | W_OK) == 0)
			unlink(lst->tmp_file);
		del(lst->tmp_file);
	}
	while (lst->cmd[i])
	{
		free(lst->cmd[i]);
		i++;
	}
	if (lst->cmd)
		free(lst->cmd);
	free (lst);
}

void	ft_cmdsclear(t_cmd **lst, void (*del)(void*))
{
	t_cmd	*tmp;
	t_cmd	*curr;
	t_cmd	*start;

	if (!lst || !(*lst) || !del)
		return ;
	start = *lst;
	curr = start;
	while (curr)
	{
		tmp = curr->next;
		ft_cmddelone(curr, del);
		curr = tmp;
	}
	ft_cmddelone(curr, del);
	*lst = NULL;
}

static void	ft_cmd_heredoc_delone(t_cmd *lst, void (*del)(void *))
{
	int	i;

	i = 0;
	if (!lst || !del)
		return ;
	while (lst->cmd[i])
	{
		free(lst->cmd[i]);
		i++;
	}
	if (lst->tmp_file)
		free(lst->tmp_file);
	if (lst->cmd)
		free(lst->cmd);
	free (lst);
}

void	ft_cmds_heredoc_clear(t_cmd **lst, void (*del)(void*))
{
	t_cmd	*tmp;
	t_cmd	*curr;
	t_cmd	*start;

	if (!lst || !(*lst) || !del)
		return ;
	start = *lst;
	curr = start;
	while (curr)
	{
		tmp = curr->next;
		ft_cmd_heredoc_delone(curr, del);
		curr = tmp;
	}
	ft_cmddelone(curr, del);
	*lst = NULL;
}
