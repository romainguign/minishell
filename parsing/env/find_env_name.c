/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:50:01 by roguigna          #+#    #+#             */
/*   Updated: 2024/07/01 10:24:53 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cpy_value(char *value)
{
	char	*word;

	if (!value)
		return (NULL);
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
	if (!name && quote != '\'' && quote != '"' && j == 1
		&& line[1] != '"' && line[1] != '\'')
		name = ft_strdup("$");
	if ((!name && j == 1 && (is_space(line[j])
				|| (line[j] == quote && (quote == '"' || quote == '\''))))
		|| (!is_env_syntax(line[1]) && !name && quote == '"'))
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

void	find_env_w_name(t_env **tmp, char *name)
{
	while ((*tmp))
	{
		if (!ft_strcmp(name, (*tmp)->name))
			break ;
		(*tmp) = (*tmp)->next;
	}
	free(name);
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
		return (error_code_ascii(i, infos));
	}
	if (name[0] == '$')
		return (name);
	tmp = infos->env;
	find_env_w_name(&tmp, name);
	if (!tmp)
		return (0);
	return (cpy_value(tmp->value));
}
