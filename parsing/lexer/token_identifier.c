/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:47:54 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/10 20:24:32 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_token_type(char *value, t_token *token)
{
	if (token->quote == '"' || token->quote == '\'')
		return (WORD);
	else if (!ft_strcmp("<<", value))
		return (HERE_DOC);
	else if (!ft_strcmp("<", value))
		return (REDIRECT_IN);
	else if (!ft_strcmp(">", value) || !ft_strcmp(">>", value))
		return (REDIRECT_OUT);
	else if (!ft_strcmp("|", value))
		return (PIPE);
	else
		return (WORD);
}

char	*parse_redirect(char *line, int	*i)
{
	char	*word;

	word = ft_calloc(3, sizeof(char));
	if (!word)
		return (0);
	word[0] = line[0];
	if (line[0] == line[1] && (line[1] == '<' || line[1] == '>'))
	{
		word[1] = line[1];
		(*i)++;
	}
	return (word);
}
