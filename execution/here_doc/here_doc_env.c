/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:46:39 by roguigna          #+#    #+#             */
/*   Updated: 2024/07/01 10:19:05 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_env_var(char quote, char *line, t_minishell *infos)
{
	int		i;
	char	*value;
	char	*new_line;

	i = 0;
	if (quote)
		return (line);
	new_line = ft_calloc(1, sizeof(char));
	if (!new_line)
		return (0);
	while (line[i])
	{
		if (line[i] == '$')
		{
			value = find_dollar_value(&line[i], infos, &i, quote);
			new_line = ft_strjoinfree(new_line, value);
			if (value)
				free(value);
		}
		else
			new_line = strljoin_token(new_line, &line[i], 1);
		i++;
	}
	return (new_line);
}
