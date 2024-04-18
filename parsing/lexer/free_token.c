/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:53:54 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/18 15:18:39 by roguigna         ###   ########.fr       */
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

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = tmp;
	}
}
