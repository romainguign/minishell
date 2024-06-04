/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:47:54 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/04 13:28:56 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_token_type(char *value)
{
	if (!ft_strcmp("<<", value))
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

static void	unexpected_token(char *line, t_minishell *infos)
{
	int	i;

	i = 1;
	if (line[0] != line[1])
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		while (line[i] && (line[i] == '<' || line[i] == '|' || line[i] == '>'))
			i++;
		write(2, &line[1], i - 1);
		write(2, "'\n", 2);
	}
	else
	{
		i++;
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		while (line[i] && (line[i] == '<' || line[i] == '|' || line[i] == '>'))
			i++;
		write(2, &line[2], i - 2);
		write(2, "'\n", 2);
	}
	infos->exit_code = 2;
}

char	*parse_redirect(char *line, int	*i, t_minishell *infos)
{
	char	*word;

	word = ft_calloc(3, sizeof(char));
	if (!word)
		return (0);
	if ((line[1] != '>') && (line[1] != '<') && (line[1] != '|'))
		word[0] = line[0];
	else if (line[0] != '|' && line[1] == line[0] && line[2] != '|'
		&& line[2] != '>' && line[2] != '<')
	{
		word[0] = line[0];
		word[1] = line[1];
		(*i)++;
	}
	else
	{
		free (word);
		unexpected_token(line, infos);
		infos->exit_code = 2;
		return (0);
	}
	return (word);
}
