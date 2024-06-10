/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:43:19 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/10 19:49:18 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_token_loop(t_token **tmp, t_minishell *infos)
{
	while ((*tmp)->next)
	{
		if ((*tmp)->token_type == PIPE && (*tmp)->next->token_type == PIPE)
		{
			ft_tokenerror((*tmp)->next->token_type, infos);
			ft_tokenclear(&infos->token, free);
			return (0);
		}
		if (((*tmp)->token_type == REDIRECT_IN
				|| (*tmp)->token_type == REDIRECT_OUT)
			&& (*tmp)->next->token_type != WORD)
		{
			ft_tokenerror((*tmp)->next->token_type, infos);
			ft_tokenclear(&infos->token, free);
			return (0);
		}
		(*tmp) = (*tmp)->next;
	}
	return (1);
}

int	check_token(t_minishell *infos)
{
	t_token	*tmp;

	tmp = infos->token;
	if (tmp->token_type == PIPE)
	{
		ft_tokenerror(tmp->token_type, infos);
		ft_tokenclear(&infos->token, free);
		return (0);
	}
	if (!check_token_loop(&tmp, infos))
		return (0);
	if (tmp->token_type != WORD)
	{
		ft_tokenerror(tmp->token_type, infos);
		ft_tokenclear(&infos->token, free);
		return (0);
	}
	return (1);
}
