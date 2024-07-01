/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:37:37 by roguigna          #+#    #+#             */
/*   Updated: 2024/07/01 13:28:50 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	del_null_token(t_token **token)
{
	t_token	*curr;
	t_token	*prev;

	curr = *token;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(curr->value, "") && prev)
		{
			prev->next = curr->next;
			ft_lstdeltoken(curr, free);
			curr = prev;
		}
		prev = curr;
		if (curr)
			curr = curr->next;
	}
	return (1);
}

static int	insert_new_token_list(t_minishell *infos, t_token *tmp,
							t_token *next, t_token *last)
{
	t_token	*new;

	new = new_list_token(infos, tmp->value);
	if (!new)
		return (0);
	if (infos->token == tmp)
		infos->token = new;
	else
		last->next = new;
	while (new->next)
		new = new->next;
	new->next = next;
	free(tmp->value);
	free(tmp);
	return (1);
}

int	env_tokenizer(t_minishell *infos)
{
	t_token	*tmp;
	t_token	*next;
	t_token	*last;

	tmp = infos->token;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->quote != '"' && tmp->quote != '\'' && no_space(tmp->value))
		{
			if (!insert_new_token_list(infos, tmp, next, last))
				return (0);
		}
		else
			last = tmp;
		tmp = next;
	}
	if (!del_null_token(&infos->token))
		return (0);
	return (1);
}
