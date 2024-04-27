/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:50:01 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/27 16:16:56 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*no_bracket_env_name(char *line, int *len)
{
	int		j;
	char	*name;

	j = 1;
	while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
		j++;
	name = ft_strldup(&line[1], j - 1);
	if (!name)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (NULL);
	}
	*len += j - 1;
	return (name);
}

char	*find_dollar_value(char *line, t_env *env, int *i)
{
	char	*name;
	t_env	*tmp;

	if (line[1] == '{')
		name = bracket_env_name(line, i);
	else
		name = no_bracket_env_name(line, i);
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
