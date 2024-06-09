/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:43:19 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/09 14:42:07 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (tmp->next)
	{
		if (tmp->token_type == PIPE && tmp->next->token_type == PIPE)
		{
			ft_tokenerror(tmp->next->token_type, infos);
			ft_tokenclear(&infos->token, free);
			return (0);
		}
		if ((tmp->token_type == REDIRECT_IN
				|| tmp->token_type == REDIRECT_OUT)
			&& tmp->next->token_type != WORD)
		{
			ft_tokenerror(tmp->next->token_type, infos);
			ft_tokenclear(&infos->token, free);
			return (0);
		}
		tmp = tmp->next;
	}
	if (tmp->token_type != WORD)
	{
		ft_tokenerror(tmp->token_type, infos);
		ft_tokenclear(&infos->token, free);
		return (0);
	}
	return (1);
}
