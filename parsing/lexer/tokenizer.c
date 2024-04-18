/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:29:25 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/18 15:20:26 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_newtoken(char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (0);
	token->value = value;
	token->token_type = get_token_type(value);
	token->next = NULL;
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
	char	*word;

	i = 0;
	len_line = ft_strlen(infos->line);
	while (i < len_line)
	{
		if (infos->line[i] != ' ' && (infos->line[i] >= 13
				|| infos->line[i] <= 9))
		{
			word = dup_token(&infos->line[i], &i, infos->env);
			if (!word || !ft_tokenadd_back(&infos->token,
					ft_newtoken(word)))
			{
				ft_tokenclear(&infos->token, free);
				return (0);
			}
		}
		i++;
	}
	t_token *tmp = infos->token;
	const char* tokensname[] = {"WORD", "REDIRECT_IN", "REDIRECT_OUT", "PIPE",
	"HERE_DOC" };
	while (tmp)
	{
		printf ("token : %s, ", tmp->value);
		printf ("type : %s\n", tokensname[tmp->token_type]);
		tmp = tmp->next;
	}
	return (1);
}
