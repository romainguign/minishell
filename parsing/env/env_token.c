/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:37:37 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/18 17:04:32 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	insert_new_token_list(t_minishell *infos, t_token *tmp,
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
	return (1);
}
