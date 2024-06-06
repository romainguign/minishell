/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:37:37 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/06 16:53:36 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static t_token *new_tkn(char *value)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return (0);
	}
	new_token->token_type =  get_token_type(new_token->value, new_token);
	return (new_token);
}

static int	ft_tokadd_back(t_token **token, t_token *new)
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

static t_token	*add_list_token(char **splited_token)
{
	int	i;
	t_token	*new;

	i = 0;
	new = NULL;
	while (splited_token[i])
	{
		if (!ft_tokadd_back(&new, new_tkn(splited_token[i])))
			return (0);
		i++;
	}
	return (new);
}

static t_token	*new_list_token(t_minishell *infos, char *value)
{
	t_token *new;

	char	**splited_token;
	splited_token = ft_split_token(value, " \t\n");
	if (!splited_token)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		free_all(infos);
		return (0);
	}
	new = add_list_token(splited_token);
	if (!new)
	{
		free_tab((void **)splited_token);
		free_all(infos);
		return (0);
	}
	free_tab((void **)splited_token);
	return (new);
}

int	insert_new_token_list(t_minishell *infos, t_token *tmp, t_token *next, t_token *last)
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
	t_token *tmp;
	t_token *next;
	t_token *last;

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
