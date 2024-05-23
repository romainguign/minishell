/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:56:18 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/23 15:33:56 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	accessing(t_token *redir)
{
	if (redir->token_type == REDIRECT_IN)
	{
		if (access(redir->next->value, R_OK) == -1)
		{
			ft_puterrors(redir->next->value);
			exit (1);
		}
	}
	if (redir->token_type == REDIRECT_OUT)
	{
		if (access(redir->next->value, W_OK) == -1)
		{
			ft_puterrors(redir->next->value);
			exit (1);
		}
	}
	return (1);
}

int	check_access(t_token *redir)
{
	t_token	*token;

	token = redir;
	while (token && token->token_type != PIPE)
	{
		if (token->token_type != WORD)
		{
			accessing(token);
			token = token->next;
		}
		token = token->next;
	}
	return (1);
	
}
