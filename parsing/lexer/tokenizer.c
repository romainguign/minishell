/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:29:25 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/15 13:32:30 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dup_token(char *line, int *i)
{
	int		j;
	int		len;
	char	*word;

	len = *i;
	while (line[len] && ((line[len] != ' ') && (line[len] >= 13 
			|| line[len] <= 9)))
		len++;
	word = ft_calloc(len - *i + 2, sizeof(char));
	if (!word)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	j = 0;
	while (line[*i] && *i <= len)
	{
		word[j] =  line[*i];
		j++;
		(*i)++;
	}
	return (word);
}

static t_token	*ft_newtoken(char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (0);
	token->value = value;
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
	int	i;
	char *word;

	i = 0;
	while (infos->line[i])
	{
		if (infos->line[i] != ' ' && (infos->line[i] >= 13 
			|| infos->line[i] <= 9))
			{
				word = dup_token(&infos->line[i], &i);
				if (!word || !ft_tokenadd_back(&infos->token,
					ft_newtoken(word)))
				{
					ft_tokenclear(&infos->token, free);
					return (0);
				}
			}
		if (infos->line[i])
			i++;
		t_token *tmp = infos->token;
		while (tmp)
		{
			printf ("token : '%s', ", tmp->value);
			printf ("type : %u\n", tmp->token_type);
			tmp = tmp->next;
		}
	}
	return (1);
}
