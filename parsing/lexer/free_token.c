/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:53:54 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/08 13:32:39 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_lstdelone(t_token *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->value)
		del(lst->value);
	free (lst);
}

void	ft_tokenclear(t_token **lst, void (*del)(void*))
{
	t_token	*tmp;
	t_token	*curr;
	t_token	*start;

	if (!lst || !(*lst) || !del)
		return ;
	start = *lst;
	curr = start;
	while (curr && curr->next && curr->next != start)
	{
		tmp = curr->next;
		ft_lstdelone(curr, del);
		curr = tmp;
	}
	ft_lstdelone(curr, del);
	*lst = NULL;
}
