/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:50:01 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/18 15:18:15 by roguigna         ###   ########.fr       */
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
	name = ft_strldup(&line[2], j - 3);
	if (!name)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (NULL);
	}
	*len += j - 1;
	return (name);
}

char	*no_bracket_env_name(char *line, int *len, char c)
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
