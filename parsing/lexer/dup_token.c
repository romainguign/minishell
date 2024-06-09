/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brguicho <brguicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:22:24 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/09 14:40:10 by brguicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strljoin_token(char *s1, char *s2, int len)
{
	int			i;
	int			j;
	char		*str;

	i = 0;
	if (!s1 || !s2)
		return (0);
	str = ft_calloc(sizeof(char), (ft_strlen(s1) + len + 1));
	if (str == 0)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	free(s1);
	j = 0;
	while (j < len)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (str);
}

static char	*manage_quote(char *word, char *line, int *i, t_minishell *infos)
{
	char	*dollar_value;
	char	c;

	c = line[0];
	while (line[*i] && line[*i] != c && (c == '\'' || c == '"'))
	{
		if (line[*i] != '$' || c != '"')
			word = strljoin_token(word, &line[*i], 1);
		if (line[*i] == '$' && c == '"')
		{
			dollar_value = find_dollar_value(&line[(*i)], infos, i, c);
			word = ft_strjoinfree(word, dollar_value);
			free(dollar_value);
		}
		if (word == NULL)
			return (0);
		(*i)++;
	}
	if (line[*i] != c)
	{
		free (word);
		syntax_errors(c, infos);
		return (0);
	}
	return (word);
}

static char	*manage_dollar_quote(char *word, char *line, int *len,
	t_minishell *infos)
{
	char	*dollar_value;
	char	*trimmed;
	int		i;

	i = 1;
	if (line[0] == '$')
	{
		dollar_value = find_dollar_value(line, infos, &i, 0);
		trimmed = ft_strtrim_spaces(dollar_value);
		free(dollar_value);
		word = ft_strjoinfree(word, trimmed);
		free(trimmed);
		if (!word)
			return (0);
		i--;
	}
	else
		word = manage_quote(word, line, &i, infos);
	*len += i;
	return (word);
}

static char	*token_loop(char *line, int *i, t_token *token, t_minishell *infos)
{
	int		len;
	int		len_str;
	char	*word;

	len = 0;
	len_str = ft_strlen(line);
	word = ft_calloc(1, sizeof(char));
	if (!word)
		return (0);
	while (len < len_str && !is_space(line[len]) && (line[len] != '<'
			&& line[len] != '|' && line[len] != '>'))
	{
		if (line[len] != '"' && line[len] != '\'' && (line[len] != '$'
				|| (line[len] == '$' && (line[len + 1] == ' '
						|| !line[len + 1]))))
			word = strljoin_token(word, &line[len], 1);
		else
		{
			word = manage_dollar_quote(word, &line[len], &len, infos);
			token->quote = line[len];
		}
		len++;
	}
	*i += len;
	return (word);
}

char	*dup_token(char *line, int *i, t_minishell *infos, t_token *token)
{
	char	*word;
	int		save_i;

	save_i = *i;
	if (line[0] == '<' || line[0] == '>' || line[0] == '|')
	{
		word = parse_redirect(line, i);
		if (!word)
			return (0);
	}
	else
	{
		word = token_loop(line, i, token, infos);
		if (line[*i - save_i - 1] == '\0' || line[*i - save_i] == '|'
			|| line[*i - save_i] == '>' || line[*i - save_i] == '<')
			(*i)--;
	}
	if (!word)
		return (NULL);
	return (word);
}
