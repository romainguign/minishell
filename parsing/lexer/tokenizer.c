/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:29:25 by roguigna          #+#    #+#             */
/*   Updated: 2024/05/08 17:03:36 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_newtoken(t_minishell *infos, int *i)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (0);
	token->value = dup_token(&infos->line[*i], i, infos->env, token);
	if (!token->value)
	{
		free (token);
		return (0);
	}
	token->token_type = get_token_type(token->value);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

static int	ft_tokenadd_back(t_token **token, t_token *new)
{
	t_token	*e_last;

	if (!new)
		return (0);
	if (!(*token))
	{
		*token = new;
		return (1);
	}
	e_last = *token;
	while (e_last->next)
		e_last = e_last->next;
	e_last->next = new;
	return (1);
}

int	tokenizer(t_minishell *infos)
{
	int		i;
	int		len_line;

	i = 0;
	len_line = ft_strlen(infos->line);
	while (i < len_line)
	{
		if (infos->line[i] != ' ' && (infos->line[i] >= 13
				|| infos->line[i] <= 9))
		{
			if (!ft_tokenadd_back(&infos->token,
					ft_newtoken(infos, &i)))
			{
				ft_tokenclear(&infos->token, free);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
