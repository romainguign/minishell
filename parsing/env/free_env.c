/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:50:45 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/17 17:13:31 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_lstdelone(t_env *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->name)
		del(lst->name);
	if (lst->value)
		del(lst->value);
	free (lst);
}

void	ft_envclear(t_env **lst, void (*del)(void*))
{
	t_env	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = tmp;
	}
}
