/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:50:01 by roguigna          #+#    #+#             */
/*   Updated: 2024/06/10 18:50:15 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*error_code(int *len, t_minishell *infos)
{
	char	*name;

	name = NULL;
	name = ft_itoa(infos->exit_code);
	*len += 1;
	if (!name)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	return (name);
}

static char	*cpy_value(char *value)
{
	char	*word;

	word = ft_strdup(value);
	if (!word)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	return (word);
}

char	*bracket_env_name(char *line, int *len)
{
	int		j;
	char	*name;

	j = 2;
	while (line[j] != '}')
	{
		if (j == '\0')
		{
			ft_putstr_fd(BRACKET_ERROR, 2);
			return (NULL);
		}
		j++;
	}
	name = ft_strldup(&line[2], j - 2);
	if (!name)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (NULL);
	}
	*len += j;
	return (name);
}

char	*no_bracket_env_name(char *line, int *len, char quote)
{
	int		j;
	char	*name;

	j = 1;
	name = NULL;
	while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
		j++;
	if (line[j] == '?' && j == 1)
		name = ft_strdup("?");
	if (!name && quote != '\'' && quote != '"' && j == 1 && line[1] != '"' && line[1] != '\'')
		name = ft_strdup("$");
	if (!name && j == 1 && (is_space(line[j])
			|| (line[j] == quote && (quote == '"' || quote == '\''))))
		name = ft_strdup("$");
	if (!is_env_syntax(line[1]) && !name && quote == '"')
		name = ft_strdup("$");
	if (!name)
		name = ft_strldup(&line[1], j - 1);
	if (!name)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (NULL);
	}
	*len += j - 1;
	return (name);
}

char	*find_dollar_value(char *line, t_minishell *infos, int *i, char quote)
{
	char	*name;
	t_env	*tmp;

	if (line[1] == '{')
		name = bracket_env_name(line, i);
	else
		name = no_bracket_env_name(line, i, quote);
	if (!name)
		return (0);
	if (name[0] == '?')
	{
		free(name);
		return (error_code(i, infos));
	}
	if (name[0] == '$')
		return (name);
	tmp = infos->env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			break ;
		tmp = tmp->next;
	}
	free(name);
	if (!tmp)
		return (0);
	return (cpy_value(tmp->value));
}
