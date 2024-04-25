/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:53:42 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/25 12:57:19 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_lstdelone(t_cmd *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->tmp_file)
	{
		unlink(lst->tmp_file);
		del(lst->tmp_file);
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
		ft_lstdelone(curr, del);
		curr = tmp;
	}
	ft_lstdelone(curr, del);
	*lst = NULL;
}