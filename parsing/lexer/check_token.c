/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:43:19 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/30 17:01:05 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token(t_minishell *infos)
{
	t_token *tmp;

	tmp = infos->token;
	while (tmp->next)
	{
		if (tmp->token_type == PIPE && tmp->next->token_type == PIPE)
		{
			ft_tokenerror(tmp->next->token_type);
			ft_tokenclear(&infos->token, free);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}