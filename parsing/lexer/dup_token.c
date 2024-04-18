/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:22:24 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/18 15:23:12 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_dollar_value(char *line, t_env *env, int *i, char c)
{
	char	*name;
	t_env	*tmp;

	if (line[1] == '{')
		name = bracket_env_name(line, i);
	else
		name = no_bracket_env_name(line, i, c);
	if (!name)
		return (0);
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			break ;
		tmp = tmp->next;
	}
	if (name)
		free(name);
	if (!tmp)
		return (0);
	return (tmp->value);
}

static char	*strljoin_token(char *s1, char *s2, int len)
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

static char	*manage_quote(char *word, char *line, int *i, t_env *env)
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
			dollar_value = find_dollar_value(&line[(*i)], env, i, c);
			word = ft_strjoin(word, dollar_value);
		}
		(*i)++;
	}
	return (word);
}

static char	*manage_dollar_quote(char *word, char *line, int *len, t_env *env)
{
	char	c;
	char	*dollar_value;
	int		i;

	i = 1;
	c = line[0];
	if (line[0] == '$')
	{
		dollar_value = find_dollar_value(line, env, &i, '$');
		word = ft_strjoin(word, dollar_value);
		if (dollar_value)
			free(dollar_value);
		i--;
	}
	else
		word = manage_quote(word, line, &i, env);
	*len += i;
	return (word);
}

char	*dup_token(char *line, int *i, t_env *env)
{
	int		len;
	int		len_str;
	char	*word;

	len = 0;
	len_str = ft_strlen(line);
	word = ft_calloc(1, sizeof(char));
	if (!word)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (NULL);
	}
	while (len < len_str && !is_space(line[len]))
	{
		if (line[len] != '"' && line[len] != '\'' && line[len] != '$')
		{
			word = strljoin_token(word, &line[len], 1);
		}
		else
			word = manage_dollar_quote(word, &line[len], &len, env);
		len++;
	}
	*i = *i + len;
	return (word);
}
